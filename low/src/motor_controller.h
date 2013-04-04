/*
 *  File:   motor_controller.h
 *  Description: Forward, Face Left, Face Right, and Face Back Functions.
 *
 *  UH Manoa Micromouse | Team PG
 *
 */

#define LM4 (LATBbits.LATB8)
#define LM3 (LATBbits.LATB9)
#define LM2 (LATBbits.LATB10)
#define LM1 (LATBbits.LATB11)
#define RM4 (LATAbits.LATA2)
#define RM3 (LATAbits.LATA3)
#define RM2 (LATAbits.LATA4)
#define RM1 (LATBbits.LATB4)
 
#ifndef MOTOR_CONTROLLER_H
#define	MOTOR_CONTROLLER_H

    void wait(void);

    /* Timer Interrupt Routine */
    void __attribute__((__interrupt__, __auto_psv__)) _T1Interrupt(void);

    /* High-Level Functions */
    void MoveForward(int distance);
    void FaceLeft(void);
    void FaceRight(void);
    void FaceBack(void);

    /* Low-Level Functions */
    void StepLMotor(Motor motor);
    void StepRMotor(Motor motor);

   
    extern int TurnStage, MoveStage, QueueTurnStage;

#ifdef	__cplusplus
extern "C" {
#endif

    


#ifdef	__cplusplus
}
#endif

#endif	/* MOTOR_CONTROLLER_H */

