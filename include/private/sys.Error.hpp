/**
 * @file      sys.Error.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017-2023, Sergey Baigudin
 */
#ifndef SYS_ERROR_HPP_
#define SYS_ERROR_HPP_

namespace eoos
{
namespace sys
{
    
/**
 * @enum  Error
 * @brief The operating system error codes.
 */
enum Error
{
    /**
     * @brief No errors have been occurred.
     */
    ERROR_OK = 0,

    /**
     * @brief Error of the operating system kernel syscall calling.
     */
    ERROR_SYSCALL_CALLED = -1,

    /**
     * @brief Error of the OS termination.
     */
    ERROR_SYSTEM_ABORT = -2,

    /**
     * @brief Error of a user program occurred.
     */
    ERROR_USER_ABORT = -3,

    /**
     * @brief Error of searching of a resource.
     */
    ERROR_RESOURCE_NOT_FOUND = -4,

    /**
     * @brief Error of a function argument.
     */
    ERROR_ARGUMENT = -5,
    
    /**
     * @brief An undefined error has been occurred.
     */
    ERROR_UNDEFINED = -127,

    /**
     * @brief The last unused error code.
     */
    ERROR_LAST = -128

};

} // namespace sys
} // namespace eoos
#endif // SYS_ERROR_HPP_
