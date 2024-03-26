/**
 * @file      sys.Semaphore.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017-2024, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_SEMAPHORE_HPP_
#define SYS_SEMAPHORE_HPP_

#include "sys.SemaphoreResource.hpp"

namespace eoos
{
namespace sys
{

/**
 * @class Semaphore
 * @brief System semaphore for called by protected software components.
 */
typedef SemaphoreResource<NoAllocator> Semaphore;
        
} // namespace sys
} // namespace eoos
#endif // SYS_SEMAPHORE_HPP_
