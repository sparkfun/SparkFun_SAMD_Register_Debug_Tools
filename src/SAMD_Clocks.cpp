/*------------------------------------------------------------------------------
SAMD_Clocks.cpp

Decode and print the values of the SAMD21 clock registers.

License: MIT. Please see LICENSE.md for more details
------------------------------------------------------------------------------*/

#if defined(ARDUINO_ARCH_SAMD)

#include "SparkFun_SAMD_Register_Debug_Tools.h"

static const char * const samdGclkPeripheral[] =
{
    "GCLK_DFLL48M_REF",     //  0
    "GCLK_DPLL",            //  1
    "GCLK_DPLL_32K",        //  2
    "GCLK_WDT",             //  3
    "GCLK_RTC",             //  4
    "GCLK_EIC",             //  5
    "GCLK_USB",             //  6
    "GCLK_EVSYS_CHANNEL_0", //  7
    "GCLK_EVSYS_CHANNEL_1", //  8
    "GCLK_EVSYS_CHANNEL_2", //  9
    "GCLK_EVSYS_CHANNEL_3", // 10
    "GCLK_EVSYS_CHANNEL_4", // 11
    "GCLK_EVSYS_CHANNEL_5", // 12
    "GCLK_EVSYS_CHANNEL_6", // 13
    "GCLK_EVSYS_CHANNEL_7", // 14
    "GCLK_EVSYS_CHANNEL_8", // 15
    "GCLK_EVSYS_CHANNEL_9", // 16
    "GCLK_EVSYS_CHANNEL_10",// 17
    "GCLK_EVSYS_CHANNEL_11",// 18
    "GCLK_SERCOMx_SLOW",    // 19
    "GCLK_SERCOM0_CORE",    // 20
    "GCLK_SERCOM1_CORE",    // 21
    "GCLK_SERCOM2_CORE",    // 22
    "GCLK_SERCOM3_CORE",    // 23
    "GCLK_SERCOM4_CORE",    // 24
    "GCLK_SERCOM5_CORE",    // 25
    "GCLK_TCC0, GCLK_TCC1", // 26
    "GCLK_TCC2, GCLK_TC3",  // 27
    "GCLK_TC4, GCLK_TC5",   // 28
    "GCLK_TC6, GCLK_TC7",   // 29
    "GCLK_ADC",             // 30
    "GCLK_AC_DIG",          // 31
    "GCLK_AC_ANA",          // 32
    "GCLK_DAC",             // 33
    "GCLK_PTC",             // 34
    "GCLK_I2S_0",           // 35
    "GCLK_I2S_1"            // 36
};

static const uint16_t samdGclkPmClkEn0[] =
{
    0, 0, 0, 0x418, 0x518, 0x618, 0x614, 0x120,
    0x120, 0x120, 0x120, 0x120, 0x120, 0x120, 0x120, 0x120,
    0x120, 0x120, 0x120, 0, 0x220, 0x320, 0x420, 0x520,
    0x620, 0x720, 0x820, 0xa20, 0xc20, 0xe20, 0x1020, 0x1120,
    0x1120, 0x1220, 0x1320, 0x1420, 0x1420
};

static const uint16_t samdGclkPmClkEn1[] =
{
    0, 0, 0, 0, 0, 0, 0x61c, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0x920, 0xb20, 0xd20, 0xf20, 0, 0,
    0, 0, 0, 0, 0
};

static const char * const samdGclkClockSrc[] =
{
    "XOSC", "GCLKIN", "GCLKGEN1", "OSCULP32K", "OSC32K", "XOSC32K",
    "OSC8M", "DFLL48M", "FDPLL96M"
};

static const uint32_t samdGclkClockFrequency[] =
{
    0,                  // Unknown
    0,                  // Unknown
    0,                  // Unknown
    32768,              // 32 KHz
    32768,              // 32 KHz
    32768,              // 32 KHz
    8 * 1000 * 1000,    //  8 MHz
    48 * 1000 * 1000,   // 48 MHz
    96 * 1000 * 1000    // 96 MHz
};

static const bool samdGclkFinalClockSrc[] =
{
    true, true, false, true, true, true, true, true, true
};

void samdGclkCtrl(void)
{
    // Get the register value
    uint8_t regValue = samdGclk->CTRL;

    // Print the register value
    samdRdtPrint->print("  CTRL: 0x");
    samdRdtPrint->print(regValue, HEX);

    // Decode and print the register value
    if (regValue & SAMD_GCLK_CTRL_SWRST)
        samdRdtPrint->print(", SWRST");
    samdRdtPrint->println();
}

void samdGclkStatus(void)
{
    uint8_t regValue;

    // Get the register value
    regValue = samdGclk->STATUS;

    // Print the register value
    samdRdtPrint->print("  STATUS: 0x");
    samdRdtPrint->print(regValue, HEX);

    // Decode and print the register value
    if (regValue & SAMD_GCLK_STATUS_SYNCBUSY)
        samdRdtPrint->print(", SYNCBUSY");
    samdRdtPrint->println();
}

void samdGclkClkCtrl(uint8_t srcId)
{
    bool enabled;
    uint16_t regValue;
    int value;

    // Validate the srcId value
    if (srcId >= (sizeof(samdGclkPeripheral) / sizeof(samdGclkPeripheral[0])))
        return;

    // Get the register value
    samdGclk->CLKCTRL.u8 = srcId;
    regValue = samdGclk->CLKCTRL.u16;
    enabled = regValue & SAMD_GCLK_CLKCTRL_CLKEN;

    // Print the register value
    samdRdtPrint->print(samdGclkPeripheral[srcId]);
    samdRdtPrint->print(" clock: 0x");
    samdRdtPrint->print(regValue, HEX);

    // Decode and print the register value
    if (regValue & SAMD_GCLK_CLKCTRL_WRTLOCK)
        samdRdtPrint->print(", Locked");
    samdRdtPrint->println(enabled ? ", Enabled" : ", Disabled");
    if (enabled)
    {
        samdRdtPrint->print("  GEN: ");
        value = (regValue & SAMD_GCLK_CLKCTRL_GEN) >> 8;
        if (value <= 8)
        {
          samdRdtPrint->print("GCLKGEN");
          samdRdtPrint->println(value);
        }
        else
          samdRdtPrint->println("Reserved");

        samdRdtPrint->print("  ID: ");
        samdRdtPrint->print(srcId);
        samdRdtPrint->print(", ");
        samdRdtPrint->println(samdGclkPeripheral[srcId]);
    }
}

// Get the divisor value
uint32_t samdGclkGetDiv(uint8_t genId)
{
    uint32_t div;
    uint32_t gendiv;
    uint32_t genctrl;

    // Validate the genId value
    if (genId > 8)
        return 0;

    // Get the register values
    samdGclk->GENCTRL.u8 = genId;
    samdGclk->GENDIV.u8 = genId;
    genctrl = samdGclk->GENCTRL.u32;
    gendiv = samdGclk->GENDIV.u32;

    // Extract the divisor
    div = (gendiv & SAMD_GCLK_GENDIV_DIV) >> 8;

    // Limit the bits depending upon the ID value
    switch (genId)
    {
        default:
            div &= 0xff;
            break;

        case 1:
            break;

        case 2:
            div &= 0x1f;
            break;
    }

    // Determine if div is used as an exponent
    if (genctrl & SAMD_GCLK_GENCTRL_DIVSEL)
        div = 1 << (div + 1);
    else if (!div)
        div = 1;
    return div;
}

void samdGclkGenCtrl(uint8_t genId)
{
    uint32_t div;
    uint32_t regValue;
    uint32_t value;

    // Validate the genId value
    if (genId > 8)
        return;

    // Get the register value
    div = samdGclkGetDiv(genId);
    regValue = samdGclk->GENCTRL.u32;

    // Print the register value
    samdRdtPrint->print("  GENCTRL: 0x");
    samdRdtPrint->print(regValue, HEX);
    samdRdtPrint->println();

    // Decode and print the register value
    samdRdtPrint->print("    RUNSTDBY: Clock generator ");
    samdRdtPrint->print((regValue & SAMD_GCLK_GENCTRL_RUNSTDBY) ? "running" : "stopped");
    samdRdtPrint->println(" in standby");

    samdRdtPrint->print("    DIVSEL: Clock source / ");
    samdRdtPrint->println(div);

    samdRdtPrint->print("    OE: Output ");
    samdRdtPrint->println((regValue & SAMD_GCLK_GENCTRL_OE) ? "enabled" : "disabled");

    samdRdtPrint->print("    OOV: Output ");
    samdRdtPrint->print((regValue & SAMD_GCLK_GENCTRL_OOV) ? 1: 0);
    samdRdtPrint->println(" when clock not in use");

    samdRdtPrint->print("    IDC: Duty cycle ");
    samdRdtPrint->println((((~div) & 1) || (regValue & SAMD_GCLK_GENCTRL_IDC)) ? "50/50" : "is not 50/50");

    samdRdtPrint->print("    GENEN: Output ");
    samdRdtPrint->println((regValue & SAMD_GCLK_GENCTRL_GENEN) ? "enabled" : "disabled");

    samdRdtPrint->print("    SRC: ");
    value = (regValue & SAMD_GCLK_GENCTRL_SRC) >> 8;
    if (value < (sizeof(samdGclkClockSrc) / sizeof(samdGclkClockSrc[0])))
      samdRdtPrint->println(samdGclkClockSrc[value]);
    else
      samdRdtPrint->println("Reserved");

    samdRdtPrint->print("    ID: ");
    value = regValue & SAMD_GCLK_GENCTRL_ID;
    if (value <= 8)
    {
      samdRdtPrint->print("GCLKGEN");
      samdRdtPrint->println(value);
    }
    else
      samdRdtPrint->println("Reserved");
}

void samdGclkGenDiv(uint8_t genId)
{
    uint32_t div;
    uint32_t regValue;
    uint32_t value;

    // Validate the genId value
    if (genId > 8)
        return;

    // Get the register value
    samdGclk->GENDIV.u8 = genId;
    regValue = samdGclk->GENDIV.u32;

    // Print the register value
    samdRdtPrint->print("  GENDIV: 0x");
    samdRdtPrint->print(regValue, HEX);
    samdRdtPrint->println();

    // Decode and print the register value
    div = (regValue & SAMD_GCLK_GENDIV_DIV) >> 8;
    samdRdtPrint->print("  DIV: ");
    samdRdtPrint->println(div);

    samdRdtPrint->print("    ID: ");
    value = regValue & SAMD_GCLK_GENDIV_ID;
    if (value <= 8)
    {
      samdRdtPrint->print("GCLKGEN");
      samdRdtPrint->println(value);
    }
    else
      samdRdtPrint->println("Reserved");
}

void samdGclkGclkGenConfig(uint8_t genId)
{
    bool enabled;
    uint32_t genctrl;

    // Validate the genId value
    if (genId > 8)
        return;

    // Determine if the clock generator is enabled
    samdGclk->GENCTRL.u8 = genId;
    genctrl = samdGclk->GENCTRL.u32;
    enabled = genctrl & SAMD_GCLK_GENCTRL_GENEN;

    // Print the register name
    samdRdtPrint->print("GCLKGEN");
    samdRdtPrint->print(genId);
    samdRdtPrint->println(enabled ? ", Enabled" : ", Disabled");

    // Decode and print the registers
    if (enabled)
    {
        samdGclkGenCtrl(genId);
        samdGclkGenDiv(genId);
    }
}

void samdGclkConfig(void)
{
    int id;

    // Print the generic clock generator configurations
    for (id = 0; id < 16; id++)
        samdGclkGclkGenConfig(id);

    // Print the peripheral clock configurations
    for (id = 0; id < 32; id++)
        samdGclkClkCtrl(id);
}

void samdGclkBusClock(uint16_t clkEn)
{
    uint32_t bit;
    uint32_t bitNumber;
    uint32_t offset;
    uint32_t regValue;

    if (clkEn)
    {
        // Break up the clock enable value
        bitNumber = clkEn >> 8;
        offset = clkEn & 0xff;

        // Read the register value
        regValue = *(uint32_t *)(SAMD_PM_BASE_ADDRESS + offset);
        bit = (regValue >> bitNumber) & 1;

        // Print the clock state
        if (offset == 0x14)
            samdRdtPrint->print(", AHB clock ");
        else
            samdRdtPrint->print(", APB clock ");
        samdRdtPrint->print(bit ? "enabled" : "disabled");
    }
}

void samdRdtPrintFrequency(uint32_t frequency)
{
    uint32_t GHz;
    uint32_t MHz;
    uint32_t KHz;
    uint32_t Hz;
    uint32_t a;
    uint32_t b;
    const char * units;

    // Breakup the clock frequency
    GHz = frequency / (1000 * 1000 * 1000);
    MHz = frequency / (1000 * 1000);
    KHz = frequency / 1000;
    Hz = frequency - KHz * 1000;
    KHz -= MHz * 1000;
    MHz -= GHz * 1000;

    // Determine the units
    if (GHz)
    {
        a = GHz;
        b = MHz;
        units = " GHz";
    }
    else if (MHz)
    {
        a = MHz;
        b = KHz;
        units = " MHz";
    }
    else if (KHz)
    {
        a = KHz;
        b = Hz;
        units = " KHz";
    }
    else
    {
        a = Hz;
        b = 0;
        units = " Hz";
    }

    // Print the frequency
    samdRdtPrint->print(a);
    if (b)
    {
        samdRdtPrint->print(".");
        if (b < 100)
            samdRdtPrint->print("0");
        if (b < 10)
            samdRdtPrint->print("0");
        samdRdtPrint->print(b);
    }
    samdRdtPrint->print(units);
}

uint32_t samdGclkClock(uint8_t genId)
{
    uint32_t div;
    bool enabled;
    uint32_t frequency;
    uint32_t genctrl;
    uint8_t srcId;

    // Validate the genId value
    if (genId >= (sizeof(samdGclkClockSrc) / sizeof(samdGclkClockSrc[0])))
        return 0;

    // Get the register values
    samdGclk->GENCTRL.u8 = genId;
    genctrl = samdGclk->GENCTRL.u32;

    // Determine if this clock generator is enabled
    enabled = (genctrl & SAMD_GCLK_GENCTRL_GENEN) ? true : false;
    frequency = 0;
    if (enabled)
    {
        // Determine if this is the final source
        srcId = (genctrl & SAMD_GCLK_GENCTRL_SRC) >> 8;
        if (!samdGclkFinalClockSrc[srcId])
        {
            frequency = samdGclkClock(srcId);
            samdRdtPrint->print(" --> ");
        }

        // Get the divisor
        div = samdGclkGetDiv(genId);

        // Print the clock source
        samdRdtPrint->print(samdGclkClockSrc[srcId]);
        samdRdtPrint->print(" / ");
        samdRdtPrint->print(div);

        // Print the clock frequency if known
        if (frequency)
            frequency /= div;
        else
            frequency = samdGclkClockFrequency[srcId] / div;
        if (frequency)
        {
            samdRdtPrint->print(" (");
            samdRdtPrintFrequency(frequency);
            samdRdtPrint->print(")");
        }
    }
    else
        samdRdtPrint->print("Disabled");
    return frequency;
}

void samdGclkPeripheralClock(uint8_t srcId)
{
    uint16_t clkctrl;
    bool enabled;
    uint8_t genId;

    // Validate the srcId value
    if (srcId >= (sizeof(samdGclkPeripheral) / sizeof(samdGclkPeripheral[0])))
        return;

    // Get the register value
    samdGclk->CLKCTRL.u8 = srcId;
    clkctrl = samdGclk->CLKCTRL.u16;

    // Determine if the clock is enabled
    enabled = (clkctrl & SAMD_GCLK_CLKCTRL_CLKEN) ? true : false;
    if (enabled)
    {
        // Trace the generic clock
        genId = (clkctrl & SAMD_GCLK_CLKCTRL_GEN) >> 8;
        samdGclkClock(genId);

        // Print the generic clock name
        samdRdtPrint->print(" --> GENCLK");
        samdRdtPrint->print(genId);
    }
    else
        samdRdtPrint->print("Disabled");

    // Print the peripheral name
    samdRdtPrint->print(" --> ");
    samdRdtPrint->print(samdGclkPeripheral[srcId]);

    // Display the clocks
    samdGclkBusClock(samdGclkPmClkEn0[srcId]);
    samdGclkBusClock(samdGclkPmClkEn1[srcId]);
    samdRdtPrint->println();
}

void samdGclkPeripheralClocks(void)
{
    uint8_t srcId;

    // Display the peripheral clocks
    samdRdtPrint->println("Peripheral Clocks");
    for (srcId = 0; srcId < 32; srcId++)
    {
        // Validate the srcId value
        if (srcId >= (sizeof(samdGclkPeripheral) / sizeof(samdGclkPeripheral[0])))
            continue;

        // Print the peripheral clock summary
        samdRdtPrint->print("  ");
        samdGclkPeripheralClock(srcId);
    }
}

void samdGclkgenClock(uint8_t genId)
{
    // Validate the genId value
    if (genId >= (sizeof(samdGclkClockSrc) / sizeof(samdGclkClockSrc[0])))
        return;

    // Print the clock source
    samdGclkClock(genId);
    samdRdtPrint->print(" --> GCLKGEN");
    samdRdtPrint->println(genId);
}

void samdGclkgenClocks(void)
{
    int genId;

    // Print the generic clock generator configurations
    samdRdtPrint->println("Global Clocks Generators");
    for (genId = 0; genId < 16; genId++)
    {
        // Validate the genId value
        if (genId >= (sizeof(samdGclkClockSrc) / sizeof(samdGclkClockSrc[0])))
            continue;

        // Print the generic clock generator summary
        samdRdtPrint->print("  ");
        samdGclkgenClock(genId);
    }
}

#endif  //ARDUINO_ARCH_SAMD
