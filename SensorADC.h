/* 
 * File:   SensorADC.h
 * Author: Doswah
 *
 * Created on March 6, 2013, 6:29 PM
 */

#ifndef SENSORADC_H
#define	SENSORADC_H

#ifdef	__cplusplus
extern "C" {
#endif

#define CORR_CONSTANT 600000

/* Variables */
extern volatile int SENSOR1;    // Sensor 1 Value
extern volatile int SENSOR2;    // Sensor 2 Value
extern volatile int SENSOR3;    // Sensor 3 Value
extern volatile int SENSOR4;    // Sensor 4 Value

/* Functions */
void InitADC(void);             // Initialize ADC and begins sampling
void ConvertADC(void);           // Stops sampling and begins coverting
                                //   results to correction values
int TrackCORR(void);            // Returns Tracking correction





#ifdef	__cplusplus
}
#endif

#endif	/* SENSORADC_H */

