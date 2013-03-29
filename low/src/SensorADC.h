/* 
 *  File:   SensorADC.h
 *  Description: Initialize and Perform Analog-to-Digital Conversion
 *
 *  DetectorL2 -> AN0
 *  DetectorL1 -> AN1
 *  DetectorR1 -> AN4
 *  DetectorR2 -> AN5
 *
 *  UH Manoa Micromouse | Team PG
 *
 */

#ifndef SENSORADC_H
#define	SENSORADC_H

#ifdef	__cplusplus
extern "C" {
#endif



/* Variables */
extern volatile int SensorL2;    // Sensor 4 Value
extern volatile int SensorL1;    // Sensor 3 Value
extern volatile int SensorR1;    // Sensor 2 Value
extern volatile int SensorR2;    // Sensor 1 Value

/* Functions */

void ConvertADC(int sensor);          // Stops sampling and begins coverting.
                                //  Converts selected sensor to appropriate
                                //  sensor value as raw data.

int CalcCorr(void);             // Returns Tracking correction





#ifdef	__cplusplus
}
#endif

#endif	/* SENSORADC_H */

