/*
 * pins_def.h
 *
 *  Created on: Jan 12, 2019
 *      Author: Luke
 */

#ifndef SRC_PINS_DEF_H_
#define SRC_PINS_DEF_H_

#include <stdint.h>
#include <stdbool.h>

#include "inc/hw_memmap.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"


#define EXT_EN  GPIO_PIN_0 // PORT L
#define AUX_EN  GPIO_PIN_1 // PORT L
#define SOL_EN  GPIO_PIN_4 // PORT Q


//int slot_relays[]  = {22,23,24,25,26,27,28,29,30,31,32, 33, 34, 35, 36, 37, 38,39,40,41,42,43,44,45,46};
//int button_map[]   = {A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14,A15,4, 5, 6, 7, 8, 9, 10,11,12};
//int interuptPins[] = {18,19,20,21};


void initPins(void);

#endif /* SRC_PINS_DEF_H_ */
