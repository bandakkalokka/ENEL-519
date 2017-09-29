#include "States.h"

volatile unsigned int State;
volatile unsigned int ButtonPressed;
unsigned int Min;    // Minutes set by user
unsigned int Sec;    // Seconds set by user

void ZeroDisplay(void){
    Mins = 0;
    Secs = 0;
    char* zeroTime = "\r\n00:00\r";
    DispString(zeroTime);
    
    State = S_WAIT_BUTTON_PRESS;
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
        if (Min == 59)
            Min = 0;
        else
            Min += 1;
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
        if (Sec == 59)
            Sec = 0;
        else
            Sec += 1;
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
    delay_onesec();
    
    if(Mins <= 0 && Secs <= 0) {        // Clock reaches 00:00
        State = S_ALARM;
    }
    else if(Secs <= 0 && Mins > 0) {    // Clock reaches XX:00
        Secs = 59;
        Mins--;
    }
    else {
        Secs--;
        Mins--;
    }
    
}
void Alarm(void){
  T1CONbits.TON = 0;
  TMR1 = 0;
  DispString("ALARM");
  Min = 0; Sec = 0;
  State = S_ZERO_DISPLAY;
}
void Reset(void){
  T1CONbits.TON = 0;
  TMR1 = 0;
  DispString("RESET");
  Min = 0; Sec = 0;
  State = S_ZERO_DISPLAY;
}
