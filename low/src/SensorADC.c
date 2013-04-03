/* 
 *  File:   SensorADC.c
 *  Description: Initialize and Perform Analog-to-Digital Conversion
 *
 *  UH Manoa Micromouse | Team PG
 *
 */

#if defined(__dsPIC33F__)
#include <p33FJ128MC802.h>
#include "SensorADC.h"
#include "macros.h"
#include <stdio.h>
#include <stdlib.h>
#include <dsp.h>
#include <xc.h>
#endif

float value;                        // ADC1BUF0 value as a float
int corr;                           // Correction Integer

int ReadADC(int channel) {
    AD1CHS0bits.CH0SA = channel;
    IFS0bits.AD1IF = 0;
    AD1CON1bits.ADON = 1;               // Begin Sampling Sequence
    ADC1BUF0 = 0x0000;                  // Clear ADC1 Buffer
    AD1CON1bits.DONE=0;
    AD1CON1bits.SAMP = 1;               // Start Conversion
    while(IFS0bits.AD1IF == 0);
    AD1CON1bits.ASAM = 0;
    return ADC1BUF0;
   
}