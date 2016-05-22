#include <ch.h>
#include <hal.h>

#include "buzzer.h"

static PWMConfig pwmcfg = {
  TIMER3CLK,       /* 1Mhz PWM clock frequency*/
  TIMER3PWMPERIOD,         /* PWM period of 250 ticks ~  */
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


void buzzerStart(){
	pwmStart(&PWMD3, &pwmcfg);
}


void buzzerBeep(bool enable)
{
    if (enable) {
    	pwmEnableChannel(&PWMD3, TIMER3BUZZERCH, 150);   
	} else {
		pwmEnableChannel(&PWMD3, TIMER3BUZZERCH, 0);
    }
}