#include "States.h"

volatile unsigned int State;
volatile unsigned int ButtonPressed;
unsigned int Min;    // Minutes set by user
unsigned int Sec;    // Seconds set by user

void ZeroDisplay(void){
    Min = 0;
    Sec = 0;
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
        delay_ms(100);
        if (Min == 59)
            Min = 0;
        else
            Min += 1;
        delay_ms(80);

        if ((~PB1 || PB2))
        {
            ButtonPressed = 0;
            State = S_WAIT_BUTTON_PRESS;
        }
    }
    else if (ButtonPressed == 2)
    {
        delay_ms(100);
        if (Sec == 59)
            Sec = 0;
        else
            Sec += 1;
        delay_ms(80);

        if (PB1 || ~PB2)
        {
            ButtonPressed = 0;
            State = S_WAIT_BUTTON_PRESS;
        }
    }

    char inc_time[7];
    sprintf(inc_time, "%02d:%02d\r", Min, Sec);
    DispString(inc_time);
}
void Countdown(void){
  // TODO -- Put code for updating UART with minute and second holders
    
    if(CNFlag) {
        delay_ms(80);
        PollCN(); 
        CNFlag = 0;
        return;
    }
    
    delay_onesec();
    
    if(Min <= 0 && Sec <= 0) {        // Clock reaches 00:00
        State = S_ALARM;
    }
    else if(Sec <= 0 && Min > 0) {    // Clock reaches XX:00
        Sec = 59;
        Min--;
    }
    else {
        Sec--;
        Min--;
    }
    
    char dow_time[7];
    sprintf(dow_time, "%02d:%02d\r", Min, Sec);
    DispString(dow_time);
}

void Alarm(void){
  T1CONbits.TON = 0;
  TMR1 = 0;
  DispString("\r\nALARM\r\n");
  Min = 0; Sec = 0;
  State = S_ZERO_DISPLAY;
}

void Reset(void){
  T1CONbits.TON = 0;
  TMR1 = 0;
  DispString("\r\nRESET\r\n");
  Min = 0; Sec = 0;
  State = S_ZERO_DISPLAY;
}
