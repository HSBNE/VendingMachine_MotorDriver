//*****************************************************************************
//
// zeuslib.c - Driver for ZEUS interface PSV Database.
//
// Copyright (c) 2005 Texas Instruments Incorporated.  All rights reserved.
// TI Information - Selective Disclosure
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup zeus_api
//! @{
//
//*****************************************************************************

#include "d_ina226.h"

//*******************************************************************
//
//! Initializes I2C for Transfer
//!
//!
//! \return None.
//
//*******************************************************************
void 
ZEUSLibInit()
{
    uint32_t ui32I2CClock;

    //
    // Disable, Reset and Enable the I2C Module Instance
    //
    SysCtlPeripheralDisable(SYSCTL_PERIPH_I2C5);
    SysCtlPeripheralReset(SYSCTL_PERIPH_I2C5);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C5);

    // Configure the pin muxing for I2C0 functions on port B2 and B3.
    GPIOPinConfigure(GPIO_PB4_I2C5SCL);
    GPIOPinConfigure(GPIO_PB5_I2C5SDA);

    GPIOPinTypeI2CSCL(GPIO_PORTB_BASE, GPIO_PIN_4);
    GPIOPinTypeI2C(GPIO_PORTB_BASE, GPIO_PIN_5);

    //    
    // Configure the I2C Baud Rate for 400KHz
    //
    ui32I2CClock = SysCtlClockGet();

    I2CMasterInitExpClk(I2C5_BASE,ui32I2CClock,true);

    //
    // Enable I2C Master Operation
    //
    I2CMasterEnable(I2C5_BASE);

}

//*******************************************************************
//
//! Initializes INA226 for Current Measurement
//!
//! \param ui32Channel is the INA226A or INA226B to Configure
//! \param ui32Resistor is the Resistance Value in milli-ohms
//! \param ui32MaxCurrentInmA is the Maximum Current to measure in mA
//!
//!
//! The \e ui32Channel parameter should be one of the following values:
//!
//! \b ZEUS_CURR_CHA
//! \b ZEUS_CURR_CHB
//!
//! The \e ui32Resistor parameter should be a value between 1 to 3300
//! milli-ohms
//!
//! The \e ui32MaxCurrentInmA is the Maximum Current to measure in mA and
//! should be set to 150mA
//!
//! \return None.
//
//*******************************************************************
void
ZEUSLibConfigureCurrentSense(uint32_t ui32Channel,
                             uint32_t ui32Resistor,
                             uint32_t ui32MaxCurrentInmA)
{
    uint32_t ui32CalibrationValue;
    uint32_t ui32CalibrationRem;
    uint32_t ui32BaseAddress = I2C5_BASE;

    ui32CalibrationValue = (512*32768*10)/(ui32MaxCurrentInmA*ui32Resistor);
    ui32CalibrationRem   = (512*32768*10)%(ui32MaxCurrentInmA*ui32Resistor);

    //
    // INA 226 advises Trunc. Hence check if the Remained is more than
    // 0.5 and increment the Calibration Value by 1
    //
    if(ui32CalibrationRem > (ui32MaxCurrentInmA*ui32Resistor)/2)
    {
     ui32CalibrationValue++;
    }

    //
    // Reset INA226
    //
    I2CMasterSlaveAddrSet(ui32BaseAddress, ui32Channel, ZEUS_WRITE);
    I2CMasterDataPut(ui32BaseAddress, ZEUS_INA226_CONFIG_REG);
    I2CMasterControl(ui32BaseAddress, I2C_MASTER_CMD_BURST_SEND_START);
    while(I2CMasterBusy(ui32BaseAddress));
    I2CMasterDataPut(ui32BaseAddress, (ZEUS_INA226_CONFIG_DEF_H|ZEUS_INA226_CONFIG_RESET));
    I2CMasterControl(ui32BaseAddress, I2C_MASTER_CMD_BURST_SEND_CONT);
    while(I2CMasterBusy(ui32BaseAddress));
    I2CMasterDataPut(ui32BaseAddress, ZEUS_INA226_CONFIG_DEF_L);
    I2CMasterControl(ui32BaseAddress, I2C_MASTER_CMD_BURST_SEND_FINISH);
    while(I2CMasterBusy(ui32BaseAddress));
 
    SysCtlDelay(10000);

    //
    // Write INA226 Configuration Register
    //
    I2CMasterSlaveAddrSet(ui32BaseAddress, ui32Channel, ZEUS_WRITE);
    I2CMasterDataPut(ui32BaseAddress, ZEUS_INA226_CONFIG_REG);
    I2CMasterControl(ui32BaseAddress, I2C_MASTER_CMD_BURST_SEND_START);
    while(I2CMasterBusy(ui32BaseAddress));
    I2CMasterDataPut(ui32BaseAddress, ZEUS_INA226_CONFIG_CNT_SV_H);
    I2CMasterControl(ui32BaseAddress, I2C_MASTER_CMD_BURST_SEND_CONT);
    while(I2CMasterBusy(ui32BaseAddress));
    I2CMasterDataPut(ui32BaseAddress, ZEUS_INA226_CONFIG_CNT_SV_L);
    I2CMasterControl(ui32BaseAddress, I2C_MASTER_CMD_BURST_SEND_FINISH);
    while(I2CMasterBusy(ui32BaseAddress));
 
    SysCtlDelay(10000);

    //
    // Write INA226 Calibration Register
    //
    I2CMasterSlaveAddrSet(ui32BaseAddress, ui32Channel, ZEUS_WRITE);
    I2CMasterDataPut(ui32BaseAddress, ZEUS_INA226_CAL_REG);
    I2CMasterControl(ui32BaseAddress, I2C_MASTER_CMD_BURST_SEND_START);
    while(I2CMasterBusy(ui32BaseAddress));
    I2CMasterDataPut(ui32BaseAddress, ((ui32CalibrationValue & 0xFF00) >> 8));
    I2CMasterControl(ui32BaseAddress, I2C_MASTER_CMD_BURST_SEND_CONT);
    while(I2CMasterBusy(ui32BaseAddress));
    I2CMasterDataPut(ui32BaseAddress, ((ui32CalibrationValue & 0x00FF) >> 0));
    I2CMasterControl(ui32BaseAddress, I2C_MASTER_CMD_BURST_SEND_FINISH);
    while(I2CMasterBusy(ui32BaseAddress));

    //
    // Write INA226 Mask Register for Over Voltage on Shunt
    //
    I2CMasterSlaveAddrSet(ui32BaseAddress, ui32Channel, ZEUS_WRITE);
    I2CMasterDataPut(ui32BaseAddress, ZEUS_INA226_MASK_REG);
    I2CMasterControl(ui32BaseAddress, I2C_MASTER_CMD_BURST_SEND_START);
    while(I2CMasterBusy(ui32BaseAddress));
    I2CMasterDataPut(ui32BaseAddress, ZEUS_INA226_MASK_OVF_EN_H);
    I2CMasterControl(ui32BaseAddress, I2C_MASTER_CMD_BURST_SEND_CONT);
    while(I2CMasterBusy(ui32BaseAddress));
    I2CMasterDataPut(ui32BaseAddress, ZEUS_INA226_MASK_OVF_EN_L);
    I2CMasterControl(ui32BaseAddress, I2C_MASTER_CMD_BURST_SEND_FINISH);
    while(I2CMasterBusy(ui32BaseAddress));

    //
    // Write INA226 Alert Register
    //
    I2CMasterSlaveAddrSet(ui32BaseAddress, ui32Channel, ZEUS_WRITE);
    I2CMasterDataPut(ui32BaseAddress, ZEUS_INA226_ALERT_REG);
    I2CMasterControl(ui32BaseAddress, I2C_MASTER_CMD_BURST_SEND_START);
    while(I2CMasterBusy(ui32BaseAddress));
    I2CMasterDataPut(ui32BaseAddress, ZEUS_INA226_ALERT_80MV_H);
    I2CMasterControl(ui32BaseAddress, I2C_MASTER_CMD_BURST_SEND_CONT);
    while(I2CMasterBusy(ui32BaseAddress));
    I2CMasterDataPut(ui32BaseAddress, ZEUS_INA226_ALERT_80MV_L);
    I2CMasterControl(ui32BaseAddress, I2C_MASTER_CMD_BURST_SEND_FINISH);
    while(I2CMasterBusy(ui32BaseAddress));

}

//*******************************************************************
//
//! Gets the current from corresponding channel
//!
//! \param ui32Channel is the address of analog input channel
//! \param *bSign is the sign value of the current
//! \param *ui32Quotient is the address of Integer part of the current
//! \param *ui32Remainder is the address of Fractional part of the current
//!
//! The \e ui32BaseAddress parameter should be one of the following values:
//! \param ui32Channel is the INA226A or INA226B to Configure
//!
//! The \e ui32Channel parameter should be one of the following values:
//!
//! \b ZEUS_CURR_CHA
//! \b ZEUS_CURR_CHB
//!
//! \return Returns code corresponding to voltage at specified channel in 
//! hex notation, quotient and remainder for float and Sign of the current 
//
//*******************************************************************
uint32_t
ZEUSLibGetCurrent(uint32_t ui32Channel,
                  bool     *bSign,
                  uint32_t *ui32Quotient,
                  uint32_t *ui32Remainder)
{
    uint32_t ui32ADSOut;
    uint8_t  ui8ConvRegHighByte;
    uint8_t  ui8ConvRegLowByte;
    float    fComputeVariable;
    uint32_t ui32BaseAddress = I2C5_BASE;

    I2CMasterSlaveAddrSet(ui32BaseAddress, ui32Channel, ZEUS_WRITE);
    I2CMasterDataPut(ui32BaseAddress, ZEUS_INA226_ICONV_REG);
    I2CMasterControl(ui32BaseAddress, I2C_MASTER_CMD_BURST_SEND_START);
    while(I2CMasterBusy(ui32BaseAddress));
    I2CMasterSlaveAddrSet(ui32BaseAddress, ui32Channel, ZEUS_READ);
    I2CMasterControl(ui32BaseAddress, I2C_MASTER_CMD_BURST_RECEIVE_START);
    while(I2CMasterBusy(ui32BaseAddress));
    ui8ConvRegHighByte = I2CMasterDataGet(ui32BaseAddress);
    I2CMasterControl(ui32BaseAddress, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);
    while(I2CMasterBusy(ui32BaseAddress));
    ui8ConvRegLowByte = I2CMasterDataGet(ui32BaseAddress);

    ui32ADSOut = ui8ConvRegHighByte << 8 | ui8ConvRegLowByte;

    //
    // If Negative Number then run 2's complement
    //
    *bSign  = false; 
    if((ui32ADSOut & 0x8000) == 0x8000) {
      ui32ADSOut = ~(ui32ADSOut);
      ui32ADSOut = ui32ADSOut + '1';
      ui32ADSOut = ui32ADSOut && 0xFFFF;
      *bSign  = true; 
    }

    fComputeVariable  = (float) (ui32ADSOut * 0.00457);
    *ui32Quotient     = (int32_t) fComputeVariable;
    *ui32Remainder    = (int32_t) (fComputeVariable * 1000.0f);
    *ui32Remainder    = *ui32Remainder - (*ui32Quotient * 1000);
//    if(*ui32Remainder < 0)
//    {
//       *ui32Remainder *= -1;
//    }

    return(ui32ADSOut);
}
//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
