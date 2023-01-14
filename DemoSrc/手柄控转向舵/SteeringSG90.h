#ifndef __STEERINGSG90_H__
#define __STEERINGSG90_H__

void initSteeringPWMTimer();
void setSteeringDegree(unsigned char d);
void SteeringPWMTimerInterruption();

#endif