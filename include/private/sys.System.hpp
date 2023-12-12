/**
 * @file      sys.System.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2023, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_SYSTEM_HPP_
#define SYS_SYSTEM_HPP_

#include "sys.NonCopyable.hpp"
#include "api.System.hpp"
#include "api.Supervisor.hpp"
#include "cpu.Processor.hpp"
#include "sys.Heap.hpp"
#include "sys.Scheduler.hpp"
#include "sys.MutexManager.hpp"
#include "sys.SemaphoreManager.hpp"
#include "sys.StreamManager.hpp"
#include "sys.Error.hpp"

namespace eoos
{
namespace sys
{
    
/**
 * @class System
 * @brief The operating system.
 */
class System : public NonCopyable<NoAllocator>, public api::System, public api::Supervisor
{
    typedef NonCopyable<NoAllocator> Parent;

public:

    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    virtual bool_t isConstructed() const;

    /**
     * @copydoc eoos::api::System::getScheduler()
     */
    virtual api::Scheduler& getScheduler();

    /**
     * @copydoc eoos::api::System::getHeap()
     */
    virtual api::Heap& getHeap();

    /**
     * @copydoc eoos::api::System::getMutexManager()
     */
    virtual api::MutexManager& getMutexManager();

    /**
     * @copydoc eoos::api::System::getSemaphoreManager()
     */
    virtual api::SemaphoreManager& getSemaphoreManager();
    
    /**
     * @copydoc eoos::api::System::getStreamManager()
     */
    virtual api::StreamManager& getStreamManager();
    
    /**
     * @copydoc eoos::api::Supervisor::getProcessor()
     */
    virtual api::CpuProcessor& getProcessor();
        
    /**
     * @brief Runs the EOOS system.
     *
     * @return error code or zero.
     */
    static int32_t run();

    /**
     * @brief Runs the EOOS system.
     *
     * @param argc The number of arguments passed to the program.
     * @param argv An array of c-string of arguments where the last one - argc + 1 is null. 
     * @return error code or zero.
     */
    static int32_t run(int32_t argc, char_t** argv);

    /**
     * @brief Returns an only one created instance of the EOOS system.
     *
     * @return The EOOS system instance.
     */
    static System& getSystem();

private:
    
    /**
     * @struct Check variable of global object.
     */
    struct Check
    {
        /**
         * @brief Constructor.
         */
        Check();
      
        /**
         * @brief Constructor.
         *
         * @param initial Initialization value.
         */
        Check(uint32_t initial);

        /**
         * @brief Constructor.
         *
         * @param initialHi Initialization value hi.
         * @param initialLow Initialization value low.        
         */
        Check(uint32_t initialHi, uint32_t initialLow);
        
        /**
         * @brief Check variable in .data section.
         */
        uint32_t value;

    };
    
    /**
     * @brief Constructor.
     */
    System();

    /**
     * @brief Destructor.
     */
    virtual ~System();    

    /**
     * @brief Constructs this object.
     *
     * @return True if object has been constructed successfully.
     */
    bool_t construct();
    
    /**
     * @brief Executes the operating system.
     *
     * @param argc The number of arguments passed to the program.
     * @param argv An array of c-string of arguments where the last one - argc + 1 is null.
     * @return Zero, or error code if the execution has been terminated.
     */
    int32_t execute(int32_t argc, char_t* argv[]);    
    
    /**
     * @brief Terminates the system execution.
     *
     * @param Error an exit code.
     */
    static void exit(Error error);

    /**
     * @brief Returns a value.
     *
     * @param Value to be checked.
     */
    static uint32_t getCheckValue();

    /**
     * @brief Test if all global variable correct.
     *
     * @param True if values are correct.
     */
    static bool_t isVarChecked();
    
    /**
     * @brief Operator new.
     *
     * @param size A number of bytes of this class.
     * @return The address memory_[] array.
     */
    static void* operator new(size_t size);
    
    /**
     * @brief Operator delete.
     *
     * @param ptr An address of allocated memory block or a null pointer.
     */
    static void operator delete(void* const ptr);    

    /**
     * @brief The operating system.
     */
    static System* eoos_;

    /**
     * @brief Check variable in .bss section.
     */
    static uint32_t varBss_;

    /**
     * @brief Check variable in .data section initialized by constant.
     */
    static uint64_t varDataByConstant_;

    /**
     * @brief Check variable in .data section initialized by function.
     */
    static uint32_t varDataByFunction_;

    /**
     * @brief Check variable of global object.
     */
    static Check varObjectByDefault_;

    /**
     * @brief Check variable of global object.
     */
    static Check varObjectByValue_;

    /**
     * @brief Check variable of global object.
     */
    static Check varObjectByTwoValues_;
    
    /**
     * @brief The target processor.
     */
    cpu::Processor cpu_;

    /**
     * @brief The system heap.
     */
    Heap heap_;
 
    /**
     * @brief The operating system scheduler.
     */
    Scheduler scheduler_;

    /**
     * @brief The mutex sub-system manager.
     */
    MutexManager mutexManager_;

    /**
     * @brief The semaphore sub-system manager.
     */
    SemaphoreManager semaphoreManager_;
    
    /**
     * @brief The stream sub-system manager.
     */
    StreamManager streamManager_;
    
    /**
     * @brief The FreeRTOS kernel port.
     */
    port::Kernel kernel_;

};

} // namespace sys
} // namespace eoos
#endif // SYS_SYSTEM_HPP_
