/**
 * @file      sys.SchedulerRoutineBase.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017-2023, Sergey Baigudin, Baigudin Software
 */
#include "sys.SchedulerRoutineBase.hpp"

namespace eoos
{
namespace sys
{

SchedulerRoutineBase::SchedulerRoutineBase()
    : NonCopyable<NoAllocator>()
    , api::Task() {
    bool_t const isConstructed( construct() );
    setConstructed( isConstructed );    
}

SchedulerRoutineBase::~SchedulerRoutineBase()
{
}

bool_t SchedulerRoutineBase::isConstructed() const
{
    return Parent::isConstructed();
}

size_t SchedulerRoutineBase::getStackSize() const
{
    return 0;
}

bool_t SchedulerRoutineBase::construct()
{
    bool_t res( false );
    do 
    {
        if( !isConstructed() )
        {
            break;
        }
        res = true;
    } while(false);
    return res;
}

} // namespace sys
} // namespace eoos
