/**
 * @file      sys.MutexResource.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2021-2024, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_MUTEXRESOURCE_HPP_
#define SYS_MUTEXRESOURCE_HPP_

#include "sys.NonCopyable.hpp"
#include "api.Mutex.hpp"

namespace eoos
{
namespace sys
{

/**
 * @class MutexResource.
 * @brief MutexResource class.
 * 
 * @tparam A Heap memory allocator class.
 */
template <class A>
class MutexResource : public NonCopyable<A>, public api::Mutex
{
    typedef NonCopyable<A> Parent;

public:

    /**
     * @brief Constructor.
     */
    MutexResource();

    /**
     * @brief Destructor.
     */
    virtual ~MutexResource();

    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    virtual bool_t isConstructed() const;

    /**
     * @copydoc eoos::api::Mutex::tryLock()
     */
    virtual bool_t tryLock();

    /**
     * @copydoc eoos::api::Mutex::lock()
     */
    virtual bool_t lock();

    /**
     * @copydoc eoos::api::Mutex::unlock()
     */
    virtual bool_t unlock();

protected:

    using Parent::setConstructed;

private:

    /**
     * @brief Constructs this object.
     *
     * @return True if object has been constructed successfully.
     */
    bool_t construct();

    /**
     * @brief Initializes kernel mutex resource.
     * 
     * @return True if initialized sucessfully. 
     */
    bool_t initialize();

    /**
     * @brief Deinitializes kernel mutex resource.
     */
    void deinitialize();

    /**
     * @brief Mutex FreeRTOS resource.
     */
    ::SemaphoreHandle_t mutex_;

    /**
     * @brief Mutex FreeRTOS statatic buffer.
     */    
    ::StaticSemaphore_t buffer_;
    
};

template <class A>
MutexResource<A>::MutexResource()
    : NonCopyable<A>()
    , api::Mutex()
    , mutex_()
    , buffer_() {
    bool_t const isConstructed( construct() );
    setConstructed( isConstructed );
}

template <class A>
MutexResource<A>::~MutexResource()
{
    deinitialize();
}

template <class A>
bool_t MutexResource<A>::isConstructed() const
{
    return Parent::isConstructed();
}

template <class A>
bool_t MutexResource<A>::tryLock()
{
    return false;
}    

template <class A>
bool_t MutexResource<A>::lock()
{
    bool_t res( false );
    if( isConstructed() )
    {
        ::BaseType_t const isTaken( ::xSemaphoreTakeRecursive(mutex_, portMAX_DELAY) );
        res = (isTaken == pdPASS) ? true : false;
    }
    return res;
}

template <class A>
bool_t MutexResource<A>::unlock()
{
    bool_t res( false );
    if( isConstructed() )
    {
        ::BaseType_t const isGiven( ::xSemaphoreGiveRecursive(mutex_) );
        res = (isGiven == pdPASS) ? true : false;
    }
    return res;    
}

template <class A>
bool_t MutexResource<A>::construct()
{
    bool_t res( false );
    do
    {   
        if( !isConstructed() )
        {   ///< UT Justified Branch: HW dependency
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
bool_t MutexResource<A>::initialize()
{
    
    mutex_ = ::xSemaphoreCreateRecursiveMutexStatic( &buffer_ );
    return mutex_ != NULL;
}

template <class A>
void MutexResource<A>::deinitialize()
{
    if( mutex_ != NULL )
    {
        ::vSemaphoreDelete( mutex_ );
    }
}

} // namespace sys
} // namespace eoos
#endif // SYS_MUTEXRESOURCE_HPP_
