/*
 * can.h
 *
 *  Created on: Jan 12, 2019
 *      Author: Luke
 */

#ifndef SRC_D_CAN_H_
#define SRC_D_CAN_H_

#include <stdint.h>
#include <stdbool.h>

#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/can.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"

#include "inc/hw_can.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"

//*****************************************************************************
//
// Message Identifiers and Objects
// RXID is set to 0 so all messages are received
//
//*****************************************************************************
#define CAN0RXID                0
#define RXOBJECT                1
#define CAN0TXID                2
#define TXOBJECT                2

void InitCAN0(void);
void CANErrorHandler(void);
void CAN_Send_Receive(void);
void sendPackage(void);

#endif /* SRC_D_CAN_H_ */
