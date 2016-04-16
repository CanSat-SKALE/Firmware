#include <ch.h>
#include "sensor-drivers/mpu60X0.h"
#include "thread_prio.h"

static THD_WORKING_AREA(mpu6050_readout_wa, 256);
static THD_FUNCTION(mpu6050_readout, arg)
{
    (void) arg;
    chRegSetThreadName("mpu6050_readout");

    mpu60X0_t dev;
    mpu60X0_init_using_i2c(&dev, &I2CD1, 0);

    if (!mpu60X0_ping(&dev)) {
        return; // error
    }

    int config = MPU60X0_LOW_PASS_FILTER_6 | MPU60X0_SAMPLE_RATE_DIV(0)
                 | MPU60X0_ACC_FULL_RANGE_16G | MPU60X0_GYRO_FULL_RANGE_1000DPS;
    mpu60X0_setup(&dev, config);

    while (true) {
        // mpu60X0_read(&dev, float *gyro, float *acc, float *temp);
        chThdSleepMilliseconds(1);
    }
}

void sensor_readout_start(void)
{
    chThdCreateStatic(mpu6050_readout_wa, sizeof(mpu6050_readout_wa),
                      THD_PRIO_SENSOR_MPU6050_READOUT, mpu6050_readout, NULL);
}
