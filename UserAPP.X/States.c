#include "States.h"

volatile unsigned int State; 

void ZeroDisplay(void){
  // TODO -- Put code for displaying 00:00
}
void WaitForButtonPress(void){
  // TODO -- Put code for waiting for button press
}
void IncrementTimer(void){
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
