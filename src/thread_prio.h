#ifndef THREAD_PRIO_H
#define THREAD_PRIO_H

// use priorities in the range of 2 to 127, higher number means higher priority

#define THD_PRIO_SENSOR_MPU6050_READOUT                 11
#define THD_PRIO_SENSOR_MS5611_READOUT                  10
#define THD_PRIO_SENSOR_H3LIS331DL_READOUT              11
#define THD_PRIO_COMM                                   20
#define THD_PRIO_SHELL                                  100
#define THD_PRIO_DEPLOY                                 21

#endif /* THREAD_PRIO_H */
