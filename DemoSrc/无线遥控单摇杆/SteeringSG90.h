#ifndef __STEERINGSG90_H__
#define __STEERINGSG90_H__

void initSteeringPWMTimer();
void initSteeringPWMTimer24M12T();
void setSteeringDegree(unsigned char d);
void SteeringPWMTimerInterruption();

#endif