#include <ch.h>
#include <hal.h>
#include <chprintf.h>


void panic_handler(const char *reason)
{
    (void)reason;
    led_heartbeat(true);
    led_error(true);
    led_sdcard(true);
    while (1) {
    }
}



int main(void)
{
    halInit();
    chSysInit();

    pwr_gps(true);
    pwr_sdcard(true);
    pwr_5V(true);

    while (true) {
        led_heartbeat(true);
        chThdSleepMilliseconds(500);
        led_heartbeat(false);
        chThdSleepMilliseconds(500);
    }
}
