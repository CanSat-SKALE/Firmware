#include <ch.h>
#include <hal.h>
#include "log.h"
#include "chprintf.h"
#include "blocking_uart_driver.h"
#include "sensor_readout.h"
#include "thread_prio.h"
#include "air_data.h"
#include "deploy.h"


void panic_handler(const char *reason)
{
    (void)reason;
    led_heartbeat(true);
    led_error(true);

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


static THD_WORKING_AREA(deploy_thd_wa, 256);
static THD_FUNCTION(deploy_thd, arg)
{
    (void) arg;
    static deployment_trigger_t t;

    while (true) {
        float pressure, temperature;
        sensor_get_ms5611(&pressure, &temperature);
        float alt_above_sea = air_data_compute_altitude(pressure);
        log_info("altitude above sea: %f", alt_above_sea);
        if (deployment_trigger_should_activate_update_10Hz(&t, alt_above_sea)) {
            log_info("deploy");
            deploy();
        }

        chThdSleepMilliseconds(100);
    }
}


int main(void)
{
    halInit();
    chSysInit();

    sdStart(&SD6, NULL);

    log_info("=== boot ===");

    chThdSleepMilliseconds(1000);
    pwr_sensors(true);

    static const I2CConfig i2c_cfg = {
        .op_mode = OPMODE_I2C,
        .clock_speed = 400000,
        .duty_cycle = FAST_DUTY_CYCLE_2
    };
    i2cStart(&I2CD1, &i2c_cfg);

    chThdSleepMilliseconds(1000);

    sensor_readout_start_ms5611();

    chThdSleepMilliseconds(500);

    chThdCreateStatic(deploy_thd_wa, sizeof(deploy_thd_wa),
                      THD_PRIO_DEPLOY, deploy_thd, NULL);

    while (true) {
        float pressure, temp;
        sensor_get_ms5611(&pressure, &temp);
        log_info("pressure: %f\n", pressure);

        led_heartbeat(true);
        chThdSleepMilliseconds(500);
        led_heartbeat(false);
        chThdSleepMilliseconds(500);
    }
}
