
#include <p24F16KA101.h>
#include "Timer2.h"
#include "ChangeClk.h"

/*
 * 
 * void InitTimer2(void){}
 * 
 * Initializes Timer2 (button delay timer)
 */
void InitTimer2(void) {
    T2CONbits.T32 = 0b00;               //Set timer2 to 16-bit
    T2CONbits.TCKPS = 0b00;             //Set pre-scale to 1
    T2CONbits.TCS = 0b0;                //Use Internal Clock
    IPC1bits.T2IP = 7;                  //Set to Highest priority
    IFS0bits.T2IF = 0b0;                //Clear Flag status
    IEC0bits.T2IE = 0b1;                //Enable the Timer Interrupt
}

/*
 * 
 * void delay_ms(void){}
 * 
 * Sets delay in milliseconds based on time_ms parameter
 */
void delay_ms(unsigned int time_ms) {
    PR2 = (time_ms) * 16;
    T2CONbits.TON = 0b1;                //Turn on Timer
    Idle();

    return;
}

/*
 * 
 * void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void){}
 * 
 * subroutine for T2Interrupt
 */
void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void)
{
    IFS0bits.T2IF = 0;                //Clear Flag status
    T2CONbits.TON = 0;                //Turn off timer
    TMR2 = 0;                         //Clear TMR2
    Nop();
}
