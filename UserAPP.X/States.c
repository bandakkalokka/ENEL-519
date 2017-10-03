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
        Sleep();
    }
}
void IncrementTimer(void){
    // TODO -- Put code for updating UART with minute and second holders
    char inc_time[7];
    
    if (ButtonPressed == 1)
    {
        if(PB1 && !CNFlag) {
            delay_ms(80);
            if (Min == 59)
                Min = 0;
            else
                Min += 1;
            delay_ms(80);
            
            sprintf(inc_time, "%02d:%02d\r", Min, Sec);
            DispString(inc_time);
        }
        else {
            ButtonPressed = 0;
            CNFlag = 0;
            State = S_WAIT_BUTTON_PRESS;
        }
    }
    else if (ButtonPressed == 2)
    {
        if(PB2 && !CNFlag) {
            delay_ms(80);
            if (Sec == 59)
                Sec = 0;
            else
                Sec += 1;
            delay_ms(80);
            
            sprintf(inc_time, "%02d:%02d\r", Min, Sec);
            DispString(inc_time);
            
        }
        else {
            ButtonPressed = 0;
            CNFlag = 0;
            State = S_WAIT_BUTTON_PRESS;
        }
    }
}
void Countdown(void){
  // TODO -- Put code for updating UART with minute and second holders
    
    char dow_time[7];
    sprintf(dow_time, "%02d:%02d\r", Min, Sec);
    DispString(dow_time);

    IEC1bits.CNIE = 0;
    delay_onesec();
    IEC1bits.CNIE = 1;
    
    if(CNFlag) {
        delay_ms(80);
        PollCN(); 
        CNFlag = 0;
    }
    
    if(Min <= 0 && Sec <= 0) {        // Clock reaches 00:00
        State = S_ALARM;
    }
    else if(Sec <= 0 && Min > 0) {    // Clock reaches XX:00
        Sec = 59;
        Min--;
    }
    else{
        Sec--;
    }      
}

void Alarm(void){
  T1CONbits.TON = 0;
  TMR1 = 0;
  DispString("\r\nALARM\r");
  Min = 0; Sec = 0;
  State = S_ZERO_DISPLAY;
}

void Reset(void){
  T1CONbits.TON = 0;
  TMR1 = 0;
  DispString("\r\nRESET\r");
  Min = 0; Sec = 0;
  State = S_ZERO_DISPLAY;
}
