/**
 * @file      sys.Heap.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2022-2023, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_HEAP_HPP_
#define SYS_HEAP_HPP_

#include "api.Heap.hpp"

namespace eoos
{
namespace sys
{

/**
 * @class Heap.
 * @brief Heap class.
 */
class Heap : public api::Heap
{

public:

    /**
     * @brief Constructor.
     */
    Heap();

    /**
     * @brief Destructor.
     */
    virtual ~Heap();

    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    virtual bool_t isConstructed() const;

    /**
     * @copydoc eoos::api::Heap::allocate(size_t,void*)
     */
    virtual void* allocate(size_t const size, void* ptr);

    /**
     * @copydoc eoos::api::Heap::free(void*)
     */
    virtual void free(void* ptr);
    
};

} // namespace sys
} // namespace eoos
#endif // SYS_HEAP_HPP_
