#include <ch.h>
#include <hal.h>
#include <chprintf.h>


void panic_handler(const char *reason)
{
    (void)reason;
    while (1) {

    }
}



int main(void)
{
    halInit();
    chSysInit();

    while (true) {
        chThdSleepMilliseconds(500);
    }
}
