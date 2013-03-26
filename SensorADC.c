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

void ConvertADC(int select) {
    AD1CSSL = 0;                        // Clear scan
    ADC1BUF0 = 0x0000;                  // Clear ADC1 Buffer
    AD1CON1bits.ADON = 1;               // Begin Sampling Sequence
    AD1CON1bits.SAMP = 1;               // Start Conversion
    while (!AD1CON1bits.DONE);          // Conversion done? Waiting for 1
    AD1CON1bits.DONE = 0;               // Clear conversion done status bit
   
}

int CalcCorr(void) {  
    //value = (float) 1 / ADC1BUF0;       // Take Inverse of buffer value
    //value = value * CORR_CONSTANT;      // Multiply by CORR_CONSTANT
    //corr = (int) value;                 // Cast float to integer
    //return corr;
    return ADC1BUF0;
}


    /* ADC1 Configuration Bit Detail

       30 TAD
       16 words per buffer input
       AD1CON1bits.ADON = 1;           // ADC Module is operating
       AD1CON1bits.ADSIDL = 0;         // Continue in Idle Mode
       AD1CON1bits.ADDMABM = 0;        // Same DMA buffer as non-DMA
       AD1CON1bits.AD12B = 1;          // 12-bit, 1-Channel
       AD1CON1bits.FORM = 11;          // Signed Fractional
       AD1CON1bits.SSRC0 = 000;        // Clear sample bit starts/ends
       AD1CON1bits.SIMSAM = 0;         // Since using 1-channel, unimplemented
       AD1CON1bits.ASAM = 0;           // Sampling starts when SAMP is set
       AD1CON1bits.SAMP = 0;           // ADC sampling are sampling
       AD1CON1bits.DONE = 0;           // ADC not done converting
       AD1CON2bits.VCFG = 000;         // ADREF+ ADREF-
       AD1CON2bits.CSCNA = 0;          // Scan Inputs
       AD1CON2bits.CHPS = 00;          // Converts CH0
       AD1CON2bits.BUFS = 0;           // Fill buffer 0x0-0x7
       AD1CON2bits.SMPI = 0000;        // Increment DMA every interrupt
       AD1CON2bits.BUFM = 0;           // Fill buffer at 0x0
       AD1CON2bits.ALTS = 0;           // Always uses Sample A

    */
