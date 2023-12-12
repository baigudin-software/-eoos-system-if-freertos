/**
 * @file      sys.Types.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2021-2023, Sergey Baigudin, Baigudin Software
 * 
 * @brief System type definitions.
 */
#ifndef SYS_TYPES_HPP_
#define SYS_TYPES_HPP_

#include "lib.Types.hpp"
#include "sys.Freertos.hpp" ///< @note Has to be second to avoid NULL definition by FreeRTOS. 
#include "sys.Definitions.hpp"

#if EOOS_CPP_STANDARD >= 2011 && defined (EOOS_CPP_NOTHROW)
#include <new>
#endif // EOOS_CPP_STANDARD >= 2011

namespace eoos
{
namespace sys
{

#if EOOS_CPP_STANDARD >= 2011 && defined (EOOS_CPP_NOTHROW)

/**
 * @brief Empty class type used to disambiguate the overloads of throwing and non-throwing allocation.
 */
struct nothrow_t 
{ 
    explicit nothrow_t() = default; 
};

/**
 * @brief Constant of type lib::nothrow_t used to disambiguate the overloads of throwing and non-throwing allocation functions.
 */
const ::std::nothrow_t nothrow { ::std::nothrow };

#endif // EOOS_CPP_STANDARD >= 2011

} // namespace sys
} // namespace eoos
#endif // SYS_TYPES_HPP_
