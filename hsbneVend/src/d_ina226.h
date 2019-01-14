//*****************************************************************************
//
// zeuslib.h - Prototypes for the ZEUS Board
//
//*****************************************************************************

#ifndef __ZEUSLIB_H__
#define __ZEUSLIB_H__

#include <stdbool.h>
#include <stdint.h>

#include "driverlib/i2c.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"

#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"
#include "inc/hw_i2c.h"

//****************************************************************************
//
// I2C Read Write value 
//
//****************************************************************************
#define ZEUS_WRITE 				0x0
#define ZEUS_READ 				0x1

//****************************************************************************
//
// ZEUS_INA226 Register addresses 
//
//****************************************************************************
#define ZEUS_INA226_CONFIG_REG 			0x0
#define ZEUS_INA226_SVCONV_REG  		0x1
#define ZEUS_INA226_BVCONV_REG  		0x2
#define ZEUS_INA226_PCONV_REG  			0x3
#define ZEUS_INA226_ICONV_REG  			0x4
#define ZEUS_INA226_CAL_REG     		0x5
#define ZEUS_INA226_MASK_REG    		0x6
#define ZEUS_INA226_ALERT_REG   		0x7

//****************************************************************************
//
// ZEUS_INA226 Config Register Values
//
//****************************************************************************
#define ZEUS_INA226_CONFIG_RESET		0x80
#define ZEUS_INA226_CONFIG_DEF_H		0x41
#define ZEUS_INA226_CONFIG_DEF_L		0x27
#define ZEUS_INA226_CONFIG_CNT_SV_H		0x43
#define ZEUS_INA226_CONFIG_CNT_SV_L		0x25

//****************************************************************************
//
// ZEUS_INA226 Mask Register Values
//
//****************************************************************************
#define ZEUS_INA226_MASK_OVF_EN_H		0x80
#define ZEUS_INA226_MASK_OVF_EN_L		0x00

//****************************************************************************
//
// ZEUS_INA226 Alert Register Values
//
//****************************************************************************
#define ZEUS_INA226_ALERT_80MV_H		0x7D
#define ZEUS_INA226_ALERT_80MV_L		0x00

//****************************************************************************
//
// ZEUS I2C Slave IC Address
// ADS1115 is for Voltage Sense
// INA226A and INA226B are Channel Encoding for Current Sense
//
//****************************************************************************
#define ZEUS_INA226A_ADDR			0x40
#define ZEUS_INA226B_ADDR			0x45

//****************************************************************************
//
// ZEUS DVIC Defines
//
//****************************************************************************
#define ZEUS_ZERO_CODE				0x2001
#define ZEUS_MAX_MIN_LIMIT                      0x3C002000
#define ZEUS_DVIC_CHANNEL_A                     0
#define ZEUS_DVIC_CHANNEL_B                     1
#define ZEUS_ERR_CODE                           0xFFFFFFFF

#define ZEUS_RISEEDGE                           0
#define ZEUS_FALLEDGE                           1

#define ZEUS_TRIG_ABORTEN                       1
#define ZEUS_TRIG_ABORTDIS                      0

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
extern void     ZEUSLibInit();
extern void     ZEUSLibConfigureCurrentSense(uint32_t ui32Channel,
                                             uint32_t ui32Resistor,
                                             uint32_t ui32MaxCurrentInmA);
extern uint32_t ZEUSLibGetCurrent(uint32_t ui32Channel,
                                  bool     *bSign,
                                  uint32_t *ui32Quotient,
                                  uint32_t *ui32Remainder);


#endif // __ZEUSLIB_H__
