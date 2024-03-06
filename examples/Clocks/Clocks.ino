/*------------------------------------------------------------------------------
Clocks.ino

Decode and print the values of the SAMD21 clock registers.

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
    SerialUSB.println("Clocks Example");

    // Initializee the SAMD register debug tools library
    samdRegisterDebugToolsInit(&SerialUSB);

    SerialUSB.println("======================================================================");
    SerialUSB.println("Detailed GCLKGEN and peripheral clock setup");
    SerialUSB.println("======================================================================");

    samdGclkConfig();

    SerialUSB.println("======================================================================");
    SerialUSB.println("GCLKGEN summary");
    SerialUSB.println("======================================================================");

    samdGclkgenClocks();

    SerialUSB.println("======================================================================");
    SerialUSB.println("Peripheral clock summary");
    SerialUSB.println("======================================================================");

    samdGclkPeripheralClocks();
}

// Idle loop for the CPU
void loop()
{
}
