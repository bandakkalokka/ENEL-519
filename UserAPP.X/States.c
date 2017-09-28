#include "States.h"

volatile unsigned int State; 
volatile unsigned int ButtonPressed;
unsigned int Mins;    // Minutes set by user
unsigned int Secs;    // Seconds set by user

void ZeroDisplay(void){
  // TODO -- Put code for displaying 00:00
}
void WaitForButtonPress(void){
    if (CNFlag)
    {
        delay_ms(80);
        PollCN();
        CNFlag = 0;
    }
    else
    {
        Idle();
    }
}
void IncrementTimer(void){
    // TODO -- Put code for updating UART with minute and second holders
    if (ButtonPressed == 1)
    {
        delay_ms(500);
        Mins += 1;   
        delay_ms(80);
        
        if (!(PB1 && ~PB2))
        {
            ButtonPressed = 0;
            State = S_WAIT_BUTTON_PRESS;
        }
    }
    else if (ButtonPressed == 2)
    {
        delay_ms(500);
        Secs += 1;     
        delay_ms(80);
        
        if (!(~PB1 && PB2))
        {
            ButtonPressed = 0;
            State = S_WAIT_BUTTON_PRESS;
        }
    }
   
    // Update UART here
}
void Countdown(void){
  // TODO -- Put code for counting down timer
  // TODO -- Put code for updating UART with minute and second holders
}
void Alarm(void){
  // TODO -- Turn off timer1
  // TODO -- Put code for displaying "ALARM" on UART
  // TODO -- Put code for resetting minute and second holders to 0
}
void Reset(void){
  // TODO -- Turn off timer1
  // TODO -- Put code for displaying "RESET" on UART
  // TODO -- Put code for resetting minute
}
