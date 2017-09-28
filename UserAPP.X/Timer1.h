/*
 * File:   Timer1.h
 * Author: bandakka
 *
 * Created on September 27, 2017, 12:12 PM
 */

#ifndef TIMER1_H
#define	TIMER1_H

#ifdef	__cplusplus
extern "C" {
#endif

void InitTimer1(void);

void delay_onesec(void);

void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void);


#ifdef	__cplusplus
}
#endif

#endif	/* TIMER1_H */
