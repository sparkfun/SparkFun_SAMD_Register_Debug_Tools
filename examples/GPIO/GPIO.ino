/*------------------------------------------------------------------------------
GPIO.ino

Decode and print the values of the SAMD21 GPIO registers.

License: MIT. Please see LICENSE.md for more details
------------------------------------------------------------------------------*/

#include "SparkFun_SAMD_Register_Debug_Tools.h"

// Initial entrypoint following any runtime library initialization
void setup()
{
    int index;
    uint16_t ctrlA;

    // Wait for serial to come online before printing
    SerialUSB.begin(57600);
    while (!SerialUSB);
    SerialUSB.println("GPIO Example");

    // Initializee the SAMD register debug tools library
    samdRegisterDebugToolsInit(&SerialUSB);

    // Display the GPIO registers
    samdGpioPortsConfig();
}

// Idle loop for the CPU
void loop()
{
}
