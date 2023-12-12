/**
 * @file      sys.NoAllocator.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#include "sys.NoAllocator.hpp"

namespace eoos
{
namespace sys
{
 
void* NoAllocator::allocate(size_t)
{
    return NULLPTR;
}

void NoAllocator::free(void*)
{
}

} // namespace sys
} // namespace eoos
