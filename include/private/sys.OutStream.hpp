/**
 * @file      sys.OutStream.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2022-2023, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_OUTSTREAM_HPP_
#define SYS_OUTSTREAM_HPP_

#include "sys.NonCopyable.hpp"
#include "api.OutStream.hpp"

namespace eoos
{
namespace sys
{

/**
 * @class OutStream.
 * @brief Default system output stream.
 */
class OutStream : public NonCopyable<NoAllocator>, public api::OutStream<char_t>
{
    typedef NonCopyable<NoAllocator> Parent;

public:

    /**
     * @class Type.
     * @brief Type output.
     */
    enum Type
    {
        TYPE_COUT, ///< @brief COUT
        TYPE_CERR  ///< @brief CERR
    };

    /**
     * @brief Constructor.
     *
     * @param type Type output.
     */
    OutStream(Type type);

    /**
     * @brief Destructor.
     */
    virtual ~OutStream();

    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    virtual bool_t isConstructed() const;
    
    /**
     * @copydoc eoos::api::OutStream::operator<<(T const*)
     */
    virtual api::OutStream<char_t>& operator<<(char_t const* source);

    /**
     * @copydoc eoos::api::OutStream::operator<<(int32_t)
     */
    virtual api::OutStream<char_t>& operator<<(int32_t value);    

    /**
     * @copydoc eoos::api::OutStream::flush()
     */    
    virtual api::OutStream<char_t>& flush();

protected:

    using Parent::setConstructed;
    
private:

    /**
     * @brief Constructor.
     *
     * @param type Type output.     * 
     * @return True if object has been constructed successfully.
     */
    bool_t construct(Type type);

};

} // namespace sys
} // namespace eoos
#endif // SYS_OUTSTREAM_HPP_
