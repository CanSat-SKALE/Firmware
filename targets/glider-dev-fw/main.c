#include <ch.h>
#include <hal.h>
#include "log.h"
#include "chprintf.h"
#include <serial_lld.h>
#include "blocking_uart_driver.h"
#include "comm.h"

#include "sensor_readout.h"
#include "buzzer.h"

#define ADC_GRP1_NUM_CHANNELS   1
#define ADC_GRP1_BUF_DEPTH      8
//static adcsample_t samples1[ADC_GRP1_NUM_CHANNELS * ADC_GRP1_BUF_DEPTH];

size_t nx = 0, ny = 0;
// static void adccallback(ADCDriver *adcp, adcsample_t *buffer, size_t n) {

//   (void)adcp;
//   (void)n;

//   static BlockingUARTDriver blocking_uart_stream;

//    blocking_uart_init(&blocking_uart_stream,
//                        USART6, SERIAL_DEFAULT_BITRATE);

//   //BaseSequentialStream* uart = (BaseSequentialStream*)&blocking_uart_stream;
  
//   //chprintf(uart, "ADC[0] = %d, ADC[1] = %d \n", buffer[0], buffer[1]);

//   //chprintf(&samples1);
// }
// static void adcerrorcallback(ADCDriver *adcp, adcerror_t err) {

//   (void)adcp;
//   (void)err;
// }


// static const ADCConversionGroup adcgrpcfg1 = {
//   TRUE,   // continuous conversion
//   ADC_GRP1_NUM_CHANNELS,
//   adccallback,
//   adcerrorcallback,
//   0,                        /* CR1 */
//   ADC_CR2_SWSTART,          /* CR2 */
//   ADC_SMPR1_SMP_AN10(ADC_SAMPLE_3),   // 3 cycles sampling time
//   0,                        /* SMPR2 */
//   ADC_SQR1_NUM_CH(ADC_GRP1_NUM_CHANNELS),
//   0,                        /* SQR2 */
//   ADC_SQR3_SQ1_N(ADC_CHANNEL_IN10)
// };



void panic_handler(const char *reason)
{
    // led_heartbeat(true);
    // led_error(true);
    // led_sdcard(true);

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

        /* Toggle ERROR LED in case of panic */
        palTogglePad(GPIOB, GPIOB_LED_ERR);

        unsigned int i = 10000000;
        while(i--) {
            __asm__ volatile ("nop");
        }
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



static void rxchar(UARTDriver *uartp, uint16_t c) {

  (void)uartp;
  (void)c;

   // Flashing the LED each time a character is received.
  palTogglePad(GPIOD, GPIOB_LED_SDCARD);
}


 /* UART driver configuration structure. */

static UARTConfig uart_cfg_1 = {NULL, NULL, NULL, rxchar, NULL, 115200, 0,
                                0, 0};



int main(void)
{
    halInit();
    chSysInit();

    sdStart(&SD1, NULL);
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
    //buzzerStart();
    //pwmStart(&PWMD3, &pwmcfg);

    //adcStart(&ADCD1, NULL);
    //adcSTM32EnableTSVREFE();
    //adcStartConversion(&ADCD1, &adcgrpcfg1, samples1, ADC_GRP1_BUF_DEPTH);

    palSetPadMode(GPIOB, GPIOB_BUZZER_PWM, PAL_MODE_ALTERNATE(2));
    palSetPadMode(GPIOB, GPIOB_IR_LED_PWM, PAL_MODE_ALTERNATE(2));

    chThdCreateStatic(waHeartBeat, sizeof(waHeartBeat), NORMALPRIO, HeartBeat, NULL);
    //chThdCreateStatic(waBuzzer, sizeof(waBuzzer), NORMALPRIO, Buzzer, NULL);
    //chThdCreateStatic(waIRLED, sizeof(waIRLED), NORMALPRIO, IRLED, NULL);

    uartStart(&UARTD2, &uart_cfg_1);
    palSetPadMode(GPIOA, 2, PAL_MODE_ALTERNATE(7));
    palSetPadMode(GPIOA, 3, PAL_MODE_ALTERNATE(7));
     
    

    while (true) {
        buzzerBeep(true);
        chThdSleepMilliseconds(500);
        buzzerBeep(false);
        chThdSleepMilliseconds(500);
    }
}
