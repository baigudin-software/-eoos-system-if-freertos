/**
 * @file      sys.SchedulerRoutineBase.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017-2023, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_SCHEDULERROUTINEBASE_HPP_
#define SYS_SCHEDULERROUTINEBASE_HPP_

#include "sys.NonCopyable.hpp"
#include "api.Task.hpp"

namespace eoos
{
namespace sys
{

/**
 * @class SchedulerRoutineBase
 * @brief Scheduler interrupt service routine.
 */
class SchedulerRoutineBase : public NonCopyable<NoAllocator>, public api::Task
{
    typedef NonCopyable<NoAllocator> Parent;

public:

    /**
     * @brief Constructor.
     */
    SchedulerRoutineBase();

    /**
     * @brief Destructor.
     */
    virtual ~SchedulerRoutineBase();

    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    virtual bool_t isConstructed() const;

    /**
     * @copydoc eoos::api::Task::getStackSize()
     */
    virtual size_t getStackSize() const;

protected:

    using Parent::setConstructed;    

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
#endif // SYS_SCHEDULERROUTINEBASE_HPP_
