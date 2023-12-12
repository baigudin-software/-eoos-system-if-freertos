/**
 * @file      sys.Svc.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_SVC_HPP_
#define SYS_SVC_HPP_

#include "api.Supervisor.hpp"

namespace eoos
{
namespace sys
{
    
/**
 * @class Svc
 * @brief System supervisor calls to the operating system.
 */
class Svc
{

public:

    /**
     * @brief Returns the operating system supervisor call interface.
     *
     * @return The operating system supervisor call interface.
     */
    static api::Supervisor& get();

};

} // namespace sys
} // namespace eoos
#endif // SYS_SVC_HPP_
