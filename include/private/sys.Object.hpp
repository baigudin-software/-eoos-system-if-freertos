/**
 * @file      sys.Object.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2023, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_OBJECT_HPP_
#define SYS_OBJECT_HPP_

#include "lib.Object.hpp"
#include "sys.NoAllocator.hpp"

namespace eoos
{
namespace sys
{

/**
 * @class Object
 * @brief Root class of the operating system class hierarchy.
 *
 * @tparam A Heap memory allocator class.
 */
template <class A>
class Object : public lib::Object<A>
{
    typedef lib::Object<A> Parent;

public:

    /**
     * @brief Constructor.
     */
    Object();

    /**
     * @brief Destructor.
     */
    virtual ~Object();
    
    /**
     * @copydoc eoos::Object::Object(const Object&)
     */
    Object(const Object& obj);

    /**
     * @copydoc eoos::Object::operator=(const Object&)
     */       
    Object& operator=(const Object& obj);

    #if EOOS_CPP_STANDARD >= 2011

    /**
     * @copydoc eoos::Object::Object(const Object&&)
     */       
    Object(Object&& obj) noexcept;
    
    /**
     * @copydoc eoos::Object::operator=(const Object&&)
     */
    Object& operator=(Object&& obj) & noexcept;
    
    #endif // EOOS_CPP_STANDARD >= 2011    

};

template <class A>
Object<A>::Object()
    : lib::Object<A>() {
}

template <class A>
Object<A>::~Object()
{
}

template <class A>
Object<A>::Object(const Object& obj) 
    : lib::Object<A>(obj) {
} 

template <class A>
Object<A>& Object<A>::operator=(const Object& obj)
{
    static_cast<void>( Parent::operator=(obj) );
    return *this;
}

#if EOOS_CPP_STANDARD >= 2011

template <class A>
Object<A>::Object(Object&& obj) noexcept
    : lib::Object<A>( lib::move(obj) ) {
}

template <class A>
Object<A>& Object<A>::operator=(Object&& obj) & noexcept
{
    Parent::operator=( lib::move(obj) );
    return *this;
}
    
#endif // EOOS_CPP_STANDARD >= 2011    


} // namespace sys
} // namespace eoos
#endif // SYS_OBJECT_HPP_
