/**
 * @file      sys.SchedulerRoutineTimer.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017-2024, Sergey Baigudin, Baigudin Software
 */
#include "sys.SchedulerRoutineTimer.hpp"

namespace eoos
{
namespace sys
{

SchedulerRoutineTimer::SchedulerRoutineTimer()
    : NonCopyable<NoAllocator>()
    , api::Runnable() {
    bool_t const isConstructed( construct() );
    setConstructed( isConstructed );    
}

SchedulerRoutineTimer::~SchedulerRoutineTimer()
{
}

bool_t SchedulerRoutineTimer::isConstructed() const
{
    return Parent::isConstructed();
}

void SchedulerRoutineTimer::start()
{
    // Called by the portable layer each time a tick interrupt occurs.
    // Increments the tick then checks to see if the new tick 
    // value will cause any tasks to be unblocked.
    ::BaseType_t xSwitchRequired( ::xTaskIncrementTick() );
    // Select the next task to execute
    if(xSwitchRequired == pdTRUE)
    {
        ::vTaskSwitchContext();
    }    
}

bool_t SchedulerRoutineTimer::construct()
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
