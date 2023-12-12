/**
 * @file      sys.SemaphoreManager.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#include "sys.SemaphoreManager.hpp"
#include "lib.UniquePointer.hpp"

namespace eoos
{
namespace sys
{

api::Heap* SemaphoreManager::resource_( NULLPTR );

SemaphoreManager::SemaphoreManager() 
    : NonCopyable<NoAllocator>()
    , api::SemaphoreManager()
    , pool_() {
    bool_t const isConstructed( construct() );
    setConstructed( isConstructed );
}

SemaphoreManager::~SemaphoreManager()
{
    SemaphoreManager::deinitialize();
}

bool_t SemaphoreManager::isConstructed() const
{
    return Parent::isConstructed();
}    

api::Semaphore* SemaphoreManager::create(int32_t permits)
{
    api::Semaphore* ptr( NULLPTR );
    if( isConstructed() )
    {
        lib::UniquePointer<api::Semaphore> res( new Resource(permits) );
        if( !res.isNull() )
        {
            if( !res->isConstructed() )
            {
                res.reset();
            }
        }
        ptr = res.release();
    }    
    return ptr;
}

bool_t SemaphoreManager::construct()
{
    bool_t res( false );
    do 
    {
        if( !isConstructed() )
        {
            break;
        }
        if( !pool_.memory.isConstructed() )
        {
            break;
        }
        if( !SemaphoreManager::initialize(&pool_.memory) )
        {
            break;
        }
        res = true;
    } while(false);
    return res;
}

void* SemaphoreManager::allocate(size_t size)
{
    if( resource_ != NULLPTR )
    {
        return resource_->allocate(size, NULLPTR);
    }
    else
    {
        return NULLPTR;
    }
}

void SemaphoreManager::free(void* ptr)
{
    if( resource_ != NULLPTR )
    {
        resource_->free(ptr);
    }
}

bool_t SemaphoreManager::initialize(api::Heap* resource)
{
    if( resource_ == NULLPTR )
    {
        resource_ = resource;
        return true;
    }
    else
    {
        return false;
    }
}

void SemaphoreManager::deinitialize()
{
    resource_ = NULLPTR;
}

SemaphoreManager::ResourcePool::ResourcePool()
    : mutex_()
    , memory( mutex_ ) {
}

} // namespace sys
} // namespace eoos
