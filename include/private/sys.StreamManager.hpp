/**
 * @file      sys.StreamManager.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_STREAMMANAGER_HPP_
#define SYS_STREAMMANAGER_HPP_

#include "sys.NonCopyable.hpp"
#include "api.StreamManager.hpp"
#include "sys.OutStream.hpp"

namespace eoos
{
namespace sys
{

/**
 * @class StreamManager.
 * @brief Stream sub-system manager.
 */
class StreamManager : public NonCopyable<NoAllocator>, public api::StreamManager
{
    typedef NonCopyable<NoAllocator> Parent;

public:

    /**
     * @brief Constructor.
     */
    StreamManager();

    /**
     * @brief Destructor.
     */
    virtual ~StreamManager();

    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    virtual bool_t isConstructed() const;
    
    /**
     * @copydoc eoos::api::StreamManager::getCout()
     */    
    virtual api::OutStream<char_t>& getCout();
    
    /**
     * @copydoc eoos::api::StreamManager::getCerr()
     */
    virtual api::OutStream<char_t>& getCerr();
    
    /**
     * @copydoc eoos::api::StreamManager::setCout()
     */
    virtual bool_t setCout(api::OutStream<char_t>& cout);

    /**
     * @copydoc eoos::api::StreamManager::setCerr()
     */
    virtual bool_t setCerr(api::OutStream<char_t>& cerr);    

    /**
     * @copydoc eoos::api::StreamManager::resetCout()
     */
    virtual void resetCout();

    /**
     * @copydoc eoos::api::StreamManager::resetCerr()
     */
    virtual void resetCerr();

protected:

    using Parent::setConstructed;

private:
    
    /**
     * @brief The default system output character stream.
     */
    OutStream coutDef_;

    /**
     * @brief The default system error character stream.
     */
    OutStream cerrDef_;

    /**
     * @brief The system output character stream.
     */    
    api::OutStream<char_t>* cout_;

    /**
     * @brief The system error character stream.
     */    
    api::OutStream<char_t>* cerr_;

};

} // namespace sys
} // namespace eoos
#endif // SYS_STREAMMANAGER_HPP_
