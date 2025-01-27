#include "EvoBQ25887.h"

// public methods
EvoBQ25887::EvoBQ25887()
{
}

bool EvoBQ25887::begin()
{

    Wire1.begin(SDA1_PIN, SCL1_PIN);

    if (this->readPartInfoReg() != BQ25887_PARTINFO)
    {
        return false;
    }

    return true;
}

uint8_t EvoBQ25887::readCellVoltageLimitReg()
{
    this->rawCellVoltageLimitReg = this->read8(BQ25887_REG_CELL_VOLTAGE_LIMIT);
    return this->rawCellVoltageLimitReg;
}

float EvoBQ25887::getCellVoltageLimit()
{
    float cellVoltageLimit = 3.4;

    cellVoltageLimit = cellVoltageLimit + (0.005 * this->rawCellVoltageLimitReg);

    if (cellVoltageLimit > 4.6)
    {
        cellVoltageLimit = 4.6;
    }

    return cellVoltageLimit;
}

uint8_t EvoBQ25887::readChargeCurrentLimitReg()
{
    this->rawChargeCurrentLimitReg = this->read8(BQ25887_REG_CHARGE_CURRENT_LIMIT);
    return this->rawChargeCurrentLimitReg;
}

float EvoBQ25887::getChargeCurrentLimit()
{
    float chargeCurrentLimit = 0.0;

    // add fractions for bits: from table 9 on page 34
    chargeCurrentLimit = chargeCurrentLimit + (1.600 * ((0b00100000 & this->rawChargeCurrentLimitReg) >> 5));
    chargeCurrentLimit = chargeCurrentLimit + (0.800 * ((0b00010000 & this->rawChargeCurrentLimitReg) >> 4));
    chargeCurrentLimit = chargeCurrentLimit + (0.400 * ((0b00001000 & this->rawChargeCurrentLimitReg) >> 3));
    chargeCurrentLimit = chargeCurrentLimit + (0.200 * ((0b00000100 & this->rawChargeCurrentLimitReg) >> 2));
    chargeCurrentLimit = chargeCurrentLimit + (0.100 * ((0b00000010 & this->rawChargeCurrentLimitReg) >> 1));
    chargeCurrentLimit = chargeCurrentLimit + (0.050 * ((0b00000001 & this->rawChargeCurrentLimitReg) >> 0));

    if (chargeCurrentLimit < 0.1)
    {
        chargeCurrentLimit = 0.1;
    }
    if (chargeCurrentLimit > 2.2)
    {
        chargeCurrentLimit = 2.2;
    }

    return chargeCurrentLimit;
}

bool EvoBQ25887::getHIZMode()
{
    bool hizMode = ((0b10000000 & this->rawChargeCurrentLimitReg) >> 7);
    return hizMode;
}

bool EvoBQ25887::getILIMPinFunction()
{
    bool ilimPinFunction = ((0b01000000 & this->rawChargeCurrentLimitReg) >> 6);
    return ilimPinFunction;
}

uint8_t EvoBQ25887::readInputVoltageLimitReg()
{
    this->rawInputVoltageLimitReg = this->read8(BQ25887_REG_INPUT_VOLTAGE_LIMIT);
    return this->rawInputVoltageLimitReg;
}

float EvoBQ25887::getInputVoltageLimit()
{
    float inputVoltageLimit = 3.9;

    // add fractions for bits: from table 10 on page 35
    inputVoltageLimit = inputVoltageLimit + (1.600 * ((0b00010000 & this->rawInputVoltageLimitReg) >> 4));
    inputVoltageLimit = inputVoltageLimit + (0.800 * ((0b00001000 & this->rawInputVoltageLimitReg) >> 3));
    inputVoltageLimit = inputVoltageLimit + (0.400 * ((0b00000100 & this->rawInputVoltageLimitReg) >> 2));
    inputVoltageLimit = inputVoltageLimit + (0.200 * ((0b00000010 & this->rawInputVoltageLimitReg) >> 1));
    inputVoltageLimit = inputVoltageLimit + (0.100 * ((0b00000001 & this->rawInputVoltageLimitReg) >> 0));

    if (inputVoltageLimit > 5.5)
    {
        inputVoltageLimit = 5.5;
    }

    return inputVoltageLimit;
}

bool EvoBQ25887::getEN_VINDPM_RST()
{
    bool enVindpmRst = ((0b10000000 & this->rawInputVoltageLimitReg) >> 7);
    return enVindpmRst;
}

bool EvoBQ25887::getEN_BAT_DISCHG()
{
    bool enBatDischg = ((0b01000000 & this->rawInputVoltageLimitReg) >> 6);
    return enBatDischg;
}

bool EvoBQ25887::getPFM_OOA_DIS()
{
    bool pfmOoaDis = ((0b00100000 & this->rawInputVoltageLimitReg) >> 5);
    return pfmOoaDis;
}

uint8_t EvoBQ25887::readInputCurrentLimitReg()
{
    this->rawInputCurrentLimitReg = this->read8(BQ25887_REG_INPUT_CURRENT_LIMIT);
    return this->rawInputCurrentLimitReg;
}

float EvoBQ25887::getInputCurrentLimit()
{
    float inputCurrentLimit = 0.5;

    // add fractions for bits: from table 11 on page 36
    inputCurrentLimit = inputCurrentLimit + (1.600 * ((0b00010000 & this->rawInputCurrentLimitReg) >> 4));
    inputCurrentLimit = inputCurrentLimit + (0.800 * ((0b00001000 & this->rawInputCurrentLimitReg) >> 3));
    inputCurrentLimit = inputCurrentLimit + (0.400 * ((0b00000100 & this->rawInputCurrentLimitReg) >> 2));
    inputCurrentLimit = inputCurrentLimit + (0.200 * ((0b00000010 & this->rawInputCurrentLimitReg) >> 1));
    inputCurrentLimit = inputCurrentLimit + (0.100 * ((0b00000001 & this->rawInputCurrentLimitReg) >> 0));

    if (inputCurrentLimit > 3.3)
    {
        inputCurrentLimit = 3.3;
    }

    return inputCurrentLimit;
}

bool EvoBQ25887::getFORCE_ICO()
{
    bool forceIco = ((0b10000000 & this->rawInputCurrentLimitReg) >> 7);
    return forceIco;
}

bool EvoBQ25887::getFORCE_INDET()
{
    bool forceIndet = ((0b01000000 & this->rawInputCurrentLimitReg) >> 6);
    return forceIndet;
}

bool EvoBQ25887::getEN_ICO()
{
    bool enIco = ((0b00100000 & this->rawInputCurrentLimitReg) >> 5);
    return enIco;
}

uint8_t EvoBQ25887::readPreTermCurrentLimitReg()
{
    this->rawPreTermCurrentLimitReg = this->read8(BQ25887_REG_PRE_TERM_CURRENT_LIMIT);
    return this->rawPreTermCurrentLimitReg;
}

float EvoBQ25887::getPrechargeCurrentLimit()
{
    float prechargeCurrentLimit = 0.05;

    // add fractions for bits: from table 12 on page 37
    prechargeCurrentLimit = prechargeCurrentLimit + (0.400 * ((0b10000000 & this->rawPreTermCurrentLimitReg) >> 7));
    prechargeCurrentLimit = prechargeCurrentLimit + (0.200 * ((0b01000000 & this->rawPreTermCurrentLimitReg) >> 6));
    prechargeCurrentLimit = prechargeCurrentLimit + (0.100 * ((0b00100000 & this->rawPreTermCurrentLimitReg) >> 5));
    prechargeCurrentLimit = prechargeCurrentLimit + (0.050 * ((0b00010000 & this->rawPreTermCurrentLimitReg) >> 4));

    if (prechargeCurrentLimit > 0.8)
    {
        prechargeCurrentLimit = 0.8;
    }

    return prechargeCurrentLimit;
}

float EvoBQ25887::getTerminationCurrentLimit()
{
    float terminationCurrentLimit = 0.05;

    // add fractions for bits: from table 12 on page 37
    terminationCurrentLimit = terminationCurrentLimit + (0.400 * ((0b00001000 & this->rawPreTermCurrentLimitReg) >> 3));
    terminationCurrentLimit = terminationCurrentLimit + (0.200 * ((0b00000100 & this->rawPreTermCurrentLimitReg) >> 2));
    terminationCurrentLimit = terminationCurrentLimit + (0.100 * ((0b00000010 & this->rawPreTermCurrentLimitReg) >> 1));
    terminationCurrentLimit = terminationCurrentLimit + (0.050 * ((0b00000001 & this->rawPreTermCurrentLimitReg) >> 0));

    if (terminationCurrentLimit > 0.8)
    {
        terminationCurrentLimit = 0.8;
    }

    return terminationCurrentLimit;
}

uint32_t EvoBQ25887::readChargeControlSettingsReg()
{
    this->rawChargeControlSettingsReg = this->read32(BQ25887_REG_CHARGER_CONTROL_1);
    return this->rawChargeControlSettingsReg;
}

bool EvoBQ25887::getEN_TERM()
{
    bool enTerm = ((0x00000080 & this->rawChargeControlSettingsReg) >> 7);
    return enTerm;
}

bool EvoBQ25887::getSTAT_DIS()
{
    bool statDis = ((0x00000040 & this->rawChargeControlSettingsReg) >> 6);
    return statDis;
}

uint8_t EvoBQ25887::getWATCHDOG()
{
    uint8_t watchdog = ((0x00000030 & this->rawChargeControlSettingsReg) >> 4);

    switch (watchdog)
    {
    case 0b00:
        watchdog = 0;
        break;
    case 0b01:
        watchdog = 40;
        break;
    case 0b10:
        watchdog = 80;
        break;
    case 0b11:
        watchdog = 160;
        break;
    default:
        watchdog = 255;
        break;
    }

    return watchdog;
}

bool EvoBQ25887::getEN_TIMER()
{
    bool enTimer = ((0x00000008 & this->rawChargeControlSettingsReg) >> 3);
    return enTimer;
}

uint8_t EvoBQ25887::getCHG_TIMER()
{
    uint8_t chgTimer = ((0x00000006 & this->rawChargeControlSettingsReg) >> 1);

    switch (chgTimer)
    {
    case 0b00:
        chgTimer = 5;
        break;
    case 0b01:
        chgTimer = 8;
        break;
    case 0b10:
        chgTimer = 12;
        break;
    case 0b11:
        chgTimer = 20;
        break;
    default:
        chgTimer = 255;
        break;
    }

    return chgTimer;
}

bool EvoBQ25887::getTMR2X_EN()
{
    bool tmr2xEn = ((0x00000001 & this->rawChargeControlSettingsReg) >> 0);
    return tmr2xEn;
}

bool EvoBQ25887::getAUTO_INDET_EN()
{
    bool autoIndetEn = ((0x00004000 & this->rawChargeControlSettingsReg) >> 14);
    return autoIndetEn;
}

uint8_t EvoBQ25887::getT_REG_THRESH()
{
    uint8_t tRegThresh = ((0x00003000 & this->rawChargeControlSettingsReg) >> 12);

    switch (tRegThresh)
    {
    case 0b00:
        tRegThresh = 60;
        break;
    case 0b01:
        tRegThresh = 80;
        break;
    case 0b10:
        tRegThresh = 100;
        break;
    case 0b11:
        tRegThresh = 120;
        break;
    default:
        tRegThresh = 255;
        break;
    }

    return tRegThresh;
}

bool EvoBQ25887::getEN_CHG()
{
    bool enChg = ((0x00000800 & this->rawChargeControlSettingsReg) >> 11);
    return enChg;
}

float EvoBQ25887::getCELLLOWV_THRESH()
{
    bool preChgThresh = ((0x00000400 & this->rawChargeControlSettingsReg) >> 10);
    float cellLowVThresh = 0.0;

    if (preChgThresh)
    {
        cellLowVThresh = 3.0;
    }
    else
    {
        cellLowVThresh = 2.8;
    }

    return cellLowVThresh;
}

float EvoBQ25887::getVCELL_RECHG_THRESH_OFF()
{
    uint8_t vCellRechgThreshOffReg = ((0x00000300 & this->rawChargeControlSettingsReg) >> 8);
    float vCellRechgThreshOff = 0.05;
    vCellRechgThreshOff = (0.05 * vCellRechgThreshOffReg);
    return vCellRechgThreshOff;
}

bool EvoBQ25887::getPFM_DIS()
{
    bool pfmDis = ((0x00800000 & this->rawChargeControlSettingsReg) >> 23);
    return pfmDis;
}

bool EvoBQ25887::getWD_RST()
{
    bool wdRst = ((0x00400000 & this->rawChargeControlSettingsReg) >> 22);
    return wdRst;
}

uint8_t EvoBQ25887::getTOPOFF_TIMER()
{
    uint8_t topOffTimer = ((0x00300000 & this->rawChargeControlSettingsReg) >> 20);

    switch (topOffTimer)
    {
    case 0b00:
        topOffTimer = 0;
        break;
    case 0b01:
        topOffTimer = 15;
        break;
    case 0b10:
        topOffTimer = 30;
        break;
    case 0b11:
        topOffTimer = 45;
        break;
    default:
        topOffTimer = 255;
        break;
    }

    return topOffTimer;
}

float EvoBQ25887::getJEITA_VSET()
{
    uint8_t jeitaVsetReg = ((0x18000000 & this->rawChargeControlSettingsReg) >> 27);
    float jeitaVset = 999.99;

    switch (jeitaVsetReg)
    {
    case 0b00:
        jeitaVset = 0.0;
        break;
    case 0b01:
        jeitaVset = 8.0;
        break;
    case 0b10:
        jeitaVset = 8.3;
        break;
    case 0b11:
        jeitaVset = 111.11;
        // use get VREG instead
        break;
    default:
        jeitaVset = 888.88;
        break;
    }

    return jeitaVset;
}

uint8_t EvoBQ25887::getJEITA_ISETH()
{
    uint8_t jeitaIsetH = ((0x04000000 & this->rawChargeControlSettingsReg) >> 26);

    switch (jeitaIsetH)
    {
    case 0:
        jeitaIsetH = 40;
        break;
    case 1:
        jeitaIsetH = 100;
        break;
    default:
        jeitaIsetH = 255;
        break;
    }

    return jeitaIsetH;
}

uint8_t EvoBQ25887::getJEITA_ISETC()
{
    uint8_t jeitaIsetC = ((0x03000000 & this->rawChargeControlSettingsReg) >> 24);

    switch (jeitaIsetC)
    {
    case 0b00:
        jeitaIsetC = 0;
        break;
    case 0b01:
        jeitaIsetC = 20;
        break;
    case 0b10:
        jeitaIsetC = 40;
        break;
    case 0b11:
        jeitaIsetC = 100;
        break;
    default:
        jeitaIsetC = 255;
        break;
    }

    return jeitaIsetC;
}

uint8_t EvoBQ25887::readIcoCurrentLimitReg()
{
    this->rawIcoCurrentLimitReg = this->read8(BQ25887_REG_ICO_CURRENT_LIMIT);
    return this->rawIcoCurrentLimitReg;
}

float EvoBQ25887::getICOCurrentLimit()
{
    float icoCurrentLimit = 0.5;

    // add fractions for bits: from table 18 on page 43
    icoCurrentLimit = icoCurrentLimit + (1.600 * ((0b00010000 & this->rawIcoCurrentLimitReg) >> 4));
    icoCurrentLimit = icoCurrentLimit + (0.800 * ((0b00001000 & this->rawIcoCurrentLimitReg) >> 3));
    icoCurrentLimit = icoCurrentLimit + (0.400 * ((0b00000100 & this->rawIcoCurrentLimitReg) >> 2));
    icoCurrentLimit = icoCurrentLimit + (0.200 * ((0b00000010 & this->rawIcoCurrentLimitReg) >> 1));
    icoCurrentLimit = icoCurrentLimit + (0.100 * ((0b00000001 & this->rawIcoCurrentLimitReg) >> 0));

    if (icoCurrentLimit > 3.3)
    {
        icoCurrentLimit = 3.3;
    }

    return icoCurrentLimit;
}

uint16_t EvoBQ25887::readChargeStatusReg()
{
    this->rawChargeStatusReg = this->read16(BQ25887_REG_CHARGER_STATUS_1);
    return this->rawChargeStatusReg;
}

bool EvoBQ25887::getIINDPM_STAT()
{
    bool iInDpmStat = ((0x0040 & this->rawChargeStatusReg) >> 6);
    return iInDpmStat;
}

bool EvoBQ25887::getVINDPM_STAT()
{
    bool vInDpmStat = ((0x0020 & this->rawChargeStatusReg) >> 5);
    return vInDpmStat;
}

bool EvoBQ25887::getTREG_STAT()
{
    bool tRegStat = ((0x0010 & this->rawChargeStatusReg) >> 4);
    return tRegStat;
}

bool EvoBQ25887::getWD_STAT()
{
    bool wdStat = ((0x0008 & this->rawChargeStatusReg) >> 3);
    return wdStat;
}

uint8_t EvoBQ25887::getCHRG_STAT()
{
    uint8_t chrgStat = ((0x0007 & this->rawChargeStatusReg) >> 0);
    return chrgStat;
}

bool EvoBQ25887::getPG_STAT()
{
    bool pgStat = ((0x8000 & this->rawChargeStatusReg) >> 15);
    return pgStat;
}

uint8_t EvoBQ25887::getVBUS_STAT()
{
    uint8_t vBusStat = ((0x7000 & this->rawChargeStatusReg) >> 12);
    return vBusStat;
}

uint8_t EvoBQ25887::getICO_STAT()
{
    uint8_t icoStat = ((0x0600 & this->rawChargeStatusReg) >> 9);
    return icoStat;
}

uint8_t EvoBQ25887::readNtcStatusReg()
{
    this->rawNtcStatusReg = this->read8(BQ25887_REG_NTC_STATUS);
    return this->rawNtcStatusReg;
}

uint8_t EvoBQ25887::getNTCStatus()
{ // should give exact same result as readNtcStatusReg().  Adding this method for consistency
    uint8_t ntcStatus = ((0b00000111 & this->rawNtcStatusReg) >> 0);
    return ntcStatus;
}

uint8_t EvoBQ25887::readFaultStatusReg()
{
    this->rawFaultStatusReg = this->read8(BQ25887_REG_FAULT_STATUS);
    return this->rawFaultStatusReg;
}

bool EvoBQ25887::getVBUS_OVP_STAT()
{
    bool vbusOvpStat = ((0b10000000 & this->rawFaultStatusReg) >> 7);
    return vbusOvpStat;
}

bool EvoBQ25887::getTSHUT_STAT()
{
    bool tShutStat = ((0b01000000 & this->rawFaultStatusReg) >> 6);
    return tShutStat;
}

bool EvoBQ25887::getTMR_STAT()
{
    bool tmrStat = ((0b00010000 & this->rawFaultStatusReg) >> 4);
    return tmrStat;
}

uint16_t EvoBQ25887::readChargeFlagsReg()
{
    this->rawChargeFlagsReg = this->read16(BQ25887_REG_CHARGER_FLAG_1);
    return this->rawChargeFlagsReg;
}

bool EvoBQ25887::getIINDPM_FLAG()
{
    bool iInDpmFlag = ((0x0040 & this->rawChargeFlagsReg) >> 6);
    return iInDpmFlag;
}

bool EvoBQ25887::getVINDPM_FLAG()
{
    bool vInDpmFlag = ((0x0020 & this->rawChargeFlagsReg) >> 5);
    return vInDpmFlag;
}

bool EvoBQ25887::getTREG_FLAG()
{
    bool tRegFlag = ((0x0010 & this->rawChargeFlagsReg) >> 4);
    return tRegFlag;
}

bool EvoBQ25887::getWD_FLAG()
{
    bool wdFlag = ((0x0008 & this->rawChargeFlagsReg) >> 3);
    return wdFlag;
}

bool EvoBQ25887::getCHRG_FLAG()
{
    bool chrgFlag = ((0x0001 & this->rawChargeFlagsReg) >> 0);
    return chrgFlag;
}

bool EvoBQ25887::getPG_FLAG()
{
    bool pgFlag = ((0x8000 & this->rawChargeFlagsReg) >> 15);
    return pgFlag;
}

bool EvoBQ25887::getVBUS_FLAG()
{
    bool vbusFlag = ((0x1000 & this->rawChargeFlagsReg) >> 12);
    return vbusFlag;
}

bool EvoBQ25887::getTS_FLAG()
{
    bool tsFlag = ((0x0400 & this->rawChargeFlagsReg) >> 10);
    return tsFlag;
}

bool EvoBQ25887::getICO_FLAG()
{
    bool icoFlag = ((0x0200 & this->rawChargeFlagsReg) >> 9);
    return icoFlag;
}

uint8_t EvoBQ25887::readFaultFlagsReg()
{
    this->rawFaultFlagsReg = this->read8(BQ25887_REG_FAULT_FLAG);
    return this->rawFaultFlagsReg;
}

bool EvoBQ25887::getVBUS_OVP_FLAG()
{
    bool vbusOvpFlag = ((0b10000000 & this->rawFaultFlagsReg) >> 7);
    return vbusOvpFlag;
}

bool EvoBQ25887::getTSHUT_FLAG()
{
    bool tShutFlag = ((0b01000000 & this->rawFaultFlagsReg) >> 6);
    return tShutFlag;
}

bool EvoBQ25887::getTMR_FLAG()
{
    bool tmrFlag = ((0b00010000 & this->rawFaultFlagsReg) >> 4);
    return tmrFlag;
}

uint16_t EvoBQ25887::readChargerIntMaskReg()
{
    this->rawChargerIntMaskReg = this->read16(BQ25887_REG_CHARGER_MASK_1);
    return this->rawChargerIntMaskReg;
}

bool EvoBQ25887::getADC_DONE_MASK()
{
    bool adcDoneMask = ((0x0080 & this->rawChargerIntMaskReg) >> 7);
    return adcDoneMask;
}

bool EvoBQ25887::getIINDPM_MASK()
{
    bool iInDpmMask = ((0x0040 & this->rawChargerIntMaskReg) >> 6);
    return iInDpmMask;
}

bool EvoBQ25887::getVINDPM_MASK()
{
    bool vInDpmMask = ((0x0020 & this->rawChargerIntMaskReg) >> 5);
    return vInDpmMask;
}

bool EvoBQ25887::getT_REG_MASK()
{
    bool tRegMask = ((0x0010 & this->rawChargerIntMaskReg) >> 4);
    return tRegMask;
}

bool EvoBQ25887::getWD_MASK()
{
    bool wdMask = ((0x0008 & this->rawChargerIntMaskReg) >> 3);
    return wdMask;
}

bool EvoBQ25887::getCHRG_MASK()
{
    bool chrgMask = ((0x0001 & this->rawChargerIntMaskReg) >> 0);
    return chrgMask;
}

bool EvoBQ25887::getPG_MASK()
{
    bool pgMask = ((0x8000 & this->rawChargerIntMaskReg) >> 15);
    return pgMask;
}

bool EvoBQ25887::getVBUS_MASK()
{
    bool vbusMask = ((0x1000 & this->rawChargerIntMaskReg) >> 12);
    return vbusMask;
}

bool EvoBQ25887::getTS_MASK()
{
    bool tsMask = ((0x0400 & this->rawChargerIntMaskReg) >> 10);
    return tsMask;
}

bool EvoBQ25887::getICO_MASK()
{
    bool icoMask = ((0x0200 & this->rawChargerIntMaskReg) >> 9);
    return icoMask;
}

uint8_t EvoBQ25887::readFaultIntMaskReg()
{
    this->rawFaultIntMaskReg = this->read8(BQ25887_REG_FAULT_MASK);
    return this->rawFaultIntMaskReg;
}

bool EvoBQ25887::getVBUS_OVP_MASK()
{
    bool vbusOvpMask = ((0b10000000 & this->rawFaultIntMaskReg) >> 7);
    return vbusOvpMask;
}

bool EvoBQ25887::getTSHUT_MASK()
{
    bool tShutMask = ((0b01000000 & this->rawFaultIntMaskReg) >> 6);
    return tShutMask;
}

bool EvoBQ25887::getTMR_MASK()
{
    bool tmrMask = ((0b00010000 & this->rawFaultIntMaskReg) >> 4);
    return tmrMask;
}

bool EvoBQ25887::getSNS_SHORT_MASK()
{
    bool snsShortMask = ((0b00001000 & this->rawFaultIntMaskReg) >> 3);
    return snsShortMask;
}

uint8_t EvoBQ25887::readADCControlSettingsReg()
{
    this->rawADCControlSettingsReg = this->read8(BQ25887_REG_ADC_CONTROL);
    return this->rawADCControlSettingsReg;
}

bool EvoBQ25887::getADC_EN()
{
    bool adcEn = ((0b10000000 & this->rawADCControlSettingsReg) >> 7);
    return adcEn;
}

bool EvoBQ25887::getADC_ONE_SHOT()
{
    bool adcRate = ((0b01000000 & this->rawADCControlSettingsReg) >> 6);
    return adcRate;
}

uint8_t EvoBQ25887::getADC_SAMPLE_SPEED()
{
    uint8_t adcSample = ((0b00110000 & this->rawADCControlSettingsReg) >> 4);
    return adcSample;
}

uint8_t EvoBQ25887::readADCFuncDisSettingsReg()
{
    this->rawADCFuncDisSettingsReg = this->read8(BQ25887_REG_ADC_FUNCTION_DISABLE);
    return this->rawADCFuncDisSettingsReg;
}

bool EvoBQ25887::getIBUS_ADC_DIS()
{
    bool ibusAdcDis = ((0b10000000 & this->rawADCFuncDisSettingsReg) >> 7);
    return ibusAdcDis;
}

bool EvoBQ25887::getICHG_ADC_DIS()
{
    bool ichgAdcDis = ((0b01000000 & this->rawADCFuncDisSettingsReg) >> 6);
    return ichgAdcDis;
}

bool EvoBQ25887::getVBUS_ADC_DIS()
{
    bool vbusAdcDis = ((0b00100000 & this->rawADCFuncDisSettingsReg) >> 5);
    return vbusAdcDis;
}

bool EvoBQ25887::getVBAT_ADC_DIS()
{
    bool vbatAdcDis = ((0b00010000 & this->rawADCFuncDisSettingsReg) >> 4);
    return vbatAdcDis;
}

bool EvoBQ25887::getTS_ADC_DIS()
{
    bool tsAdcDis = ((0b00000100 & this->rawADCFuncDisSettingsReg) >> 2);
    return tsAdcDis;
}

bool EvoBQ25887::getVCELL_ADC_DIS()
{
    bool vcellAdcDis = ((0b00000010 & this->rawADCFuncDisSettingsReg) >> 1);
    return vcellAdcDis;
}

bool EvoBQ25887::getTDIE_ADC_DIS()
{
    bool tDieAdcDis = ((0b00000001 & this->rawADCFuncDisSettingsReg) >> 0);
    return tDieAdcDis;
}

int16_t EvoBQ25887::readADCIbusReg()
{
    this->rawADCIbusReg = this->readADC(BQ25887_REG_IBUS_ADC_1);
    return this->rawADCIbusReg;
}

float EvoBQ25887::getADC_IBUS()
{
    float adcIbus = float(this->rawADCIbusReg) / 1000.0;
    return adcIbus;
}

int16_t EvoBQ25887::readADCIchgReg()
{
    this->rawADCIchgReg = this->readADC(BQ25887_REG_ICHG_ADC_1);
    return this->rawADCIchgReg;
}

float EvoBQ25887::getADC_ICHG()
{
    float adcIchg = float(this->rawADCIchgReg) / 1000.0;
    return adcIchg;
}

int16_t EvoBQ25887::readADCVbusReg()
{
    this->rawADCVbusReg = this->readADC(BQ25887_REG_VBUS_ADC_1);
    return this->rawADCVbusReg;
}

float EvoBQ25887::getADC_VBUS()
{
    float adcVbus = float(this->rawADCVbusReg) / 1000.0;
    return adcVbus;
}

int16_t EvoBQ25887::readADCVbatReg()
{
    this->rawADCVbatReg = this->readADC(BQ25887_REG_VBAT_ADC_1);
    return this->rawADCVbatReg;
}

float EvoBQ25887::getADC_VBAT()
{
    float adcVbat = float(this->rawADCVbatReg) / 1000.0;
    return adcVbat;
}

int16_t EvoBQ25887::readADCVCellTopReg()
{
    this->rawADCVCellTopReg = this->readADC(BQ25887_REG_VCELL_TOP_ADC_1);
    return this->rawADCVCellTopReg;
}

float EvoBQ25887::getADC_VCELLTOP()
{
    float adcVCellTop = float(this->rawADCVCellTopReg) / 1000.0;
    return adcVCellTop;
}

uint16_t EvoBQ25887::readADCTsReg()
{
    this->rawADCTsReg = this->read16(BQ25887_REG_TS_ADC_1);
    return this->rawADCTsReg;
}

float EvoBQ25887::getADC_TS()
{
    float adcTs = 0.0;

    adcTs = adcTs + (50.000 * ((0x0002 & this->rawADCTsReg) >> 1));
    adcTs = adcTs + (25.000 * ((0x0001 & this->rawADCTsReg) >> 0));

    adcTs = adcTs + (12.500 * ((0x8000 & this->rawADCTsReg) >> 15));
    adcTs = adcTs + (6.250 * ((0x4000 & this->rawADCTsReg) >> 14));
    adcTs = adcTs + (3.125 * ((0x2000 & this->rawADCTsReg) >> 13));
    adcTs = adcTs + (1.563 * ((0x1000 & this->rawADCTsReg) >> 12));
    adcTs = adcTs + (0.781 * ((0x0800 & this->rawADCTsReg) >> 11));
    adcTs = adcTs + (0.391 * ((0x0400 & this->rawADCTsReg) >> 10));
    adcTs = adcTs + (0.195 * ((0x0200 & this->rawADCTsReg) >> 9));
    adcTs = adcTs + (0.098 * ((0x0100 & this->rawADCTsReg) >> 8));

    if (adcTs > 94.9)
    {
        adcTs = 94.9;
    }

    return adcTs;
}

uint16_t EvoBQ25887::readADCTDieReg()
{
    this->rawADCTDieReg = this->read16(BQ25887_REG_TDIE_ADC_1);
    return this->rawADCTDieReg;
}

float EvoBQ25887::getADC_TDIE()
{
    float adcTDie = 0.0;

    adcTDie = adcTDie + (128.0 * ((0x0001 & this->rawADCTDieReg) >> 0));

    adcTDie = adcTDie + (64.0 * ((0x8000 & this->rawADCTDieReg) >> 15));
    adcTDie = adcTDie + (32.0 * ((0x4000 & this->rawADCTDieReg) >> 14));
    adcTDie = adcTDie + (16.0 * ((0x2000 & this->rawADCTDieReg) >> 13));
    adcTDie = adcTDie + (8.0 * ((0x1000 & this->rawADCTDieReg) >> 12));
    adcTDie = adcTDie + (4.0 * ((0x0800 & this->rawADCTDieReg) >> 11));
    adcTDie = adcTDie + (2.0 * ((0x0400 & this->rawADCTDieReg) >> 10));
    adcTDie = adcTDie + (1.0 * ((0x0200 & this->rawADCTDieReg) >> 9));
    adcTDie = adcTDie + (0.5 * ((0x0100 & this->rawADCTDieReg) >> 8));

    if (adcTDie > 128.0)
    {
        adcTDie = 128.0;
    }

    return adcTDie;
}

int16_t EvoBQ25887::readADCVCellBotReg()
{
    this->rawADCVCellBotReg = this->readADC(BQ25887_REG_VCELL_BOT_ADC_1);
    return this->rawADCVCellBotReg;
}

float EvoBQ25887::getADC_VCELLBOT()
{
    float adcVCellBot = float(this->rawADCVCellBotReg) / 1000.0;
    return adcVCellBot;
}

uint8_t EvoBQ25887::readPartInfoReg()
{
    this->rawPartInfoReg = this->read8(BQ25887_REG_PART_INFORMATION);
    return this->rawPartInfoReg;
}

bool EvoBQ25887::getREG_RST()
{
    bool regRst = ((0b10000000 & this->rawPartInfoReg) >> 7);
    return regRst;
}

uint8_t EvoBQ25887::getPartNumber()
{
    uint8_t partNumber = ((0b01111000 & this->rawPartInfoReg) >> 3);
    return partNumber;
}

uint8_t EvoBQ25887::getDevRev()
{
    uint8_t devNumber = ((0b00000111 & this->rawPartInfoReg) >> 0);
    return devNumber;
}

uint16_t EvoBQ25887::readCellBalContSettingsReg()
{
    this->rawCellBalContSettingsReg = this->read16(BQ25887_REG_CELL_BALANCING_CONTROL_1);
    return this->rawCellBalContSettingsReg;
}

float EvoBQ25887::getVDIFF_END_OFFSET()
{
    float vDiffEndOffset = 0.030;
    vDiffEndOffset = vDiffEndOffset + (0.01 * ((0x00E0 & this->rawCellBalContSettingsReg) >> 5));
    return vDiffEndOffset;
}

float EvoBQ25887::getTCB_QUAL_INTERVAL()
{
    float tcbQualInterval = 0.0;
    if (((0x0010 & this->rawCellBalContSettingsReg) >> 4))
    {
        tcbQualInterval = 240.0; // 4 minutes in seconds
    }
    else
    {
        tcbQualInterval = 120.0; // 2 minutes in seconds
    }
    return tcbQualInterval;
}

float EvoBQ25887::getTCB_ACTIVE()
{
    float tcbActive = 0.0;
    switch (((0x000C & this->rawCellBalContSettingsReg) >> 2))
    {
    case 0b00:
        tcbActive = 4.0;
        break;
    case 0b01:
        tcbActive = 32.0;
        break;
    case 0b10:
        tcbActive = 120.0;
        break;
    case 0b11:
        tcbActive = 240.0;
        break;
    default:
        tcbActive = 999.99;
        break;
    }

    return tcbActive;
}

float EvoBQ25887::getTSETTLE()
{
    float tSettle = 0.0;
    switch (((0x0003 & this->rawCellBalContSettingsReg) >> 0))
    {
    case 0b00:
        tSettle = 0.01;
        break;
    case 0b01:
        tSettle = 0.10;
        break;
    case 0b10:
        tSettle = 1.0;
        break;
    case 0b11:
        tSettle = 2.0;
        break;
    default:
        tSettle = 999.99;
        break;
    }

    return tSettle;
}

float EvoBQ25887::getVQUAL_TH()
{
    float vQualTh = 0.04;
    uint16_t vQualThRaw = ((0xF000 & this->rawCellBalContSettingsReg) >> 12);
    if (vQualThRaw != 0x000F)
    {
        vQualTh = vQualTh + (0.01 * vQualThRaw);
    }
    else
    {
        vQualTh = 0.0;
    }

    return vQualTh;
}

float EvoBQ25887::getVDIFF_START()
{
    float vDiffStart = 0.04;
    uint16_t vDiffStartRaw = ((0x0F00 & this->rawCellBalContSettingsReg) >> 8);
    vDiffStart = vDiffStart + (0.01 * vDiffStartRaw);

    return vDiffStart;
}

uint8_t EvoBQ25887::readCellBalStatReg()
{
    this->rawCellBalStatReg = this->read8(BQ25887_REG_CELL_BALANCING_STAT_CONT);
    return this->rawCellBalStatReg;
}

bool EvoBQ25887::getCB_CHG_DIS()
{
    bool cbChgDis = ((0b10000000 & this->rawCellBalStatReg) >> 7);
    return cbChgDis;
}

bool EvoBQ25887::getCB_AUTO_EN()
{
    bool cbAutoEn = ((0b01000000 & this->rawCellBalStatReg) >> 6);
    return cbAutoEn;
}

bool EvoBQ25887::getCB_STAT()
{
    bool cbStat = ((0b00100000 & this->rawCellBalStatReg) >> 5);
    return cbStat;
}

bool EvoBQ25887::getHS_CV_STAT()
{
    bool hsCvStat = ((0b00010000 & this->rawCellBalStatReg) >> 4);
    return hsCvStat;
}

bool EvoBQ25887::getLS_CV_STAT()
{
    bool lsCvStat = ((0b00001000 & this->rawCellBalStatReg) >> 3);
    return lsCvStat;
}

bool EvoBQ25887::getHS_OV_STAT()
{
    bool hsOvStat = ((0b00000100 & this->rawCellBalStatReg) >> 2);
    return hsOvStat;
}

bool EvoBQ25887::getLS_OV_STAT()
{
    bool lsOvStat = ((0b00000010 & this->rawCellBalStatReg) >> 1);
    return lsOvStat;
}

bool EvoBQ25887::getCB_OC_STAT()
{
    bool cbOcStat = ((0b00000001 & this->rawCellBalStatReg) >> 0);
    return cbOcStat;
}

uint8_t EvoBQ25887::readCellBalFlagsReg()
{
    this->rawCellBalFlagsReg = this->read8(BQ25887_REG_CELL_BALANCING_FLAG);
    return this->rawCellBalFlagsReg;
}

bool EvoBQ25887::getQCBH_EN()
{
    bool qcbhEn = ((0b10000000 & this->rawCellBalFlagsReg) >> 7);
    return qcbhEn;
}

bool EvoBQ25887::getQCBL_EN()
{
    bool qcblEn = ((0b01000000 & this->rawCellBalFlagsReg) >> 6);
    return qcblEn;
}

bool EvoBQ25887::getCB_FLAG()
{
    bool cbFlag = ((0b00100000 & this->rawCellBalFlagsReg) >> 5);
    return cbFlag;
}

bool EvoBQ25887::getHS_CV_FLAG()
{
    bool hsCvFlag = ((0b00010000 & this->rawCellBalFlagsReg) >> 4);
    return hsCvFlag;
}

bool EvoBQ25887::getLS_CV_FLAG()
{
    bool lsCvFlag = ((0b00001000 & this->rawCellBalFlagsReg) >> 3);
    return lsCvFlag;
}

bool EvoBQ25887::getHS_OV_FLAG()
{
    bool hsOvFlag = ((0b00000100 & this->rawCellBalFlagsReg) >> 2);
    return hsOvFlag;
}

bool EvoBQ25887::getLS_OV_FLAG()
{
    bool lsOvFlag = ((0b00000010 & this->rawCellBalFlagsReg) >> 1);
    return lsOvFlag;
}

bool EvoBQ25887::getCB_OC_FLAG()
{
    bool cbOcFlag = ((0b00000001 & this->rawCellBalFlagsReg) >> 0);
    return cbOcFlag;
}

uint8_t EvoBQ25887::readCellBalIntMaskReg()
{
    this->rawCellBalIntMaskReg = this->read8(BQ25887_REG_CELL_BALANCING_MASK);
    return this->rawCellBalIntMaskReg;
}

bool EvoBQ25887::getCB_MASK()
{
    bool cbMask = ((0b00100000 & this->rawCellBalIntMaskReg) >> 5);
    return cbMask;
}

bool EvoBQ25887::getHS_CV_MASK()
{
    bool hsCvMask = ((0b00010000 & this->rawCellBalIntMaskReg) >> 4);
    return hsCvMask;
}

bool EvoBQ25887::getLS_CV_MASK()
{
    bool lsCvMask = ((0b00001000 & this->rawCellBalIntMaskReg) >> 3);
    return lsCvMask;
}

bool EvoBQ25887::getHS_OV_MASK()
{
    bool hsOvMask = ((0b00000100 & this->rawCellBalIntMaskReg) >> 2);
    return hsOvMask;
}

bool EvoBQ25887::getLS_OV_MASK()
{
    bool lsOvMask = ((0b00000010 & this->rawCellBalIntMaskReg) >> 1);
    return lsOvMask;
}

bool EvoBQ25887::getCB_OC_MASK()
{
    bool cbOcMask = ((0b00000001 & this->rawCellBalIntMaskReg) >> 0);
    return cbOcMask;
}

void EvoBQ25887::pollAllRegs()
{
    this->readCellVoltageLimitReg();
    this->readChargeCurrentLimitReg();
    this->readInputVoltageLimitReg();
    this->readInputCurrentLimitReg();
    this->readPreTermCurrentLimitReg();
    this->readChargeControlSettingsReg();
    this->readIcoCurrentLimitReg();
    this->readChargeStatusReg();
    this->readNtcStatusReg();
    this->readFaultStatusReg();
    this->readChargeFlagsReg();
    this->readFaultFlagsReg();
    this->readChargerIntMaskReg();
    this->readFaultIntMaskReg();
    this->readADCControlSettingsReg();
    this->readADCFuncDisSettingsReg();
    this->readADCIbusReg();
    this->readADCIchgReg();
    this->readADCVbusReg();
    this->readADCVbatReg();
    this->readADCVCellTopReg();
    this->readADCTsReg();
    this->readADCTDieReg();
    this->readADCVCellBotReg();
    this->readPartInfoReg();
    this->readCellBalContSettingsReg();
    this->readCellBalStatReg();
    this->readCellBalFlagsReg();
    this->readCellBalIntMaskReg();
}

void EvoBQ25887::setCellVoltageLimit(float voltLimit)
{
    if (voltLimit < 3.4)
    {
        voltLimit = 3.4;
    }
    else if (voltLimit > 4.6)
    {
        voltLimit = 4.6;
    }
    uint8_t cellVoltageLimit = lround(((voltLimit - 3.4) * 1000.0) / 5.0);

    this->write8(BQ25887_REG_CELL_VOLTAGE_LIMIT, cellVoltageLimit);
    return;
}

void EvoBQ25887::setChargeCurrentLimit(float chgCurrentLimit)
{
    // save previous register value to save bit 7 and 6
    uint8_t regValue = this->read8(BQ25887_REG_CHARGE_CURRENT_LIMIT);
    regValue = (regValue & 0b11000000);

    // adjust input to be within limits 100mA to 2200mA
    if (chgCurrentLimit < 0.1)
    {
        chgCurrentLimit = 0.1;
    }
    else if (chgCurrentLimit > 2.2)
    {
        chgCurrentLimit = 2.2;
    }

    uint8_t chargeCurrentLimit = lround((chgCurrentLimit * 1000.0) / 50.0); // calculate uint8 value
    chargeCurrentLimit = (chargeCurrentLimit & 0b00111111);                 // make sure to keep only the lower 6 bits

    regValue = (regValue | chargeCurrentLimit); // or the old and new to get new register value

    this->write8(BQ25887_REG_CHARGE_CURRENT_LIMIT, regValue); // write uint8
    return;
}

void EvoBQ25887::setHIZMode(bool enable)
{
    uint8_t regValue = this->read8(BQ25887_REG_CHARGE_CURRENT_LIMIT);
    regValue = (regValue & 0b01111111);
    if (enable)
    {
        regValue = (regValue | 0b10000000);
    }
    this->write8(BQ25887_REG_CHARGE_CURRENT_LIMIT, regValue);
    return;
}

void EvoBQ25887::setILIMPinFunction(bool enable)
{
    uint8_t regValue = this->read8(BQ25887_REG_CHARGE_CURRENT_LIMIT);
    regValue = (regValue & 0b10111111);
    if (enable)
    {
        regValue = (regValue | 0b01000000);
    }
    this->write8(BQ25887_REG_CHARGE_CURRENT_LIMIT, regValue);
    return;
}

void EvoBQ25887::setInputVoltageLimit(float inputVoltLimit)
{
    // save previous register value to save bit 7, 6 and 5
    uint8_t regValue = this->read8(BQ25887_REG_INPUT_VOLTAGE_LIMIT);
    regValue = (regValue & 0b11100000);

    // adjust input to be within limits 3.9V to 5.5V
    if (inputVoltLimit < 3.9)
    {
        inputVoltLimit = 3.9;
    }
    else if (inputVoltLimit > 5.5)
    {
        inputVoltLimit = 5.5;
    }

    uint8_t inputVoltageLimit = lround(((inputVoltLimit - 3.9) * 1000.0) / 100.0);
    inputVoltageLimit = (inputVoltageLimit & 0b00011111);

    regValue = (regValue | inputVoltageLimit);

    this->write8(BQ25887_REG_INPUT_VOLTAGE_LIMIT, regValue);
    return;
}

void EvoBQ25887::setEN_VINDPM_RST(bool enable)
{
    uint8_t regValue = this->read8(BQ25887_REG_INPUT_VOLTAGE_LIMIT);
    regValue = (regValue & 0b01111111);
    if (enable)
    {
        regValue = (regValue | 0b10000000);
    }
    this->write8(BQ25887_REG_INPUT_VOLTAGE_LIMIT, regValue);
    return;
}

void EvoBQ25887::setEN_BAT_DISCHG(bool enable)
{
    uint8_t regValue = this->read8(BQ25887_REG_INPUT_VOLTAGE_LIMIT);
    regValue = (regValue & 0b10111111);
    if (enable)
    {
        regValue = (regValue | 0b01000000);
    }
    this->write8(BQ25887_REG_INPUT_VOLTAGE_LIMIT, regValue);
    return;
}

void EvoBQ25887::setPFM_OOA_DIS(bool disable)
{
    uint8_t regValue = this->read8(BQ25887_REG_INPUT_VOLTAGE_LIMIT);
    regValue = (regValue & 0b11011111);
    if (disable)
    {
        regValue = (regValue | 0b00100000);
    }
    this->write8(BQ25887_REG_INPUT_VOLTAGE_LIMIT, regValue);
    return;
}

void EvoBQ25887::setInputCurrentLimit(float inputCurLimit)
{
    // save previous register value to save bit 7, 6 and 5
    uint8_t regValue = this->read8(BQ25887_REG_INPUT_CURRENT_LIMIT);
    regValue = (regValue & 0b11100000);

    // adjust input to be within limits 0.5mA to 3.3mA
    if (inputCurLimit < 0.5)
    {
        inputCurLimit = 0.5;
    }
    else if (inputCurLimit > 3.3)
    {
        inputCurLimit = 3.3;
    }

    uint8_t inputCurrentLimit = lround(((inputCurLimit - 0.5) * 1000.0) / 100.0);
    inputCurrentLimit = (inputCurrentLimit & 0b00011111);

    regValue = (regValue | inputCurrentLimit);

    this->write8(BQ25887_REG_INPUT_CURRENT_LIMIT, regValue);
    return;
}

void EvoBQ25887::setFORCE_ICO(bool enable)
{
    uint8_t regValue = this->read8(BQ25887_REG_INPUT_CURRENT_LIMIT);
    regValue = (regValue & 0b01111111);
    if (enable)
    {
        regValue = (regValue | 0b10000000);
    }
    this->write8(BQ25887_REG_INPUT_CURRENT_LIMIT, regValue);
    return;
}

void EvoBQ25887::setFORCE_INDET(bool enable)
{
    uint8_t regValue = this->read8(BQ25887_REG_INPUT_CURRENT_LIMIT);
    regValue = (regValue & 0b10111111);
    if (enable)
    {
        regValue = (regValue | 0b01000000);
    }
    this->write8(BQ25887_REG_INPUT_CURRENT_LIMIT, regValue);
    return;
}

void EvoBQ25887::setEN_ICO(bool enable)
{
    uint8_t regValue = this->read8(BQ25887_REG_INPUT_CURRENT_LIMIT);
    regValue = (regValue & 0b11011111);
    if (enable)
    {
        regValue = (regValue | 0b00100000);
    }
    this->write8(BQ25887_REG_INPUT_CURRENT_LIMIT, regValue);
    return;
}

void EvoBQ25887::setPrechargeCurrentLimit(float preCurrentLimit)
{
    // save previous register value to save bit 7, 6 and 5
    uint8_t regValue = this->read8(BQ25887_REG_PRE_TERM_CURRENT_LIMIT);
    regValue = (regValue & 0b00001111);

    // adjust input to be within limits 0.05A to 0.80A
    if (preCurrentLimit < 0.05)
    {
        preCurrentLimit = 0.05;
    }
    else if (preCurrentLimit > 0.8)
    {
        preCurrentLimit = 0.8;
    }

    uint8_t prechargeCurrentLimit = lround(((preCurrentLimit - 0.05) * 1000.0) / 50.0);
    prechargeCurrentLimit = (prechargeCurrentLimit & 0b11110000);

    regValue = (regValue | prechargeCurrentLimit);

    this->write8(BQ25887_REG_PRE_TERM_CURRENT_LIMIT, regValue);
    return;
}

void EvoBQ25887::setTerminationCurrentLimit(float termCurrentLimit)
{
    // save previous register value to save bit 7, 6 and 5
    uint8_t regValue = this->read8(BQ25887_REG_PRE_TERM_CURRENT_LIMIT);
    regValue = (regValue & 0b11110000);

    // adjust input to be within limits 0.05A to 0.80A
    if (termCurrentLimit < 0.05)
    {
        termCurrentLimit = 0.05;
    }
    else if (termCurrentLimit > 0.8)
    {
        termCurrentLimit = 0.8;
    }

    uint8_t terminationCurrentLimit = lround(((termCurrentLimit - 0.05) * 1000.0) / 50.0);
    terminationCurrentLimit = (terminationCurrentLimit & 0b00001111);

    regValue = (regValue | terminationCurrentLimit);

    this->write8(BQ25887_REG_PRE_TERM_CURRENT_LIMIT, regValue);
    return;
}

void EvoBQ25887::setEN_TERM(bool enable)
{
    uint8_t regValue = this->read8(BQ25887_REG_CHARGER_CONTROL_1);
    regValue = (regValue & 0b01111111);
    if (enable)
    {
        regValue = (regValue | 0b10000000);
    }
    this->write8(BQ25887_REG_CHARGER_CONTROL_1, regValue);
    return;
}

void EvoBQ25887::setSTAT_DIS(bool disable)
{
    uint8_t regValue = this->read8(BQ25887_REG_CHARGER_CONTROL_1);
    regValue = (regValue & 0b10111111);
    if (disable)
    {
        regValue = (regValue | 0b01000000);
    }
    this->write8(BQ25887_REG_CHARGER_CONTROL_1, regValue);
    return;
}

void EvoBQ25887::setWATCHDOG(uint8_t timerSetting)
{
    uint8_t regValue = this->read8(BQ25887_REG_CHARGER_CONTROL_1);
    regValue = (regValue & 0b11001111);
    switch (timerSetting)
    {
    case 0: // if it is 0 leave regValue alone because it will be 0 from the & above
        break;
    case 2: // if it is 2 set it to 80s
        regValue = (regValue | 0b00100000);
        break;
    case 3: // if it is 3 set it to 160s
        regValue = (regValue | 0b00110000);
        break;
    default: // if it is the default value of 1 or anything incorrect set it to the default value of 1 (40s)
        regValue = (regValue | 0b00010000);
        break;
    }
    this->write8(BQ25887_REG_CHARGER_CONTROL_1, regValue);
    return;
}

void EvoBQ25887::setEN_TIMER(bool enable)
{
    uint8_t regValue = this->read8(BQ25887_REG_CHARGER_CONTROL_1);
    regValue = (regValue & 0b11110111);
    if (enable)
    {
        regValue = (regValue | 0b00001000);
    }
    this->write8(BQ25887_REG_CHARGER_CONTROL_1, regValue);
    return;
}

void EvoBQ25887::setCHG_TIMER(uint8_t timerSetting)
{
    uint8_t regValue = this->read8(BQ25887_REG_CHARGER_CONTROL_1);
    regValue = (regValue & 0b11111001);
    switch (timerSetting)
    {
    case 0: // if it is 0 leave regValue alone because it will be 0 from the & above (5hrs)
        break;
    case 1: // if it is 1 set it to 8hrs
        regValue = (regValue | 0b00000010);
        break;
    case 3: // if it is 3 set it to 20hrs
        regValue = (regValue | 0b00000110);
        break;
    default: // if it is the default value of 2 or anything incorrect set it to the default value of 2 (12hrs)
        regValue = (regValue | 0b00000100);
        break;
    }
    this->write8(BQ25887_REG_CHARGER_CONTROL_1, regValue);
    return;
}

void EvoBQ25887::setTMR2X_EN(bool enable)
{
    uint8_t regValue = this->read8(BQ25887_REG_CHARGER_CONTROL_1);
    regValue = (regValue & 0b11111110);
    if (enable)
    {
        regValue = (regValue | 0b00000001);
    }
    this->write8(BQ25887_REG_CHARGER_CONTROL_1, regValue);
    return;
}

void EvoBQ25887::setAUTO_INDET_EN(bool enable)
{
    uint8_t regValue = this->read8(BQ25887_REG_CHARGER_CONTROL_2);
    regValue = (regValue & 0b10111111);
    if (enable)
    {
        regValue = (regValue | 0b01000000);
    }
    this->write8(BQ25887_REG_CHARGER_CONTROL_2, regValue);
    return;
}

void EvoBQ25887::setT_REG_THRESH(uint8_t thermalRegulationThreshold)
{
    uint8_t regValue = this->read8(BQ25887_REG_CHARGER_CONTROL_2);
    regValue = (regValue & 0b11001111);
    switch (thermalRegulationThreshold)
    {
    case 0: // if it is 0 leave regValue alone because it will be 0 from the & above (60C)
        break;
    case 1: // if it is 1 set it to (80C)
        regValue = (regValue | 0b00010000);
        break;
    case 2: // if it is 2 set it to (100C)
        regValue = (regValue | 0b00100000);
        break;
    default: // if it is the default value of 3 or anything incorrect set it to the default value of 3 (120C)
        regValue = (regValue | 0b00110000);
        break;
    }
    this->write8(BQ25887_REG_CHARGER_CONTROL_2, regValue);
    return;
}

void EvoBQ25887::setEN_CHG(bool enable)
{
    uint8_t regValue = this->read8(BQ25887_REG_CHARGER_CONTROL_2);
    regValue = (regValue & 0b11110111);
    if (enable)
    {
        regValue = (regValue | 0b00001000);
    }
    this->write8(BQ25887_REG_CHARGER_CONTROL_2, regValue);
    return;
}

void EvoBQ25887::setCELLLOWV_THRESH(uint8_t cellLowThreshold)
{
    uint8_t regValue = this->read8(BQ25887_REG_CHARGER_CONTROL_2);
    regValue = (regValue & 0b11111011);
    switch (cellLowThreshold)
    {
    case 0:
        break;
    default:
        regValue = (regValue | 0b00000100);
        break;
    }
    this->write8(BQ25887_REG_CHARGER_CONTROL_2, regValue);
    return;
}

void EvoBQ25887::setVCELL_RECHG_THRESH_OFF(uint8_t rechargeThresholdOffset)
{
    uint8_t regValue = this->read8(BQ25887_REG_CHARGER_CONTROL_2);
    regValue = (regValue & 0b11111100);
    switch (rechargeThresholdOffset)
    {
    case 0: // if it is 0 leave regValue alone because it will be 0 from the & above (50mV)
        break;
    case 2: // if it is 2 set it to (150mV)
        regValue = (regValue | 0b00000010);
        break;
    case 3: // if it is 3 set it to (200mV)
        regValue = (regValue | 0b00000011);
        break;
    default: // if it is the default value of 1 or anything incorrect set it to the default value of 1 (100mV)
        regValue = (regValue | 0b00000001);
        break;
    }
    this->write8(BQ25887_REG_CHARGER_CONTROL_2, regValue);
    return;
}

void EvoBQ25887::setPFM_DIS(bool disable)
{
    uint8_t regValue = this->read8(BQ25887_REG_CHARGER_CONTROL_3);
    regValue = (regValue & 0b01111111);
    if (disable)
    {
        regValue = (regValue | 0b10000000);
    }
    this->write8(BQ25887_REG_CHARGER_CONTROL_3, regValue);
    return;
}

void EvoBQ25887::wdReset()
{
    uint8_t regValue = this->read8(BQ25887_REG_CHARGER_CONTROL_3);
    regValue = (regValue & 0b10111111);
    regValue = (regValue | 0b01000000);
    this->write8(BQ25887_REG_CHARGER_CONTROL_3, regValue);
    return;
}

void EvoBQ25887::setTOPOFF_TIMER(uint8_t topOffTimer)
{
    uint8_t regValue = this->read8(BQ25887_REG_CHARGER_CONTROL_3);
    regValue = (regValue & 0b11001111);
    switch (topOffTimer)
    {
    case 1: // if it is 1 set it to (15min)
        regValue = (regValue | 0b00010000);
        break;
    case 2: // if it is 2 set it to (30min)
        regValue = (regValue | 0b00100000);
        break;
    case 3: // if it is 3 set it to (45min)
        regValue = (regValue | 0b00110000);
        break;
    default: // if it is the default value of 0 or anything incorrect leave it at the default value of 0 (Disabled)
        break;
    }
    this->write8(BQ25887_REG_CHARGER_CONTROL_3, regValue);
    return;
}

void EvoBQ25887::setJEITA_VSET(uint8_t jeitaSetting)
{
    uint8_t regValue = this->read8(BQ25887_REG_CHARGER_CONTROL_4);
    regValue = (regValue & 0b11100111);
    switch (jeitaSetting)
    {
    case 0: // if it is 0 leave it at 0 (Charge Suspend)
        break;
    case 2: // if it is 2 set it to 2 (8.3V)
        regValue = (regValue | 0b00010000);
        break;
    case 3: // if it is 3 set it to 3 (Unchanged)
        regValue = (regValue | 0b00011000);
        break;
    default: // if it is the default value of 1 or anything incorrect set it to the default value of 1 (8.0V)
        regValue = (regValue | 0b00001000);
        break;
    }
    this->write8(BQ25887_REG_CHARGER_CONTROL_4, regValue);
    return;
}

void EvoBQ25887::setJEITA_ISETH(uint8_t jeitaSetting)
{
    uint8_t regValue = this->read8(BQ25887_REG_CHARGER_CONTROL_4);
    regValue = (regValue & 0b11111011);
    switch (jeitaSetting)
    {
    case 0: // if it is 0 leave it at 0 (Charge Suspend)
        break;
    default: // if it is the default value of 1 or anything incorrect set it to the default value of 1 (8.0V)
        regValue = (regValue | 0b00000100);
        break;
    }
    this->write8(BQ25887_REG_CHARGER_CONTROL_4, regValue);
    return;
}

void EvoBQ25887::setJEITA_ISETC(uint8_t jeitaSetting)
{
    uint8_t regValue = this->read8(BQ25887_REG_CHARGER_CONTROL_4);
    regValue = (regValue & 0b11111100);
    switch (jeitaSetting)
    {
    case 0: // if it is 0 leave it at 0 (Charge Suspend)
        break;
    case 2: // if it is 2 set it to 2 (8.3V)
        regValue = (regValue | 0b00000010);
        break;
    case 3: // if it is 3 set it to 3 (Unchanged)
        regValue = (regValue | 0b00000011);
        break;
    default: // if it is the default value of 1 or anything incorrect set it to the default value of 1 (8.0V)
        regValue = (regValue | 0b00000001);
        break;
    }
    this->write8(BQ25887_REG_CHARGER_CONTROL_4, regValue);
    return;
}

void EvoBQ25887::setADC_DONE_MASK(bool disable)
{
    uint8_t regValue = this->read8(BQ25887_REG_CHARGER_MASK_1);
    regValue = (regValue & 0b01111111);
    if (disable)
    {
        regValue = (regValue | 0b10000000);
    }
    this->write8(BQ25887_REG_CHARGER_MASK_1, regValue);
    return;
}

void EvoBQ25887::setIINDPM_MASK(bool disable)
{
    uint8_t regValue = this->read8(BQ25887_REG_CHARGER_MASK_1);
    regValue = (regValue & 0b10111111);
    if (disable)
    {
        regValue = (regValue | 0b01000000);
    }
    this->write8(BQ25887_REG_CHARGER_MASK_1, regValue);
    return;
}

void EvoBQ25887::setVINDPM_MASK(bool disable)
{
    uint8_t regValue = this->read8(BQ25887_REG_CHARGER_MASK_1);
    regValue = (regValue & 0b11011111);
    if (disable)
    {
        regValue = (regValue | 0b00100000);
    }
    this->write8(BQ25887_REG_CHARGER_MASK_1, regValue);
    return;
}

void EvoBQ25887::setT_REG_MASK(bool disable)
{
    uint8_t regValue = this->read8(BQ25887_REG_CHARGER_MASK_1);
    regValue = (regValue & 0b11101111);
    if (disable)
    {
        regValue = (regValue | 0b00010000);
    }
    this->write8(BQ25887_REG_CHARGER_MASK_1, regValue);
    return;
}

void EvoBQ25887::setWD_MASK(bool disable)
{
    uint8_t regValue = this->read8(BQ25887_REG_CHARGER_MASK_1);
    regValue = (regValue & 0b11110111);
    if (disable)
    {
        regValue = (regValue | 0b00001000);
    }
    this->write8(BQ25887_REG_CHARGER_MASK_1, regValue);
    return;
}

void EvoBQ25887::setCHRG_MASK(bool disable)
{
    uint8_t regValue = this->read8(BQ25887_REG_CHARGER_MASK_1);
    regValue = (regValue & 0b11111110);
    if (disable)
    {
        regValue = (regValue | 0b00000001);
    }
    this->write8(BQ25887_REG_CHARGER_MASK_1, regValue);
    return;
}

void EvoBQ25887::setPG_MASK(bool disable)
{
    uint8_t regValue = this->read8(BQ25887_REG_CHARGER_MASK_2);
    regValue = (regValue & 0b01111111);
    if (disable)
    {
        regValue = (regValue | 0b10000000);
    }
    this->write8(BQ25887_REG_CHARGER_MASK_2, regValue);
    return;
}

void EvoBQ25887::setVBUS_MASK(bool disable)
{
    uint8_t regValue = this->read8(BQ25887_REG_CHARGER_MASK_2);
    regValue = (regValue & 0b11101111);
    if (disable)
    {
        regValue = (regValue | 0b00010000);
    }
    this->write8(BQ25887_REG_CHARGER_MASK_2, regValue);
    return;
}

void EvoBQ25887::setTS_MASK(bool disable)
{
    uint8_t regValue = this->read8(BQ25887_REG_CHARGER_MASK_2);
    regValue = (regValue & 0b11111011);
    if (disable)
    {
        regValue = (regValue | 0b00000100);
    }
    this->write8(BQ25887_REG_CHARGER_MASK_2, regValue);
    return;
}

void EvoBQ25887::setICO_MASK(bool disable)
{
    uint8_t regValue = this->read8(BQ25887_REG_CHARGER_MASK_2);
    regValue = (regValue & 0b11111101);
    if (disable)
    {
        regValue = (regValue | 0b00000010);
    }
    this->write8(BQ25887_REG_CHARGER_MASK_2, regValue);
    return;
}

void EvoBQ25887::setVBUS_OVP_MASK(bool disable)
{
    uint8_t regValue = this->read8(BQ25887_REG_FAULT_MASK);
    regValue = (regValue & 0b01111111);
    if (disable)
    {
        regValue = (regValue | 0b10000000);
    }
    this->write8(BQ25887_REG_FAULT_MASK, regValue);
    return;
}

void EvoBQ25887::setTSHUT_MASK(bool disable)
{
    uint8_t regValue = this->read8(BQ25887_REG_FAULT_MASK);
    regValue = (regValue & 0b10111111);
    if (disable)
    {
        regValue = (regValue | 0b01000000);
    }
    this->write8(BQ25887_REG_FAULT_MASK, regValue);
    return;
}

void EvoBQ25887::setTMR_MASK(bool disable)
{
    uint8_t regValue = this->read8(BQ25887_REG_FAULT_MASK);
    regValue = (regValue & 0b11101111);
    if (disable)
    {
        regValue = (regValue | 0b00010000);
    }
    this->write8(BQ25887_REG_FAULT_MASK, regValue);
    return;
}

void EvoBQ25887::setSNS_SHORT_MASK(bool disable)
{
    uint8_t regValue = this->read8(BQ25887_REG_FAULT_MASK);
    regValue = (regValue & 0b11110111);
    if (disable)
    {
        regValue = (regValue | 0b00001000);
    }
    this->write8(BQ25887_REG_FAULT_MASK, regValue);
    return;
}

void EvoBQ25887::setADC_EN(bool enable)
{
    uint8_t regValue = this->read8(BQ25887_REG_ADC_CONTROL);
    regValue = (regValue & 0b01111111);
    if (enable)
    {
        regValue = (regValue | 0b10000000);
    }
    this->write8(BQ25887_REG_ADC_CONTROL, regValue);
    return;
}

void EvoBQ25887::setADC_ONE_SHOT(bool enable)
{
    uint8_t regValue = this->read8(BQ25887_REG_ADC_CONTROL);
    regValue = (regValue & 0b10111111);
    if (enable)
    {
        regValue = (regValue | 0b01000000);
    }
    this->write8(BQ25887_REG_ADC_CONTROL, regValue);
    return;
}

void EvoBQ25887::setADC_SAMPLE_SPEED(uint8_t sampleSpeed)
{
    uint8_t regValue = this->read8(BQ25887_REG_ADC_CONTROL);
    regValue = (regValue & 0b11001111);
    switch (sampleSpeed)
    {
    case 1:
        regValue = (regValue | 0b00010000);
        break;
    case 2:
        regValue = (regValue | 0b00100000);
        break;
    case 3:
        regValue = (regValue | 0b00110000);
        break;
    default: // if it is 0 or any wrong value set it to 0 (slowest speed, highest resolution)
        break;
    }
    this->write8(BQ25887_REG_ADC_CONTROL, regValue);
    return;
}

void EvoBQ25887::setIBUS_ADC_DIS(bool disable)
{
    uint8_t regValue = this->read8(BQ25887_REG_ADC_FUNCTION_DISABLE);
    regValue = (regValue & 0b01111111);
    if (disable)
    {
        regValue = (regValue | 0b10000000);
    }
    this->write8(BQ25887_REG_ADC_FUNCTION_DISABLE, regValue);
    return;
}

void EvoBQ25887::setICHG_ADC_DIS(bool disable)
{
    uint8_t regValue = this->read8(BQ25887_REG_ADC_FUNCTION_DISABLE);
    regValue = (regValue & 0b10111111);
    if (disable)
    {
        regValue = (regValue | 0b01000000);
    }
    this->write8(BQ25887_REG_ADC_FUNCTION_DISABLE, regValue);
    return;
}

void EvoBQ25887::setVBUS_ADC_DIS(bool disable)
{
    uint8_t regValue = this->read8(BQ25887_REG_ADC_FUNCTION_DISABLE);
    regValue = (regValue & 0b11011111);
    if (disable)
    {
        regValue = (regValue | 0b00100000);
    }
    this->write8(BQ25887_REG_ADC_FUNCTION_DISABLE, regValue);
    return;
}

void EvoBQ25887::setVBAT_ADC_DIS(bool disable)
{
    uint8_t regValue = this->read8(BQ25887_REG_ADC_FUNCTION_DISABLE);
    regValue = (regValue & 0b11101111);
    if (disable)
    {
        regValue = (regValue | 0b00010000);
    }
    this->write8(BQ25887_REG_ADC_FUNCTION_DISABLE, regValue);
    return;
}

void EvoBQ25887::setTS_ADC_DIS(bool disable)
{
    uint8_t regValue = this->read8(BQ25887_REG_ADC_FUNCTION_DISABLE);
    regValue = (regValue & 0b11111011);
    if (disable)
    {
        regValue = (regValue | 0b00000100);
    }
    this->write8(BQ25887_REG_ADC_FUNCTION_DISABLE, regValue);
    return;
}

void EvoBQ25887::setVCELL_ADC_DIS(bool disable)
{
    uint8_t regValue = this->read8(BQ25887_REG_ADC_FUNCTION_DISABLE);
    regValue = (regValue & 0b11111101);
    if (disable)
    {
        regValue = (regValue | 0b00000010);
    }
    this->write8(BQ25887_REG_ADC_FUNCTION_DISABLE, regValue);
    return;
}

void EvoBQ25887::setTDIE_ADC_DIS(bool disable)
{
    uint8_t regValue = this->read8(BQ25887_REG_ADC_FUNCTION_DISABLE);
    regValue = (regValue & 0b11111110);
    if (disable)
    {
        regValue = (regValue | 0b00000001);
    }
    this->write8(BQ25887_REG_ADC_FUNCTION_DISABLE, regValue);
    return;
}

void EvoBQ25887::registerReset()
{
    this->write8(BQ25887_REG_PART_INFORMATION, 0b10000000);
    return;
}

void EvoBQ25887::setVDIFF_END_OFFSET(uint8_t cellBalExitThresh)
{
    uint8_t regValue = this->read8(BQ25887_REG_CELL_BALANCING_CONTROL_1);
    regValue = (regValue & 0b00011111);
    if (cellBalExitThresh > 7)
    {
        cellBalExitThresh = 1;
    }
    cellBalExitThresh = (cellBalExitThresh << 5);
    regValue = (regValue | cellBalExitThresh);
    this->write8(BQ25887_REG_CELL_BALANCING_CONTROL_1, regValue);
    return;
}

void EvoBQ25887::setTCB_QUAL_INTERVAL(uint8_t cbQualInterval)
{
    uint8_t regValue = this->read8(BQ25887_REG_CELL_BALANCING_CONTROL_1);
    regValue = (regValue & 0b11101111);
    if (cbQualInterval > 1)
    {
        cbQualInterval = 0;
    }
    cbQualInterval = (cbQualInterval << 4);
    regValue = (regValue | cbQualInterval);
    this->write8(BQ25887_REG_CELL_BALANCING_CONTROL_1, regValue);
    return;
}

void EvoBQ25887::setTCB_ACTIVE(uint8_t tcbActive)
{
    uint8_t regValue = this->read8(BQ25887_REG_CELL_BALANCING_CONTROL_1);
    regValue = (regValue & 0b11110011);
    if (tcbActive > 3)
    {
        tcbActive = 2;
    }
    tcbActive = (tcbActive << 2);
    regValue = (regValue | tcbActive);
    this->write8(BQ25887_REG_CELL_BALANCING_CONTROL_1, regValue);
    return;
}

void EvoBQ25887::setTSETTLE(uint8_t tSettle)
{
    uint8_t regValue = this->read8(BQ25887_REG_CELL_BALANCING_CONTROL_1);
    regValue = (regValue & 0b11111100);
    if (tSettle > 3)
    {
        tSettle = 2;
    }
    regValue = (regValue | tSettle);
    this->write8(BQ25887_REG_CELL_BALANCING_CONTROL_1, regValue);
    return;
}

void EvoBQ25887::setVQUAL_TH(uint8_t vQualThreshold)
{
    uint8_t regValue = this->read8(BQ25887_REG_CELL_BALANCING_CONTROL_2);
    regValue = (regValue & 0b00001111);
    if (vQualThreshold > 15)
    {
        vQualThreshold = 15;
    }
    vQualThreshold = (vQualThreshold << 4);
    regValue = (regValue | vQualThreshold);
    this->write8(BQ25887_REG_CELL_BALANCING_CONTROL_2, regValue);
    return;
}

void EvoBQ25887::setVDIFF_START(uint8_t vDiffStartThreshold)
{
    uint8_t regValue = this->read8(BQ25887_REG_CELL_BALANCING_CONTROL_2);
    regValue = (regValue & 0b11110000);
    if (vDiffStartThreshold > 15)
    {
        vDiffStartThreshold = 5;
    }
    regValue = (regValue | vDiffStartThreshold);
    this->write8(BQ25887_REG_CELL_BALANCING_CONTROL_2, regValue);
    return;
}

void EvoBQ25887::setCB_CHG_DIS(bool disable)
{
    uint8_t regValue = this->read8(BQ25887_REG_CELL_BALANCING_STAT_CONT);
    regValue = (regValue & 0b01111111);
    if (disable)
    {
        regValue = (regValue | 0b10000000);
    }
    this->write8(BQ25887_REG_CELL_BALANCING_STAT_CONT, regValue);
    return;
}

void EvoBQ25887::setCB_AUTO_EN(bool enable)
{
    uint8_t regValue = this->read8(BQ25887_REG_CELL_BALANCING_STAT_CONT);
    regValue = (regValue & 0b10111111);
    if (enable)
    {
        regValue = (regValue | 0b01000000);
    }
    this->write8(BQ25887_REG_CELL_BALANCING_STAT_CONT, regValue);
    return;
}

void EvoBQ25887::setQCBL_EN(bool enable)
{
    uint8_t regValue = this->read8(BQ25887_REG_CELL_BALANCING_FLAG);
    regValue = (regValue & 0b01111111);
    if (enable)
    {
        regValue = (regValue | 0b10000000);
    }
    this->write8(BQ25887_REG_CELL_BALANCING_FLAG, regValue);
    return;
}

void EvoBQ25887::setQCBH_EN(bool enable)
{
    uint8_t regValue = this->read8(BQ25887_REG_CELL_BALANCING_FLAG);
    regValue = (regValue & 0b10111111);
    if (enable)
    {
        regValue = (regValue | 0b01000000);
    }
    this->write8(BQ25887_REG_CELL_BALANCING_FLAG, regValue);
    return;
}

void EvoBQ25887::setCB_MASK(bool disable)
{
    uint8_t regValue = this->read8(BQ25887_REG_CELL_BALANCING_MASK);
    regValue = (regValue & 0b11011111);
    if (disable)
    {
        regValue = (regValue | 0b00100000);
    }
    this->write8(BQ25887_REG_CELL_BALANCING_MASK, regValue);
    return;
}

void EvoBQ25887::setHS_CV_MASK(bool disable)
{
    uint8_t regValue = this->read8(BQ25887_REG_CELL_BALANCING_MASK);
    regValue = (regValue & 0b11101111);
    if (disable)
    {
        regValue = (regValue | 0b00010000);
    }
    this->write8(BQ25887_REG_CELL_BALANCING_MASK, regValue);
    return;
}

void EvoBQ25887::setLS_CV_MASK(bool disable)
{
    uint8_t regValue = this->read8(BQ25887_REG_CELL_BALANCING_MASK);
    regValue = (regValue & 0b11110111);
    if (disable)
    {
        regValue = (regValue | 0b00001000);
    }
    this->write8(BQ25887_REG_CELL_BALANCING_MASK, regValue);
    return;
}

void EvoBQ25887::setHS_OV_MASK(bool disable)
{
    uint8_t regValue = this->read8(BQ25887_REG_CELL_BALANCING_MASK);
    regValue = (regValue & 0b11111011);
    if (disable)
    {
        regValue = (regValue | 0b00000100);
    }
    this->write8(BQ25887_REG_CELL_BALANCING_MASK, regValue);
    return;
}

void EvoBQ25887::setLS_OV_MASK(bool disable)
{
    uint8_t regValue = this->read8(BQ25887_REG_CELL_BALANCING_MASK);
    regValue = (regValue & 0b11111101);
    if (disable)
    {
        regValue = (regValue | 0b00000010);
    }
    this->write8(BQ25887_REG_CELL_BALANCING_MASK, regValue);
    return;
}

void EvoBQ25887::setCB_OC_MASK(bool disable)
{
    uint8_t regValue = this->read8(BQ25887_REG_CELL_BALANCING_MASK);
    regValue = (regValue & 0b11111110);
    if (disable)
    {
        regValue = (regValue | 0b00000001);
    }
    this->write8(BQ25887_REG_CELL_BALANCING_MASK, regValue);
    return;
}

// private methods

// private read/write methods
uint8_t EvoBQ25887::read8(uint8_t reg)
{
    uint8_t byte0 = 0;

    Wire1.beginTransmission(BQ25887_I2C_ADDRESS);
    Wire1.write(reg);
    Wire1.endTransmission(false);

    Wire1.requestFrom(BQ25887_I2C_ADDRESS, 1, true);
    byte0 = Wire1.read();

    return byte0;
}

uint16_t EvoBQ25887::read16(uint8_t reg)
{
    uint8_t byte0 = 0;
    uint8_t byte1 = 0;

    Wire1.beginTransmission(BQ25887_I2C_ADDRESS);
    Wire1.write(reg);
    Wire1.endTransmission(false);

    Wire1.requestFrom(BQ25887_I2C_ADDRESS, 2, true);
    byte0 = Wire1.read();
    byte1 = Wire1.read();

    return (byte1 << 8) | byte0;
}

uint32_t EvoBQ25887::read32(uint8_t reg)
{
    uint8_t byte0 = 0;
    uint8_t byte1 = 0;
    uint8_t byte2 = 0;
    uint8_t byte3 = 0;
    uint32_t returnValue = 0;

    Wire1.beginTransmission(BQ25887_I2C_ADDRESS);
    Wire1.write(reg);
    Wire1.endTransmission(false);

    Wire1.requestFrom(BQ25887_I2C_ADDRESS, 4, true);
    byte0 = Wire1.read();
    byte1 = Wire1.read();
    byte2 = Wire1.read();
    byte3 = Wire1.read();

    returnValue += (uint32_t)byte3 << 24;
    returnValue += (uint32_t)byte2 << 16;
    returnValue += (uint32_t)byte1 << 8;
    returnValue += byte0;

    return returnValue;

    // return (byte3 << 24) | (byte2 << 16) | (byte1 << 8) | byte0;
}

int16_t EvoBQ25887::readADC(uint8_t reg)
{
    uint8_t byte1 = 0;
    uint8_t byte0 = 0;

    Wire1.beginTransmission(BQ25887_I2C_ADDRESS);
    Wire1.write(reg);
    Wire1.endTransmission(false);

    Wire1.requestFrom(BQ25887_I2C_ADDRESS, 2, true);
    byte1 = Wire1.read();
    byte0 = Wire1.read();

    return (byte1 << 8) | byte0;
}

void EvoBQ25887::write8(uint8_t reg, uint8_t data)
{
    Wire1.beginTransmission(BQ25887_I2C_ADDRESS);
    Wire1.write(reg);
    Wire1.write(data);
    Wire1.endTransmission();
}

void EvoBQ25887::write16(uint8_t reg, uint16_t data)
{
    Wire1.beginTransmission(BQ25887_I2C_ADDRESS);
    Wire1.write(reg);
    Wire1.write((uint8_t)(0xFF & (data >> 0))); // Byte0
    Wire1.write((uint8_t)(0xFF & (data >> 8))); // Byte1
    Wire1.endTransmission();
}

void EvoBQ25887::write32(uint8_t reg, uint32_t data)
{
    Wire1.beginTransmission(BQ25887_I2C_ADDRESS);
    Wire1.write(reg);
    Wire1.write((uint8_t)(0xFF & (data >> 0)));  // Byte0
    Wire1.write((uint8_t)(0xFF & (data >> 8)));  // Byte1
    Wire1.write((uint8_t)(0xFF & (data >> 16))); // Byte2
    Wire1.write((uint8_t)(0xFF & (data >> 24))); // Byte3
    Wire1.endTransmission();
}