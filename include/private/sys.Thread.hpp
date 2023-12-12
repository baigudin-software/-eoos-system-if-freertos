/**
 * @file      sys.Thread.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2023, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_THREAD_HPP_
#define SYS_THREAD_HPP_

#include "sys.NonCopyable.hpp"
#include "api.Thread.hpp"
#include "api.Task.hpp"

namespace eoos
{
namespace sys
{

/**
 * @class Thread
 * @brief Thread class.
 * 
 * @tparam A Heap memory allocator class.
 */
template <class A>
class Thread : public NonCopyable<A>, public api::Thread
{
    typedef NonCopyable<A> Parent;

public:

    /**
     * @brief Constructor of not constructed object.
     *
     * @param task A task interface whose main method is invoked when this thread is started.
     */
    Thread(api::Task& task);

    /**
     * @brief Destructor.
     */
    virtual ~Thread();

    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    virtual bool_t isConstructed() const;

    /**
     * @copydoc eoos::api::Thread::execute()
     */
    virtual bool_t execute();
    
    /**
     * @copydoc eoos::api::Thread::join()
     */
    virtual bool_t join();

    /**
     * @copydoc eoos::api::Thread::getPriority()
     */
    virtual int32_t getPriority() const;

    /**
     * @copydoc eoos::api::Thread::setPriority(int32_t)
     */
    virtual bool_t setPriority(int32_t priority);

protected:

    using Parent::setConstructed;

private:

    /**
     * @brief Constructor.
     *
     * @return True if object has been constructed successfully.
     */
    bool_t construct();

    /**
     * @brief Starts a thread routine.
     *
     * @param pvParameters Pointer to arguments passed to the thread.
     */
    static void start(void* pvParameters);

    /**
     * @brief Nubmer of stack elements of uint32_t.
     */    
    static const uint32_t THREAD_STACK_DEPTH = EOOS_GLOBAL_SYS_FREERTOS_TASK_STACK_SIZE / 4;
    
    /**
     * @brief User executing runnable interface.
     */
    api::Task* task_;

    /**
     * @brief Current status.
     */
    Status status_;
    
    /**
     * @brief This thread priority.
     */    
    int32_t priority_;    
    
    /**
     * @brief The new thread resource identifier.
     */
    ::TaskHandle_t thread_;
    
    /**
     * @brief FreeRTOS Task Control Block.
     */     
    ::StaticTask_t tcb_;

    /**
     * @brief Stack of this thread aligened 8.
     */ 
    uint64_t stack_[THREAD_STACK_DEPTH / 2];

};

template <class A>
Thread<A>::Thread(api::Task& task) 
    : NonCopyable<A>()
    , api::Thread()
    , task_( &task )
    , status_( STATUS_NEW )
    , priority_( PRIORITY_NORM )
    , thread_( NULL )
    , tcb_() {
    bool_t const isConstructed( construct() );
    setConstructed( isConstructed );
}

template <class A>
Thread<A>::~Thread()
{
    if( thread_ != NULL )
    {
        ::vTaskDelete( thread_ );
        status_ = STATUS_DEAD;            
    }
}

template <class A>
bool_t Thread<A>::isConstructed() const ///< SCA MISRA-C++:2008 Justified Rule 10-3-1
{
    return Parent::isConstructed();
}

template <class A>
bool_t Thread<A>::execute()
{
    bool_t res( false );
    do{
        if( !isConstructed() )
        {
            break;
        }
        if( status_ != STATUS_NEW )
        {
            break;
        }
        ::TaskFunction_t pvTaskCode( start );
        const char* pcName( "EOOS Thread" );
        uint32_t ulStackDepth( THREAD_STACK_DEPTH );
        void* pvParameters( this );
        ::UBaseType_t uxPriority( tskIDLE_PRIORITY + 1 );
        ::StackType_t* puxStackBuffer( reinterpret_cast<::StackType_t*>(stack_) );
        ::StaticTask_t* pxTaskBuffer( &tcb_ );
        thread_ = ::xTaskCreateStatic( 
            pvTaskCode,         // The function that implements the task.
            pcName,             // The text name assigned to the task - for debug only as it is not used by the kernel.
            ulStackDepth,       // The size of the stack to allocate to the task.
            pvParameters,       // The parameter passed to the task - just to check the functionality.
            uxPriority,         // The priority assigned to the task.
            puxStackBuffer,     // The stack buffer
            pxTaskBuffer        // The task control block
        );
        if( thread_ == NULL )
        {
            break;
        }        
        status_ = STATUS_RUNNABLE;
        res = true;
    } while(false);
    return res;        
}

template <class A>
bool_t Thread<A>::join()
{
    bool_t res( false );    
    if( isConstructed() && (status_ == STATUS_RUNNABLE) )
    {
        while(true)
        {
            if(status_ == STATUS_DEAD)
            {
                res = true;
                break;
            }
            taskYIELD();
        }
    }
    return res;
}

template <class A>
int32_t Thread<A>::getPriority() const
{
    return isConstructed() ? priority_ : PRIORITY_WRONG;        
}

template <class A>
bool_t Thread<A>::setPriority(int32_t priority)
{
    bool_t res( false );
    if( isConstructed() )
    {
        if( (PRIORITY_MIN <= priority) && (priority <= PRIORITY_MAX) )
        {
            priority_ = priority;
            res = true;
        }
        else if (priority == PRIORITY_LOCK)
        {
            priority_ = priority;
            res = true;
        }
        else 
        {
            res = false;
        }
    }
    // @todo Implemet setting priority on system level regarding common API rage
    return res;
}

template <class A>
bool_t Thread<A>::construct()
{  
    bool_t res( false );
    do
    {
        if( !isConstructed() )
        {   ///< UT Justified Branch: HW dependency
            break;
        }
        if( task_ == NULLPTR )
        {   ///< UT Justified Branch: SW dependency
            break;
        }
        if( !task_->isConstructed() )
        {
            break;
        }
        status_ = STATUS_NEW;
        res = true;
    } while(false);
    if( res == false )
    {
        status_ = STATUS_DEAD;
    }
    return res;    
}

template <class A>
void Thread<A>::start(void* pvParameters)
{
    Thread* thread( NULLPTR );
    do
    {
        thread = reinterpret_cast<Thread*>(pvParameters);
        if(thread == NULLPTR)
        {   
            break;
        }
        if( !thread->isConstructed() )
        {
            break;
        }                
        if( !thread->task_->isConstructed() )
        {
            break;
        }        
        thread->task_->start();
        thread->status_ = STATUS_DEAD;
    } while(false);
    ::vTaskSuspend(NULL);
    // @note From The FreeRTOS Reference Manual:
    // Tasks are simply C functions that never exit and, 
    // as such, are normally implemented as an infinite loop.
    // Thus, if program is executed here, this means thread is null
    // and a error occurred. Therefore, go to exit the function to
    // the task exit address and terminate FreeRTOS port execution.
}

} // namespace sys
} // namespace eoos
#endif // SYS_THREAD_HPP_
