/**
 * @file      sys.Semaphore.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017-2023, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_SEMAPHORE_HPP_
#define SYS_SEMAPHORE_HPP_

#include "sys.NonCopyable.hpp"
#include "api.Semaphore.hpp"

namespace eoos
{
namespace sys
{

/**
 * @class Semaphore
 * @brief Semaphore class.
 * 
 * @tparam A Heap memory allocator class.
 */
template <class A>
class Semaphore : public NonCopyable<A>, public api::Semaphore
{
    typedef NonCopyable<A> Parent;

public:

    /**
     * @brief Constructor.
     *
     * @param permits The initial number of permits available.
     */
    explicit Semaphore(int32_t permits);

    /**
     * @brief Destructor.
     */
    virtual ~Semaphore();

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
    static const int32_t MAX_PERMITS = 0x1A;
    
    /**
     * @brief Number of permits available.
     */
    int32_t permits_;

    /**
     * @brief Semaphore FreeRTOS resource.
     */
    ::SemaphoreHandle_t sem_;

    /**
     * @brief Mutex FreeRTOS statatic buffer.
     */    
    ::StaticSemaphore_t buffer_;

};

template <class A>
Semaphore<A>::Semaphore(int32_t permits) 
    : NonCopyable<A>()
    , api::Semaphore()
    , permits_(permits)
    , sem_()
    , buffer_() {
    bool_t const isConstructed( construct() );
    setConstructed( isConstructed );
}

template <class A>
Semaphore<A>::~Semaphore()
{
    deinitialize();
}

template <class A>
bool_t Semaphore<A>::isConstructed() const ///< SCA MISRA-C++:2008 Justified Rule 10-3-1
{
    return Parent::isConstructed();
}

template <class A>
bool_t Semaphore<A>::acquire()
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
bool_t Semaphore<A>::release()
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
bool_t Semaphore<A>::construct()
{
    bool_t res( false );
    do {
        if( !isConstructed() )
        {   ///< UT Justified Branch: HW dependency
            break;
        }
        if( permits_ > MAX_PERMITS )
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
bool_t Semaphore<A>::initialize()
{
    ::UBaseType_t const uxMaxCount( static_cast<::UBaseType_t>(MAX_PERMITS) );
    ::UBaseType_t const uxInitialCount( static_cast<::UBaseType_t>(permits_) );
    sem_ = ::xSemaphoreCreateCountingStatic(uxMaxCount, uxInitialCount, &buffer_);
    return sem_ != NULL;
}

template <class A>
void Semaphore<A>::deinitialize()
{
    if( sem_ != NULL )
    {
        ::vSemaphoreDelete(sem_);
    }
}
        
} // namespace sys
} // namespace eoos
#endif // SYS_SEMAPHORE_HPP_
