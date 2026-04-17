#ifndef __KALMAN_H
#define __KALMAN_H 

//¿¨¶ûÂü½âËã·¨¿â

typedef struct {
float Q_angle;
float Q_bias;
float R_measure;

float angle;
float bias;
float rate;

float P[2][2];
} Kalman;

void Kalman_init(Kalman *kalman);
float Kalman_getAngle(Kalman *kalman, float newAngle, float newRate, float dt);
void Kalman_setAngle(Kalman *kalman, float angle);
float Kalman_getRate(Kalman *kalman);
void Kalman_setQangle(Kalman *kalman, float Q_angle);
void Kalman_setQbias(Kalman *kalman, float Q_bias);
void Kalman_setRmeasure(Kalman *kalman, float R_measure);
float Kalman_getQangle(Kalman *kalman);
float Kalman_getQbias(Kalman *kalman);
float Kalman_getRmeasure(Kalman *kalman);
void Angle_Calcu(void);
#define RAD_TO_DEG 57.2957795131

#pragma diag_suppress 177	
#pragma diag_suppress 550

#endif




