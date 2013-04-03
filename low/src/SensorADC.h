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

/* Functions */

int ReadADC(int channel);       // Stops sampling and begins coverting.
                                //  Converts selected sensor to appropriate
                                //  sensor value as raw data.




#ifdef	__cplusplus
}
#endif

#endif	/* SENSORADC_H */

