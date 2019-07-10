/*
 * released under GNU AFFERO GENERAL PUBLIC LICENSE Version 3, 19 November 2007
 * 
 *      Author:     Andrea Biasutti
 *      Date:       July 5th 2019
 *      Hardware:   PIC32MX440256H
 * 
 * source available here https://github.com/andb70/Timers.X
 * 
 */
#pragma config FPLLIDIV = DIV_2 // PLL Input Divider (1x Divider)
#pragma config FPLLMUL = MUL_20 // PLL Multiplier (24x Multiplier)
#pragma config UPLLIDIV = DIV_2 // USB PLL Input Divider (12x Divider)
#pragma config UPLLEN = OFF // USB PLL Enable (Disabled and Bypassed)
#pragma config FPLLODIV = DIV_1 // System PLL Output Clock Divider (PLL Divide by 256)
// DEVCFG1
#pragma config FNOSC = PRIPLL // Oscillator Selection Bits (Primary Osc w/PLL (XT+,HS+,EC+PLL))
#pragma config FSOSCEN = ON // Secondary Oscillator Enable (Enabled)
#pragma config IESO = ON // Internal/External Switch Over (Enabled)
#pragma config POSCMOD = HS // Primary Oscillator Configuration (HS osc mode)
#pragma config OSCIOFNC = ON // CLKO Output Signal Active on the OSCO Pin (Enabled)
#pragma config FPBDIV = DIV_8 // Peripheral Clock Divisor (Pb_Clk is Sys_Clk/8)
#pragma config FCKSM = CSDCMD // Clock Switching and Monitor Selection (Clock Switch Disable, FSCM Disabled)
#pragma config WDTPS = PS1048576 // Watchdog Timer Postscaler (1:1048576)
#pragma config FWDTEN = OFF // Watchdog Timer Enable (WDT Disabled (SWDTEN Bit Controls))
// DEVCFG0
#pragma config DEBUG = OFF // Background Debugger Enable (Debugger is disabled)
#pragma config ICESEL = ICS_PGx2 // ICE/ICD Comm Channel Select (ICE EMUC2/EMUD2 pins shared with PGC2/PGD2)
#pragma config PWP = OFF // Program Flash Write Protect (Disable)
#pragma config BWP = OFF // Boot Flash Write Protect bit (Protection Disabled)
#pragma config CP = OFF // Code Protect (Protection Disabled)

#include <p32xxxx.h> // Include PIC32 specifics header file
#include <plib.h> // Include the PIC32 Peripheral Library
#include "timers.h"

// use the green led to monitor hertbeat
#define monitorGLed(state)      LATGbits.LATG6 = state
#define monitorGLedToggle()     LATGbits.LATG6 = !LATGbits.LATG6

// use the yellow led to monitor timer_us(0)
#define monitorYLed(state)      LATDbits.LATD1 = state
#define monitorYLedToggle()     LATDbits.LATD1 = !LATDbits.LATD1

// use the red led to monitor timer_us(x)
#define monitorRLed(state)      LATBbits.LATB13 = state
#define monitorRLedToggle()     LATBbits.LATB13 = !LATBbits.LATB13
/******************************************************************************/
int main() {

    // enable leds
    PORTSetPinsDigitalOut(IOPORT_D, BIT_1); //  YELLOW led on-board
    PORTSetPinsDigitalOut(IOPORT_G, BIT_6); //  GREEN  led on-board
    mJTAGPortEnable(0); // Disable JTAG
    PORTSetPinsDigitalOut(IOPORT_B, BIT_13); // RED led @ D8  
    
    // switch all off
    LATD=0;
    LATB=0;
    LATG=0;
    
    // initialize timer service
    initTimers();  
    
    unsigned int count = 0;
    while (1) 
    {
        // read input
        checkTimers();

        if(heartbeat()) 
        {
            monitorYLedToggle();
        }

        if (timer1Status())
        {
            if (++count == TMR_FREQ_1)
            {
                count = 0;
                monitorYLedToggle();
            }
        }
        if(timer_usElapsed(0))
        {
            monitorGLedToggle();
            timer_usSet(0, TMR_FREQ_2<<TMR_FREQ_K);
        }
        if(timer_usElapsed(1))
        {
            monitorRLedToggle();
            timer_sSet(1, 1);
        }
        
        /**********************************************************************/
        // test full instance impact
        if(timer_usElapsed(2))
        {
            monitorRLedToggle();
            timer_sSet(2, 1);
        }
        if(timer_usElapsed(3))
        {
            monitorRLedToggle();
            timer_sSet(3, 1);
        }
        if(timer_usElapsed(4))
        {
            monitorRLedToggle();
            timer_sSet(4, 1);
        }
        if(timer_usElapsed(5))
        {
            monitorRLedToggle();
            timer_sSet(5, 1);
        }
        if(timer_usElapsed(6))
        {
            monitorRLedToggle();
            timer_sSet(6, 1);
        }
        if(timer_usElapsed(7))
        {
            monitorRLedToggle();
            timer_sSet(7, 1);
        }
        if(timer_usElapsed(8))
        {
            monitorRLedToggle();
            timer_sSet(8, 1);
        }
        if(timer_usElapsed(9))
        {
            monitorRLedToggle();
            timer_sSet(9, 1);
        }
        if(timer_usElapsed(10))
        {
            monitorRLedToggle();
            timer_sSet(10, 1);
        }
        if(timer_usElapsed(11))
        {
            monitorRLedToggle();
            timer_sSet(11, 1);
        }
        if(timer_usElapsed(12))
        {
            monitorRLedToggle();
            timer_sSet(12, 1);
        }
        if(timer_usElapsed(13))
        {
            monitorRLedToggle();
            timer_sSet(13, 1);
        }
        if(timer_usElapsed(14))
        {
            monitorRLedToggle();
            timer_sSet(14, 1);
        }
        if(timer_usElapsed(15))
        {
            monitorRLedToggle();
            timer_sSet(15, 1);
        }
        /*if(timer_usElapsed(16))
        {
            monitorRLedToggle();
            timer_sSet(16, 1);
        }
        if(timer_usElapsed(17))
        {
            monitorRLedToggle();
            timer_sSet(17, 1);
        }
        if(timer_usElapsed(18))
        {
            monitorRLedToggle();
            timer_sSet(18, 1);
        }
        if(timer_usElapsed(19))
        {
            monitorRLedToggle();
            timer_sSet(19, 1);
        }
        if(timer_usElapsed(20))
        {
            monitorRLedToggle();
            timer_sSet(20, 1);
        }
        if(timer_usElapsed(21))
        {
            monitorRLedToggle();
            timer_sSet(21, 1);
        }
        if(timer_usElapsed(22))
        {
            monitorRLedToggle();
            timer_sSet(22, 1);
        }
        if(timer_usElapsed(23))
        {
            monitorRLedToggle();
            timer_sSet(23, 1);
        }
        if(timer_usElapsed(24))
        {
            monitorRLedToggle();
            timer_sSet(24, 1);
        }
        if(timer_usElapsed(25))
        {
            monitorRLedToggle();
            timer_sSet(25, 1);
        }
        if(timer_usElapsed(26))
        {
            monitorRLedToggle();
            timer_sSet(26, 1);
        }
        if(timer_usElapsed(27))
        {
            monitorRLedToggle();
            timer_sSet(27, 1);
        }
        if(timer_usElapsed(28))
        {
            monitorRLedToggle();
            timer_sSet(28, 1);
        }
        if(timer_usElapsed(29))
        {
            monitorRLedToggle();
            timer_sSet(29, 1);
        }*/

        /**********************************************************************/
        
    }
    return 1;
}