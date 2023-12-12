/**
 * @file      sys.ThreadPrimary.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#ifndef API_THREADPRIMARY_HPP_
#define API_THREADPRIMARY_HPP_

#include "sys.NonCopyable.hpp"
#include "api.Thread.hpp"
#include "api.Task.hpp"
#include "api.Scheduler.hpp"

namespace eoos
{
namespace sys
{
    
/**
 * @class ThreadPrimary
 * @brief Primary thread.
 */        
class ThreadPrimary : public NonCopyable<NoAllocator>, public api::Thread, public api::Task
{
    typedef NonCopyable<NoAllocator> Parent;

public:

    /**
     * @brief Constructor.
     *
     * @param scheduler The operating system scheduler.
     * @param argc The number of arguments passed to the program.
     * @param argv An array of c-string of arguments where the last one - argc + 1 is null.     
     */
    ThreadPrimary(api::Scheduler& scheduler, int32_t argc, char_t* argv[]);

    /**
     * @brief Destructor.
     */
    virtual ~ThreadPrimary();
    
    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    virtual bool_t isConstructed() const;

    /**
     * @copydoc eoos::api::Thread::execute()
     */
    virtual bool_t execute();

    /**
     * @copydoc eoos::api::Thread::join()
     */
    virtual bool_t join();

    /**
     * @copydoc eoos::api::Task::getStackSize()
     */
    virtual size_t getStackSize() const;
    
    /**
     * @brief Returns program execution error.
     *
     * @return Program execution error.
     */
    int32_t getError() const;    
    
private:

    /**
     * @copydoc eoos::api::Thread::getPriority()
     */
    virtual int32_t getPriority() const;

    /**
     * @copydoc eoos::api::Thread::setPriority(int32_t)
     */
    virtual bool_t setPriority(int32_t priority);

    /**
     * @copydoc eoos::api::Task::start()
     */
    virtual void start();

    /**
     * @brief Constructs this object.
     *
     * @return True if object has been constructed successfully.
     */
    bool_t construct();

    /**
     * @brief Program execution error.
     */
    int32_t error_;
    
    /**
     * @brief The operating system scheduler.
     */
    api::Scheduler& scheduler_;    
    
    /**
     * @brief The number of arguments passed to the program.
     */
    int32_t argc_;
    
    /**
     * @brief The number of arguments passed to the program.
     */
    char_t** argv_;    

    /**
     * @brief A system scheduler thread.
     */
    api::Thread* thread_;

};

} // namespace sys
} // namespace eoos
#endif // API_TASK_HPP_
