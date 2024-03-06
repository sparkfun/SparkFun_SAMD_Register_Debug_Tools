/*------------------------------------------------------------------------------
SparkFun_SAMD_Register_Debug_Tools.h

Declare the values and structures for the SAMD21.

License: MIT. Please see LICENSE.md for more details
------------------------------------------------------------------------------*/

#if defined(ARDUINO_ARCH_SAMD)
#ifndef __SPARKFUN_SAMD_REGISTER_DEBUG_TOOLS_H__
#define __SPARKFUN_SAMD_REGISTER_DEBUG_TOOLS_H__

#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>

#include <Arduino.h>

extern Print * samdRdtPrint;

void samdRegisterDebugToolsInit(Print *print = &Serial);

#define SAMD_INTERNAL_FLASH_BASE    0
#define SAMD_INTERNAL_RWW_BASE_ADDR 0x00400000

// SRAM
#define SAMD_SRAM_BASE_ADDRESS      0x20000000

// AHB-APB Bridge A
#define SAMD_PERIPHERALS_BASE_ADDR  0x40000000
#define SAMD_AHB_APB_BRIDGE_A_BASE  0x40000000
#define SAMD_PAC0_BASE_ADDRESS      0x40000000
#define SAMD_PM_BASE_ADDRESS        0x40000400
#define SAMD_SYSCTRL_BASE_ADDRESS   0x40000800
#define SAMD_GCLK_BASE_ADDRESS      0x40000c00
#define SAMD_WDT_BASE_ADDRESS       0x40001000
#define SAMD_RTC_BASE_ADDRESS       0x40001400
#define SAMD_EIC_BASE_ADDRESS       0x40001800

// AHB-APB Bridge B
#define SAMD_AHB_APB_BRIDGE_B_BASE  0x41000000
#define SAMD_PAC1_BASE_ADDRESS      0x41000000
#define SAMD_DSU_BASE_ADDRESS       0x41002000
#define SAMD_NVMCRTL_BASE_ADDRESS   0x41004000
#define SAMD_PORT_BASE_ADDRESS      0x41004400
#define SAMD_DMAC_BASE_ADDRESS      0x41004800
#define SAMD_USB_BASE_ADDRESS       0x41005000
#define SAMD_MTB_BASE_ADDRESS       0x41006000

// AHB-APB Bridge C
#define SAMD_AHB_APB_BRIDGE_C_BASE  0x42000000
#define SAMD_PAC2_BASE_ADDRESS      0x42000000
#define SAMD_EVSYS_BASE_ADDRESS     0x42000400
#define SAMD_SERCOM0_BASE_ADDRESS   0x42000800
#define SAMD_SERCOM1_BASE_ADDRESS   0x42000C00
#define SAMD_SERCOM2_BASE_ADDRESS   0x42001000
#define SAMD_SERCOM3_BASE_ADDRESS   0x42001400
#define SAMD_SERCOM4_BASE_ADDRESS   0x42001800
#define SAMD_SERCOM5_BASE_ADDRESS   0x42001C00
#define SAMD_TCC_0_BASE_ADDRESS     0x42002000
#define SAMD_TCC_1_BASE_ADDRESS     0x42002400
#define SAMD_TCC_2_BASE_ADDRESS     0x42002800
#define SAMD_TC_3_BASE_ADDRESS      0x42002c00
#define SAMD_TC_4_BASE_ADDRESS      0x42003000
#define SAMD_TC_5_BASE_ADDRESS      0x42003400
#define SAMD_TC_6_BASE_ADDRESS      0x42003800
#define SAMD_TC_7_BASE_ADDRESS      0x42003c00
#define SAMD_ADC_BASE_ADDRESS       0x42004000
#define SAMD_AC_BASE_ADDRESS        0x42004400
#define SAMD_DAC_BASE_ADDRESS       0x42004800
#define SAMD_PTC_BASE_ADDRESS       0x42004C00
#define SAMD_I2S_BASE_ADDRESS       0x42005000

// System
#define SAMD_SYSTEM_BASE_ADDRESS    0xe0000000
#define SAMD_SCS_BASE_ADDRESS       0xe000e000
#define SAMD_ROM_TABLE_BASE_ADDRESS 0xe00ff000

typedef struct _SAMD_GCLK_REGS
{
    uint8_t CTRL;       //0
    uint8_t STATUS;     //1
    union
    {
        uint8_t u8;
        uint16_t u16;
    } CLKCTRL;          //2
    union
    {
        uint8_t u8;
        uint32_t u32;
    } GENCTRL;          //4
    union
    {
        uint8_t u8;
        uint32_t u32;
    } GENDIV;           //8
} SAMD_GCLK_REGS;

SAMD_GCLK_REGS * const samdGclk = (SAMD_GCLK_REGS *)SAMD_GCLK_BASE_ADDRESS;

// Define the CTRL register
#define SAMD_GCLK_CTRL_SWRST        0x01

// Define the STATUS register
#define SAMD_GCLK_STATUS_SYNCBUSY   0x80

// Define the CLKCTRL register
#define SAMD_GCLK_CLKCTRL_WRTLOCK   0x8000
#define SAMD_GCLK_CLKCTRL_CLKEN     0x4000
#define SAMD_GCLK_CLKCTRL_GEN       0x0f00
#define SAMD_GCLK_CLKCTRL_ID        0x001f

#define SAMD_GCLK_CLKCTRL_GEN_GCLKGEN0      0
#define SAMD_GCLK_CLKCTRL_GEN_GCLKGEN1      0x0100
#define SAMD_GCLK_CLKCTRL_GEN_GCLKGEN2      0x0200
#define SAMD_GCLK_CLKCTRL_GEN_GCLKGEN3      0x0300
#define SAMD_GCLK_CLKCTRL_GEN_GCLKGEN4      0x0400
#define SAMD_GCLK_CLKCTRL_GEN_GCLKGEN5      0x0500
#define SAMD_GCLK_CLKCTRL_GEN_GCLKGEN6      0x0600
#define SAMD_GCLK_CLKCTRL_GEN_GCLKGEN7      0x0700
#define SAMD_GCLK_CLKCTRL_GEN_GCLKGEN8      0x0800

#define SAMD_GCLK_CLKCTRL_ID_DFLL48M_REF    0
#define SAMD_GCLK_CLKCTRL_ID_DPLL           0x0001
#define SAMD_GCLK_CLKCTRL_ID_DPLL_32K       0x0002
#define SAMD_GCLK_CLKCTRL_ID_WDT            0x0003
#define SAMD_GCLK_CLKCTRL_ID_RTC            0x0004
#define SAMD_GCLK_CLKCTRL_ID_EIC            0x0005
#define SAMD_GCLK_CLKCTRL_ID_USB            0x0006
#define SAMD_GCLK_CLKCTRL_ID_EVSYS_CH0      0x0007
#define SAMD_GCLK_CLKCTRL_ID_EVSYS_CH1      0x0008
#define SAMD_GCLK_CLKCTRL_ID_EVSYS_CH2      0x0009
#define SAMD_GCLK_CLKCTRL_ID_EVSYS_CH3      0x000a
#define SAMD_GCLK_CLKCTRL_ID_EVSYS_CH4      0x000b
#define SAMD_GCLK_CLKCTRL_ID_EVSYS_CH5      0x000c
#define SAMD_GCLK_CLKCTRL_ID_EVSYS_CH6      0x000d
#define SAMD_GCLK_CLKCTRL_ID_EVSYS_CH7      0x000e
#define SAMD_GCLK_CLKCTRL_ID_EVSYS_CH8      0x000f
#define SAMD_GCLK_CLKCTRL_ID_EVSYS_CH9      0x0010
#define SAMD_GCLK_CLKCTRL_ID_EVSYS_CH10     0x0011
#define SAMD_GCLK_CLKCTRL_ID_EVSYS_CH11     0x0012
#define SAMD_GCLK_CLKCTRL_ID_SERCOM_SLOW    0x0013
#define SAMD_GCLK_CLKCTRL_ID_SERCOM0_CORE   0x0014
#define SAMD_GCLK_CLKCTRL_ID_SERCOM1_CORE   0x0015
#define SAMD_GCLK_CLKCTRL_ID_SERCOM2_CORE   0x0016
#define SAMD_GCLK_CLKCTRL_ID_SERCOM3_CORE   0x0017
#define SAMD_GCLK_CLKCTRL_ID_SERCOM4_CORE   0x0018
#define SAMD_GCLK_CLKCTRL_ID_SERCOM5_CORE   0x0019
#define SAMD_GCLK_CLKCTRL_ID_TCC0_TCC1      0x001a
#define SAMD_GCLK_CLKCTRL_ID_TCC2_TC3       0x001b
#define SAMD_GCLK_CLKCTRL_ID_TC4_TC5        0x001c
#define SAMD_GCLK_CLKCTRL_ID_TC6_TC7        0x001d
#define SAMD_GCLK_CLKCTRL_ID_ADC            0x001e
#define SAMD_GCLK_CLKCTRL_ID_AC_DIG         0x001f
#define SAMD_GCLK_CLKCTRL_ID_AC_ANA         0x0020
#define SAMD_GCLK_CLKCTRL_ID_DAC            0x0021
#define SAMD_GCLK_CLKCTRL_ID_PTC            0x0022
#define SAMD_GCLK_CLKCTRL_ID_I2S_0          0x0023
#define SAMD_GCLK_CLKCTRL_ID_I2S_1          0x0024

// Define the GENCTRL register
#define SAMD_GCLK_GENCTRL_RUNSTDBY  0x00200000
#define SAMD_GCLK_GENCTRL_DIVSEL    0x00100000
#define SAMD_GCLK_GENCTRL_OE        0x00080000
#define SAMD_GCLK_GENCTRL_OOV       0x00040000
#define SAMD_GCLK_GENCTRL_IDC       0x00020000
#define SAMD_GCLK_GENCTRL_GENEN     0x00010000
#define SAMD_GCLK_GENCTRL_SRC       0x00001f00
#define SAMD_GCLK_GENCTRL_ID        0x0000000f

#define SAMD_GCLK_GENCTRL_SRC_XOSC      0
#define SAMD_GCLK_GENCTRL_SRC_GCLKIN    0x00000100
#define SAMD_GCLK_GENCTRL_SRC_GCLKGEN1  0x00000200
#define SAMD_GCLK_GENCTRL_SRC_OSCULP32K 0x00000300
#define SAMD_GCLK_GENCTRL_SRC_OSC32K    0x00000400
#define SAMD_GCLK_GENCTRL_SRC_XOSC32K   0x00000500
#define SAMD_GCLK_GENCTRL_SRC_OSC8M     0x00000600
#define SAMD_GCLK_GENCTRL_SRC_DFLL48M   0x00000700
#define SAMD_GCLK_GENCTRL_SRC_FDPLL96M  0x00000800

#define SAMD_GCLK_GENCTRL_ID_GCLKGEN0   0
#define SAMD_GCLK_GENCTRL_ID_GCLKGEN1   1
#define SAMD_GCLK_GENCTRL_ID_GCLKGEN2   2
#define SAMD_GCLK_GENCTRL_ID_GCLKGEN3   3
#define SAMD_GCLK_GENCTRL_ID_GCLKGEN4   4
#define SAMD_GCLK_GENCTRL_ID_GCLKGEN5   5
#define SAMD_GCLK_GENCTRL_ID_GCLKGEN6   6
#define SAMD_GCLK_GENCTRL_ID_GCLKGEN7   7
#define SAMD_GCLK_GENCTRL_ID_GCLKGEN8   8

// Define the GENDIV register
#define SAMD_GCLK_GENDIV_DIV        0x00ffff00
#define SAMD_GCLK_GENDIV_ID         0x0000000f

#define SAMD_GCLK_GENDIV_ID_GCLKGEN0    0
#define SAMD_GCLK_GENDIV_ID_GCLKGEN1    1
#define SAMD_GCLK_GENDIV_ID_GCLKGEN2    2
#define SAMD_GCLK_GENDIV_ID_GCLKGEN3    3
#define SAMD_GCLK_GENDIV_ID_GCLKGEN4    4
#define SAMD_GCLK_GENDIV_ID_GCLKGEN5    5
#define SAMD_GCLK_GENDIV_ID_GCLKGEN6    6
#define SAMD_GCLK_GENDIV_ID_GCLKGEN7    7
#define SAMD_GCLK_GENDIV_ID_GCLKGEN8    8

void samdGclkCtrl(void);
void samdGclkStatus(void);
void samdGclkClkCtrl(uint8_t srcId);
uint32_t samdGclkGetDiv(uint8_t genId);
void samdGclkGenCtrl(uint8_t genId);
void samdGclkGenDiv(uint8_t genId);
void samdGclkGclkGenConfig(uint8_t genId);
void samdGclkConfig(void);
void samdGclkPeripheralClock(uint8_t srcId);
void samdGclkPeripheralClocks(void);
void samdGclkgenClock(uint8_t genId);
void samdGclkgenClocks(void);

typedef struct _SAMD_GPIO_REGS
{
    uint32_t DIR;         //0x00
    uint32_t DIRCLR;      //0x04
    uint32_t DIRSET;      //0x08
    uint32_t DIRTGL;      //0x0c
    uint32_t OUT;         //0x10
    uint32_t OUTCLR;      //0x14
    uint32_t OUTSET;      //0x18
    uint32_t OUTTGL;      //0x1c
    uint32_t IN;          //0x20
    uint32_t CTRL;        //0x24
    uint32_t WRCONFIG;    //0x28
    uint32_t res_2c;      //0x2c
    uint8_t PMUX0;        //0x30
    uint8_t PMUX1;        //0x31
    uint8_t PMUX2;        //0x32
    uint8_t PMUX3;        //0x33
    uint8_t PMUX4;        //0x34
    uint8_t PMUX5;        //0x35
    uint8_t PMUX6;        //0x36
    uint8_t PMUX7;        //0x37
    uint8_t PMUX8;        //0x38
    uint8_t PMUX9;        //0x39
    uint8_t PMUX10;       //0x3a
    uint8_t PMUX11;       //0x3b
    uint8_t PMUX12;       //0x3c
    uint8_t PMUX13;       //0x3d
    uint8_t PMUX14;       //0x3e
    uint8_t PMUX15;       //0x3f
    uint8_t PINCFG0;      //0x40
    uint8_t PINCFG1;      //0x41
    uint8_t PINCFG2;      //0x42
    uint8_t PINCFG3;      //0x43
    uint8_t PINCFG4;      //0x44
    uint8_t PINCFG5;      //0x45
    uint8_t PINCFG6;      //0x46
    uint8_t PINCFG7;      //0x47
    uint8_t PINCFG8;      //0x48
    uint8_t PINCFG9;      //0x49
    uint8_t PINCFG10;     //0x4a
    uint8_t PINCFG11;     //0x4b
    uint8_t PINCFG12;     //0x4c
    uint8_t PINCFG13;     //0x4d
    uint8_t PINCFG14;     //0x4e
    uint8_t PINCFG15;     //0x4f
    uint8_t PINCFG16;     //0x50
    uint8_t PINCFG17;     //0x51
    uint8_t PINCFG18;     //0x52
    uint8_t PINCFG19;     //0x53
    uint8_t PINCFG20;     //0x54
    uint8_t PINCFG21;     //0x55
    uint8_t PINCFG22;     //0x56
    uint8_t PINCFG23;     //0x57
    uint8_t PINCFG24;     //0x58
    uint8_t PINCFG25;     //0x59
    uint8_t PINCFG26;     //0x5a
    uint8_t PINCFG27;     //0x5b
    uint8_t PINCFG28;     //0x5c
    uint8_t PINCFG29;     //0x5d
    uint8_t PINCFG30;     //0x5e
    uint8_t PINCFG31;     //0x5f
} SAMD_GPIO_REGS;

const char * const samdGpioAMux[32][8] =
{  //  A          B         C          D          E       F       G           H
   //  0          1         2          3          4       5       6           7
    {"EXTINT0",  "?",      "?",       "SERCOM1", "TCC2", "?",    "?",        "?"},        // PA0
    {"EXTINT1",  "?",      "?",       "SERCOM1", "TCC2", "?",    "?",        "?"},        // PA1
    {"EXTINT2",  "ANALOG", "?",       "?",       "?",    "?",    "?",        "?"},        // PA2
    {"EXTINT3",  "ANALOG", "?",       "?",       "?",    "?",    "?",        "?"},        // PA3
    {"EXTINT4",  "ANALOG", "?",       "SERCOM0", "TCC0", "?",    "?",        "?"},        // PA4
    {"EXTINT5",  "ANALOG", "?",       "SERCOM0", "TCC0", "?",    "?",        "?"},        // PA5
    {"EXTINT6",  "ANALOG", "?",       "SERCOM0", "TCC1", "?",    "?",        "?"},        // PA6
    {"EXTINT7",  "ANALOG", "?",       "SERCOM0", "TCC1", "?",    "I2S/SD0",  "?"},        // PA7
    {"NMI",      "ANALOG", "SERCOM0", "SERCOM2", "TCC0", "TCC1", "I2S/SD1",  "?"},        // PA8
    {"EXTINT9",  "ANALOG", "SERCOM0", "SERCOM2", "TCC0", "TCC1", "I2S/MCK0", "?"},        // PA9
    {"EXTINT10", "ANALOG", "SERCOM0", "SERCOM2", "TCC1", "TCC0", "I2S/SCK0", "GCLK_IO4"}, //PA10
    {"EXTINT11", "ANALOG", "SERCOM0", "SERCOM2", "TCC1", "TCC0", "I2S/FS0",  "GCLK_IO5"}, //PA11
    {"EXTINT12", "?",      "SERCOM2", "SERCOM4", "TCC2", "TCC0", "?",        "AC/CMP0"},  //PA12
    {"EXTINT13", "?",      "SERCOM2", "SERCOM4", "TCC2", "TCC0", "?",        "AC/CMP1"},  //PA13
    {"EXTINT14", "?",      "SERCOM2", "SERCOM4", "TC3",  "TCC0", "?",        "GCLK_IO0"}, //PA14
    {"EXTINT15", "?",      "SERCOM2", "SERCOM4", "TC3",  "TCC0", "?",        "GCLK_IO1"}, //PA15
    {"EXTINT0",  "ANALOG", "SERCOM1", "SERCOM3", "TCC2", "TCC0", "?",        "GCLK_IO2"}, //PA16
    {"EXTINT1",  "ANALOG", "SERCOM1", "SERCOM3", "TCC2", "TCC0", "?",        "GCLK_IO3"}, //PA17
    {"EXTINT2",  "ANALOG", "SERCOM1", "SERCOM3", "TC3",  "TCC0", "?",        "AC/CMP0"},  //PA18
    {"EXTINT3",  "ANALOG", "SERCOM1", "SERCOM3", "TC3",  "TCC0", "?",        "AC/CMP1"},  //PA19
    {"EXTINT4",  "ANALOG", "SERCOM5", "SERCOM3", "TC7",  "TCC0", "I2S/SCK0", "GCLK_IO4"}, //PA20
    {"EXTINT5",  "ANALOG", "SERCOM5", "SERCOM3", "TC7",  "TCC0", "I2S/FS0",  "GCLK_IO5"}, //PA21
    {"EXTINT6",  "ANALOG", "SERCOM3", "SERCOM5", "TC4",  "TCC0", "USB/SOF",  "GCLK_IO6"}, //PA22
    {"EXTINT7",  "ANALOG", "SERCOM3", "SERCOM5", "TC4",  "TCC0", "?",        "GCLK_IO7"}, //PA23
    {"EXTINT12", "?",      "SERCOM3", "SERCOM5", "TC5",  "TCC1", "USB/DM",   "?"},        //PA24
    {"EXTINT13", "?",      "SERCOM3", "SERCOM5", "TC5",  "TCC1", "USB/DP",   "?"},        //PA25
    {"?",        "?",      "?",       "?",       "?",    "?",    "?",        "?"},        //PA26
    {"EXTINT15", "?",      "?",       "?",       "?",    "?",    "?",        "GCLK_IO0"}, //PA27
    {"EXTINT8",  "?",      "?",       "?",       "?",    "?",    "?",        "GCLK_IO0"}, //PA28
    {"?",        "?",      "?",       "?",       "?",    "?",    "?",        "?"},        //PA29
    {"EXTINT10", "?",      "?",       "SERCOM1", "TCC1", "?",    "SWCLK",    "GCLK_IO0"}, //PA30
    {"EXTINT11", "?",      "?",       "SERCOM1", "TCC1", "?",    "SWDIO",    "?"},        //PA31
};

const char * const samdGpioBMux[32][8] =
{  //  A          B         C          D          E       F       G           H
   //  0          1         2          3          4       5       6           7
    {"EXTINT0",  "ANALOG", "?",       "SERCOM5", "TC7",  "?",    "?",        "?"},        // PB0
    {"EXTINT1",  "ANALOG", "?",       "SERCOM5", "TC7",  "?",    "?",        "?"},        // PB1
    {"EXTINT2",  "ANALOG", "?",       "SERCOM5", "TC6",  "?",    "?",        "?"},        // PB2
    {"EXTINT3",  "ANALOG", "?",       "SERCOM5", "TC6",  "?",    "?",        "?"},        // PB3
    {"EXTINT4",  "ANALOG", "?",       "?",       "?",    "?",    "?",        "?"},        // PB4
    {"EXTINT5",  "ANALOG", "?",       "?",       "?",    "?",    "?",        "?"},        // PB5
    {"EXTINT6",  "ANALOG", "?",       "?",       "?",    "?",    "?",        "?"},        // PB6
    {"EXTINT7",  "ANALOG", "?",       "?",       "?",    "?",    "?",        "?"},        // PB7
    {"EXTINT8",  "ANALOG", "?",       "SERCOM4", "TC4",  "?",    "?",        "?"},        // PB8
    {"EXTINT9",  "ANALOG", "?",       "SERCOM4", "TC4",  "?",    "?",        "?"},        // PB9
    {"EXTINT10", "?",      "?",       "SERCOM4", "TC5",  "TCC0", "I2S/MCK1", "GCLK_IO4"}, //PB10
    {"EXTINT11", "?",      "?",       "SERCOM4", "TC5",  "TCC0", "I2S/SCK1", "GCLK_IO5"}, //PB11
    {"EXTINT12", "ANALOG", "SERCOM4", "?",       "TC4",  "TCC0", "I2S/FS1",  "GCLK_IO6"}, //PB12
    {"EXTINT13", "ANALOG", "SERCOM4", "?",       "TC4",  "TCC0", "?",        "GCLK_IO7"}, //PB13
    {"EXTINT14", "ANALOG", "SERCOM4", "?",       "TC5",  "?",    "?",        "GCLK_IO0"}, //PB14
    {"EXTINT15", "ANALOG", "SERCOM4", "?",       "TC5",  "?",    "?",        "GCLK_IO1"}, //PB15
    {"EXTINT0",  "?",      "SERCOM5", "?",       "TC6",  "TCC0", "I2S/SD0",  "GCLK_IO2"}, //PB16
    {"EXTINT1",  "?",      "SERCOM5", "?",       "TC6",  "TCC0", "I2S/SD1",  "GCLK_IO3"}, //PB17
    {"?",        "?",      "?",       "?",       "?",    "?",    "?",        "?"},        //PB18
    {"?",        "?",      "?",       "?",       "?",    "?",    "?",        "?"},        //PB19
    {"?",        "?",      "?",       "?",       "?",    "?",    "?",        "?"},        //PB20
    {"?",        "?",      "?",       "?",       "?",    "?",    "?",        "?"},        //PB21
    {"EXTINT6",  "?",      "?",       "SERCOM5", "TC7",  "?",    "?",        "GCLK_IO0"}, //PB22
    {"EXTINT7",  "?",      "?",       "SERCOM5", "TC7",  "?",    "?",        "GCLK_IO1"}, //PB23
    {"?",        "?",      "?",       "?",       "?",    "?",    "?",        "?"},        //PB24
    {"?",        "?",      "?",       "?",       "?",    "?",    "?",        "?"},        //PB25
    {"?",        "?",      "?",       "?",       "?",    "?",    "?",        "?"},        //PB26
    {"?",        "?",      "?",       "?",       "?",    "?",    "?",        "?"},        //PB27
    {"?",        "?",      "?",       "?",       "?",    "?",    "?",        "?"},        //PB28
    {"?",        "?",      "?",       "?",       "?",    "?",    "?",        "?"},        //PB29
    {"EXTINT14", "?",      "?",       "SERCOM5", "TCC0", "TCC1", "?",        "?"},        //PB30
    {"EXTINT15", "?",      "?",       "SERCOM5", "TCC0", "TCC1", "?",        "?"},        //PB31
};

const int samdGpioAPin[32] =
{
     1,  2,  3,  4,  9, 10, 11, 12,
    13, 14, 15, 16, 21, 22, 23, 24,
    25, 26, 27, 28, 29, 30, 31, 32,
    33, 34,  0, 39, 41,  0, 45, 46
};

const int samdGpioBPin[32] =
{
    0,  0,  0,  0,  0,  0,  0,  0,
    7,  8, 19, 20,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0, 37, 38,
    0,  0,  0,  0,  0,  0,  0,  0
};

void samdGpioPortConfig(char portLetter);
void samdGpioPortsConfig();

typedef struct _SAMD_TC_REGS_8_BIT_MODE
{
    uint8_t COUNT;        //0x10
    uint8_t res_11;       //0x11
    uint8_t res_12;       //0x12
    uint8_t res_13;       //0x13
    uint8_t PER;          //0x14
    uint8_t res_15;       //0x15
    uint8_t res_16;       //0x16
    uint8_t res_17;       //0x17
    uint8_t CC0;          //0x18
    uint8_t CC1;          //0x19
    uint8_t res_1a;       //0x1a
    uint8_t res_1b;       //0x1b
    uint8_t res_1c;       //0x1c
    uint8_t res_1d;       //0x1d
    uint8_t res_1e;       //0x1e
    uint8_t res_1f;       //0x1f
} SAMD_TC_REGS_8_BIT_MODE;

typedef struct _SAMD_TC_REGS_16_BIT_MODE
{
    uint16_t COUNT;       //0x10
    uint16_t res_12;      //0x12
    uint16_t res_14;      //0x14
    uint16_t res_16;      //0x16
    uint16_t CC0;         //0x18
    uint16_t CC1;         //0x1a
    uint16_t res_1c;      //0x1c
    uint16_t res_1e;      //0x1e
} SAMD_TC_REGS_16_BIT_MODE;

typedef struct _SAMD_TC_REGS_32_BIT_MODE
{
    uint32_t COUNT;       //0x10
    uint32_t res_14;      //0x14
    uint32_t CC0;         //0x18
    uint32_t CC1;         //0x1c
} SAMD_TC_REGS_32_BIT_MODE;

typedef struct _SAMD_TC_REGS
{
    uint16_t CTRLA;       //0x00
    uint16_t READREQ;     //0x02
    uint8_t CTRLBCLR;     //0x04
    uint8_t CTRLBSET;     //0x05
    uint8_t CTRLC;        //0x06
    uint8_t res_07;       //0x07
    uint8_t DBGCTRL;      //0x08
    uint8_t res_09;       //0x09
    uint16_t EVCTRL;      //0x0a
    uint8_t INTENCLR;     //0x0c
    uint8_t INTENSET;     //0x0d
    uint8_t INTFLAG;      //0x0e
    uint8_t STATUS;       //0x0f
    union
    {
        SAMD_TC_REGS_8_BIT_MODE  bit_8;
        SAMD_TC_REGS_16_BIT_MODE bit_16;
        SAMD_TC_REGS_32_BIT_MODE bit_32;
    } mode;
} SAMD_TC_REGS;

// Define the CTRLA register
#define SAMD_TC_CTRLA_PRESCSYNC         0x3000
#define SAMD_TC_CTRLA_RUNSTDBY          0x0800
#define SAMD_TC_CTRLA_PRESCALER         0x0700
#define SAMD_TC_CTRLA_WAVEGEN           0x0060
#define SAMD_TC_CTRLA_MODE              0x000c
#define SAMD_TC_CTRLA_ENABLE            0x0002
#define SAMD_TC_CTRLA_SWRST             0x0001

#define SAMD_TC_CTRLA_PRESCSYNC_GCLK    0
#define SAMD_TC_CTRLA_PRESCSYNC_PRESC   0x1000
#define SAMD_TC_CTRLA_PRESCSYNC_RESYNC  0x2000

#define SAMD_TC_CTRLA_PRESCALER_DIV1    0
#define SAMD_TC_CTRLA_PRESCALER_DIV2    0x0100
#define SAMD_TC_CTRLA_PRESCALER_DIV4    0x0200
#define SAMD_TC_CTRLA_PRESCALER_DIV8    0x0300
#define SAMD_TC_CTRLA_PRESCALER_DIV16   0x0400
#define SAMD_TC_CTRLA_PRESCALER_DIV64   0x0500
#define SAMD_TC_CTRLA_PRESCALER_DIV256  0x0600
#define SAMD_TC_CTRLA_PRESCALER_DIV1024 0x0700

#define SAMD_TC_CTRLA_WAVEGEN_NFRQ      0
#define SAMD_TC_CTRLA_WAVEGEN_MFRQ      0x0020
#define SAMD_TC_CTRLA_WAVEGEN_NPWM      0x0040
#define SAMD_TC_CTRLA_WAVEGEN_MPWM      0x0060

#define SAMD_TC_CTRLA_MODE_COUNT16      0
#define SAMD_TC_CTRLA_MODE_COUNT8       0x0004
#define SAMD_TC_CTRLA_MODE_COUNT32      0x0008

// Define the READREQ register
#define SAMD_TC_READREQ_RCONT           0x4000
#define SAMD_TC_READREQ_ADDR            0x001f

// Define the CTRLBCLR and CTRLBSET registers
#define SAMD_TC_CTRLB_CMD               0xc0
#define SAMD_TC_CTRLB_ONESHOT           0x04
#define SAMD_TC_CTRLB_DIR               0x01

#define SAMD_TC_CTRLB_CMD_NONE          0
#define SAMD_TC_CTRLB_CMD_RETRIGGER     0x40
#define SAMD_TC_CTRLB_CMD_STOP          0x80
#define SAMD_TC_CTRLB_CMD               0xc0

#define SAMD_TC_CTRLB_DIR_UP            0
#define SAMD_TC_CTRLB_DIR_DOWN          0x01

// Define the CTRLC register
#define SAMD_TC_CTRLC_CPTEN1            0x20
#define SAMD_TC_CTRLC_CPTEN0            0x10
#define SAMD_TC_CTRLC_INVEN1            0x02
#define SAMD_TC_CTRLC_INVEN0            0x01

// Define the DBGCTRL register
#define SAMD_TC_DBGCTRL_DBGRUN          0x01

// Define the EVCTRL register
#define SAMD_TC_EVCTRL_MCEO1            0x2000
#define SAMD_TC_EVCTRL_MCEO0            0x1000
#define SAMD_TC_EVCTRL_OVFEO            0x0100
#define SAMD_TC_EVCTRL_TCEI             0x0020
#define SAMD_TC_EVCTRL_TCINV            0x0010
#define SAMD_TC_EVCTRL_EVACT            0x0007

// Define the INTENCLR, INTENSET and INTFLAG registers
#define SAMD_TC_INTEN_MC1               0x20
#define SAMD_TC_INTEN_MC0               0x10
#define SAMD_TC_INTEN_SYNCRDY           0x08
#define SAMD_TC_INTEN_ERR               0x02
#define SAMD_TC_INTEN_OVF               0x01

// Define the STATUS register
#define SAMD_TC_STATUS_SYNCBUSY         0x80
#define SAMD_TC_STATUS_SLAVE            0x10
#define SAMD_TC_STATUS_STOP             0x08

typedef struct _SAMD_TCC_REGS
{
    uint16_t CTRLA;       //0x00
    uint8_t CTRLBCLR;     //0x04
    uint8_t CTRLBSET;     //0x05
    uint8_t res_06;       //0x06
    uint8_t res_07;       //0x07
    uint32_t SYNCBUSY;    //0x08
    uint32_t FCTRLA;      //0x0c
    uint32_t FCTRLB;      //0x10
    uint32_t WEXCTRL;     //0x14
    uint32_t DRVCTRL;     //0x18
    uint8_t res_1c;       //0x1c
    uint8_t res_1d;       //0x1d
    uint8_t DBGCTRL;      //0x1e
    uint8_t res_1f;       //0x1f
    uint32_t EVCTRL;      //0x20
    uint32_t INTENCLR;    //0x24
    uint32_t INTENSET;    //0x28
    uint32_t INTFLAG;     //0x2c
    uint32_t STATUS;      //0x30
    uint32_t COUNT;       //0x34
    uint16_t PATT;        //0x38
    uint8_t res_3a;       //0x3a
    uint8_t res_3b;       //0x3b
    uint32_t WAVE;        //0x3c
    uint32_t PER;         //0x40
    uint32_t CC0;         //0x44
    uint32_t CC1;         //0x48
    uint32_t CC2;         //0x4c
    uint32_t CC3;         //0x50
    uint32_t res_54;      //0x54
    uint32_t res_58;      //0x58
    uint32_t res_5c;      //0x5c
    uint32_t res_60;      //0x60
    uint16_t PATTB;       //0x64
    uint8_t res_66;       //0x66
    uint8_t res_67;       //0x67
    uint32_t WAVEB;       //0x68
    uint32_t PERB;        //0x6c
    uint32_t CCB0;        //0x70
    uint32_t CCB1;        //0x74
    uint32_t CCB2;        //0x78
    uint32_t CCB3;        //0x7c
} SAMD_TCC_REGS;

// Define the CTRLA register
#define SAMD_TCC_CTRLA_CPTEN3       0x08000000
#define SAMD_TCC_CTRLA_CPTEN2       0x04000000
#define SAMD_TCC_CTRLA_CPTEN1       0x02000000
#define SAMD_TCC_CTRLA_CPTEN0       0x01000000
#define SAMD_TCC_CTRLA_ALOCK        0x00004000
#define SAMD_TCC_CTRLA_PRESCSYNC    0x00003000
#define SAMD_TCC_CTRLA_RUNSTDBY     0x00000800
#define SAMD_TCC_CTRLA_PRESCALER    0x00000700
#define SAMD_TCC_CTRLA_RESOLUTION   0x00000060
#define SAMD_TCC_CTRLA_ENABLE       0x00000002
#define SAMD_TCC_CTRLA_SWRST        0x00000001

#define SAMD_TCC_CTRLA_PRESCSYNC_GCLK       0
#define SAMD_TCC_CTRLA_PRESCSYNC_PRSC       0x00001000
#define SAMD_TCC_CTRLA_PRESCSYNC_RESYNC     0x00002000

#define SAMD_TCC_CTRLA_PRESCALER_DIV1       0
#define SAMD_TCC_CTRLA_PRESCALER_DIV2       0x00000100
#define SAMD_TCC_CTRLA_PRESCALER_DIV4       0x00000200
#define SAMD_TCC_CTRLA_PRESCALER_DIV8       0x00000300
#define SAMD_TCC_CTRLA_PRESCALER_DIV16      0x00000400
#define SAMD_TCC_CTRLA_PRESCALER_DIV64      0x00000500
#define SAMD_TCC_CTRLA_PRESCALER_DIV256     0x00000600
#define SAMD_TCC_CTRLA_PRESCALER_DIV1024    0x00000700

#define SAMD_TCC_CTRLA_RESOLUTION_NONE      0
#define SAMD_TCC_CTRLA_RESOLUTION_DITH4     0x00000020
#define SAMD_TCC_CTRLA_RESOLUTION_DITH5     0x00000040
#define SAMD_TCC_CTRLA_RESOLUTION_DITH6     0x00000060

// Define the CTRLBCLR and CTRLBSET registers
#define SAMD_TCC_CTRLB_CMD          0xe0
#define SAMD_TCC_CTRLB_IDXCMD       0x18
#define SAMD_TCC_CTRLB_ONESHOT      0x04
#define SAMD_TCC_CTRLB_LUPD         0x02
#define SAMD_TCC_CTRLB_DIR          0x01

// Define the SYNCBUSY register
#define SAMD_TCC_SYNCBUSY_CCB3      0x00400000
#define SAMD_TCC_SYNCBUSY_CCB2      0x00200000
#define SAMD_TCC_SYNCBUSY_CCB1      0x00100000
#define SAMD_TCC_SYNCBUSY_CCB0      0x00080000
#define SAMD_TCC_SYNCBUSY_PERB      0x00040000
#define SAMD_TCC_SYNCBUSY_WAVEB     0x00020000
#define SAMD_TCC_SYNCBUSY_PATTB     0x00010000
#define SAMD_TCC_SYNCBUSY_CC3       0x00000800
#define SAMD_TCC_SYNCBUSY_CC2       0x00000400
#define SAMD_TCC_SYNCBUSY_CC1       0x00000200
#define SAMD_TCC_SYNCBUSY_CC0       0x00000100
#define SAMD_TCC_SYNCBUSY_PER       0x00000080
#define SAMD_TCC_SYNCBUSY_WAVE      0x00000040
#define SAMD_TCC_SYNCBUSY_PATT      0x00000020
#define SAMD_TCC_SYNCBUSY_COUNT     0x00000010
#define SAMD_TCC_SYNCBUSY_STATUS    0x00000008
#define SAMD_TCC_SYNCBUSY_CTRLB     0x00000004
#define SAMD_TCC_SYNCBUSY_ENABLE    0x00000002
#define SAMD_TCC_SYNCBUSY_SWRST     0x00000001

// Define the FCTRLA and FCTRLB registers
#define SAMD_TCC_FCTRL_FILTERVAL    0x0f000000
#define SAMD_TCC_FCTRL_BLANKVAL     0x00ff0000
#define SAMD_TCC_FCTRL_CAPTURE      0x00007000
#define SAMD_TCC_FCTRL_CHSEL        0x00000c00
#define SAMD_TCC_FCTRL_HALT         0x00000300
#define SAMD_TCC_FCTRL_RESTART      0x00000080
#define SAMD_TCC_FCTRL_BLANK        0x00000060
#define SAMD_TCC_FCTRL_QUAL         0x00000010
#define SAMD_TCC_FCTRL_KEEP         0x00000008
#define SAMD_TCC_FCTRL_SRC          0x00000003

// Define the WEXCTRL register
#define SAMD_TCC_WEXCTRL_DTHS       0xff000000
#define SAMD_TCC_WEXCTRL_DTLS       0x00ff0000
#define SAMD_TCC_WEXCTRL_DTIEN3     0x00000800
#define SAMD_TCC_WEXCTRL_DTIEN2     0x00000400
#define SAMD_TCC_WEXCTRL_DTIEN1     0x00000200
#define SAMD_TCC_WEXCTRL_DTIEN0     0x00000100
#define SAMD_TCC_WEXCTRL_OTMX       0x00000003

// Define the DRVCTRL register
#define SAMD_TCC_DRVCTRL_FILTERVAL1 0xf0000000
#define SAMD_TCC_DRVCTRL_FILTERVAL0 0x0f000000
#define SAMD_TCC_DRVCTRL_INVEN7     0x00800000
#define SAMD_TCC_DRVCTRL_INVEN6     0x00400000
#define SAMD_TCC_DRVCTRL_INVEN5     0x00200000
#define SAMD_TCC_DRVCTRL_INVEN4     0x00100000
#define SAMD_TCC_DRVCTRL_INVEN3     0x00080000
#define SAMD_TCC_DRVCTRL_INVEN2     0x00040000
#define SAMD_TCC_DRVCTRL_INVEN1     0x00020000
#define SAMD_TCC_DRVCTRL_INVEN0     0x00010000
#define SAMD_TCC_DRVCTRL_NRV7       0x00008000
#define SAMD_TCC_DRVCTRL_NRV6       0x00004000
#define SAMD_TCC_DRVCTRL_NRV5       0x00002000
#define SAMD_TCC_DRVCTRL_NRV4       0x00001000
#define SAMD_TCC_DRVCTRL_NRV3       0x00000800
#define SAMD_TCC_DRVCTRL_NRV2       0x00000400
#define SAMD_TCC_DRVCTRL_NRV1       0x00000200
#define SAMD_TCC_DRVCTRL_NRV0       0x00000100
#define SAMD_TCC_DRVCTRL_NRE7       0x00000080
#define SAMD_TCC_DRVCTRL_NRE6       0x00000040
#define SAMD_TCC_DRVCTRL_NRE5       0x00000020
#define SAMD_TCC_DRVCTRL_NRE4       0x00000010
#define SAMD_TCC_DRVCTRL_NRE3       0x00000008
#define SAMD_TCC_DRVCTRL_NRE2       0x00000004
#define SAMD_TCC_DRVCTRL_NRE1       0x00000002
#define SAMD_TCC_DRVCTRL_NRE0       0x00000001

// Define the DBGCTRL register
#define SAMD_TCC_DBGCTRL_FDDBD      0x04
#define SAMD_TCC_DBGCTRL_DBGRUN     0x01

// Define the EVCTRL register
#define SAMD_TCC_EVCTRL_MCEO3       0x08000000
#define SAMD_TCC_EVCTRL_MCEO2       0x04000000
#define SAMD_TCC_EVCTRL_MCEO1       0x02000000
#define SAMD_TCC_EVCTRL_MCEO0       0x01000000
#define SAMD_TCC_EVCTRL_MCEI3       0x00080000
#define SAMD_TCC_EVCTRL_MCEI2       0x00040000
#define SAMD_TCC_EVCTRL_MCEI1       0x00020000
#define SAMD_TCC_EVCTRL_MCEI0       0x00010000
#define SAMD_TCC_EVCTRL_TCEI1       0x00008000
#define SAMD_TCC_EVCTRL_TCEI0       0x00004000
#define SAMD_TCC_EVCTRL_TCINV1      0x00002000
#define SAMD_TCC_EVCTRL_TCINV0      0x00001000
#define SAMD_TCC_EVCTRL_CNTEO       0x00000400
#define SAMD_TCC_EVCTRL_TRGEO       0x00000200
#define SAMD_TCC_EVCTRL_OVFEO       0x00000100
#define SAMD_TCC_EVCTRL_CNTSEL      0x000000c0
#define SAMD_TCC_EVCTRL_EVACT1      0x00000038
#define SAMD_TCC_EVCTRL_EVACT0      0x00000007

// Define the INTENCLR, INTENSET and INTFLAG registers
#define SAMD_TCC_INTEN_MC3          0x00080000
#define SAMD_TCC_INTEN_MC2          0x00040000
#define SAMD_TCC_INTEN_MC1          0x00020000
#define SAMD_TCC_INTEN_MC0          0x00010000
#define SAMD_TCC_INTEN_FAULT1       0x00008000
#define SAMD_TCC_INTEN_FAULT0       0x00004000
#define SAMD_TCC_INTEN_FAULTB       0x00002000
#define SAMD_TCC_INTEN_FAULTA       0x00001000
#define SAMD_TCC_INTEN_DFS          0x00000800
#define SAMD_TCC_INTEN_ERR          0x00000008
#define SAMD_TCC_INTEN_CNT          0x00000004
#define SAMD_TCC_INTEN_TRG          0x00000002
#define SAMD_TCC_INTEN_OVF          0x00000001

// Define the STATUS register
#define SAMD_TCC_STATUS_CMP3        0x08000000
#define SAMD_TCC_STATUS_CMP2        0x04000000
#define SAMD_TCC_STATUS_CMP1        0x02000000
#define SAMD_TCC_STATUS_CMP0        0x01000000
#define SAMD_TCC_STATUS_CCBV3       0x00080000
#define SAMD_TCC_STATUS_CCBV2       0x00040000
#define SAMD_TCC_STATUS_CCBV1       0x00020000
#define SAMD_TCC_STATUS_CCBV0       0x00010000
#define SAMD_TCC_STATUS_FAULT1      0x00008000
#define SAMD_TCC_STATUS_FAULT0      0x00004000
#define SAMD_TCC_STATUS_FAULTB      0x00002000
#define SAMD_TCC_STATUS_FAULTA      0x00001000
#define SAMD_TCC_STATUS_FAULT1IN    0x00000800
#define SAMD_TCC_STATUS_FAULT0IN    0x00000400
#define SAMD_TCC_STATUS_FAULTBIN    0x00000200
#define SAMD_TCC_STATUS_FAULTAIN    0x00000100
#define SAMD_TCC_STATUS_PERBV       0x00000080
#define SAMD_TCC_STATUS_WAVEBV      0x00000040
#define SAMD_TCC_STATUS_PATTBV      0x00000020
#define SAMD_TCC_STATUS_SLAVE       0x00000010
#define SAMD_TCC_STATUS_DFS         0x00000008
#define SAMD_TCC_STATUS_IDX         0x00000002
#define SAMD_TCC_STATUS_STOP        0x00000001

// Define the COUNT register
#define SAMD_TCC_COUNT_DITH4        0x00fffff0
#define SAMD_TCC_COUNT_DITH5        0x00ffffe0
#define SAMD_TCC_COUNT_DITH6        0x00ffffc0

// Define the PATT and PATTB registers
#define SAMD_TCC_PATT_PGV7          0x8000
#define SAMD_TCC_PATT_PGV6          0x4000
#define SAMD_TCC_PATT_PGV5          0x2000
#define SAMD_TCC_PATT_PGV4          0x1000
#define SAMD_TCC_PATT_PGV3          0x0800
#define SAMD_TCC_PATT_PGV2          0x0400
#define SAMD_TCC_PATT_PGV1          0x0200
#define SAMD_TCC_PATT_PGV0          0x0100
#define SAMD_TCC_PATT_PGE7          0x0080
#define SAMD_TCC_PATT_PGE6          0x0040
#define SAMD_TCC_PATT_PGE5          0x0020
#define SAMD_TCC_PATT_PGE4          0x0010
#define SAMD_TCC_PATT_PGE3          0x0008
#define SAMD_TCC_PATT_PGE2          0x0004
#define SAMD_TCC_PATT_PGE1          0x0002
#define SAMD_TCC_PATT_PGE0          0x0001

// Define the WAVE and WAVEB register
#define SAMD_TCC_WAVE_SWAP3         0x08000000
#define SAMD_TCC_WAVE_SWAP2         0x04000000
#define SAMD_TCC_WAVE_SWAP1         0x02000000
#define SAMD_TCC_WAVE_SWAP0         0x01000000
#define SAMD_TCC_WAVE_POL3          0x00080000
#define SAMD_TCC_WAVE_POL2          0x00040000
#define SAMD_TCC_WAVE_POL1          0x00020000
#define SAMD_TCC_WAVE_POL0          0x00010000
#define SAMD_TCC_WAVE_CICCEN3       0x00000800
#define SAMD_TCC_WAVE_CICCEN2       0x00000400
#define SAMD_TCC_WAVE_CICCEN1       0x00000200
#define SAMD_TCC_WAVE_CICCEN0       0x00000100
#define SAMD_TCC_WAVE_CIPEREN       0x00000080
#define SAMD_TCC_WAVE_RAMP          0x00000030
#define SAMD_TCC_WAVE_WAVEGEN       0x00000007

// Define the PER and CC* registers
#define SAMD_TCC_PER_DITH4_VALUE    0x00fffff0
#define SAMD_TCC_PER_DITH4_DITHERCY 0x0000000f
#define SAMD_TCC_PER_DITH5_VALUE    0x00ffffe0
#define SAMD_TCC_PER_DITH5_DITHERCY 0x0000001f
#define SAMD_TCC_PER_DITH6_VALUE    0x00ffffc0
#define SAMD_TCC_PER_DITH6_DITHERCY 0x0000003f

void samdTcConfig(uint32_t timerBaseAddress);
void samdTccConfig(uint32_t timerBaseAddress);
void samdTimerConfigs();

#endif  // __SPARKFUN_SAMD_REGISTER_DEBUG_TOOLS_H__
#endif  //ARDUINO_ARCH_SAMD
