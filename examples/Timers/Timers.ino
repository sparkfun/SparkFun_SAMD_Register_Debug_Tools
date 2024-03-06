/*------------------------------------------------------------------------------
Timers.ino

Decode and print the values of the SAMD21 TCC and TC registers.

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
    SerialUSB.println("Timers Example");

    // Initializee the SAMD register debug tools library
    samdRegisterDebugToolsInit(&SerialUSB);

    SerialUSB.println("======================================================================");
    SerialUSB.println("Initial TCC and TC setup");
    SerialUSB.println("======================================================================");

    // Display the TCC and TC registers
    samdTimerConfigs();

    SerialUSB.println("======================================================================");
    SerialUSB.println("GCLKGEN4 setup");
    SerialUSB.println("======================================================================");

    // Initialize the generic clock (GCLKGEN4) to generate 16 MHz
    REG_GCLK_GENDIV = GCLK_GENDIV_ID(4)         // Input is GCLK4
                    | GCLK_GENDIV_DIV(3);       // Freq: 48MHz / 3 = 16 MHz

    REG_GCLK_GENCTRL = GCLK_GENCTRL_ID(4)       // Select GCLK4
                     | GCLK_GENCTRL_SRC_DFLL48M // Input is 48 MHz
                     | GCLK_GENCTRL_IDC         // 50/50 duty cycle
                     | GCLK_GENCTRL_GENEN;      // Output is enabled

    // Display the generic clock generator configuration
    samdGclkGclkGenConfig(4);

    SerialUSB.println("======================================================================");
    SerialUSB.println("TC4 and TC5 clock setup");
    SerialUSB.println("======================================================================");

    // Feed GCLK4 to TC4 and TC5
    REG_GCLK_CLKCTRL = GCLK_CLKCTRL_GEN_GCLK4   // Select frequency input
                     | GCLK_CLKCTRL_ID_TC4_TC5  // Send to TC4 and TC5
                     | GCLK_CLKCTRL_CLKEN;      // Turn on clock frequency

    // Display the peripheral clock configuration
    samdGclkPeripheralClock(SAMD_GCLK_CLKCTRL_ID_TC4_TC5);

    SerialUSB.println("======================================================================");
    SerialUSB.println("TC4 and TC5 setup");
    SerialUSB.println("======================================================================");

    // Configure Count Mode (32-bit), using both TC4 and TC5
    TC4->COUNT32.CTRLA.bit.MODE = 2;

    // Disable the prescaler (divide by 1)
    TC4->COUNT32.CTRLA.bit.PRESCALER = 0;

    // Configure TC4 Compare Mode for compare channel 0
    TC4->COUNT32.CTRLA.bit.WAVEGEN = 0x1;   // Match operation
    TC4->COUNT32.CTRLBSET.bit.CMD = 1;      // Zero the counter upon match
    TC4->COUNT32.CC[0].reg = 400 * 1000 * 16;   // Match at 400 milliseconds

    // Disable all TC4 interrupts
    TC4->COUNT32.INTENCLR.bit.MC1 = 1;
    TC4->COUNT32.INTENCLR.bit.SYNCRDY = 1;
    TC4->COUNT32.INTENCLR.bit.ERR = 1;
    TC4->COUNT32.INTENCLR.bit.OVF = 1;

    // Enable TC4 match interrupt on channel 0
    TC4->COUNT32.INTENSET.bit.MC0 = 0x1;

    // Enable TC4
    TC4->COUNT32.CTRLA.bit.ENABLE = 1;

    // Wait until TC4 is enabled
    while(TC4->COUNT32.STATUS.bit.SYNCBUSY == 1);

    // Clear previous TC4 interrupts
    TC4->COUNT32.INTFLAG.bit.MC0 = 1;

    // Display the TC4 and TC5 registers
    samdTcConfig(SAMD_TC_4_BASE_ADDRESS);
    samdTcConfig(SAMD_TC_5_BASE_ADDRESS);

    // Route the interrupt to TC4_Handler
    NVIC_DisableIRQ(TC4_IRQn);
    NVIC_ClearPendingIRQ(TC4_IRQn);
    NVIC_SetPriority(TC4_IRQn, 0);
    NVIC_EnableIRQ(TC4_IRQn);

    SerialUSB.println("======================================================================");
    SerialUSB.println("TC4 interrupts");
    SerialUSB.println("======================================================================");
}

// Idle loop for the CPU
void loop()
{
}

//ISR that handles the TC4 interrupt
void TC4_Handler()
{
    static uint32_t lastMillis;
    uint32_t currentMillis;

    // Clear the interrupt
    TC4->COUNT32.INTFLAG.bit.MC0 = 1;

    // Remember the time when the interrupt occurred
    currentMillis = millis();

    // Adjust the frequency after 10 seconds to interrupt every 5 Sec
    if (currentMillis >= (10 * 1000))
        TC4->COUNT32.CC[0].reg = 5 * 1000 * 1000 * 16;

    // Print the test time
    int seconds = currentMillis / 1000;
    int milliseconds = currentMillis - (seconds * 1000);
    int minutes = seconds / 60;
    seconds -= minutes * 60;
    int hours = minutes / 60;
    minutes -= hours * 60;
    if (hours < 100)
      SerialUSB.print(" ");
    if (hours < 10)
      SerialUSB.print(" ");
    SerialUSB.print(hours);
    SerialUSB.print(":");
    if (minutes < 10)
      SerialUSB.print("0");
    SerialUSB.print(minutes);
    SerialUSB.print(":");
    if (seconds < 10)
      SerialUSB.print("0");
    SerialUSB.print(seconds);
    SerialUSB.print(".");
    if (milliseconds < 100)
      SerialUSB.print("0");
    if (milliseconds < 10)
      SerialUSB.print("0");
    SerialUSB.print(milliseconds);
    if (lastMillis)
    {
        SerialUSB.print(", ");

        // Print the duration between interrupts
        SerialUSB.print(currentMillis - lastMillis);
        SerialUSB.print(" mSec");
    }
    SerialUSB.println();

    // Remember the last time this interrupt occurred
    lastMillis = currentMillis;
}
