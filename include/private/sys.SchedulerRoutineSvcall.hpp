/**
 * @file      sys.SchedulerRoutineSvcall.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017-2024, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_SCHEDULERROUTINESVCALL_HPP_
#define SYS_SCHEDULERROUTINESVCALL_HPP_

#include "sys.NonCopyable.hpp"
#include "api.Runnable.hpp"

namespace eoos
{
namespace sys
{

/**
 * @class SchedulerRoutineSvcall
 * @brief Scheduler interrupt service routine.
 */
class SchedulerRoutineSvcall : public NonCopyable<NoAllocator>, public api::Runnable
{
    typedef NonCopyable<NoAllocator> Parent;

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
#endif // SYS_SCHEDULERROUTINESVCALL_HPP_
