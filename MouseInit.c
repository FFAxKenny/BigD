#if defined(__dsPIC33F__)
#include "MouseInit.h"
#include "Left_Motor.h"
#include "SensorADC.h"
#include <p33FJ128MC802.h>
#endif

void InitTimer_IO(void) {
    TRISA = 0b0000000001100011;         /* Digital I/O Port A
                                             Inputs: RA0 RA1 RA5 RA6
                                             Outputs: Everything else   */

    TRISB = 0b1000000000000111;         /* Digital I/O Port B
                                             Inputs: RB0 RB1 RB2 RB15
                                             Outputs: Everything else    */

    AD1PCFGL = 0b11001100;              // AN0, AN1, AN2, AN3 Analog Ports

    
    /* Timer Initialization */
    T1CONbits.TON = 0;                  // Disable Timer
    T1CONbits.TCS = 0;                  // Internal instruction cycle clock
    T1CONbits.TGATE = 0;                // Disable Gated Timer mode
    T1CONbits.TCKPS = 0b00;             // Select 1:1 Prescaler
    TMR1 = 0x00;                        // Clear timer register
    PR1 = PERIOD;                       // Load the period value
    IPC0bits.T1IP = 0x01;               // Set Timer1 Interrupt Priority Level
    IFS0bits.T1IF = 0;                  // Clear Timer1 Interrupt Flag
}


void InitBuzzer(int startup) {
    int i;
    while(startup != 1) {               // Wait for start button to be pressed
        if(startup == 1) {
            for(i=0; i<12000; i++) { 
                PORTBbits.RB14 = 1;     // Create Buzzer noise
            }
                PORTBbits.RB14 = 0;
                break;
            }
        }
}