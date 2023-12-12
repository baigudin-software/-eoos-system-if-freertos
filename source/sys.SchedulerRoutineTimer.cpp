/**
 * @file      sys.SchedulerRoutineTimer.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017-2023, Sergey Baigudin, Baigudin Software
 */
#include "sys.SchedulerRoutineTimer.hpp"

namespace eoos
{
namespace sys
{

SchedulerRoutineTimer::SchedulerRoutineTimer()
    : SchedulerRoutineBase() {
    bool_t const isConstructed( construct() );
    setConstructed( isConstructed );    
}

SchedulerRoutineTimer::~SchedulerRoutineTimer()
{
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
