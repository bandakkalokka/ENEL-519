/*
 * File:   Timer2.h
 * Author: bandakka
 *
 * Created on September 18, 2017, 5:14 PM
 */

#ifndef TIMER2_H
#define	TIMER2_H

#ifdef	__cplusplus
extern "C" {
#endif

void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void);

void delay_ms(unsigned int time_ms);

void InitTimer2(void);

#endif	/* TIMER2_H */
