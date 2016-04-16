#include <ch.h>
#include "sensor-drivers/mpu60X0.h"
#include "sensor-drivers/ms5611.h"
#include "sensor-drivers/h3lis331dl.h"
#include "log.h"
#include "thread_prio.h"

static float mpu6050_rate[3];
static float mpu6050_acc[3];
static float mpu6050_temp;
static float ms5611_pressure;
static float ms5611_temperature;
static float h3lis331dl_acc[3];


static THD_WORKING_AREA(mpu6050_readout_wa, 256);
static THD_FUNCTION(mpu6050_readout, arg)
{
    (void) arg;
    chRegSetThreadName("mpu6050_readout");

    mpu60X0_t dev;
    mpu60X0_init_using_i2c(&dev, &I2CD1, 0);

    i2cAcquireBus(&I2CD1);
    if (!mpu60X0_ping(&dev)) {
        i2cReleaseBus(&I2CD1);
        log_error("MPU6050 communication failed");
        return;
    }

    int config = MPU60X0_LOW_PASS_FILTER_6 | MPU60X0_SAMPLE_RATE_DIV(0)
                 | MPU60X0_ACC_FULL_RANGE_16G | MPU60X0_GYRO_FULL_RANGE_1000DPS;
    mpu60X0_setup(&dev, config);
    i2cReleaseBus(&I2CD1);

    while (true) {
        float gyro[3];
        float acc[3];
        float temp;
        i2cAcquireBus(&I2CD1);
        mpu60X0_read(&dev, gyro, acc, &temp);
        i2cReleaseBus(&I2CD1);

        chSysLock();
        mpu6050_rate[0] = gyro[0];
        mpu6050_rate[1] = gyro[1];
        mpu6050_rate[2] = gyro[2];
        mpu6050_acc[0] = acc[0];
        mpu6050_acc[1] = acc[1];
        mpu6050_acc[2] = acc[2];
        mpu6050_temp = temp;
        chSysUnlock();

        // log_info("MPU6050: rate: %f %f %f, acc: %f %f %f, temp: %f",
        //          gyro[0], gyro[1], gyro[2], acc[0], acc[1], acc[2], temp);

        chThdSleepMilliseconds(1);
    }
}


static THD_WORKING_AREA(ms5611_readout_wa, 256);
static THD_FUNCTION(ms5611_readout, arg)
{
    (void) arg;
    chRegSetThreadName("ms5611_readout");

    ms5611_t barometer;

    i2cAcquireBus(&I2CD1);
    int init = ms5611_i2c_init(&barometer, &I2CD1, 0);
    i2cReleaseBus(&I2CD1);
    if (init != 0) {
        log_error("ms5611 init failed");
        return;
    }

    while (true) {
        uint32_t raw_t, raw_p, press;
        int32_t temp, t;
        i2cAcquireBus(&I2CD1);
        t = ms5611_adc_start(&barometer, MS5611_ADC_TEMP, MS5611_OSR_4096);
        i2cReleaseBus(&I2CD1);
        if (t > 0) {
            chThdSleepMilliseconds((t - 1)/1000 + 1);
            i2cAcquireBus(&I2CD1);
            ms5611_adc_read(&barometer, &raw_t);
            i2cReleaseBus(&I2CD1);
        }

        i2cAcquireBus(&I2CD1);
        t = ms5611_adc_start(&barometer, MS5611_ADC_PRESS, MS5611_OSR_4096);
        i2cReleaseBus(&I2CD1);

        if (t > 0) {
            chThdSleepMilliseconds((t - 1)/1000 + 1);
            i2cAcquireBus(&I2CD1);
            ms5611_adc_read(&barometer, &raw_p);
            i2cReleaseBus(&I2CD1);
        }
        press = ms5611_calc_press(&barometer, raw_p, raw_t, &temp);

        log_info("MS5611: pressure: %d, temperature: %f", press, (float)temp/100);

        chSysLock();
        ms5611_pressure = press;
        ms5611_temperature = (float)temp/100;
        chSysUnlock();
    }
}


static THD_WORKING_AREA(h3lis331dl_readout_wa, 256);
static THD_FUNCTION(h3lis331dl_readout, arg)
{
    (void) arg;
    chRegSetThreadName("h3lis331dl_readout");

    h3lis331dl_t high_g_acc;
    h3lis331dl_init_using_i2c(&high_g_acc, &I2CD1, H3LIS331DL_ADDR_SA0_HIGH);

    i2cAcquireBus(&I2CD1);
    bool ping = h3lis331dl_ping(&high_g_acc);
    i2cReleaseBus(&I2CD1);
    if (!ping) {
        log_error("h3lis331dl init failed");
        return;
    }

    i2cAcquireBus(&I2CD1);
    h3lis331dl_setup(&high_g_acc, H3LIS331DL_CONFIG_ODR_400HZ | H3LIS331DL_CONFIG_FS_400G);
    i2cReleaseBus(&I2CD1);

    while (true) {
        static float acc[3];
        i2cAcquireBus(&I2CD1);
        h3lis331dl_read(&high_g_acc, acc);
        i2cReleaseBus(&I2CD1);

        chSysLock();
        h3lis331dl_acc[0] = acc[0];
        h3lis331dl_acc[1] = acc[1];
        h3lis331dl_acc[2] = acc[2];
        chSysUnlock();
    }
}

void sensor_readout_start(void)
{
    chThdCreateStatic(mpu6050_readout_wa, sizeof(mpu6050_readout_wa),
                      THD_PRIO_SENSOR_MPU6050_READOUT, mpu6050_readout, NULL);
    chThdCreateStatic(ms5611_readout_wa, sizeof(ms5611_readout_wa),
                      THD_PRIO_SENSOR_MS5611_READOUT, ms5611_readout, NULL);
    chThdCreateStatic(h3lis331dl_readout_wa, sizeof(h3lis331dl_readout_wa),
                      THD_PRIO_SENSOR_H3LIS331DL_READOUT, h3lis331dl_readout, NULL);
}
