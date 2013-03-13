/*
 * File:   SensorADC.c
 * Author: Joshua Rivera
 *
 * Initialize ADC
 *
 * SENSOR1 -> AN0
 * SENSOR2 -> AN1
 * SENSOR3 -> AN4
 * SENSOR4 -> AN5
 *
 *  1. Configure the ADC module:
 *      a) Select port pins as analog inputs
 *          (AD1PCFGH<15:0> or AD1PCFGL<15:0>)
 *      b) Select voltage reference source to match
 *          expected range on analog inputs
 *          (AD1CON2<15:13>)
 *      c) Select the analog conversion clock to
 *           match desired data rate with processor
 *          clock (AD1CON3<7:0>)
 *       d) Determine how many S/H channels is used
 *           (AD1CON2<9:8> and AD1PCFGH<15:0>
 *           or AD1PCFGL<15:0>)
 *      e) Select the appropriate sample/conversion
 *           sequence (AD1CON1<7:5> and AD1CON3<12:8>)
 *       f) Select how conversion results are
 *           presented in the buffer (AD1CON1<9:8>)
 *       g) Turn on ADC module (AD1CON1<15>)
 *  2. Configure ADC interrupt (if required):
 *       a) Clear the AD1IF bit
 *       b) Select ADC interrupt priority
 *
 */
#if defined(__dsPIC33F__)
#include <p33FJ128MC802.h>
#include "SensorADC.h"
#include <dsp.h>
#include <xc.h>
#endif

float value;                        // ADC1BUF0 value as a float
int corr;                           // Correction Integer

void InitADC() {
    /* A/D Control Register 1 */
    AD1CON1 = 0x04E0;
    /*AD1CON1bits.ADON = 0;         // ADC Module is off
    AD1CON1bits.ADSIDL = 0;         // Continue in Idle Mode
    AD1CON1bits.ADDMABM = 1;        // Same DMA buffer as non-DMA
    AD1CON1bits.AD12B = 1;          // 12-bit, 1-Channel
    AD1CON1bits.FORM = 00;          // Integer Output Format
    AD1CON1bits.SSRC0 = 0;          // Clear sample bit starts/ends
    AD1CON1bits.SSRC1 = 0;          // Clear sample bit starts/ends
    AD1CON1bits.SSRC2 = 0;          // Clear sample bit starts/ends
    AD1CON1bits.SIMSAM = 0;         // Since using 1-channel, unimplemented
    AD1CON1bits.ASAM = 0;           // Sampling starts when SAMP is set
    AD1CON1bits.SAMP = 1;           // ADC sampling are sampling
    AD1CON1bits.DONE = 0;           // Reset ADC
    */

    /* A/D Control Register 2 */
    AD1CON2 = 0;
    /*
    AD1CON2bits.VCFG = 000;         // ADREF+ ADREF-
    AD1CON2bits.CSCNA = 0;          // Scan Inputs
    AD1CON2bits.CHPS = 00;          // Converts CH0
    AD1CON2bits.BUFS = 0;           // Fill buffer 0x0-0x7
    AD1CON2bits.SMPI = 0000;        // Increment DMA every interrupt
    AD1CON2bits.BUFM = 0;           // Fill buffer at 0x0
    AD1CON2bits.ALTS = 0;           // Always uses Sample A
    */

    /* A/D Control Register 3 */
    AD1CON3bits.SAMC = 0b11000;     // Auto Sample Time
    AD1CON3bits.ADCS = 8;           // Conversion Clock Select

    /* A/D Control Register 4 */
    AD1CON4 = 0;                    // 16 words of buffer per input

    /* ADC1 Input Scan Select Register Low */
    AD1CSSLbits.CSS0 = 1;           // Select AN0 for input scan
    AD1CSSLbits.CSS1 = 0;           // Select AN1 for input scan
    AD1CSSLbits.CSS4 = 0;           // Select AN4 for input scan
    AD1CSSLbits.CSS5 = 0;           // Select AN5 for input scan

    AD1CON1bits.ADON = 1;           // Begin Sampling Sequence
}

void ConvertADC(void) {
    AD1CON1bits.SAMP = 1;           // Start Conversion
    ADC1BUF0 = 0x0000;              // Clear ADC1 Buffer
    while (!AD1CON1bits.DONE);      // Conversion done? Waiting for 1
    AD1CON1bits.DONE = 0;           // Clear conversion done status bit
}

int TrackCORR(void) {
    value = (float) ((1/ADC1BUF0)   // Take inverse of reading
            *CORR_CONSTANT);        //  Multiply by CORR_CONSTANT
    return corr = (int) value;      // Cast float to integer
}