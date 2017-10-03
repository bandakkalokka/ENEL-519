#include <p24F16KA101.h>
#include "IO.h"
#include "Timer2.h"
#include "UART2.H"
#include "States.h"

volatile unsigned int CNFlag;

void InitCN(void){
    TRISBbits.TRISB4 = 1;           //Set RB4 as input
    TRISAbits.TRISA4 = 1;           //Set RA4 as input
    CNEN1bits.CN1IE = 1;            //Enable CN1
    CNEN1bits.CN0IE = 1;            //Enable CN0
    CNPD1bits.CN0PDE = 1;           //Pin CN0 pull down enable
    CNPD1bits.CN1PDE = 1;           //Pin CN1 pull down enable
    IPC4bits.CNIP = 6;              //Highest priority interrupt
    IFS1bits.CNIF = 0;              //Clear interrupt
    IEC1bits.CNIE = 1;              //Enables change notification interrupt
}

void PollCN (void){
    if(PB1 && PB2) {
        if(State == S_COUNTDOWN) {
            State = S_RESET;
        }
        else if(State ==  S_WAIT_BUTTON_PRESS){
            delay_onesec();
            State = S_COUNTDOWN;
        }
    }
    else if(PB1 && ~PB2 && State ==  S_WAIT_BUTTON_PRESS) {
        State = S_INC_TIMER;
        ButtonPressed = 1;
    }
    else if(PB2 && ~PB1 && State ==  S_WAIT_BUTTON_PRESS){
        State = S_INC_TIMER;
        ButtonPressed = 2;
    }
}

void __attribute__ ((interrupt, no_auto_psv)) _CNInterrupt(void){
    
    if(PB1 || PB2) {
        CNFlag = 1;
    }
    
    IFS1bits.CNIF = 0;                  //Clear Interrupt
    //Nop();
}

