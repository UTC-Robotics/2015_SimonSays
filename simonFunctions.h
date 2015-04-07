/* 
 * File:   simonFunctions.h
 * Author: Lee Napier
 *
 * Created on September 27, 2014, 4:06 PM
 */

#ifndef SIMONFUNCTIONS_H
#define	SIMONFUNCTIONS_H

#ifdef	__cplusplus
extern "C" {
#endif

void sensorRead(void);
void press(int button);
int buttonState(void);
void calibrateSensor(void);

#ifdef	__cplusplus
}
#endif

#endif	/* SIMONFUNCTIONS_H */

