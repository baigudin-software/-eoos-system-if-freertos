/**
 * @file      sys.SchedulerRoutineTimer.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017-2024, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_SCHEDULERROUTINETIMER_HPP_
#define SYS_SCHEDULERROUTINETIMER_HPP_

#include "sys.NonCopyable.hpp"
#include "api.Runnable.hpp"

namespace eoos
{
namespace sys
{

/**
 * @class SchedulerRoutineTimer
 * @brief Scheduler interrupt service routine.
 */
class SchedulerRoutineTimer : public NonCopyable<NoAllocator>, public api::Runnable
{
    typedef NonCopyable<NoAllocator> Parent;

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
     * @copydoc eoos::api::Object::isConstructed()
     */
    virtual bool_t isConstructed() const;

    /**
     * @copydoc eoos::api::Runnable::start()
     */
    virtual void start();

private:

    /**
     * @brief Constructs this object.
     *
     * @return true if object has been constructed successfully.
     */
    bool_t construct();

};

} // namespace sys
} // namespace eoos
#endif // SYS_SCHEDULERROUTINETIMER_HPP_
