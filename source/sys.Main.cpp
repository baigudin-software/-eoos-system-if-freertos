/**
 * @file      sys.Main.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2018-2023, Sergey Baigudin, Baigudin Software
 */
#include "sys.System.hpp"

/**
 * @brief The main function.
 *
 * The following tasks must be done before the function called:
 * 1. Stack has been set.
 * 2. CPU registers have been set.
 * 3. Run-time initialization has been completed.
 * 4. Global variables have been set.
 * 5. Global constructors have been called.
 *
 * @param argc The number of arguments passed to the program.
 * @param argv An array of c-string of arguments where the last one - argc + 1 is null. 
 * @return error code or zero.
 */
int main(int const argc, char** const argv) try
{
    eoos::int32_t const error( eoos::sys::System::run(argc, argv) );
    return static_cast<int>(error); ///< SCA MISRA-C++:2008 Justified Rule 3-9-2
} 
catch (...) 
{
    // Handle unexpected exceptions following MISRA-C++:2008 Rule 15–3–2 and AUTOSAR C++14 Rule A15-3-2
    return ::eoos::sys::ERROR_UNDEFINED;
}
