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
    IPC4bits.CNIP = 7;              //2nd highest priority interrupt
    IFS1bits.CNIF = 0;              //Clear interrupt
    IEC1bits.CNIE = 1;              //Enables change notification interrupt
}

void PollCN (void){
    if(PORTBbits.RB4 && PORTAbits.RA4) {
        State = S_COUNTDOWN;
    }
    else if(PORTBbits.RB4 && ~PORTAbits.RA4) {
        State = S_INC_TIMER;
        ButtonPressed = 1;
    }
    else if(PORTAbits.RA4 && ~PORTBbits.RB4){
        State = S_INC_TIMER;
        ButtonPressed = 2;
    }
}

void __attribute__ ((interrupt, no_auto_psv)) _CNInterrupt(void){
    
    if(PORTBbits.RB4 || PORTAbits.RA4) {
        CNFlag = 1;
    }
    
    IFS1bits.CNIF = 0;                  //Clear Interrupt
    Nop();
}

void EmitCN (unsigned char pin)
{
  if (pin == PIN_RB4)
  {
    DispString("RB4 Triggered");
  }
  if (pin == PIN_RA4)
  {
    DispString("RA4 Triggered");
  }
  if (pin == BOTH) {
    DispString("Both Triggered");
  }

  return;
}
