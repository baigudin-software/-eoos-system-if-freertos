/**
 * @file      sys.SchedulerRoutineTimer.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017-2023, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_SCHEDULERROUTINETIMER_HPP_
#define SYS_SCHEDULERROUTINETIMER_HPP_

#include "sys.SchedulerRoutineBase.hpp"

namespace eoos
{
namespace sys
{

/**
 * @class SchedulerRoutineTimer
 * @brief Scheduler interrupt service routine.
 */
class SchedulerRoutineTimer : public SchedulerRoutineBase
{
    typedef SchedulerRoutineBase Parent;

public:

    /**
     * @brief Constructor.
     */
    SchedulerRoutineTimer();

    /**
     * @brief Destructor.
     */
    virtual ~SchedulerRoutineTimer();

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
#endif // SYS_SCHEDULERROUTINETIMER_HPP_
