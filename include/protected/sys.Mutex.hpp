/**
 * @file      sys.Mutex.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2021-2024, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_MUTEX_HPP_
#define SYS_MUTEX_HPP_

#include "sys.MutexResource.hpp"

namespace eoos
{
namespace sys
{
    
/**
 * @class Mutex
 * @brief System mutex for called by protected software components.
 */
typedef MutexResource<NoAllocator> Mutex;

} // namespace sys
} // namespace eoos
#endif // SYS_MUTEX_HPP_
