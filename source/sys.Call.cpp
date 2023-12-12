/**
 * @file      sys.Call.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2023, Sergey Baigudin, Baigudin Software
 */
#include "sys.Call.hpp"
#include "sys.System.hpp"

namespace eoos
{
namespace sys
{

api::System& Call::get()
{
    return System::getSystem();
}

} // namespace sys
} // namespace eoos
