/*------------------------------------------------------------------------------
SAMD_GPIO.cpp

Decode and print the values of the SAMD21 GPIO registers.

License: MIT. Please see LICENSE.md for more details
------------------------------------------------------------------------------*/

#if defined(ARDUINO_ARCH_SAMD)

#include "SparkFun_SAMD_Register_Debug_Tools.h"

void * const samdGpioBaseAddress = (void *)0x41004400;
const uint32_t samdGpioPorts[3] = {0xdbffffff, 0xc0c3ffff, 0};

void * samdGpioValidatePortLetter(char portLetter)
{
    void * gpioRegs;

    //Section 22.7, GPIO registers
    portLetter = toupper(portLetter);
    if ((portLetter < 'A') || (portLetter > 'C'))
    {
        samdRdtPrint->println("ERROR - Invalid port letter, needs to be in the range A - C");
        return NULL;
    }

    //Get the base address of the GPIO port register set
    gpioRegs = samdGpioBaseAddress + ((portLetter - 'A') << 7);
    return gpioRegs;
}

uint32_t samdGpioValidatePin(char portLetter, int pinNumber)
{
    uint32_t pinMask;

    //Determine if this is a valid pin number
    if ((pinNumber >= 0) && (pinNumber < 32))
    {
        pinMask = 1 << pinNumber;
        if (samdGpioPorts[portLetter - 'A'] & pinMask)
            return pinMask;
        samdRdtPrint->print("ERROR - pin ");
        samdRdtPrint->print(pinNumber);
        samdRdtPrint->print(" is not supported by port ");
        samdRdtPrint->write(portLetter);
        samdRdtPrint->println();
    }

    //Invalid pin number specified
    samdRdtPrint->println("ERROR - Invalid port number, needs to be in the range 0 - 32");
    return 0;
}

int samdGpioDirGet(char portLetter, int pinNumber)
{
    SAMD_GPIO_REGS * gpioRegs;
    uint32_t pinMask;

    //Validate the portLetter
    gpioRegs = (SAMD_GPIO_REGS *)samdGpioValidatePortLetter(portLetter);
    if (!gpioRegs)
        return 0;

    //Validate the pinNumber
    pinMask = samdGpioValidatePin(portLetter, pinNumber);
    if (!pinMask)
        return 0;

    //Section 22.7, DIR register
    return (gpioRegs->DIR & pinMask) ? 1 : 0;
}

int samdGpioDvrstrGet(char portLetter, int pinNumber)
{
    uint8_t * config;
    SAMD_GPIO_REGS * gpioRegs;
    uint32_t pinMask;

    //Validate the portLetter
    gpioRegs = (SAMD_GPIO_REGS *)samdGpioValidatePortLetter(portLetter);
    if (!gpioRegs)
        return 0;

    //Validate the pinNumber
    pinMask = samdGpioValidatePin(portLetter, pinNumber);
    if (!pinMask)
        return 0;

    //Section 22.7, PINCFG register
    config = &gpioRegs->PINCFG0;
    return (config[pinNumber] & 0x40) ? 1 : 0;
}

int samdGpioInGet(char portLetter, int pinNumber)
{
    SAMD_GPIO_REGS * gpioRegs;
    uint32_t pinMask;

    //Validate the portLetter
    gpioRegs = (SAMD_GPIO_REGS *)samdGpioValidatePortLetter(portLetter);
    if (!gpioRegs)
        return 0;

    //Validate the pinNumber
    pinMask = samdGpioValidatePin(portLetter, pinNumber);
    if (!pinMask)
        return 0;

    //Section 22.7, IN register
    return (gpioRegs->IN & pinMask) ? 1 : 0;
}

int samdGpioInenGet(char portLetter, int pinNumber)
{
    uint8_t * config;
    SAMD_GPIO_REGS * gpioRegs;
    uint32_t pinMask;

    //Validate the portLetter
    gpioRegs = (SAMD_GPIO_REGS *)samdGpioValidatePortLetter(portLetter);
    if (!gpioRegs)
        return 0;

    //Validate the pinNumber
    pinMask = samdGpioValidatePin(portLetter, pinNumber);
    if (!pinMask)
        return 0;

    //Section 22.7, PINCFG register
    config = &gpioRegs->PINCFG0;
    return (config[pinNumber] & 2) ? 1 : 0;
}

int samdGpioMuxGet(char portLetter, int pinNumber)
{
    uint8_t * config;
    SAMD_GPIO_REGS * gpioRegs;
    uint32_t pinMask;
    uint8_t * pmux;

    //Validate the portLetter
    gpioRegs = (SAMD_GPIO_REGS *)samdGpioValidatePortLetter(portLetter);
    if (!gpioRegs)
        return 0;

    //Validate the pinNumber
    pinMask = samdGpioValidatePin(portLetter, pinNumber);
    if (!pinMask)
        return 0;

    //Section 22.7, PINCFG register
    config = &gpioRegs->PINCFG0;
    if (config[pinNumber] & 1)
    {
        //Get the MUX value
        pmux = &gpioRegs->PMUX0;
        return (pmux[pinNumber >> 1] >> ((pinNumber & 1) ? 4 : 0)) & 0xf;
    }
    return 0;
}

int samdGpioMuxenGet(char portLetter, int pinNumber)
{
    uint8_t * config;
    SAMD_GPIO_REGS * gpioRegs;
    uint32_t pinMask;
    uint8_t * pmux;

    //Validate the portLetter
    gpioRegs = (SAMD_GPIO_REGS *)samdGpioValidatePortLetter(portLetter);
    if (!gpioRegs)
        return 0;

    //Validate the pinNumber
    pinMask = samdGpioValidatePin(portLetter, pinNumber);
    if (!pinMask)
        return 0;

    //Section 22.7, PINCFG register
    config = &gpioRegs->PINCFG0;
    return config[pinNumber] & 1;
}

int samdGpioOutGet(char portLetter, int pinNumber)
{
    SAMD_GPIO_REGS * gpioRegs;
    uint32_t pinMask;

    //Validate the portLetter
    gpioRegs = (SAMD_GPIO_REGS *)samdGpioValidatePortLetter(portLetter);
    if (!gpioRegs)
        return 0;

    //Validate the pinNumber
    pinMask = samdGpioValidatePin(portLetter, pinNumber);
    if (!pinMask)
        return 0;

    //Section 22.7, OUT register
    return (gpioRegs->OUT & pinMask) ? 1 : 0;
}

int samdGpioPullenGet(char portLetter, int pinNumber)
{
    uint8_t * config;
    SAMD_GPIO_REGS * gpioRegs;
    uint32_t pinMask;

    //Validate the portLetter
    gpioRegs = (SAMD_GPIO_REGS *)samdGpioValidatePortLetter(portLetter);
    if (!gpioRegs)
        return 0;

    //Validate the pinNumber
    pinMask = samdGpioValidatePin(portLetter, pinNumber);
    if (!pinMask)
        return 0;

    //Section 22.7, PINCFG register
    config = &gpioRegs->PINCFG0;
    return (config[pinNumber] & 4) ? 1 : 0;
}

void samdGpioPortConfig(char portLetter)
{
    SAMD_GPIO_REGS * gpioRegs;
    int pinNumber;
    int physicalPin;

    //Validate the portLetter
    gpioRegs = (SAMD_GPIO_REGS *)samdGpioValidatePortLetter(portLetter);
    if (!gpioRegs)
        return;

    //Verify that this port has pins
    if (!samdGpioPorts[portLetter - 'A'])
        return;

    //Display the port name
    for (pinNumber = 0; pinNumber < 32; pinNumber++)
    {
        //Display the pin configuration
        if (samdGpioPorts[portLetter - 'A'] & (1 << pinNumber))
        {
            samdRdtPrint->print("Port ");
            if (pinNumber <= 9)
                samdRdtPrint->write(' ');
            samdRdtPrint->write(portLetter);
            samdRdtPrint->print(pinNumber);
            samdRdtPrint->print(" Pin ");
            if (portLetter == 'A')
                physicalPin = samdGpioAPin[pinNumber];
            else
                physicalPin = samdGpioBPin[pinNumber];
            if (physicalPin < 10)
                samdRdtPrint->write(' ');
            samdRdtPrint->print(physicalPin);
            if (samdGpioMuxenGet(portLetter, pinNumber))
            {
                samdRdtPrint->print(" MUX:");
                if (portLetter == 'A')
                    samdRdtPrint->print(samdGpioAMux[pinNumber][samdGpioMuxGet(portLetter, pinNumber)]);
                else
                    samdRdtPrint->print(samdGpioBMux[pinNumber][samdGpioMuxGet(portLetter, pinNumber)]);
                samdRdtPrint->write(',');
            }
            else
                samdRdtPrint->print(" GPIO");
            samdRdtPrint->print(samdGpioDirGet(portLetter, pinNumber) ? " 1(Output)" : "  0(Input)");
            samdRdtPrint->print(", INEN:");
            samdRdtPrint->print(samdGpioInenGet(portLetter, pinNumber));
            samdRdtPrint->print(", PULLEN:");
            samdRdtPrint->print(samdGpioPullenGet(portLetter, pinNumber));
            samdRdtPrint->print(", OUT:");
            samdRdtPrint->print(samdGpioOutGet(portLetter, pinNumber));
            samdRdtPrint->print(", IN:");
            samdRdtPrint->print(samdGpioInGet(portLetter, pinNumber));
            samdRdtPrint->print(", DRVSTR:");
            samdRdtPrint->println(samdGpioDvrstrGet(portLetter, pinNumber));
        }
    }
}

void samdGpioPortsConfig()
{
    samdGpioPortConfig('A');
    samdGpioPortConfig('B');
    samdGpioPortConfig('C');
}

#endif  //ARDUINO_ARCH_SAMD
