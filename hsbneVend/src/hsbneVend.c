//*****************************************************************************
//
// project0.c - Example to demonstrate minimal TivaWare setup
//
// Copyright (c) 2012-2017 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 2.1.4.178 of the EK-TM4C1294XL Firmware Package.
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>

#include "driverlib/systick.h"
#include "driverlib/watchdog.h"
#include "driverlib/can.h"
#include "driverlib/timer.h"

#include "inc/hw_types.h"
#include "inc/hw_memmap.h"

#include "pins_def.h"
#include "d_ina226.h"
#include "d_can.h"


//****************************************************************************
//
// System clock rate in Hz.
//
//****************************************************************************
uint32_t g_ui32SysClock;

uint32_t time;

volatile uint32_t g_ui32Flags = 0;


//*****************************************************************************
//
// Flag to tell the watchdog interrupt handler whether or not to clear the
// interrupt (feed the watchdog).
//
//*****************************************************************************
volatile bool g_bFeedWatchdog = true;


#define DEBUG

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}
#endif

void
SysTick_IntHandler(void)
{
   time++;
//   if(time > 1000)
//   {
//       g_ui32Flags = 1;
//       time = 0;
//   }
}

//*****************************************************************************
//
// The interrupt handler for the watchdog.  This feeds the dog (so that the
// processor does not get reset) and winks the LED connected to GPIO B3.
//
//*****************************************************************************
void
WatchdogIntHandler(void)
{
    //
    // If we have been told to stop feeding the watchdog, return immediately
    // without clearing the interrupt.  This will cause the system to reset
    // next time the watchdog interrupt fires.
    //
    if(!g_bFeedWatchdog)
    {
        return;
    }

    //
    // Clear the watchdog interrupt.
    //
    WatchdogIntClear(WATCHDOG0_BASE);
}

//*****************************************************************************
//
// The interrupt handler for the first timer interrupt.
//
//*****************************************************************************
void
Timer0IntHandler(void)
{
    //
    // Clear the timer interrupt.
    //
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    //
    // Toggle the flag for the first timer.
    //
//    HWREGBITW(&g_ui32Flags, 0) ^= 1;
    g_ui32Flags = 1;

    //
    // Update the interrupt status.
    //
//    IntMasterDisable();
//    IntMasterEnable();
}

void
SysTickbegin()
{
    SysTickPeriodSet(80000);
    SysTickIntRegister(SysTick_IntHandler);
    SysTickIntEnable();
    SysTickEnable();
}

//*****************************************************************************
//
// Main 'C' Language entry point.
//
//*****************************************************************************
int
main(void)
{
    //
    // Run from the PLL at 120 MHz.
    //
    g_ui32SysClock = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                                       SYSCTL_OSC_MAIN |
                                       SYSCTL_USE_PLL |
                                       SYSCTL_CFG_VCO_480), 120000000);

    initPins();
    IntMasterEnable();

    //
    // Enable the watchdog interrupt.
    //
//    IntEnable(INT_WATCHDOG);

    //
    // Set the period of the watchdog timer to 5 seconds.
    //
//    WatchdogReloadSet(WATCHDOG0_BASE, g_ui32SysClock*5);

    //
    // Enable reset generation from the watchdog timer.
    //
//    WatchdogResetEnable(WATCHDOG0_BASE);

    GPIOPinWrite(GPIO_PORTL_BASE, (EXT_EN|AUX_EN), EXT_EN);

    //
    // Initialize CAN0
    //
    InitCAN0();

//    //
//    // Configure 32-bit periodic timers.
//    //
//    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
//    // Setup 1 second timer
//    TimerLoadSet(TIMER0_BASE, TIMER_A, g_ui32SysClock*10);
//
//    //
//    // Setup the interrupts for the timer timeouts.
//    //
//    IntEnable(INT_TIMER0A);
//    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
//
//    //
//    // Enable the timers.
//    //
//    TimerEnable(TIMER0_BASE, TIMER_A);


    SysTickbegin();

    //
    // Enable the watchdog timer.
    //
    //WatchdogEnable(WATCHDOG0_BASE);

//    ZEUSLibInit();
//    ZEUSLibConfigureCurrentSense(ZEUS_INA226A_ADDR, 100, 150);
//    ZEUSLibConfigureCurrentSense(ZEUS_INA226B_ADDR, 100, 150);

    bool     bSign;
//    uint32_t ui32Current;
//    uint32_t ui32Quotient;
//    uint32_t ui32Remainder;

//    HWREGBITW(&g_ui32Flags, 0) ^= 1;

    //
    // Loop Forever
    //
    while(1)
    {
        CAN_Send_Receive();

        if(g_ui32Flags > 0)
        {
            g_ui32Flags = 0;
            //
            // Turn on the LED
            //
//            GPIOPinWrite(GPIO_PORTQ_BASE, SOL_EN, 0);
            GPIOPinWrite(GPIO_PORTL_BASE, (EXT_EN|AUX_EN), EXT_EN);
    //        ui32Current = ZEUSLibGetCurrent(ZEUS_INA226A_ADDR, &bSign, &ui32Quotient, &ui32Remainder);

            if(bSign)
            {
                GPIOPinWrite(GPIO_PORTL_BASE, (EXT_EN|AUX_EN), EXT_EN);
                bSign = false;
            }
            else
            {
                GPIOPinWrite(GPIO_PORTL_BASE, (EXT_EN|AUX_EN), AUX_EN);
                bSign = true;
            }

            //
            // Delay for a bit
            //
//            SysCtlDelay(g_ui32SysClock);

            //
            // Turn on the LED
            //
//            GPIOPinWrite(GPIO_PORTL_BASE, (EXT_EN|AUX_EN), AUX_EN);

            //
            // Delay for a bit
            //
//            SysCtlDelay(g_ui32SysClock);
            //
            // Turn on the LED
            //
//            GPIOPinWrite(GPIO_PORTL_BASE, (EXT_EN|AUX_EN), 0);
//            GPIOPinWrite(GPIO_PORTQ_BASE, SOL_EN, SOL_EN);

            //
            // Delay for a bit
            //
//            SysCtlDelay(g_ui32SysClock);


            //
            // See if there is something new to transmit
            //
            if(true)
            {
                sendPackage();
            }
        }
    }
}
