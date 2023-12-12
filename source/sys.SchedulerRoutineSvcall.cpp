/**
 * @file      sys.SchedulerRoutineSvcall.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017-2023, Sergey Baigudin, Baigudin Software
 */
#include "sys.SchedulerRoutineSvcall.hpp"

namespace eoos
{
namespace sys
{

SchedulerRoutineSvcall::SchedulerRoutineSvcall()
    : SchedulerRoutineBase() {
    bool_t const isConstructed( construct() );
    setConstructed( isConstructed );    
}

SchedulerRoutineSvcall::~SchedulerRoutineSvcall()
{
}

void SchedulerRoutineSvcall::start()
{
    ::vTaskSwitchContext();
}

bool_t SchedulerRoutineSvcall::construct()
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
