/**
 * @file      sys.Call.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2023, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_CALL_HPP_
#define SYS_CALL_HPP_

#include "api.System.hpp"

namespace eoos
{
namespace sys
{
    
/**
 * @class Call
 * @brief System calls to the operating system.
 */
class Call
{

public:

    /**
     * @brief Returns the operating system syscall interface.
     *
     * @return The operating system syscall interface.
     */
    static api::System& get();

};

} // namespace sys
} // namespace eoos
#endif // SYS_CALL_HPP_
