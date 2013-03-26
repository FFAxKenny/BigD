/* 
 * File:   DrivingMoves.h
 * Author: Doswah
 *
 * Created on March 13, 2013, 12:48 AM
 */


#define FORWARD     5000
#define FACE_LEFT   5000
#define FACE_RIGHT  5000
#define FACE_BACK   5000



#ifndef DRIVINGMOVES_H
#define	DRIVINGMOVES_H

#ifdef	__cplusplus
extern "C" {
#endif

    void Forward();
    void FaceLeft();
    void FaceRight();
    void FaceBack();

#ifdef	__cplusplus
}
#endif

#endif	/* DRIVINGMOVES_H */

