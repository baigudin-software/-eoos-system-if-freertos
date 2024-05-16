/**
 * @file      sys.SemaphoreResource.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017-2024, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_SEMAPHORERESOURCE_HPP_
#define SYS_SEMAPHORERESOURCE_HPP_

#include "sys.NonCopyable.hpp"
#include "api.Semaphore.hpp"

namespace eoos
{
namespace sys
{

/**
 * @class SemaphoreResource
 * @brief SemaphoreResource class.
 * 
 * @tparam A Heap memory allocator class.
 */
template <class A>
class SemaphoreResource : public NonCopyable<A>, public api::Semaphore
{
    typedef NonCopyable<A> Parent;

public:

    /**
     * @enum Type
     * @brief Semaphore type.
     */
    enum Type
    {
        TYPE_COUNTING,        
        TYPE_BINARY
    };

    /**
     * @brief Constructor a semaphore with maximum available permits.
     *
     * @param type    This semaphore type.
     * @param permits The initial number of permits available [unused for Binary semaphore].
     */
    SemaphoreResource(Type type, int32_t permits=0);

    /**
     * @brief Constructor a counting semaphore with user available permits.
     *
     * @param permits The initial number of permits available.
     * @param maximum The maximum number of permits available.
     */
    SemaphoreResource(int32_t permits, int32_t maximum);

    /**
     * @brief Destructor.
     */
    virtual ~SemaphoreResource();

    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    virtual bool_t isConstructed() const;

    /**
     * @copydoc eoos::api::Semaphore::acquire()
     */
    virtual bool_t acquire();

    /**
     * @copydoc eoos::api::Semaphore::release()
     */
    virtual bool_t release();
    
    /**
     * @brief Releases from interrupt service routine.
     *
     * @return True if the semaphore is released successfully.
     */    
    bool_t releaseFromInterrupt();
    
    /**
     * @brief Test if the contex has to be switched.
     *
     * @return True to switch contex.
     */
    bool_t hasToSwitchContex() const;

    /**
     * @brief Returns this semaphore count value.
     *
     * @return Count value.
     */
    int32_t getCount() const;

protected:

    using Parent::setConstructed;

private:

    /**
     * @brief Constructs this object.
     *
     * @return true if object has been constructed successfully.
     */
    bool_t construct();

    /**
     * @brief Initializes kernel semaphore resource.
     * 
     * @return True if initialized sucessfully. 
     */
    bool_t initialize();

    /**
     * @brief Deinitializes kernel semaphore resource.
     */
    void deinitialize();

    /**
     * @brief Max number of permits including the value.
     */    
    static const int32_t MAX_PERMITS = 0x7FFFFFFF;
    
    /**
     * @brief Number of permits available.
     */
    int32_t permits_;

    /**
     * @brief Maximum number of permits.
     */
    int32_t maximum_;

    /**
     * @brief Semaphore FreeRTOS resource.
     */
    ::SemaphoreHandle_t sem_;
    
    /**
     * @brief Semaphore type.
     */
    Type type_;

    /**
     * @brief Mutex FreeRTOS statatic buffer.
     */    
    ::StaticSemaphore_t buffer_;
    
    /**
     * @brief Higher priority task woken flag.
     *
     * The releaseFromInterrupt() function will set
     * the variable to pdTRUE if releaseing the semaphore caused a task
     * to unblock, and the unblocked task has a priority higher than the currently
     * running task.  If the release() function sets this value to pdTRUE then
     * a context switch should be requested before the interrupt is exited by checking
     * the contex switching by the hasToSwitchContex() function.
     */
    ::BaseType_t xHigherPriorityTaskWoken_;

};

template <class A>
SemaphoreResource<A>::SemaphoreResource(Type type, int32_t permits) 
    : NonCopyable<A>()
    , api::Semaphore()
    , permits_( permits )
    , maximum_( MAX_PERMITS )
    , sem_()
    , type_( type )
    , buffer_()
    , xHigherPriorityTaskWoken_( pdFALSE ) {
    bool_t const isConstructed( construct() );
    setConstructed( isConstructed );
}

template <class A>
SemaphoreResource<A>::SemaphoreResource(int32_t permits, int32_t maximum)
    : NonCopyable<A>()
    , api::Semaphore()
    , permits_( permits )
    , maximum_( maximum )    
    , sem_()
    , type_( TYPE_COUNTING )
    , buffer_()
    , xHigherPriorityTaskWoken_( pdFALSE ) {
    bool_t const isConstructed( construct() );
    setConstructed( isConstructed );
}

template <class A>
SemaphoreResource<A>::~SemaphoreResource()
{
    deinitialize();
}

template <class A>
bool_t SemaphoreResource<A>::isConstructed() const ///< SCA MISRA-C++:2008 Justified Rule 10-3-1
{
    return Parent::isConstructed();
}

template <class A>
bool_t SemaphoreResource<A>::acquire()
{
    bool_t res( false );
    if( isConstructed() )
    {
        ::BaseType_t const isTaken( ::xSemaphoreTake(sem_, portMAX_DELAY) );
        res = (isTaken == pdPASS) ? true : false;
    }
    return res;
}

template <class A>
bool_t SemaphoreResource<A>::release()
{
    bool_t res( false );    
    if( isConstructed() )
    {
        ::BaseType_t const isGiven( ::xSemaphoreGive(sem_) );
        res = (isGiven == pdPASS) ? true : false;
    }
    return res;    
}

template <class A>
bool_t SemaphoreResource<A>::releaseFromInterrupt()
{
    bool_t res( false );
    if( isConstructed() )
    {
        xHigherPriorityTaskWoken_ = pdFALSE;
        ::BaseType_t const isGiven( ::xSemaphoreGiveFromISR(sem_, &xHigherPriorityTaskWoken_) );
        res = (isGiven == pdPASS) ? true : false;
    }
    return res;    
}

template <class A>
int32_t SemaphoreResource<A>::getCount() const
{
    ::UBaseType_t const count( ::uxSemaphoreGetCount(sem_) );
    return static_cast<int32_t>( count );
}

template <class A>
bool_t SemaphoreResource<A>::hasToSwitchContex() const
{
    return xHigherPriorityTaskWoken_ != pdFALSE;
}

template <class A>
bool_t SemaphoreResource<A>::construct()
{
    bool_t res( false );
    do {
        if( !isConstructed() )
        {   ///< UT Justified Branch: HW dependency
            break;
        }
        if( permits_ < 0 )
        {
            break;
        }
        if( maximum_ < 0 )
        {
            break;
        }
        if( maximum_ > MAX_PERMITS )
        {
            break;
        }        
        if( !initialize() )
        {
            break;
        }
        res = true;
    } while(false);
    return res;
}

template <class A>
bool_t SemaphoreResource<A>::initialize()
{
    switch( type_ )
    {
        case TYPE_COUNTING:
        {
            ::UBaseType_t const uxMaxCount( static_cast<::UBaseType_t>(maximum_) );
            ::UBaseType_t const uxInitialCount( static_cast<::UBaseType_t>(permits_) );
            sem_ = ::xSemaphoreCreateCountingStatic(uxMaxCount, uxInitialCount, &buffer_);
            break;
        }
        case TYPE_BINARY:
        {
            sem_ = ::xSemaphoreCreateBinaryStatic(&buffer_);
            break;
        }
        default: 
        {
            break;
        }
    }   
    return sem_ != NULL;
}

template <class A>
void SemaphoreResource<A>::deinitialize()
{
    if( sem_ != NULL )
    {
        ::vSemaphoreDelete(sem_);
    }
}
        
} // namespace sys
} // namespace eoos
#endif // SYS_SEMAPHORERESOURCE_HPP_
