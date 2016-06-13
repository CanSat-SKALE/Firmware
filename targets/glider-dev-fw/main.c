#include <ch.h>
#include <hal.h>
#include "log.h"
#include "chprintf.h"
#include "blocking_uart_driver.h"
#include "comm.h"
#include "air_data.h"
#include "deploy.h"

#include "sensor_readout.h"


void panic_handler(const char *reason)
{
    (void)reason;
    led_heartbeat(true);
    led_error(true);
    led_sdcard(true);

    static BlockingUARTDriver blocking_uart_stream;

    blocking_uart_init(&blocking_uart_stream,
                       USART6, SERIAL_DEFAULT_BITRATE);

    BaseSequentialStream* uart = (BaseSequentialStream*)&blocking_uart_stream;

    while (1) {
        chprintf(uart, "\033[1;31m"); // red color
        chprintf(uart, "\n\nPANIC: %s", reason);

        if (ch.rlist.r_current != NULL) {
            chprintf(uart, "\ncurrent thread: ");
            if (ch.rlist.r_current->p_name != NULL) {
                chprintf(uart, "%s\n", ch.rlist.r_current->p_name);
            } else {
                chprintf(uart, "0x%p\n", ch.rlist.r_current);
            }
        }

        unsigned int i = 100000000;
        while(i--) {
            __asm__ volatile ("nop");
        }
    }
}


int main(void)
{
    halInit();
    chSysInit();

    sdStart(&SD1, NULL);
    sdStart(&SD2, NULL);
    sdStart(&SD3, NULL);
    sdStart(&SD6, NULL);

    log_info("=== boot ===");

    static const I2CConfig i2c_cfg = {
        .op_mode = OPMODE_I2C,
        .clock_speed = 400000,
        .duty_cycle = FAST_DUTY_CYCLE_2
    };
    i2cStart(&I2CD1, &i2c_cfg);


    pwr_gps(true);
    pwr_sdcard(true);
    pwr_5V(true);

    sensor_readout_start_mpu6050();
    sensor_readout_start_ms5611();
    sensor_readout_start_h3lis331dl();

    // comm_start((BaseSequentialStream*)&SD2);
    
    chThdSleepMilliseconds(1000);

    static deployment_trigger_t t;
    deployment_init(&t);
    while (true) {
        float pressure, temperature;
        sensor_get_ms5611(&pressure, &temperature);
        float alt_above_sea = air_data_compute_altitude(pressure);
        log_info("altitude above sea: %f, zero %f set %d, ready %d", alt_above_sea, t.altitude_reference, t.altitude_reference_set, (int)t.ready);
        if (deployment_trigger_should_activate_update_10Hz(&t, alt_above_sea)) {
            log_info("deploy");
            // deploy();

            palSetPad(GPIOA, GPIOA_SERVO_PWM);
            chThdSleepSeconds(120);
            palClearPad(GPIOA, GPIOA_SERVO_PWM);
            while (1);
        }

        chThdSleepMilliseconds(100);
    }

    // IR_pwm(true);
    while (true) {
        led_heartbeat(true);
        // IR_pwm(true);
        chThdSleepMilliseconds(3000);
        led_heartbeat(false);
        // IR_pwm(false);
        chThdSleepMilliseconds(3000);
    }
}
