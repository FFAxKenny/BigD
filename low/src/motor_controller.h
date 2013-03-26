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
 
#ifndef CONTROLLER_H
#define	CONTROLLER_H

#ifdef	__cplusplus
extern "C" {
#endif

    /* High-Level Functions */
    void MoveForward(Motor *LMotor, Motor *RMotor);
    void FaceLeft(Motor *LMotor, Motor *RMotor);
    void FaceRight(Motor *LMotor, Motor *RMotor);
    void FaceBack(Motor *LMotor, Motor *RMotor);

    /* Low-Level Functions */
    void Move(Motor motor);
    void StepLMotor(Motor motor);
    void StepRMotor(Motor motor);

#ifdef	__cplusplus
}
#endif

#endif	/* CONTROLLER_H */

