#include <p24F16KA101.h>
#include "Timer1.h"
#include "ChangeClk.h"


void InitTimer1(void) {
    T1CONbits.TCKPS = 0b00;             //Set pre-scale to 1
    T1CONbits.TCS = 0b0;                //Use Internal Clock
    IPC0bits.T1IP = 5;                  //Set to priority level 5
    IFS0bits.T1IF = 0b0;                //Clear Flag status
    IEC0bits.T1IE = 0b1;                //Enable the Timer Interrupt
}

void delay(unsigned int time) {
    //NewClk(32);
    T1CONbits.TON = 1;                  //Turn on timer 1
    
}

//Timer1 Interrupt subroutine
void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void)
{
    IFS0bits.T1IF = 0b0;                //Clear Flag status
    T1CONbits.TON = 0b0;                //Turn off timer
    TMR2 = 0;
    //Nop();
}