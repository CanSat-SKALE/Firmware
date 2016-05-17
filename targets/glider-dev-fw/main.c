#include <ch.h>
#include <hal.h>
#include "log.h"
#include "chprintf.h"
#include <serial_lld.h>
#include "blocking_uart_driver.h"
#include "comm.h"

#include "sensor_readout.h"

BaseSequentialStream* chp = (BaseSequentialStream*) &SD2;

SerialConfig uartCfg = {115200, 0, USART_CR2_STOP1_BITS | USART_CR2_LINEN, 0};

static PWMConfig pwmcfg = {
  100000,       /* 200Khz PWM clock frequency*/
  2000,         /* PWM period of 2000 ticks ~ 500 Hz */
  NULL,         /* No callback */
  {             /* channel 3 and 4 enabled */
    {PWM_OUTPUT_DISABLED, NULL},
    {PWM_OUTPUT_DISABLED, NULL},
    {PWM_OUTPUT_ACTIVE_HIGH, NULL},
    {PWM_OUTPUT_ACTIVE_HIGH, NULL}
  },
0,
0
};




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

static THD_WORKING_AREA(waBuzzer, 128);
static THD_FUNCTION(Buzzer, arg) {
    
    (void) arg;

    chRegSetThreadName("Buzzer");


    pwmEnableChannel(&PWMD3, 3, 1000);

    while(true)
    {
        chThdSleepMilliseconds(100);
    }

}

static THD_WORKING_AREA(waIRLED, 128);
static THD_FUNCTION(IRLED, arg) {
    
    (void) arg;

    chRegSetThreadName("IR Led");

    pwmEnableChannel(&PWMD3, 2, 1000);

    while(true)
    {
        chThdSleepMilliseconds(100);
    }

}



static THD_WORKING_AREA(waHeartBeat, 256);
static THD_FUNCTION(HeartBeat, arg) {

  (void)arg;
  chRegSetThreadName("HeartBeat");

  while (true) {
    palTogglePad(GPIOB, GPIOB_LED_HEARTBEAT);     
    chThdSleepMilliseconds(100);
  }
}



int main(void)
{
    halInit();
    chSysInit();

    sdStart(&SD1, NULL);
    sdStart(&SD2, &uartCfg);
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

    sensor_readout_start();
    comm_start();

    pwmStart(&PWMD3, &pwmcfg);
    palSetPadMode(GPIOB, GPIOB_BUZZER_PWM, PAL_MODE_ALTERNATE(2));
    palSetPadMode(GPIOB, GPIOB_IR_LED_PWM, PAL_MODE_ALTERNATE(2));

    chThdCreateStatic(waHeartBeat, sizeof(waHeartBeat), NORMALPRIO, HeartBeat, NULL);
    chThdCreateStatic(waBuzzer, sizeof(waBuzzer), NORMALPRIO, Buzzer, NULL);
    chThdCreateStatic(waIRLED, sizeof(waIRLED), NORMALPRIO, IRLED, NULL);


     
    

    while (true) {
        led_error(true);
        chThdSleepMilliseconds(500);
        led_error(false);
        chThdSleepMilliseconds(500);
    }
}
