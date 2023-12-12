/**
 * @file      sys.ThreadPrimary.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#include "sys.ThreadPrimary.hpp"
#include "sys.Error.hpp"
#include "Program.hpp"

namespace eoos
{
namespace sys
{
    
ThreadPrimary::ThreadPrimary(api::Scheduler& scheduler, int32_t argc, char_t* argv[])
    : NonCopyable<NoAllocator>()
    , api::Task()
    , error_( ERROR_SYSTEM_ABORT )
    , scheduler_( scheduler )
    , argc_( argc )
    , argv_( argv )
    , thread_( NULLPTR ) {
    bool_t const isConstructed( construct() );
    setConstructed( isConstructed );
}    

ThreadPrimary::~ThreadPrimary()
{
    if( thread_ != NULLPTR )
    {
        delete thread_;
    }
}

bool_t ThreadPrimary::isConstructed() const
{
    return Parent::isConstructed();
}

bool_t ThreadPrimary::execute()
{
    bool_t res( false );
    if( isConstructed() )
    {
        res = thread_->execute();
    }
    return res;
}

bool_t ThreadPrimary::join()
{
    bool_t res( false );
    if( isConstructed() )
    {
        res = thread_->join();
    }
    return res;    
}

int32_t ThreadPrimary::getPriority() const
{
    int32_t priority( api::Thread::PRIORITY_WRONG );
    if( isConstructed() )
    {
        priority = thread_->getPriority();
    }
    return priority;
}

bool_t ThreadPrimary::setPriority(int32_t priority)
{
    bool_t res( false );
    if( isConstructed() )
    {
        res = thread_->setPriority(priority);
    }
    return res;
}

void ThreadPrimary::start()
{
    if( isConstructed() )
    {    
        error_ = Program::start(argc_, argv_);
    }
}

size_t ThreadPrimary::getStackSize() const
{
    return 0;
}

int32_t ThreadPrimary::getError() const
{
    return error_;
}

bool_t ThreadPrimary::construct()
{
    bool_t res( false );
    do 
    {
        if( !isConstructed() )
        {   ///< UT Justified Branch: HW dependency
            break;
        }
        if( !scheduler_.isConstructed() )
        {
            break;
        }        
        thread_ = scheduler_.createThread(*this);
        if( !thread_->isConstructed() )
        {
            break;
        }
        res = true;
    } while(false);    
    return res;
}

} // namespace sys
} // namespace eoos
