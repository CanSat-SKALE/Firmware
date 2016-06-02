#ifndef SENSOR_READOUT_H
#define SENSOR_READOUT_H

#ifdef __cplusplus
extern "C" {
#endif

void sensor_readout_start_mpu6050(void);
void sensor_readout_start_ms5611(void);
void sensor_readout_start_h3lis331dl(void);
void sensor_get_mpu6050(float *rate, float *acc, float *temp);
void sensor_get_ms5611(float *pressure, float *temp);
void sensor_get_h3lis331dl(float *acc);

#ifdef __cplusplus
}
#endif

#endif /* SENSOR_READOUT_H */