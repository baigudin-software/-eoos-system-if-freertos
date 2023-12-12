/**
 * @file      sys.NoAllocator.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_NOALLOCATOR_HPP_
#define SYS_NOALLOCATOR_HPP_

#include "sys.Types.hpp"

namespace eoos
{
namespace sys
{
 
/**
 * @class NoAllocator
 * @brief No memory allocator.
 */ 
class NoAllocator
{

public:

    /**
     * @brief Does not allocate memory.
     *
     * @return The null pointer.
     */
    static void* allocate(size_t);

    /**
     * @brief Frees allocated memory.
     */
    static void free(void*);

};

} // namespace sys
} // namespace eoos
#endif // SYS_NOALLOCATOR_HPP_
