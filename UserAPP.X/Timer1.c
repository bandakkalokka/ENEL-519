#include <p24F16KA101.h>
#include "Timer1.h"
#include "ChangeClk.h"

/*
 * 
 * void InitTimer1(void){}
 * 
 * Initializes Timer1 (countdown timer)
 */

void InitTimer1(void) {
    T1CONbits.TCKPS = 0b00;             //Set pre-scale to 1
    T1CONbits.TCS = 0b0;                //Use Internal Clock
    IPC0bits.T1IP = 5;                  //Set to priority level 5
    IFS0bits.T1IF = 0b0;                //Clear Flag status
    IEC0bits.T1IE = 0b1;                //Enable the Timer Interrupt
}

/*
 * 
 * void delay_onesec(void){}
 * 
 * Sets the PR1 value to match 1 second and turn on the timer
 */

void delay_onesec(void) {
    PR1 = 9500;                        // Set PR1 for 1 second
    T1CONbits.TON = 1;                  //Turn on timer 1
    Idle();

    return;
}

/*
 * 
 * void __attribute__ ((interrupt, no_auto_psv)) _T1Interrupt(void){}
 * 
 * subroutine for T1Interrupt
 */
void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void)
{
    IFS0bits.T1IF = 0;                //Clear Flag status
    T1CONbits.TON = 0;                //Turn off timer
    TMR1 = 0;
    Nop();
}
