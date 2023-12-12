/**
 * @file      sys.System.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2023, Sergey Baigudin, Baigudin Software
 */
#include "sys.System.hpp"
#include "sys.ThreadPrimary.hpp"
#include "pcb.Board.hpp"

namespace eoos
{
namespace sys
{
    
/**
 * @brief EOOS system memory.
 * 
 * @note Memory is uint64_t type to be align 8.  
 */
static uint64_t memory_[(sizeof(System) >> 3) + 1]; 

System*         System::eoos_( NULLPTR );    
uint32_t        System::varBss_;
uint64_t        System::varDataByConstant_( 0xCAE0ABCD );
uint32_t        System::varDataByFunction_( System::getCheckValue() );
System::Check   System::varObjectByDefault_;
System::Check   System::varObjectByValue_( 0x0137EDA0 );
System::Check   System::varObjectByTwoValues_( 0xABCD0000, 0x00001234 );

System::System()
    : NonCopyable<NoAllocator>()
    , api::System()
    , api::Supervisor()
    , cpu_()
    , heap_()
    , scheduler_(cpu_)
    , mutexManager_()
    , semaphoreManager_()    
    , streamManager_()
    , kernel_(cpu_) {
    bool_t const isConstructed( construct() );
    setConstructed( isConstructed );
}    

System::~System()
{
    eoos_ = NULLPTR;
}

bool_t System::isConstructed() const
{
    return Parent::isConstructed();
}

api::Scheduler& System::getScheduler()
{
    if( !isConstructed() )
    {   ///< UT Justified Branch: HW dependency
        exit(ERROR_SYSCALL_CALLED);
    }
    return scheduler_; ///< SCA MISRA-C++:2008 Justified Rule 9-3-2
}

api::Heap& System::getHeap()
{
    if( !isConstructed() )
    {   ///< UT Justified Branch: HW dependency
        exit(ERROR_SYSCALL_CALLED);
    }
    return heap_; ///< SCA MISRA-C++:2008 Justified Rule 9-3-2
}

api::MutexManager& System::getMutexManager()
{
    if( !isConstructed() )
    {   ///< UT Justified Branch: HW dependency
        exit(ERROR_SYSCALL_CALLED);
    }
    return mutexManager_; ///< SCA MISRA-C++:2008 Justified Rule 9-3-2
}

api::SemaphoreManager& System::getSemaphoreManager()
{
    if( !isConstructed() )
    {   ///< UT Justified Branch: HW dependency
        exit(ERROR_SYSCALL_CALLED);
    }
    return semaphoreManager_; ///< SCA MISRA-C++:2008 Justified Rule 9-3-2
}

api::StreamManager& System::getStreamManager()
{
    if( !isConstructed() )
    {   ///< UT Justified Branch: HW dependency
        exit(ERROR_SYSCALL_CALLED);
    }
    return streamManager_; ///< SCA MISRA-C++:2008 Justified Rule 9-3-2
}

api::CpuProcessor& System::getProcessor()
{
    if( !isConstructed() )
    {   ///< UT Justified Branch: HW dependency
        exit(ERROR_SYSCALL_CALLED);
    }
    return cpu_;
}

int32_t System::run()
{
    char_t* argv[] = {NULLPTR};
    return run(0, argv);
}

int32_t System::run(int32_t argc, char_t** argv)
{
    int32_t error( ERROR_UNDEFINED );
    System* const eoos( new System );
    if( eoos != NULLPTR )
    {
        error = eoos->execute(argc, argv);
        delete eoos;
    }
    return error;
}

System& System::getSystem()
{
    if(eoos_ == NULLPTR)
    {   ///< UT Justified Branch: Startup dependency
        exit(ERROR_SYSCALL_CALLED);
    }
    return *eoos_;
}

bool_t System::construct()
{
    bool_t res( false );
    do 
    {
        if( !isConstructed() )
        {   ///< UT Justified Branch: HW dependency
            break;
        }
        if( !isVarChecked() )
        {
            break;
        }
        if( eoos_ != NULLPTR )
        {   ///< UT Justified Branch: Startup dependency
            break;
        }
        if( !cpu_.isConstructed() )
        {
            break;
        }
        if( !heap_.isConstructed() )
        {   ///< UT Justified Branch: HW dependency
            break;
        }
        if( !scheduler_.isConstructed() )
        {   ///< UT Justified Branch: HW dependency
            break;
        }
        if( !mutexManager_.isConstructed() )
        {   ///< UT Justified Branch: HW dependency
            break;
        }
        if( !semaphoreManager_.isConstructed() )
        {   ///< UT Justified Branch: HW dependency
            break;
        }
        if( !streamManager_.isConstructed() )
        {   ///< UT Justified Branch: HW dependency
            break;
        }        
        if( !kernel_.isConstructed() )
        {   ///< UT Justified Branch: HW dependency
            break;
        }        
        eoos_ = this;
        res = true;
    } while(false);    
    return res;
}

int32_t System::execute(int32_t argc, char_t* argv[])
{
    int32_t error( ERROR_SYSTEM_ABORT );
    if( isConstructed() )
    {   
        pcb::Board board;
        if( board.isConstructed() )
        {
            ThreadPrimary thread(scheduler_, argc, argv);
            if( thread.execute() )
            {
                kernel_.execute();
                // No extit here, thus no thread join needed for FreeRTOS
            }
            error = thread.getError();
        }
    }
    return error;
}

void System::exit(Error error)
{
    portDISABLE_INTERRUPTS();
    while( true ){}
}

uint32_t System::getCheckValue()
{
    return 0x19822014;
}

bool_t System::isVarChecked()
{
    bool_t res( true );
    if( varBss_ != 0 )
    {
        res = false;
    }
    if( varDataByConstant_ != 0xCAE0ABCD )
    {
        res = false;
    }
    if( varDataByFunction_ != 0x19822014)
    {
        res = false;
    }
    if( varObjectByDefault_.value != 0x18172023 )
    {
        res = false;
    }
    if( varObjectByValue_.value != 0x0137EDA0 )
    {
        res = false;
    }
    if( varObjectByTwoValues_.value != 0xABCD1234 )
    {
        res = false;
    }
    return res;
}

void* System::operator new(size_t size)
{
    void* memory( NULLPTR );
    if( size == sizeof(System) && eoos_ == NULLPTR )
    {
        memory = memory_;
    }
    return memory;
}

void System::operator delete(void* const ptr)
{
}

System::Check::Check()
    : value(0x18172023) {
}
    
System::Check::Check(uint32_t initial)
    : value(initial) {
}
    
System::Check::Check(uint32_t initialHi, uint32_t initialLow)
    : value(initialHi | initialLow) {
}

} // namespace sys
} // namespace eoos
