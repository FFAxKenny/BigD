/*
 *  File:   init.c
 *  Description: Initialize Timer1 Interrupt and Piezo Buzzer.
 *
 *  UH Manoa Micromouse | Team PG
 *
 */

#if defined(__dsPIC33F__)
#include "init.h"
#include "macros.h"
#include "SensorADC.h"
#include "motor.h"
#include <p33FJ128MC802.h>
#endif

void TheBirthOfBigD(void) {

    /*********************** I/O Declarations ********************************/
    TRISA = 0b0000000001100011;         // Digital I/O Port A
    TRISB = 0b1000000000000111;         // Digital I/O Port B
                                        //     Inputs: RB0 RB1 RB2 RB15
                                        //     Outputs: Everything else
    AD1PCFGL = 0b11001100;              // AN0, AN1, AN2, AN3 Analog Ports


    /****************** Analog to Digital Initialization *********************/
    AD1CON1 = 0x04E0;                   // A/D Control Register 1
    AD1CON2 = 0x0000;                   // A/D Control Register 2
    AD1CON3bits.SAMC = 0b11000;         // A/D Control Register 3
    AD1CON3bits.ADCS = 8;
    AD1CON4 = 0x0000;                   // A/D Control Register 4
    AD1CSSLbits.CSS0 = 0;
    AD1CSSLbits.CSS1 = 1;
    AD1CSSLbits.CSS4 = 0;
    AD1CSSLbits.CSS5 = 0;
    
    /********************* Piezo Buzzer Initialization ***********************/
    int i;
    while(PORTBbits.RB15 != 1) {        // Wait for Start Button to be Pressed
        if(PORTBbits.RB15 == 1) {
            for(i=0; i<30000; i++) {
                PORTBbits.RB14 = 1;     // ON Buzzer Noise
            }
                PORTBbits.RB14 = 0;     // OFF Buzzer Noise
                break;
            }
        }
}


void ConfigureTimers(void) {

    /**************************** Timer 1 ************************************/
    T1CON = 0;                          // Reset Timer
    T1CONbits.TCS = 0;                  // Internal instruction cycle clock
    T1CONbits.TGATE = 0;                // Disable Gated Timer mode
    T1CONbits.TCKPS = 0;                // Select 1:1 Prescaler
    TMR1 = 0x00;                        // Clear timer register
    PR1 = PERIOD;                       // Load the PERIOD value

    _T1IP = 1;                          // Set Timer1 Interrupt Priority Level
    _T1IF = 0;                          // Clear Timer1 Interrupt Flag
    _T1IE = 1;

    T1CONbits.TON = 1;                  // Enable Timer

    /**************************** Timer 2 ************************************/
    T2CON = 0;                          // Reset Timer
    T2CONbits.TCS = 0;                  // Internal instruction cycle clock
    T2CONbits.TGATE = 0;                // Disable Gated Timer mode
    T2CONbits.TCKPS = 0;                // Select 1:1 Prescaler
    TMR2 = 0x00;                        // Clear timer register
    PR2 = PERIOD;                       // Load the PERIOD value

    _T2IP = 1;                          // Set Timer2 Interrupt Priority Level
    _T2IF = 0;                          // Clear Timer2 Interrupt Flag
    _T2IE = 1;

    T2CONbits.TON = 1;                  // Enable Timer

    /**************************** Timer 3 ************************************/
    T3CON = 0;                          // Reset Timer
    T3CONbits.TCS = 0;                  // Internal instruction cycle clock
    T3CONbits.TGATE = 0;                // Disable Gated Timer mode
    T3CONbits.TCKPS = 1;                // Select 1:1 Prescaler
    TMR3 = 0x00;                        // Clear timer register
    PR3 = 60000;                       // Load the PERIOD value

    _T3IP = 1;                          // Set Timer3 Interrupt Priority Level
    _T3IF = 0;                          // Clear Timer3 Interrupt Flag
    _T3IE = 1;

    T3CONbits.TON = 1;                  // Enable Timer

}
/*************************** Configure PLL ******************************
    // Configure PLL prescaler, PLL postscaler, PLL divisor
    PLLFBD = 63;              // M = 65
    CLKDIVbits.PLLPOST = 0;   // N2 = 2
    CLKDIVbits.PLLPRE = 1;    // N1 = e

    // Initiate Clock Switch to Primary Oscillator with PLL (NOSC = 0b011)
    __builtin_write_OSCCONH(0x03);
    __builtin_write_OSCCONL(0x01);

    // Wait for Clock switch to occur
    while(OSCCONbits.COSC != 0x11);

    //Wait for PLL to lock
    while(OSCCONbits.LOCK != 1);

 */
