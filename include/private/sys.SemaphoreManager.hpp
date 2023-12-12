/**
 * @file      sys.SemaphoreManager.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_SEMAPHOREMANAGER_HPP_
#define SYS_SEMAPHOREMANAGER_HPP_

#include "sys.NonCopyable.hpp"
#include "api.SemaphoreManager.hpp"
#include "sys.Semaphore.hpp"
#include "sys.Mutex.hpp"
#include "lib.ResourceMemory.hpp"

namespace eoos
{
namespace sys
{

/**
 * @class SemaphoreManager.
 * @brief Semaphore sub-system manager.
 */
class SemaphoreManager : public NonCopyable<NoAllocator>, public api::SemaphoreManager
{
    typedef NonCopyable<NoAllocator> Parent;
    typedef Semaphore<SemaphoreManager> Resource;

public:

    /**
     * @brief Constructor.
     */
    SemaphoreManager();

    /**
     * @brief Destructor.
     */
    virtual ~SemaphoreManager();

    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    virtual bool_t isConstructed() const;

    /**
     * @copydoc eoos::api::SemaphoreManager::create()
     */
    virtual api::Semaphore* create(int32_t permits);
    
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
     * @brief Initializes the allocator with heap for resource allocation.
     *
     * @param resource Heap for resource allocation.
     * @return True if initialized.
     */
    static bool_t initialize(api::Heap* resource);

    /**
     * @brief Initializes the allocator.
     */
    static void deinitialize();
    
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
         * @brief Semaphore memory allocator.
         */     
        lib::ResourceMemory<Resource, EOOS_GLOBAL_SYS_NUMBER_OF_SEMAPHORES> memory;

    };    

    /**
     * @brief Heap for resource allocation.
     */
    static api::Heap* resource_;

    /**
     * @brief Resource memory pool.
     */
    ResourcePool pool_;
    
};

} // namespace sys
} // namespace eoos
#endif // SYS_SEMAPHOREMANAGER_HPP_
