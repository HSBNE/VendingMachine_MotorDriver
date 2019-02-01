/*
 * pins_def.h
 *
 *  Created on: Jan 12, 2019
 *      Author: Luke
 */

#ifndef SRC_PINS_INIT_H_
#define SRC_PINS_INIT_H_

#include <stdint.h>
#include <stdbool.h>

#include "inc/hw_memmap.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

#define PC GPIO_PORTC_BASE
#define PD GPIO_PORTD_BASE
#define PE GPIO_PORTE_BASE
#define PH GPIO_PORTH_BASE
#define PK GPIO_PORTK_BASE
#define PN GPIO_PORTN_BASE
#define PQ GPIO_PORTQ_BASE

#define EXT_EN  GPIO_PIN_0 // PORT L
#define AUX_EN  GPIO_PIN_1 // PORT L
#define SOL_EN  GPIO_PIN_4 // PORT Q

extern const int motor_port[];
extern const int motor_pin[];

void initPins(void);

#endif /* SRC_PINS_INIT_H_ */
