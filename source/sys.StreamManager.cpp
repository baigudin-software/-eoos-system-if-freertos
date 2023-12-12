/**
 * @file      sys.StreamManager.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#include "sys.StreamManager.hpp"

namespace eoos
{
namespace sys
{

StreamManager::StreamManager() 
    : NonCopyable<NoAllocator>()
    , api::StreamManager() 
    , coutDef_( OutStream::TYPE_COUT ) 
    , cerrDef_( OutStream::TYPE_CERR )
    , cout_( &coutDef_ )
    , cerr_( &cerrDef_ ) {
    setConstructed( true );
}

StreamManager::~StreamManager()
{
    cout_->flush();
    cerr_->flush();        
}

bool_t StreamManager::isConstructed() const
{
    return Parent::isConstructed();
}

api::OutStream<char_t>& StreamManager::getCout()
{
    return *cout_;
}

api::OutStream<char_t>& StreamManager::getCerr()
{
    return *cerr_;
}    

bool_t StreamManager::setCout(api::OutStream<char_t>& cout)
{
    cout_ = &cout;
    return true;
}

bool_t StreamManager::setCerr(api::OutStream<char_t>& cerr)
{
    cerr_ = &cerr;
    return true;
}
    
void StreamManager::resetCout()
{
    cout_ = &coutDef_;
}

void StreamManager::resetCerr()
{
    cerr_ = &cerrDef_;
}
    
} // namespace sys
} // namespace eoos
