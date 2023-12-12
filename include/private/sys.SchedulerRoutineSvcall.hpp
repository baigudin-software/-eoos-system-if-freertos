/**
 * @file      sys.SchedulerRoutineSvcall.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017-2023, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_SCHEDULERROUTINESVCALL_HPP_
#define SYS_SCHEDULERROUTINESVCALL_HPP_

#include "sys.SchedulerRoutineBase.hpp"

namespace eoos
{
namespace sys
{

/**
 * @class SchedulerRoutineSvcall
 * @brief Scheduler interrupt service routine.
 */
class SchedulerRoutineSvcall : public SchedulerRoutineBase
{
    typedef SchedulerRoutineBase Parent;

public:

    /**
     * @brief Constructor.
     */
    SchedulerRoutineSvcall();

    /**
     * @brief Destructor.
     */
    virtual ~SchedulerRoutineSvcall();

    /**
     * @copydoc eoos::api::Task::start()
     */
    virtual void start();

private:

    /**
     * Constructs this object.
     *
     * @return true if object has been constructed successfully.
     */
    bool_t construct();

};

} // namespace sys
} // namespace eoos
#endif // SYS_SCHEDULERROUTINESVCALL_HPP_
