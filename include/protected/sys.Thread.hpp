/**
 * @file      sys.Thread.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2021-2024, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_THREAD_HPP_
#define SYS_THREAD_HPP_

#include "sys.ThreadResource.hpp"

namespace eoos
{
namespace sys
{
    
/**
 * @class Thread
 * @brief System thread for called by protected software components.
 */
class Thread : public ThreadResource<NoAllocator>
{
    typedef ThreadResource<NoAllocator> Parent;

public:

    /**
     * @brief Constructor of not constructed object.
     *
     * @param task A task interface whose main method is invoked when this thread is started.
     */
    Thread(api::Task& task);

    /**
     * @brief Destructor.
     */
    virtual ~Thread();
    
    /**
     * @copydoc eoos::api::Scheduler::sleep(int32_t)
     */
    static bool_t sleep(int32_t const ms);

    /**
     * @copydoc eoos::api::Scheduler::yield()
     */
    static bool_t yield();
    
    /**
     * @brief Yields to next thread from ISR.
     */
    static void yieldFromInterrupt();

};


} // namespace sys
} // namespace eoos
#endif // SYS_THREAD_HPP_
