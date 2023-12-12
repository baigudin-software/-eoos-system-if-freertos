/**
 * @file      sys.Definitions.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 *
 * @brief System global definitions.
 */
#ifndef SYS_DEFINITIONS_HPP_
#define SYS_DEFINITIONS_HPP_

/**
 * @brief Defines stack size of a FreeRTOS task in Bytes aligned to 8.
 */
#ifndef EOOS_GLOBAL_SYS_FREERTOS_TASK_STACK_SIZE
    #define EOOS_GLOBAL_SYS_FREERTOS_TASK_STACK_SIZE (2048)
#endif

/**
 * @brief Define number of static allocated resources.
 * 
 * @note
 *  - If EOOS_GLOBAL_SYS_NUMBER_OF_<resource_name> does not equal zero and EOOS_GLOBAL_ENABLE_NO_HEAP is any,
 *    the resource will be allocated in pre-allocated pool memory.
 *  - If EOOS_GLOBAL_SYS_NUMBER_OF_<resource_name> equals zero and EOOS_GLOBAL_ENABLE_NO_HEAP is not defined, 
 *    the resource will be allocated in heap memory.
 *  - If EOOS_GLOBAL_SYS_NUMBER_OF_<resource_name> equals zero and EOOS_GLOBAL_ENABLE_NO_HEAP is defined, 
 *    the resource will NOT be allocated.
 *  - EOOS_GLOBAL_SYS_NUMBER_OF_<resource_name> less then zero is prohibbited.
 * 
 * @note 
 *  To comply MISRA-C++:2008 in Rule 18–4–1:
 *  - EOOS_GLOBAL_SYS_NUMBER_OF_<resource_name> shall not equal zero
 *  - EOOS_GLOBAL_ENABLE_NO_HEAP shall be defined.
 *
 * @note 
 * 	The EOOS_GLOBAL_SYS_NUMBER_OF_<resource_name> shall be passed to the project build system through compile definition.
 *
 * @note
 *	Currently EOOS_GLOBAL_SYS_NUMBER_OF_<resource_name> feature supported only by EOOS POSIX and EOOS FreeRTOS.
 *  For EOOS WIN32 these defines have no effects.
 */
#ifndef EOOS_GLOBAL_SYS_NUMBER_OF_MUTEXS
    #define EOOS_GLOBAL_SYS_NUMBER_OF_MUTEXS (0)
#endif

#ifndef EOOS_GLOBAL_SYS_NUMBER_OF_SEMAPHORES
    #define EOOS_GLOBAL_SYS_NUMBER_OF_SEMAPHORES (0)
#endif

#ifndef EOOS_GLOBAL_SYS_NUMBER_OF_THREADS
    #define EOOS_GLOBAL_SYS_NUMBER_OF_THREADS (0)
#endif

#endif // SYS_DEFINITIONS_HPP_
