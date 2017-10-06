#include "States.h"

volatile unsigned int State;
volatile unsigned int ButtonPressed;
unsigned int Min;    // Minutes set by user
unsigned int Sec;    // Seconds set by user

/*
 * 
 * void zeroDisplay(void){}
 * Displays 00:00 on UART TX line
 */

void ZeroDisplay(void){
    Min = 0;
    Sec = 0;
    char* zeroTime = "\r\n00:00\r";
    DispString(zeroTime);
    
    State = S_WAIT_BUTTON_PRESS;                    //Change state to S_WAIT_BUTTON_PRESS
}


/*
 * 
 * void WaitForButtonPress(void){}
 * 
 * Waits for a button to be pressed sleeps while nothing happens
 * CNFlag is checked then pollCN is called to check which buttons were pressed
 */

void WaitForButtonPress(void){
    if (CNFlag)
    {
        delay_ms(80);
        PollCN();                   //Checks for button pushes
        CNFlag = 0;
    }
    else
    {
        Sleep();
    }
}


/*
 * 
 * void IncrementTimer(void){}
 * 
 * Increments the seconds and minutes and displays the new time
 * If minutes or seconds hits 59 then it rolls over to 00
 */
void IncrementTimer(void){
    char inc_time[7];
    
    if (ButtonPressed == 1)
    {
        if(PB1 && !CNFlag) {                            //If PushButton1 is pressed
            delay_ms(80);
            if (Min == 59)                              
                Min = 0;
            else
                Min += 1;                               //Increment minutes
            delay_ms(80);
            
            sprintf(inc_time, "%02d:%02d\r", Min, Sec);
            DispString(inc_time);                       //Display the current time
        }
        else {
            ButtonPressed = 0;                          
            CNFlag = 0;
            State = S_WAIT_BUTTON_PRESS;                //If no button is pressed, change state to S_WAIT_BUTTON_PRESS
        }
    }
    else if (ButtonPressed == 2)
    {
        if(PB2 && !CNFlag) {                            //If PushButton2 is pressed
            delay_ms(80);
            if (Sec == 59)                              
                Sec = 0;
            else
                Sec += 1;                               //Increment Seconds
            delay_ms(80);
            
            sprintf(inc_time, "%02d:%02d\r", Min, Sec);
            DispString(inc_time);                       //Display Current time
            
        }
        else {
            ButtonPressed = 0;
            CNFlag = 0;
            State = S_WAIT_BUTTON_PRESS;                //If no button is pressed, change state to S_WAIT_BUTTON_PRESS;
        }
    }
}

/*
 * 
 * void Countdown(void) {}
 * 
 * Decrements minutes and seconds and displays the time in UART TX line
 * 
 */
void Countdown(void){
    
    char dow_time[7];
    sprintf(dow_time, "%02d:%02d\r", Min, Sec);
    DispString(dow_time);                               //Display Time

    IEC1bits.CNIE = 0;                                  //Turn off CN Interrupt
    delay_onesec();
    IEC1bits.CNIE = 1;                                  //Turn on CN Interrupt (This stops the timer from being
                                                        //interrupted by push of either button during countdown)
    if(CNFlag) {
        delay_ms(80);
        PollCN();                                       //Check for any button pushes
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

/*
 * 
 * void Alarm(void) {}
 * 
 * Turns off Timer1 (countdown timer) and clears the TMR1
 * Displays ALARM and clears minutes and seconds
 * Sets state to S_ZERO_DISPLAY
 */
void Alarm(void){
  T1CONbits.TON = 0;
  TMR1 = 0;
  DispString("\r\nALARM\r");
  Min = 0; Sec = 0;
  State = S_ZERO_DISPLAY;
}

/*
 * 
 * void Reset(void) {}
 * 
 * Turns off Timer1 (countdown timer) and clears the TMR1
 * Displays RESET and clears minutes and seconds
 * Sets state to S_ZERO_DISPLAY
 */
void Reset(void){
  T1CONbits.TON = 0;
  TMR1 = 0;
  DispString("\r\nRESET\r");
  Min = 0; Sec = 0;
  State = S_ZERO_DISPLAY;
}
