/**
 * @file      sys.NonCopyable.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2021-2023, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_NONCOPYABLE_HPP_
#define SYS_NONCOPYABLE_HPP_

#include "sys.Object.hpp"

namespace eoos
{
namespace sys
{

/**
 * @class NonCopyable
 * @brief Root class of the operating system for objects which cannot be copied.
 *
 * @tparam A Heap memory allocator class.
 */
template <class A>
class NonCopyable : public Object<A>
{

public:

    /**
     * @brief Constructor.
     */
    NonCopyable();

    /**
     * @brief Destructor.
     */
    virtual ~NonCopyable();
    
private:
    
    /**
     * @copydoc eoos::Object::Object(Object const&)
     */
    NonCopyable(NonCopyable const&); ///< SCA MISRA-C++:2008 Justified Rule 3-2-2 and Rule 3-2-4
    
    /**
     * @copydoc eoos::Object::operator=(Object const&)
     */       
    NonCopyable& operator=(NonCopyable const&); ///< SCA MISRA-C++:2008 Justified Rule 3-2-2 and Rule 3-2-4

    #if EOOS_CPP_STANDARD >= 2011
    
    /**
     * @copydoc eoos::Object::Object(Object&&)
     */       
    NonCopyable(NonCopyable&&) noexcept = delete;
    
    /**
     * @copydoc eoos::Object::operator=(Object&&)
     */
    NonCopyable& operator=(NonCopyable&&) noexcept = delete;

    #endif // EOOS_CPP_STANDARD >= 2011

};

template <class A>
NonCopyable<A>::NonCopyable() 
    : Object<A>() {
}

template <class A>
NonCopyable<A>::~NonCopyable()
{
}

} // namespace sys
} // namespace eoos
#endif // SYS_NONCOPYABLE_HPP_
