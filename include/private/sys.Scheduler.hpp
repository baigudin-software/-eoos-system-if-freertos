/**
 * @file      sys.Scheduler.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017-2023, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_SCHEDULER_HPP_
#define SYS_SCHEDULER_HPP_

#include "sys.NonCopyable.hpp"
#include "api.Scheduler.hpp"
#include "api.CpuProcessor.hpp"
#include "sys.Thread.hpp"
#include "sys.SchedulerRoutineTimer.hpp"
#include "sys.SchedulerRoutineSvcall.hpp"
#include "sys.Mutex.hpp"
#include "lib.ResourceMemory.hpp"

namespace eoos
{
namespace sys
{

/**
 * @class Scheduler
 * @brief Thread tasks scheduler class.
 */
class Scheduler : public NonCopyable<NoAllocator>, public api::Scheduler
{
    typedef NonCopyable<NoAllocator> Parent;
    typedef Thread<Scheduler> Resource;

public:

    /**
     * @brief Constructor.
     *
     * @param cpu A target CPU interface.
     */
    Scheduler(api::CpuProcessor& cpu);

    /**
     * @brief Destructor.
     */
    virtual ~Scheduler();

    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    virtual bool_t isConstructed() const;

    /**
     * @copydoc eoos::api::Scheduler::createThread(api::Task&)
     */     
    virtual api::Thread* createThread(api::Task& task);
    
    /**
     * @copydoc eoos::api::Scheduler::sleep(int32_t)
     */
    virtual bool_t sleep(int32_t ms);

    /**
     * @copydoc eoos::api::Scheduler::yield()
     */
    virtual bool_t yield();
    
    /**
     * @brief Allocates memory.
     *
     * @param size Number of bytes to allocate.
     * @return Allocated memory address or a null pointer.
     */
    static void* allocate(size_t size);

    /**
     * @brief Frees allocated memory.
     *
     * @param ptr Address of allocated memory block or a null pointer.
     */
    static void free(void* ptr);  

protected:

    using Parent::setConstructed;    

private:

    /**
     * Constructs this object.
     *
     * @return true if object has been constructed successfully.
     */
    bool_t construct();

    /**
     * @brief Causes current thread to sleep in seconds.
     *
     * @param s A time to sleep in seconds.
     * @return true if no system errors occured.
     */
    static bool_t sSleep(int32_t s);
    
    /**
     * @brief Causes current thread to sleep in milliseconds.
     *
     * @param ms A time to sleep in milliseconds.
     * @return true if no system errors occured.
     */
    static bool_t msSleep(int32_t ms);

    /**
     * @brief Initializes the allocator with heap for resource allocation.
     *
     * @param resource Heap for resource allocation.
     * @return True if initialized.
     */
    bool_t initialize(api::Heap* resource);

    /**
     * @brief Initializes the allocator.
     */
    void deinitialize();
    
    /**
     * @brief Scheduler system tick in microseconds.
     */  
    static const int64_t QUANT_US = 1000;
    
    /**
     * @struct ResourcePool
     * @brief Resource memory pool.
     */
    struct ResourcePool
    {

    public:
        
        /**
         * @brief Constructor.
         */
        ResourcePool();

    private:
            
        /**
         * @brief Mutex resource.
         */    
        Mutex<NoAllocator> mutex_;
        
    public:
        
        /**
         * @brief Resource memory allocator.
         */     
        lib::ResourceMemory<Resource, EOOS_GLOBAL_SYS_NUMBER_OF_THREADS> memory;

    };

    /**
     * @brief Heap for resource allocation.
     */
    static api::Heap* resource_;
    
    /**
     * @brief Timer interrupt service routine.
     */
    SchedulerRoutineTimer isrTim_;

    /**
     * @brief SVC interrupt service routine.
     */
    SchedulerRoutineSvcall isrSvc_;
    
    /**
     * @brief Target CPU interface.
     */
    api::CpuProcessor& cpu_;

    /**
     * @brief Target CPU timer resource.
     */    
    api::CpuTimer* tim_;

    /**
     * @brief Target CPU interrupt resource.
     */    
    api::CpuInterrupt* intTim_;
    
    /**
     * @brief Target CPU interrupt resource.
     */    
    api::CpuInterrupt* intSvc_;

    /**
     * @brief Resource memory pool.
     */
    ResourcePool pool_;

};

} // namespace sys
} // namespace eoos
#endif // SYS_SCHEDULER_HPP_
