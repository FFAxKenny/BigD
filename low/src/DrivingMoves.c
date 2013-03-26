#if defined(__dsPIC33F__)
#include <p33FJ128MC802.h>
#include "DrivingMoves.h"
#include "MouseInit.h"
#include "Left_Motor.h"
#include "SensorADC.h"
#include "main.c"
#endif

int phase;
int stepCount;
int L_direction;
int R_direction;
int speed;

void __attribute__((__interrupt__, __no_auto_psv__)) _T1Interrupt(void)
        {
            ConvertADC();
            L_Motor(speed,L_direction,phase);
          //R_Motor(speed,R_direction,phase);
            IFS0bits.T1IF = 0;      // Clear Timer1 interrupt flag
        }

    void Forward(){
        L_direction = 0;                    // Spin Left Motor Forward
        R_direction = 0;                    // Spin Right Motor Forward
        stepCount = 0;                      // Initialize Step Count

        while(stepCount<FORWARD) {
            if(phase<5) phase++;            // Traverse each phase to spin
            else phase=0;

            _T1Interrupt();

            speed = TrackCORR();            // Calc. corretion for next step

            stepCount++;
        }
        
    }

    void FaceLeft() {       // TO-DO
        stepCount = 0;
        while(stepCount<FACE_LEFT) {
            if(phase<5) phase++;
            else phase=0;

            _T1Interrupt();

            speed = TURN_SPEED;

            stepCount++;
        }
    }

    void FaceRight() {      // TO-DO

    }

    void FaceBack() {       // TO-DO
        
    }