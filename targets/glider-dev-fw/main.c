#include <ch.h>
#include <hal.h>
#include <chprintf.h>


void panic_handler(const char *reason)
{
    (void)reason;
    palSetPad(GPIOB, GPIOB_LED_ERR);
    while (1) {
    }
}



int main(void)
{
    halInit();
    chSysInit();

    while (true) {
        palSetPad(GPIOB, GPIOB_LED_HEARTBEAT);
        chThdSleepMilliseconds(500);
        palClearPad(GPIOB, GPIOB_LED_HEARTBEAT);
        chThdSleepMilliseconds(500);
    }
}
