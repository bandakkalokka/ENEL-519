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
    }
    else
    {
        Idle();
    }
}
void IncrementTimer(unsigned int Button){
  // TODO -- Put code for incrementing minute and second holders
  // TODO -- Put code for updating UART with minute and second holders
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
