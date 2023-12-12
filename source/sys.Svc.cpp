/**
 * @file      sys.Svc.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#include "sys.Svc.hpp"
#include "sys.System.hpp"

namespace eoos
{
namespace sys
{

api::Supervisor& Svc::get()
{
    return System::getSystem();
}

} // namespace sys
} // namespace eoos
