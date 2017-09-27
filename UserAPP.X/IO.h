/* 
 * File:   IO.h
 * Author: bandakka
 *
 * Created on September 25, 2017, 9:54 AM
 */

#ifndef IO_H
#define	IO_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#define PIN_RB4     0x01                    //Flag for RB4 pressed
#define PIN_RA4     0x02                    //Flag for RA4 pressed
#define BOTH        0x03                    //Flag for Both pressed

extern volatile unsigned int CNFlag;

void __attribute__((interrupt, no_auto_psv)) _CNInterrupt(void);

void InitCN(void);

void EmitCN(unsigned char pin);

void PollCN (void);


#endif	/* IO_H */