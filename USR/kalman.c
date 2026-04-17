#include "kalman.h"
#include "MPU6050.h"
#include "math.h"
#include <stdlib.h>

double kalAngleX, kalAngleY; // Calculated angle using a Kalman filter

void Kalman_init(Kalman *kalman) {
kalman->Q_angle = 0.001f;
kalman->Q_bias = 0.003f;
kalman->R_measure = 0.03f;

kalman->angle = 0.0f;
kalman->bias = 0.0f;

kalman->P[0][0] = 0.0f;
kalman->P[0][1] = 0.0f;
kalman->P[1][0] = 0.0f;
kalman->P[1][1] = 0.0f;
}

float Kalman_getAngle(Kalman *kalman, float newAngle, float newRate, float dt) {
float S, y, K0, K1, P00_temp, P01_temp;

// Update xhat - Project the state ahead
kalman->rate = newRate - kalman->bias;
kalman->angle += dt * kalman->rate;

// Update estimation error covariance - Project the error covariance ahead
kalman->P[0][0] += dt * (dt * kalman->P[1][1] - kalman->P[0][1] - kalman->P[1][0] + kalman->Q_angle);
kalman->P[0][1] -= dt * kalman->P[1][1];
kalman->P[1][0] -= dt * kalman->P[1][1];
kalman->P[1][1] += kalman->Q_bias * dt;

// Calculate Kalman gain - Compute the Kalman gain
S = kalman->P[0][0] + kalman->R_measure; // Estimate error
K0 = kalman->P[0][0] / S;
K1 = kalman->P[1][0] / S;

// Calculate angle and bias - Update estimate with measurement zk (newAngle)
y = newAngle - kalman->angle; // Angle difference
kalman->angle += K0 * y;
kalman->bias += K1 * y;

// Calculate estimation error covariance - Update the error covariance
P00_temp = kalman->P[0][0];
P01_temp = kalman->P[0][1];

kalman->P[0][0] -= K0 * P00_temp;
kalman->P[0][1] -= K0 * P01_temp;
kalman->P[1][0] -= K1 * P00_temp;
kalman->P[1][1] -= K1 * P01_temp;

return kalman->angle;
}

void Kalman_setAngle(Kalman *kalman, float angle) {
kalman->angle = angle;
}

float Kalman_getRate(Kalman *kalman) {
return kalman->rate;
}

void Kalman_setQangle(Kalman *kalman, float Q_angle) {
kalman->Q_angle = Q_angle;
}

void Kalman_setQbias(Kalman *kalman, float Q_bias) {
kalman->Q_bias = Q_bias;
}

void Kalman_setRmeasure(Kalman *kalman, float R_measure) {
kalman->R_measure = R_measure;
}

float Kalman_getQangle(Kalman *kalman) {
return kalman->Q_angle;
}

float Kalman_getQbias(Kalman *kalman) {
return kalman->Q_bias;
}

float Kalman_getRmeasure(Kalman *kalman) {
return kalman->R_measure;
}
Kalman kalmanX; // Create the Kalman instances
Kalman kalmanY;
	
double accX, accY, accZ;
double gyroX, gyroY, gyroZ;
//int16_t tempRaw;
double gyroXangle, gyroYangle; // Angle calculate using the gyro only
double compAngleX, compAngleY; // Calculated angle using a complementary filter
	int16_t AX, AY, AZ, GX, GY, GZ;			//定义用于存放各个数据的变量
	double dt = 0.005;

void Angle_Calcu()
{
	Kalman_init(&kalmanX);
	Kalman_init(&kalmanY);
	MPU6050_GetData(&AX, &AY, &AZ, &GX, &GY, &GZ);		//获取MPU6050的数据
	accX = (int16_t)AX;
	accY = (int16_t)AY;
	accZ = (int16_t)AZ;
	gyroX = (int16_t)GX;
	gyroY = (int16_t)GY;
	gyroZ = (int16_t)GZ;

#ifdef RESTRICT_PITCH // Eq. 25 and 26
  double roll  = atan2(accY, accZ) * RAD_TO_DEG;
  double pitch = atan(-accX / sqrt(accY * accY + accZ * accZ)) * RAD_TO_DEG;
#else // Eq. 28 and 29
  double roll  = atan(accY / sqrt(accX * accX + accZ * accZ)) * RAD_TO_DEG;
  double pitch = atan2(-accX, accZ) * RAD_TO_DEG;
#endif
	Kalman_setAngle(&kalmanX, roll); // Set starting angle
	Kalman_setAngle(&kalmanY, pitch); // Set starting angle
  gyroXangle = roll;
  gyroYangle = pitch;
  compAngleX = roll;
  compAngleY = pitch;
	double gyroXrate = gyroX / 131.0; // Convert to deg/s
  double gyroYrate = gyroY / 131.0; // Convert to deg/s
#ifdef RESTRICT_PITCH
  // This fixes the transition problem when the accelerometer angle jumps between -180 and 180 degrees
  if ((roll < -90 && kalAngleX > 90) || (roll > 90 && kalAngleX < -90)) {
    kalmanX.setAngle(roll);
    compAngleX = roll;
    kalAngleX = roll;
    gyroXangle = roll;
  } else
    kalAngleX = kalmanX.getAngle(roll, gyroXrate, dt); // Calculate the angle using a Kalman filter

  if (abs(kalAngleX) > 90)
    gyroYrate = -gyroYrate; // Invert rate, so it fits the restriced accelerometer reading
  kalAngleY = kalmanY.getAngle(pitch, gyroYrate, dt);
#else
  // This fixes the transition problem when the accelerometer angle jumps between -180 and 180 degrees
  if ((pitch < -90 && kalAngleY > 90) || (pitch > 90 && kalAngleY < -90)) {
    Kalman_setAngle(&kalmanY, pitch);
    compAngleY = pitch;
    kalAngleY = pitch;
    gyroYangle = pitch;
  } else
    kalAngleY = Kalman_getAngle(&kalmanY, pitch, gyroYrate, dt); // Calculate the angle using a Kalman filter

  if (abs(kalAngleY) > 90)//Abs有警告	Fabs 会卡死 
    gyroXrate = -gyroXrate; // Invert rate, so it fits the restriced accelerometer reading
  kalAngleX = Kalman_getAngle(&kalmanX, roll, gyroXrate, dt); // Calculate the angle using a Kalman filter
#endif
gyroXangle += gyroXrate * dt; // Calculate gyro angle without any filter
  gyroYangle += gyroYrate * dt;
  //gyroXangle += kalmanX.getRate() * dt; // Calculate gyro angle using the unbiased rate
  //gyroYangle += kalmanY.getRate() * dt;

  compAngleX = 0.93 * (compAngleX + gyroXrate * dt) + 0.07 * roll; // Calculate the angle using a Complimentary filter
  compAngleY = 0.93 * (compAngleY + gyroYrate * dt) + 0.07 * pitch;

  // Reset the gyro angle when it has drifted too much
  if (gyroXangle < -180 || gyroXangle > 180)
    gyroXangle = kalAngleX;
  if (gyroYangle < -180 || gyroYangle > 180)
    gyroYangle = kalAngleY;

}
