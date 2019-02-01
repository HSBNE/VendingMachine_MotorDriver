/*
 * pins_init.c
 *
 *  Created on: Jan 12, 2019
 *      Author: Luke Hovington
 */

#include "pins_init.h"

/*
 * PIN MAPPING TO OUTPUT
 * 01, 02, 03, 04, 05, 06, 07, 08, 09, 10, 11, 12, 13, 14, 15
 * H3, C4, H2, C5, H1, C6, H0, C7, Q3, K3, K2, E2, K1, E3, K0
 *
 * 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30
 * Q2, E0, Q1, E1, Q0, D7, N4, D6, N3, D5, N2, D4, N1, E5, N0
*/

const int motor_port[] = { PH, PC, PH, PC, PH, PC, PH, PC, PQ, PK, PK, PE, PK, PE, PK, PQ, PE, PQ, PE, PQ, PD, PN, PD, PN, PD, PN, PD, PN, PE, PN};
const int motor_pin[] =  { 03, 04, 02, 05, 01, 06, 00, 07, 03, 03, 02, 02, 01, 03, 00, 02, 00, 01, 01, 00, 07, 04, 06, 03, 05, 03, 04, 01, 05, 00};


void initPins(void)
{
    //
    // Enable and wait for the port to be ready for access
    //

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA)){}

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB)){}

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOL)){}

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOQ);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOQ)){}

    SysCtlPeripheralEnable(SYSCTL_PERIPH_WDOG0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_WDOG0)){}

    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0)){}

    //
    // Set Pins to output
    //
    GPIOPinTypeGPIOOutput(GPIO_PORTL_BASE, (EXT_EN|AUX_EN));
}
