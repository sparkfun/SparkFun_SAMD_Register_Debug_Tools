/*------------------------------------------------------------------------------
SAMD_Globals.cpp

Define the globals and the library initialization routine.

License: MIT. Please see LICENSE.md for more details
------------------------------------------------------------------------------*/

#if defined(ARDUINO_ARCH_SAMD)

#include "SparkFun_SAMD_Register_Debug_Tools.h"

Print * samdRdtPrint;

void samdRegisterDebugToolsInit(Print *print)
{
    samdRdtPrint = print;
}

#endif  //ARDUINO_ARCH_SAMD
