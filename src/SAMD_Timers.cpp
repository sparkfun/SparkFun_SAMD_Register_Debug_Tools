/*------------------------------------------------------------------------------
SAMD_Timers.cpp

Decode and print the values of the SAMD21 timer/counter registers.

License: MIT. Please see LICENSE.md for more details
------------------------------------------------------------------------------*/

#if defined(ARDUINO_ARCH_SAMD)

#include "SparkFun_SAMD_Register_Debug_Tools.h"

uint8_t samdTcCtrlA(const SAMD_TC_REGS * tcRegs)
{
    uint16_t ctrlA;
    uint8_t bits;
    const char * const prescsync[] = {"GCLK", "PRESC", "RESYNC", "Reserved"};
    const char * const prescaler[] = {"DIV1", "DIV2", "DIV4", "DIV8", "DIV16", "DIV64", "DIV256", "DIV1024"};
    const char * const wavegen[] = {"Normal frequency", "Match frequency", "Normal PWM", "Match PWM"};
    uint8_t mode[] = {16, 8, 32, 0};

    // Read the register value
    ctrlA = tcRegs->CTRLA;

    //Decode and print the register value
    samdRdtPrint->print("  CTRLA: 0x");
    samdRdtPrint->print(ctrlA, HEX);
    if (!(ctrlA & SAMD_TC_CTRLA_ENABLE))
    {
        samdRdtPrint->println(", Disabled");
        return 0;
    }
    samdRdtPrint->println(", Enabled");

    samdRdtPrint->print("    PRESCSYNC: ");
    samdRdtPrint->println(prescsync[(ctrlA & SAMD_TC_CTRLA_PRESCSYNC) >> 12]);

    samdRdtPrint->print("    RUNSTDBY: ");
    samdRdtPrint->print((ctrlA & SAMD_TC_CTRLA_RUNSTDBY)
                ? "Halted" : "Continues to run");
    samdRdtPrint->println(" in standby");

    samdRdtPrint->print("    PRESCALER: ");
    samdRdtPrint->println(prescaler[(ctrlA & SAMD_TC_CTRLA_PRESCALER) >> 8]);

    samdRdtPrint->print("    WAVEGEN: ");
    samdRdtPrint->println(wavegen[(ctrlA & SAMD_TC_CTRLA_WAVEGEN) >> 5]);

    bits = mode[(ctrlA & SAMD_TC_CTRLA_MODE) >> 2];
    samdRdtPrint->print("    MODE: ");
    if (bits)
    {
        samdRdtPrint->print(bits);
        samdRdtPrint->println(" bits");
    }
    else
        samdRdtPrint->println("Reserved");

    if (ctrlA & SAMD_TC_CTRLA_SWRST)
        samdRdtPrint->println("    SWRST: Reset in progress");
    return bits;
}

void samdTcReadReq(const SAMD_TC_REGS * tcRegs)
{
    uint16_t readReq;

    // Read the register value
    readReq = tcRegs->READREQ;

    // Decode and print the register value
    samdRdtPrint->print("  READREQ: 0x");
    samdRdtPrint->print(readReq & SAMD_TC_READREQ_ADDR, HEX);
    samdRdtPrint->println((readReq & SAMD_TC_READREQ_RCONT) ? ", Continuous" : ", One time");
}

void samdTcCtrlB(const SAMD_TC_REGS * tcRegs)
{
    uint8_t ctrlB;
    uint8_t cmd;
    const char * const cmd_name[] = {"No action", "Start", "Stop", "Reserved"};

    // Read the register value
    ctrlB = tcRegs->CTRLBCLR;
    cmd = ctrlB >> 6;

    // Decode and print the register value
    samdRdtPrint->print("  CTRLB: 0x");
    samdRdtPrint->print(ctrlB, HEX);

    if (cmd)
    {
        samdRdtPrint->print(", ");
        samdRdtPrint->print(cmd_name[cmd]);
    }

    if (ctrlB & SAMD_TC_CTRLB_ONESHOT)
        samdRdtPrint->print(", One shot");

    samdRdtPrint->println((ctrlB & SAMD_TC_CTRLB_DIR) ? ", Down" : ", Up");
}

void samdTcCtrlC(const SAMD_TC_REGS * tcRegs)
{
    uint8_t ctrlC;

    // Read the register value
    ctrlC = tcRegs->CTRLC;

    // Decode and print the register value
    samdRdtPrint->print("  CTRLC: 0x");
    samdRdtPrint->print(ctrlC, HEX);
    samdRdtPrint->println();

    if (ctrlC & SAMD_TC_CTRLC_CPTEN1)
        samdRdtPrint->println("    Capture channel 1");
    if (ctrlC & SAMD_TC_CTRLC_CPTEN0)
        samdRdtPrint->println("    Capture channel 0");

    if (ctrlC & SAMD_TC_CTRLC_INVEN1)
        samdRdtPrint->println("    Invert output WO1");
    if (ctrlC & SAMD_TC_CTRLC_INVEN0)
        samdRdtPrint->println("    Invert output WO0");
}

void samdTcDbgCtrl(const SAMD_TC_REGS * tcRegs)
{
    uint8_t dbgCtrl;

    // Read the register value
    dbgCtrl = tcRegs->DBGCTRL;

    // Decode and print the register value
    samdRdtPrint->print("  DBGCTRL: 0x");
    samdRdtPrint->print(dbgCtrl, HEX);

    samdRdtPrint->print((dbgCtrl & SAMD_TC_DBGCTRL_DBGRUN) ? ", Run" : ", Halt");
    samdRdtPrint->println(" timer when device is halted in debug mode");
}

void samdTcEvCtrl(const SAMD_TC_REGS * tcRegs)
{
    uint8_t evCtrl;
    const char * const action[] =
    {
        "OFF: Event action disabled",
        "RETRIGGER: Start, restart or retrigger TC on event",
        "COUNT: Count on event",
        "START: Start TC on event",
        "Reserved: 4",
        "PPW: Period captured in CC0, pulse width in CC1",
        "PWP: Period captured in CC1, pulse width in CC0",
        "Reserved: 7"
    };

    // Read the register value
    evCtrl = tcRegs->EVCTRL;

    // Decode and print the register value
    samdRdtPrint->print("  EVCTRL: 0x");
    samdRdtPrint->print(evCtrl, HEX);
    samdRdtPrint->println();

    if (evCtrl & SAMD_TC_EVCTRL_MCEO1)
        samdRdtPrint->println("    MEO1: Channel 1 match/capture output enabled");
    if (evCtrl & SAMD_TC_EVCTRL_MCEO0)
        samdRdtPrint->println("    MEO0: Channel 0 match/capture output enabled");

    if (evCtrl & SAMD_TC_EVCTRL_OVFEO)
        samdRdtPrint->println("    OVFEO: Overflow/underflow output enabled");


    if (evCtrl & SAMD_TC_EVCTRL_TCEI)
        samdRdtPrint->println("    TCEI: Incoming events enabled");
    if (evCtrl & SAMD_TC_EVCTRL_TCINV)
        samdRdtPrint->println("    TCINV: Input source is inverted");

    samdRdtPrint->print("    ");
    samdRdtPrint->println(action[evCtrl & SAMD_TC_EVCTRL_EVACT]);
}

void samdTcInten(const char * regName, const char * state, uint8_t regValue)
{
    uint8_t inten;

    // Decode and print the register value
    samdRdtPrint->print("  ");
    samdRdtPrint->print(regName);
    samdRdtPrint->print(": 0x");
    samdRdtPrint->print(regValue, HEX);
    samdRdtPrint->println();

    if (regValue & SAMD_TC_INTEN_MC1)
    {
        samdRdtPrint->print("    MC1: Channel 1 match/capture interrupt ");
        samdRdtPrint->println(state);
    }
    if (regValue & SAMD_TC_INTEN_MC0)
    {
        samdRdtPrint->print("    MC0: Channel 1 match/capture interrupt ");
        samdRdtPrint->println(state);
    }

    if (regValue & SAMD_TC_INTEN_SYNCRDY)
    {
        samdRdtPrint->print("    SYNCRDY: Synchronization ready interrupt ");
        samdRdtPrint->println(state);
    }

    if (regValue & SAMD_TC_INTEN_ERR)
    {
        samdRdtPrint->print("    ERR: Error interrupt ");
        samdRdtPrint->println(state);
    }

    if (regValue & SAMD_TC_INTEN_OVF)
    {
        samdRdtPrint->print("    OVF: Overflow interrupt ");
        samdRdtPrint->println(state);
    }
}

void samdTcStatus(const SAMD_TC_REGS * tcRegs)
{
    uint8_t status;

    // Read the register value
    status = tcRegs->STATUS;

    // Decode and print the register value
    samdRdtPrint->print("  STATUS: 0x");
    samdRdtPrint->print(status, HEX);

    if (status & SAMD_TC_STATUS_SYNCBUSY)
        samdRdtPrint->println(", synchronized");

    if (status & SAMD_TC_STATUS_SLAVE)
        samdRdtPrint->println(", slave mode");

    samdRdtPrint->println((status & SAMD_TC_STATUS_STOP) ? ", stopped!" : ", running");
}

void samdTcCount(const SAMD_TC_REGS * tcRegs, uint8_t bits)
{
    samdRdtPrint->print("  COUNT: ");
    switch(bits)
    {
        case 8:
            samdRdtPrint->println(tcRegs->mode.bit_8.COUNT);
            break;

        case 16:
            samdRdtPrint->println(tcRegs->mode.bit_16.COUNT);
            break;

        case 32:
            samdRdtPrint->println(tcRegs->mode.bit_32.COUNT);
            break;
    }
}

void samdTcPer(const SAMD_TC_REGS * tcRegs, uint8_t bits)
{
    if (bits == 8)
    {
        samdRdtPrint->print("  PER: ");
        samdRdtPrint->println(tcRegs->mode.bit_8.PER);
    }
}

void samdTcCC0(const SAMD_TC_REGS * tcRegs, uint8_t bits)
{
    samdRdtPrint->print("  CC0: ");
    switch(bits)
    {
        case 8:
            samdRdtPrint->println(tcRegs->mode.bit_8.CC0);
            break;

        case 16:
            samdRdtPrint->println(tcRegs->mode.bit_16.CC0);
            break;

        case 32:
            samdRdtPrint->println(tcRegs->mode.bit_32.CC0);
            break;
    }
}

void samdTcCC1(const SAMD_TC_REGS * tcRegs, uint8_t bits)
{
    samdRdtPrint->print("  CC1: ");
    switch(bits)
    {
        case 8:
            samdRdtPrint->println(tcRegs->mode.bit_8.CC1);
            break;

        case 16:
            samdRdtPrint->println(tcRegs->mode.bit_16.CC1);
            break;

        case 32:
            samdRdtPrint->println(tcRegs->mode.bit_32.CC1);
            break;
    }
}

void samdTcConfig(uint32_t timerBaseAddress)
{
    uint8_t bits;
    bool enabled;
    bool slave;
    const SAMD_TC_REGS * tcRegs;
    uint8_t timer;

    // Validate the timer base address
    if ((timerBaseAddress < SAMD_TCC_0_BASE_ADDRESS)
    || (timerBaseAddress > SAMD_TC_7_BASE_ADDRESS)
    || (timerBaseAddress & (~SAMD_TC_7_BASE_ADDRESS)))
        return;

    // Validate the timer number
    timer = (timerBaseAddress - SAMD_TCC_0_BASE_ADDRESS) >> 10;
    if (timer < 3)
        return;
    tcRegs = (const SAMD_TC_REGS *)timerBaseAddress;

    // Print the timer name
    enabled = tcRegs->CTRLA & SAMD_TC_CTRLA_ENABLE;
    slave = tcRegs->STATUS & SAMD_TC_STATUS_SLAVE;
    samdRdtPrint->print("TC");
    samdRdtPrint->print(timer);
    samdRdtPrint->println(enabled ? " enabled"
        : (slave ? " slave" : " disabled"));

    // Print the register values
    if (enabled)
    {
        bits = samdTcCtrlA(tcRegs);
        samdTcReadReq(tcRegs);
        samdTcCtrlB(tcRegs);
        samdTcCtrlC(tcRegs);
        samdTcDbgCtrl(tcRegs);
        samdTcEvCtrl(tcRegs);
        samdTcInten("INTEN", "enabled", tcRegs->INTENSET);
        samdTcInten("INTFLAG", "occurred", tcRegs->INTFLAG);
        samdTcStatus(tcRegs);
        samdTcCount(tcRegs, bits);
        samdTcPer(tcRegs, bits);
        samdTcCC0(tcRegs, bits);
        samdTcCC1(tcRegs, bits);
        samdRdtPrint->println();
    }
}

uint8_t samdTccCtrlA(const SAMD_TCC_REGS * tccRegs)
{
    uint32_t ctrlA;
    uint8_t dither;
    const char * const prescsync[] = {"GCLK", "PRESC", "RESYNC", "Reserved"};
    const char * const prescaler[] = {"DIV1", "DIV2", "DIV4", "DIV8", "DIV16", "DIV64", "DIV256", "DIV1024"};
    const char * const ditherName[] = {"NONE", "DITH4", "DITH5", "DITH6"};

    // Read the register value
    ctrlA = tccRegs->CTRLA;

    // Decode and print the register value
    samdRdtPrint->print("  CTRLA: ");
    samdRdtPrint->println(ctrlA, HEX);

    if (ctrlA & SAMD_TCC_CTRLA_CPTEN3)
        samdRdtPrint->println("    CPTEN3: Enable channel 3 capture");
    if (ctrlA & SAMD_TCC_CTRLA_CPTEN2)
        samdRdtPrint->println("    CPTEN2: Enable channel 2 capture");
    if (ctrlA & SAMD_TCC_CTRLA_CPTEN1)
        samdRdtPrint->println("    CPTEN1: Enable channel 1 capture");
    if (ctrlA & SAMD_TCC_CTRLA_CPTEN0)
        samdRdtPrint->println("    CPTEN0: Enable channel 0 capture");

    if (ctrlA & SAMD_TCC_CTRLA_ALOCK)
        samdRdtPrint->println("    ALOCK: LUPD bit set on overflow/underflow or retrigger");

    samdRdtPrint->print("    PRESCSYNC: ");
    samdRdtPrint->println(prescsync[(ctrlA & SAMD_TCC_CTRLA_PRESCSYNC) >> 12]);

    samdRdtPrint->print("    RUNSTDBY: ");
    samdRdtPrint->print((ctrlA & SAMD_TCC_CTRLA_RUNSTDBY)
                ? "Halted" : "Continues to run");
    samdRdtPrint->println(" in standby");

    samdRdtPrint->print("    PRESCALER: ");
    samdRdtPrint->println(prescaler[(ctrlA & SAMD_TCC_CTRLA_PRESCALER) >> 8]);

    dither = (ctrlA & SAMD_TCC_CTRLA_RESOLUTION) >> 5;
    samdRdtPrint->print("    RESOLUTION (Dither): ");
    samdRdtPrint->println(ditherName[dither]);

    samdRdtPrint->println("    ENABLE: Timer enabled");

    if (ctrlA & SAMD_TCC_CTRLA_SWRST)
        samdRdtPrint->println("    SWRST: Reset in progress");
    return dither;
}

void samdTccCtrlB(const SAMD_TCC_REGS * tccRegs)
{
    uint32_t ctrlB;
    const char * const cmd[] = {"NONE", "RETRIGGER", "STOP", "UPDATE", "READSYNC", "Reserved", "Reserved", "Reserved"};
    const char * const idxCmd[] = {"DISABLE", "SET", "CLEAR", "HOLD"};

    // Read the register value
    ctrlB = tccRegs->CTRLBSET;

    // Decode and print the register value
    samdRdtPrint->print("  CTRLB: ");
    samdRdtPrint->print(ctrlB, HEX);
    samdRdtPrint->println();

    samdRdtPrint->print("    CMD: ");
    samdRdtPrint->println(cmd[(ctrlB & SAMD_TCC_CTRLB_CMD) >> 5]);

    samdRdtPrint->print("    IDXCMD: ");
    samdRdtPrint->println(idxCmd[(ctrlB & SAMD_TCC_CTRLB_IDXCMD) >> 3]);

    samdRdtPrint->print("    ONESHOT: ");
    samdRdtPrint->println((ctrlB & SAMD_TCC_CTRLB_ONESHOT) ? "One shot" : "Continuous");

    samdRdtPrint->print("    LUPD: ");
    samdRdtPrint->print((ctrlB & SAMD_TCC_CTRLB_LUPD) ? "Don't update" : "Update");
    samdRdtPrint->println(" * registers from *B* (buffer) registers");

    samdRdtPrint->print("    DIR: ");
    samdRdtPrint->println((ctrlB & SAMD_TCC_CTRLB_DIR) ? ", Down" : ", Up");
}

void samdTccSyncBusy(const SAMD_TCC_REGS * tccRegs)
{
    uint32_t syncBusy;

    // Read the register value
    syncBusy = tccRegs->SYNCBUSY;

    // Decode and print the register value
    samdRdtPrint->print("  SYNCBUSY: ");
    samdRdtPrint->print(syncBusy, HEX);
    samdRdtPrint->println();

    if (syncBusy & SAMD_TCC_SYNCBUSY_CCB3)
        samdRdtPrint->println("    CCB3: Compare/Capture channel 3 buffer busy");
    if (syncBusy & SAMD_TCC_SYNCBUSY_CCB2)
        samdRdtPrint->println("    CCB2: Compare/Capture channel 2 buffer busy");
    if (syncBusy & SAMD_TCC_SYNCBUSY_CCB1)
        samdRdtPrint->println("    CCB1: Compare/Capture channel 1 buffer busy");
    if (syncBusy & SAMD_TCC_SYNCBUSY_CCB0)
        samdRdtPrint->println("    CCB0: Compare/Capture channel 0 buffer busy");

    if (syncBusy & SAMD_TCC_SYNCBUSY_PERB)
        samdRdtPrint->println("    PERB: Period buffer busy");

    if (syncBusy & SAMD_TCC_SYNCBUSY_WAVEB)
        samdRdtPrint->println("    WAVEB: Wave buffer busy");

    if (syncBusy & SAMD_TCC_SYNCBUSY_PATTB)
        samdRdtPrint->println("    PATTB: Pattern buffer busy");

    if (syncBusy & SAMD_TCC_SYNCBUSY_CC3)
        samdRdtPrint->println("    CC3: Compare/Capture channel 3 busy");
    if (syncBusy & SAMD_TCC_SYNCBUSY_CC2)
        samdRdtPrint->println("    CC2: Compare/Capture channel 2 busy");
    if (syncBusy & SAMD_TCC_SYNCBUSY_CC1)
        samdRdtPrint->println("    CC1: Compare/Capture channel 1 busy");
    if (syncBusy & SAMD_TCC_SYNCBUSY_CC0)
        samdRdtPrint->println("    CC0: Compare/Capture channel 0 busy");

    if (syncBusy & SAMD_TCC_SYNCBUSY_PER)
        samdRdtPrint->println("    PER: Period busy");

    if (syncBusy & SAMD_TCC_SYNCBUSY_WAVE)
        samdRdtPrint->println("    WAVE: Wave busy");

    if (syncBusy & SAMD_TCC_SYNCBUSY_PATT)
        samdRdtPrint->println("    PATT: Pattern busy");

    if (syncBusy & SAMD_TCC_SYNCBUSY_COUNT)
        samdRdtPrint->println("    COUNT: Count busy");

    if (syncBusy & SAMD_TCC_SYNCBUSY_STATUS)
        samdRdtPrint->println("    STATUS: Status busy");

    if (syncBusy & SAMD_TCC_SYNCBUSY_CTRLB)
        samdRdtPrint->println("    CTRLB: CtrlB busy");

    if (syncBusy & SAMD_TCC_SYNCBUSY_ENABLE)
        samdRdtPrint->println("    ENABLE: Enable busy");

    if (syncBusy & SAMD_TCC_SYNCBUSY_SWRST)
        samdRdtPrint->println("    SWRST: SwRst busy");
}

void samdTccFctrl(const char * regName, uint32_t fCtrl)
{
    const char * const capture[] = {"DISABLE", "CAPT", "CAPTMIN", "CAPMAX", "LOCMIN", "LOCMAX", "DERIV0", "Reserved"};
    const char * const halt[] = {"Disabled", "Hardware action", "Software action", "Non-recoverable fault"};
    const char * const blank[] = {"NONE", "RISE", "FALL", "BOTH"};
    const char * const src[] = {"DISABLE", "ENABLE", "INVERT", "ALTFAULT"};

    // Decode and print the register value
    samdRdtPrint->print("  ");
    samdRdtPrint->print(regName);
    samdRdtPrint->print(": ");
    samdRdtPrint->print(fCtrl, HEX);
    samdRdtPrint->println();

    samdRdtPrint->print("    FILTERVAL: ");
    samdRdtPrint->println((fCtrl & SAMD_TCC_FCTRL_FILTERVAL) >> 24);

    samdRdtPrint->print("    BLANKVAL: ");
    samdRdtPrint->println((fCtrl & SAMD_TCC_FCTRL_BLANKVAL) >> 16);

    samdRdtPrint->print("    CAPTURE: ");
    samdRdtPrint->println(capture[(fCtrl & SAMD_TCC_FCTRL_CAPTURE) >> 12]);

    samdRdtPrint->print("    CHSEL: CC");
    samdRdtPrint->println((fCtrl & SAMD_TCC_FCTRL_CHSEL) >> 10);

    samdRdtPrint->print("    HALT: ");
    samdRdtPrint->println(halt[(fCtrl & SAMD_TCC_FCTRL_HALT) >> 8]);

    samdRdtPrint->print("    RESTART: ");
    samdRdtPrint->println((fCtrl & SAMD_TCC_FCTRL_RESTART) ? "Enabled" : "Disabled");

    samdRdtPrint->print("    BLANK: ");
    samdRdtPrint->println(blank[(fCtrl & SAMD_TCC_FCTRL_BLANK) >> 5]);

    samdRdtPrint->print("    QUAL: Fault A input ");
    samdRdtPrint->println((fCtrl & SAMD_TCC_FCTRL_QUAL) ? "disabled" : "enaabled");

    samdRdtPrint->print("    KEEP: Fault A released ");
    samdRdtPrint->println((fCtrl & SAMD_TCC_FCTRL_KEEP) ? "at end of TCC cycle" : "immediately");

    samdRdtPrint->print("    SRC: ");
    samdRdtPrint->println(src[fCtrl & SAMD_TCC_FCTRL_SRC]);
}

void samdTccWExCtrl(const SAMD_TCC_REGS * tccRegs)
{
    const char * const otmx[] =
    {
        "CC3, CC2, CC1, CC0, CC3, CC2, CC1, CC0",
        "CC1, CC0, CC1, CC0, CC1, CC0, CC1, CC0",
        "CC0, CC0, CC0, CC0, CC0, CC0, CC0, CC0",
        "CC1, CC1, CC1, CC1, CC1, CC1, CC1, CC0"
    };
    uint32_t wExCtrl;

    // Read the register value
    wExCtrl = tccRegs->WEXCTRL;

    // Decode and print the register value
    samdRdtPrint->print("  WEXCTRL: ");
    samdRdtPrint->print(wExCtrl, HEX);
    samdRdtPrint->println();

    samdRdtPrint->print("    DTHS: ");
    samdRdtPrint->println((wExCtrl & SAMD_TCC_WEXCTRL_DTHS) >> 24);

    samdRdtPrint->print("    DTLS: ");
    samdRdtPrint->println((wExCtrl & SAMD_TCC_WEXCTRL_DTLS) >> 24);

    if (wExCtrl & SAMD_TCC_WEXCTRL_DTIEN3)
        samdRdtPrint->println("    DTIEN3: Deadtime insertion on (WO_NUM/2) + 3");
    if (wExCtrl & SAMD_TCC_WEXCTRL_DTIEN2)
        samdRdtPrint->println("    DTIEN2: Deadtime insertion on (WO_NUM/2) + 2");
    if (wExCtrl & SAMD_TCC_WEXCTRL_DTIEN1)
        samdRdtPrint->println("    DTIEN1: Deadtime insertion on (WO_NUM/2) + 1");
    if (wExCtrl & SAMD_TCC_WEXCTRL_DTIEN0)
        samdRdtPrint->println("    DTIEN0: Deadtime insertion on (WO_NUM/2) + 0");

    samdRdtPrint->print("    OTMX: ");
    samdRdtPrint->println(otmx[wExCtrl & SAMD_TCC_WEXCTRL_OTMX]);
}

void samdTccDrvCtrl(const SAMD_TCC_REGS * tccRegs)
{
    uint32_t drvCtrl;

    // Read the register value
    drvCtrl = tccRegs->DRVCTRL;

    // Decode and print the register value
    samdRdtPrint->print("  DRVCTRL: ");
    samdRdtPrint->print(drvCtrl, HEX);
    samdRdtPrint->println();

    samdRdtPrint->print("    FILTERVAL1: ");
    samdRdtPrint->println((drvCtrl & SAMD_TCC_DRVCTRL_FILTERVAL1) >> 28);

    samdRdtPrint->print("    FILTERVAL0: ");
    samdRdtPrint->println((drvCtrl & SAMD_TCC_DRVCTRL_FILTERVAL0) >> 24);

    if (drvCtrl & SAMD_TCC_DRVCTRL_INVEN7)
        samdRdtPrint->println("    INVEN7: Invert WO7");
    if (drvCtrl & SAMD_TCC_DRVCTRL_INVEN6)
        samdRdtPrint->println("    INVEN6: Invert WO6");
    if (drvCtrl & SAMD_TCC_DRVCTRL_INVEN5)
        samdRdtPrint->println("    INVEN5: Invert WO5");
    if (drvCtrl & SAMD_TCC_DRVCTRL_INVEN4)
        samdRdtPrint->println("    INVEN4: Invert WO4");
    if (drvCtrl & SAMD_TCC_DRVCTRL_INVEN3)
        samdRdtPrint->println("    INVEN3: Invert WO3");
    if (drvCtrl & SAMD_TCC_DRVCTRL_INVEN2)
        samdRdtPrint->println("    INVEN2: Invert WO2");
    if (drvCtrl & SAMD_TCC_DRVCTRL_INVEN1)
        samdRdtPrint->println("    INVEN1: Invert WO1");
    if (drvCtrl & SAMD_TCC_DRVCTRL_INVEN0)
        samdRdtPrint->println("    INVEN0: Invert WO0");

    if (drvCtrl & SAMD_TCC_DRVCTRL_NRE7)
    {
        samdRdtPrint->print("    NRV7: WO7 non-recoverable fault outputs ");
        samdRdtPrint->println((drvCtrl & SAMD_TCC_DRVCTRL_NRV7) >> 15);
    }
    if (drvCtrl & SAMD_TCC_DRVCTRL_NRE6)
    {
        samdRdtPrint->print("    NRV6: WO6 non-recoverable fault outputs ");
        samdRdtPrint->println((drvCtrl & SAMD_TCC_DRVCTRL_NRV6) >> 14);
    }
    if (drvCtrl & SAMD_TCC_DRVCTRL_NRE5)
    {
        samdRdtPrint->print("    NRV5: WO5 non-recoverable fault outputs ");
        samdRdtPrint->println((drvCtrl & SAMD_TCC_DRVCTRL_NRV5) >> 13);
    }
    if (drvCtrl & SAMD_TCC_DRVCTRL_NRE4)
    {
        samdRdtPrint->print("    NRV4: WO4 non-recoverable fault outputs ");
        samdRdtPrint->println((drvCtrl & SAMD_TCC_DRVCTRL_NRV4) >> 12);
    }
    if (drvCtrl & SAMD_TCC_DRVCTRL_NRE3)
    {
        samdRdtPrint->print("    NRV3: WO3 non-recoverable fault outputs ");
        samdRdtPrint->println((drvCtrl & SAMD_TCC_DRVCTRL_NRV3) >> 11);
    }
    if (drvCtrl & SAMD_TCC_DRVCTRL_NRE2)
    {
        samdRdtPrint->print("    NRV2: WO2 non-recoverable fault outputs ");
        samdRdtPrint->println((drvCtrl & SAMD_TCC_DRVCTRL_NRV2) >> 10);
    }
    if (drvCtrl & SAMD_TCC_DRVCTRL_NRE1)
    {
        samdRdtPrint->print("    NRV1: WO1 non-recoverable fault outputs ");
        samdRdtPrint->println((drvCtrl & SAMD_TCC_DRVCTRL_NRV1) >> 9);
    }
    if (drvCtrl & SAMD_TCC_DRVCTRL_NRE0)
    {
        samdRdtPrint->print("    NRV0: WO0 non-recoverable fault outputs ");
        samdRdtPrint->println((drvCtrl & SAMD_TCC_DRVCTRL_NRV0) >> 8);
    }
}

void samdTccDbgCtrl(const SAMD_TCC_REGS * tccRegs)
{
    uint32_t dbgCtrl;

    // Read the register value
    dbgCtrl = tccRegs->DBGCTRL;

    // Decode and print the register value
    samdRdtPrint->print("  DBGCTRL: ");
    samdRdtPrint->print(dbgCtrl, HEX);
    samdRdtPrint->println();

    samdRdtPrint->print("    FDDBD: OCD break ");
    samdRdtPrint->println((dbgCtrl & SAMD_TCC_DBGCTRL_FDDBD) ? "generates non-recoverable fault" : "ignored");

    samdRdtPrint->print("    DBGRUN: In debug mode TCC is ");
    samdRdtPrint->println((dbgCtrl & SAMD_TCC_DBGCTRL_DBGRUN) ? "running" : "halted");
}

void samdTccEvCtrl(const SAMD_TCC_REGS * tccRegs)
{
    uint32_t evCtrl;
    const char * const cntsel[] = {"START", "END", "BETWEEN", "BOUNDARY"};
    const char * const action1[] = {"OFF", "RETRIGGER", "DIR", "STOP", "DEC", "PPW", "PWP", "FAULT"};
    const char * const action0[] = {"OFF", "RETRIGGER", "COUNTEV", "START", "INC", "COUNT", "Reserved", "FAULT"};

    // Read the register value
    evCtrl = tccRegs->EVCTRL;

    // Decode and print the register value
    samdRdtPrint->print("  EVCTRL: ");
    samdRdtPrint->print(evCtrl, HEX);
    samdRdtPrint->println();

    samdRdtPrint->print("    MCEO3: Channel 3 match/capture output ");
    samdRdtPrint->println((evCtrl & SAMD_TCC_EVCTRL_MCEO3) ? "enabled" : "disabled");
    samdRdtPrint->print("    MCEO2: Channel 2 match/capture output ");
    samdRdtPrint->println((evCtrl & SAMD_TCC_EVCTRL_MCEO2) ? "enabled" : "disabled");
    samdRdtPrint->print("    MCEO1: Channel 1 match/capture output ");
    samdRdtPrint->println((evCtrl & SAMD_TCC_EVCTRL_MCEO1) ? "enabled" : "disabled");
    samdRdtPrint->print("    MCEO0: Channel 0 match/capture output ");
    samdRdtPrint->println((evCtrl & SAMD_TCC_EVCTRL_MCEO0) ? "enabled" : "disabled");

    samdRdtPrint->print("    MCEI3: Channel 3 match/capture input ");
    samdRdtPrint->println((evCtrl & SAMD_TCC_EVCTRL_MCEI3) ? "enabled" : "disabled");
    samdRdtPrint->print("    MCEI2: Channel 2 match/capture input ");
    samdRdtPrint->println((evCtrl & SAMD_TCC_EVCTRL_MCEI2) ? "enabled" : "disabled");
    samdRdtPrint->print("    MCEI1: Channel 1 match/capture input ");
    samdRdtPrint->println((evCtrl & SAMD_TCC_EVCTRL_MCEI1) ? "enabled" : "disabled");
    samdRdtPrint->print("    MCEI0: Channel 0 match/capture input ");
    samdRdtPrint->println((evCtrl & SAMD_TCC_EVCTRL_MCEI0) ? "enabled" : "disabled");

    samdRdtPrint->print("    TCEI1: Timer/counter input 1 ");
    samdRdtPrint->println((evCtrl & SAMD_TCC_EVCTRL_TCEI1) ? "enabled" : "disabled");
    samdRdtPrint->print("    TCEI0: Timer/counter input 0 ");
    samdRdtPrint->println((evCtrl & SAMD_TCC_EVCTRL_TCEI0) ? "enabled" : "disabled");

    if (evCtrl & SAMD_TCC_EVCTRL_TCINV1)
        samdRdtPrint->println("    TCINV1: Invert timer/counter input 1");
    if (evCtrl & SAMD_TCC_EVCTRL_TCINV0)
        samdRdtPrint->println("    TCINV0: Invert timer/counter input 0");

    samdRdtPrint->print("    CNTEO: Timer/counter output ");
    samdRdtPrint->println((evCtrl & SAMD_TCC_EVCTRL_CNTEO) ? "enabled" : "disabled");

    samdRdtPrint->print("    TRGEO: Timer/counter retrigger ");
    samdRdtPrint->println((evCtrl & SAMD_TCC_EVCTRL_TRGEO) ? "enabled" : "disabled");

    samdRdtPrint->print("    OVFEO: Timer/counter overflow ");
    samdRdtPrint->println((evCtrl & SAMD_TCC_EVCTRL_OVFEO) ? "enabled" : "disabled");

    samdRdtPrint->print("    CNTSEL: ");
    samdRdtPrint->println(cntsel[(evCtrl & SAMD_TCC_EVCTRL_CNTSEL) >> 6]);

    samdRdtPrint->print("    EVACT1: ");
    samdRdtPrint->println(action1[(evCtrl & SAMD_TCC_EVCTRL_EVACT1) >> 3]);
    samdRdtPrint->print("    EVACT0: ");
    samdRdtPrint->println(action0[evCtrl & SAMD_TCC_EVCTRL_EVACT0]);
}

void samdTccInten(const char * regName, const char * state, uint32_t inten)
{
    // Decode and print the register value
    samdRdtPrint->print("  ");
    samdRdtPrint->print(regName);
    samdRdtPrint->print(": ");
    samdRdtPrint->print(inten, HEX);
    samdRdtPrint->println();

    if (inten & SAMD_TCC_INTEN_MC3)
    {
        samdRdtPrint->print("    MC3: Channel 3 match or capture interrupt ");
        samdRdtPrint->println(state);
    }
    if (inten & SAMD_TCC_INTEN_MC2)
    {
        samdRdtPrint->print("    MC2: Channel 2 match or capture interrupt ");
        samdRdtPrint->println(state);
    }
    if (inten & SAMD_TCC_INTEN_MC1)
    {
        samdRdtPrint->print("    MC1: Channel 1 match or capture interrupt ");
        samdRdtPrint->println(state);
    }
    if (inten & SAMD_TCC_INTEN_MC0)
    {
        samdRdtPrint->print("    MC0: Channel 0 match or capture interrupt ");
        samdRdtPrint->println(state);
    }

    if (inten & SAMD_TCC_INTEN_FAULT1)
    {
        samdRdtPrint->print("    FAULT1: Non-recoverable fault 1 interrupt ");
        samdRdtPrint->println(state);
    }
    if (inten & SAMD_TCC_INTEN_FAULT0)
    {
        samdRdtPrint->print("    FAULT1: Non-recoverable fault 0 interrupt ");
        samdRdtPrint->println(state);
    }
    if (inten & SAMD_TCC_INTEN_FAULTB)
    {
        samdRdtPrint->print("    FAULTB: Non-recoverable fault A interrupt ");
        samdRdtPrint->println(state);
    }
    if (inten & SAMD_TCC_INTEN_FAULTA)
    {
        samdRdtPrint->print("    FAULTA: Non-recoverable fault B interrupt ");
        samdRdtPrint->println(state);
    }

    if (inten & SAMD_TCC_INTEN_DFS)
    {
        samdRdtPrint->print("    DFS: Debug fault state interrupt ");
        samdRdtPrint->println(state);
    }

    if (inten & SAMD_TCC_INTEN_ERR)
    {
        samdRdtPrint->print("    DFS: Error interrupt ");
        samdRdtPrint->println(state);
    }

    if (inten & SAMD_TCC_INTEN_CNT)
    {
        samdRdtPrint->print("    DFS: Counter interrupt ");
        samdRdtPrint->println(state);
    }

    if (inten & SAMD_TCC_INTEN_TRG)
    {
        samdRdtPrint->print("    DFS: Retrigger interrupt ");
        samdRdtPrint->println(state);
    }

    if (inten & SAMD_TCC_INTEN_OVF)
    {
        samdRdtPrint->print("    OVF: Overflow interrupt ");
        samdRdtPrint->println(state);
    }
}

void samdTccStatus(const SAMD_TCC_REGS * tccRegs)
{
    uint32_t status;

    // Read the register value
    status = tccRegs->STATUS;

    // Decode and print the register value
    samdRdtPrint->print("  STATUS: ");
    samdRdtPrint->print(status, HEX);
    samdRdtPrint->println();

    samdRdtPrint->print("    CMP3: ");
    samdRdtPrint->println((status & SAMD_TCC_STATUS_CMP3) ? 1 : 0);
    samdRdtPrint->print("    CMP2: ");
    samdRdtPrint->println((status & SAMD_TCC_STATUS_CMP2) ? 1 : 0);
    samdRdtPrint->print("    CMP1: ");
    samdRdtPrint->println((status & SAMD_TCC_STATUS_CMP1) ? 1 : 0);
    samdRdtPrint->print("    CMP0: ");
    samdRdtPrint->println((status & SAMD_TCC_STATUS_CMP0) ? 1 : 0);

    samdRdtPrint->print("    CCBV3: Buffer ");
    samdRdtPrint->println((status & SAMD_TCC_STATUS_CCBV3) ? "full" : "empty");
    samdRdtPrint->print("    CCBV2: Buffer ");
    samdRdtPrint->println((status & SAMD_TCC_STATUS_CCBV2) ? "full" : "empty");
    samdRdtPrint->print("    CCBV1: Buffer ");
    samdRdtPrint->println((status & SAMD_TCC_STATUS_CCBV1) ? "full" : "empty");
    samdRdtPrint->print("    CCBV0: Buffer ");
    samdRdtPrint->println((status & SAMD_TCC_STATUS_CCBV0) ? "full" : "empty");

    if (status & SAMD_TCC_STATUS_FAULT1)
        samdRdtPrint->println("    FAULT1 detected");
    if (status & SAMD_TCC_STATUS_FAULT0)
        samdRdtPrint->println("    FAULT0 detected");
    if (status & SAMD_TCC_STATUS_FAULTA)
        samdRdtPrint->println("    FAULTA detected");
    if (status & SAMD_TCC_STATUS_FAULTB)
        samdRdtPrint->println("    FAULTB detected");

    if (status & SAMD_TCC_STATUS_FAULT1IN)
        samdRdtPrint->println("    FAULT1IN present");
    if (status & SAMD_TCC_STATUS_FAULT0IN)
        samdRdtPrint->println("    FAULT0IN present");
    if (status & SAMD_TCC_STATUS_FAULTBIN)
        samdRdtPrint->println("    FAULTBIN present");
    if (status & SAMD_TCC_STATUS_FAULTAIN)
        samdRdtPrint->println("    FAULTAIN present");

    samdRdtPrint->print("    PERBV: Buffer ");
    samdRdtPrint->println((status & SAMD_TCC_STATUS_PERBV) ? "full" : "empty");
    samdRdtPrint->print("    WAVEBV: Buffer ");
    samdRdtPrint->println((status & SAMD_TCC_STATUS_WAVEBV) ? "full" : "empty");
    samdRdtPrint->print("    PATTBV: Buffer ");
    samdRdtPrint->println((status & SAMD_TCC_STATUS_PATTBV) ? "full" : "empty");

    if (status & SAMD_TCC_STATUS_SLAVE)
        samdRdtPrint->println("    SLAVE: TCC in slave mode");

    if (status & SAMD_TCC_STATUS_DFS)
        samdRdtPrint->println("    DFS: Non-recoverable debug fault state detected");

    samdRdtPrint->print("    IDX: ");
    samdRdtPrint->println((status & SAMD_TCC_STATUS_IDX) ? 1 : 0);

    samdRdtPrint->print("    STOP: Counter ");
    samdRdtPrint->println((status & SAMD_TCC_STATUS_STOP) ? "stopped" : "running");
}

void samdTccCount(const char * regName, uint32_t value, uint8_t dither)
{
    uint32_t count;

    // Display the register name and value
    if (regName)
    {
        samdRdtPrint->print("  ");
        samdRdtPrint->print(regName);
        samdRdtPrint->print(": ");
    }

    // Get the count
    switch (dither)
    {
        case SAMD_TCC_CTRLA_RESOLUTION_NONE:
            count = 0;
            break;

        case SAMD_TCC_CTRLA_RESOLUTION_DITH4:
            count = (value & SAMD_TCC_COUNT_DITH4) >> 4;
            break;

        case SAMD_TCC_CTRLA_RESOLUTION_DITH5:
            count = (value & SAMD_TCC_COUNT_DITH5) >> 5;
            break;

        case SAMD_TCC_CTRLA_RESOLUTION_DITH6:
            count = (value & SAMD_TCC_COUNT_DITH6) >> 6;
            break;
    }

    // Decode and print the register value
    samdRdtPrint->print(count);
}

void samdTccPatt(const char * suffix, uint32_t patt)
{
    // Decode and print the register value
    samdRdtPrint->print("  PATT");
    samdRdtPrint->print(suffix);
    samdRdtPrint->print(": ");
    samdRdtPrint->print(patt, HEX);
    samdRdtPrint->println();

    if (patt & SAMD_TCC_PATT_PGE7)
    {
        samdRdtPrint->print("    WO7 outputs ");
        samdRdtPrint->println((patt & SAMD_TCC_PATT_PGV7) ? 1 : 0);
    }
    if (patt & SAMD_TCC_PATT_PGE6)
    {
        samdRdtPrint->print("    WO6 outputs ");
        samdRdtPrint->println((patt & SAMD_TCC_PATT_PGV6) ? 1 : 0);
    }
    if (patt & SAMD_TCC_PATT_PGE5)
    {
        samdRdtPrint->print("    WO5 outputs ");
        samdRdtPrint->println((patt & SAMD_TCC_PATT_PGV5) ? 1 : 0);
    }
    if (patt & SAMD_TCC_PATT_PGE4)
    {
        samdRdtPrint->print("    WO4 outputs ");
        samdRdtPrint->println((patt & SAMD_TCC_PATT_PGV4) ? 1 : 0);
    }
    if (patt & SAMD_TCC_PATT_PGE3)
    {
        samdRdtPrint->print("    WO3 outputs ");
        samdRdtPrint->println((patt & SAMD_TCC_PATT_PGV3) ? 1 : 0);
    }
    if (patt & SAMD_TCC_PATT_PGE2)
    {
        samdRdtPrint->print("    WO2 outputs ");
        samdRdtPrint->println((patt & SAMD_TCC_PATT_PGV2) ? 1 : 0);
    }
    if (patt & SAMD_TCC_PATT_PGE1)
    {
        samdRdtPrint->print("    WO1 outputs ");
        samdRdtPrint->println((patt & SAMD_TCC_PATT_PGV1) ? 1 : 0);
    }
    if (patt & SAMD_TCC_PATT_PGE0)
    {
        samdRdtPrint->print("    WO0 outputs ");
        samdRdtPrint->println((patt & SAMD_TCC_PATT_PGV0) ? 1 : 0);
    }
}

void samdTccWave(const char * suffix, uint32_t wave)
{
    const char * const ramp[] = {"RAMP1", "RAMP2A", "RAMP2", "Reserved"};
    const char * const wavegen[] = {"NFRQ", "MFRQ", "NPWM", "Reserved", "DSCRITICAL", "DSBOTTOM", "DSBOTH", "DSTOP"};

    // Decode and print the register value
    samdRdtPrint->print("  WAVE");
    samdRdtPrint->print(suffix);
    samdRdtPrint->print(": ");
    samdRdtPrint->print(wave, HEX);
    samdRdtPrint->println();

    if (wave & SAMD_TCC_WAVE_SWAP3)
        samdRdtPrint->println("    SWAP3: Swap DTIO3 and (WO_NUM/2) + 3");
    if (wave & SAMD_TCC_WAVE_SWAP2)
        samdRdtPrint->println("    SWAP2: Swap DTIO2 and (WO_NUM/2) + 2");
    if (wave & SAMD_TCC_WAVE_SWAP1)
        samdRdtPrint->println("    SWAP1: Swap DTIO1 and (WO_NUM/2) + 1");
    if (wave & SAMD_TCC_WAVE_SWAP0)
        samdRdtPrint->println("    SWAP0: Swap DTIO0 and (WO_NUM/2) + 0");

    if (wave & SAMD_TCC_WAVE_POL3)
        samdRdtPrint->println("    POL3: Compare output 3 inverted");
    if (wave & SAMD_TCC_WAVE_POL2)
        samdRdtPrint->println("    POL2: Compare output 2 inverted");
    if (wave & SAMD_TCC_WAVE_POL1)
        samdRdtPrint->println("    POL1: Compare output 1 inverted");
    if (wave & SAMD_TCC_WAVE_POL0)
        samdRdtPrint->println("    POL0: Compare output 0 inverted");

    if (wave & SAMD_TCC_WAVE_CICCEN3)
        samdRdtPrint->println("    CICCEN3: Circular channel 3 enable");
    if (wave & SAMD_TCC_WAVE_CICCEN2)
        samdRdtPrint->println("    CICCEN2: Circular channel 2 enable");
    if (wave & SAMD_TCC_WAVE_CICCEN1)
        samdRdtPrint->println("    CICCEN1: Circular channel 1 enable");
    if (wave & SAMD_TCC_WAVE_CICCEN0)
        samdRdtPrint->println("    CICCEN0: Circular channel 0 enable");

    if (wave & SAMD_TCC_WAVE_CIPEREN)
        samdRdtPrint->println("    CIPEREN: Circular PER enable");

    samdRdtPrint->print("    RAMP: ");
    samdRdtPrint->println(ramp[(wave & SAMD_TCC_WAVE_RAMP) >> 4]);

    samdRdtPrint->print("    WAVEGEN: ");
    samdRdtPrint->println(wavegen[wave & SAMD_TCC_WAVE_WAVEGEN]);
}

void samdTccCc(const char * regName, const char * fieldName, uint32_t cc, uint8_t dither)
{
    uint8_t cycles;

    // Decode and print the register value
    samdRdtPrint->print("  ");
    samdRdtPrint->print(regName);
    samdRdtPrint->print(": ");
    samdRdtPrint->print(cc, HEX);

    samdRdtPrint->print(", ");
    samdRdtPrint->print(fieldName);
    samdRdtPrint->print(": ");
    samdTccCount(nullptr, cc, dither);

    switch (dither)
    {
        case SAMD_TCC_CTRLA_RESOLUTION_NONE:
            cycles = 0;
            break;

        case SAMD_TCC_CTRLA_RESOLUTION_DITH4:
            cycles = cc & SAMD_TCC_PER_DITH4_DITHERCY;
            break;

        case SAMD_TCC_CTRLA_RESOLUTION_DITH5:
            cycles = cc & SAMD_TCC_PER_DITH5_DITHERCY;
            break;

        case SAMD_TCC_CTRLA_RESOLUTION_DITH6:
            cycles = cc & SAMD_TCC_PER_DITH6_DITHERCY;
            break;
    }
    samdRdtPrint->print(", DITHERCY: ");
    samdRdtPrint->println(cycles);
}

void samdTccConfig(uint32_t timerBaseAddress)
{
    uint8_t dither;
    bool enabled;
    const SAMD_TCC_REGS * tccRegs;
    uint8_t timer;

    // Validate the timer base address
    if ((timerBaseAddress < SAMD_TCC_0_BASE_ADDRESS)
    || (timerBaseAddress > SAMD_TCC_2_BASE_ADDRESS)
    || (timerBaseAddress & (~SAMD_TC_3_BASE_ADDRESS)))
        return;

    // Validate the timer number
    timer = (timerBaseAddress - SAMD_TCC_0_BASE_ADDRESS) >> 10;
    tccRegs = (const SAMD_TCC_REGS *)timerBaseAddress;

    // Print the timer name
    enabled = tccRegs->CTRLA & SAMD_TCC_CTRLA_ENABLE;
    samdRdtPrint->print("TCC");
    samdRdtPrint->print(timer);
    samdRdtPrint->println(enabled ? " enabled" : " disabled");

    // Print the register values
    if (enabled)
    {
        dither = samdTccCtrlA(tccRegs);
        samdTccCtrlB(tccRegs);
        samdTccSyncBusy(tccRegs);
        samdTccFctrl("FCTRLA", tccRegs->FCTRLA);
        samdTccFctrl("FCTRLB", tccRegs->FCTRLB);
        samdTccWExCtrl(tccRegs);
        samdTccDrvCtrl(tccRegs);
        samdTccDbgCtrl(tccRegs);
        samdTccEvCtrl(tccRegs);
        samdTccInten("INTEN", "enabled", tccRegs->INTENSET);
        samdTccInten("INTFLAG", "occurred", tccRegs->INTFLAG);
        samdTccStatus(tccRegs);
        samdTccCount("COUNT", tccRegs->COUNT, dither);
        samdRdtPrint->println();
        samdTccPatt("", tccRegs->PATT);
        samdTccWave("", tccRegs->WAVE);
        samdTccCc("PER", "PER", tccRegs->PER, dither);
        samdTccCc("CC0", "CC", tccRegs->CC0, dither);
        samdTccCc("CC1", "CC", tccRegs->CC1, dither);
        samdTccCc("CC2", "CC", tccRegs->CC2, dither);
        samdTccCc("CC3", "CC", tccRegs->CC3, dither);
        samdTccPatt("B", tccRegs->PATTB);
        samdTccWave("B", tccRegs->WAVEB);
        samdTccCc("PERB", "PERB", tccRegs->PERB, dither);
        samdTccCc("CCB0", "CCB", tccRegs->CCB0, dither);
        samdTccCc("CCB1", "CCB", tccRegs->CCB1, dither);
        samdTccCc("CCB2", "CCB", tccRegs->CCB2, dither);
        samdTccCc("CCB3", "CCB", tccRegs->CCB3, dither);
        samdRdtPrint->println();
    }
}

void samdTimerConfigs()
{
    samdTccConfig(SAMD_TCC_0_BASE_ADDRESS);
    samdTccConfig(SAMD_TCC_1_BASE_ADDRESS);
    samdTccConfig(SAMD_TCC_2_BASE_ADDRESS);
    samdTcConfig(SAMD_TC_3_BASE_ADDRESS);
    samdTcConfig(SAMD_TC_4_BASE_ADDRESS);
    samdTcConfig(SAMD_TC_5_BASE_ADDRESS);
    samdTcConfig(SAMD_TC_6_BASE_ADDRESS);
    samdTcConfig(SAMD_TC_7_BASE_ADDRESS);
}

#endif  //ARDUINO_ARCH_SAMD
