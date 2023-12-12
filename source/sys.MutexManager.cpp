/**
 * @file      sys.MutexManager.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#include "sys.MutexManager.hpp"
#include "lib.UniquePointer.hpp"

namespace eoos
{
namespace sys
{

api::Heap* MutexManager::resource_( NULLPTR );

MutexManager::MutexManager() 
    : NonCopyable<NoAllocator>()
    , api::MutexManager()
    , pool_() {
    bool_t const isConstructed( construct() );
    setConstructed( isConstructed );
}

MutexManager::~MutexManager()
{
    MutexManager::deinitialize();    
}

bool_t MutexManager::isConstructed() const
{
    return Parent::isConstructed();
}

api::Mutex* MutexManager::create()
{
    api::Mutex* ptr( NULLPTR );
    if( isConstructed() )
    {
        lib::UniquePointer<api::Mutex> res( new Resource() );
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

bool_t MutexManager::construct()
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
        if( !MutexManager::initialize(&pool_.memory) )
        {
            break;
        }
        res = true;
    } while(false);
    return res;
}

void* MutexManager::allocate(size_t size)
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

void MutexManager::free(void* ptr)
{
    if( resource_ != NULLPTR )
    {
        resource_->free(ptr);
    }
}

bool_t MutexManager::initialize(api::Heap* resource)
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

void MutexManager::deinitialize()
{
    resource_ = NULLPTR;
}

MutexManager::ResourcePool::ResourcePool()
    : mutex_()
    , memory( mutex_ ) {
}

} // namespace sys
} // namespace eoos
