/**
 * @file      sys.Thread.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2021-2024, Sergey Baigudin, Baigudin Software
 */
#include "sys.Thread.hpp"
#include "sys.Scheduler.hpp"

namespace eoos
{
namespace sys
{

Thread::Thread(api::Task& task)
    : ThreadResource<NoAllocator>(task) {
}

Thread::~Thread()
{
}

bool_t Thread::sleep(int32_t const ms)
{
    return Scheduler::sleepThread(ms);
}

bool_t Thread::yield()
{
    return Scheduler::yieldThread();
}
    
void Thread::yieldFromInterrupt()
{
    Scheduler::yieldThreadFromInterrupt();
}

} // namespace sys
} // namespace eoos
