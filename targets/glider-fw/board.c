
#include "hal.h"

#if HAL_USE_PAL
/**
 * @brief     PAL setup.
 * @details Digital I/O ports static configuration as defined in @p board.h.
 *                    This variable is used by the HAL when initializing the PAL driver.
 */
const PALConfig pal_default_config =
{
    {VAL_GPIOA_MODER, VAL_GPIOA_OTYPER, VAL_GPIOA_OSPEEDR, VAL_GPIOA_PUPDR,
     VAL_GPIOA_ODR, VAL_GPIOA_AFRL, VAL_GPIOA_AFRH},
    {VAL_GPIOB_MODER, VAL_GPIOB_OTYPER, VAL_GPIOB_OSPEEDR, VAL_GPIOB_PUPDR,
     VAL_GPIOB_ODR, VAL_GPIOB_AFRL, VAL_GPIOB_AFRH},
    {VAL_GPIOC_MODER, VAL_GPIOC_OTYPER, VAL_GPIOC_OSPEEDR, VAL_GPIOC_PUPDR,
     VAL_GPIOC_ODR, VAL_GPIOC_AFRL, VAL_GPIOC_AFRH},
    {VAL_GPIOD_MODER, VAL_GPIOD_OTYPER, VAL_GPIOD_OSPEEDR, VAL_GPIOD_PUPDR,
     VAL_GPIOD_ODR, VAL_GPIOD_AFRL, VAL_GPIOD_AFRH},
    {VAL_GPIOE_MODER, VAL_GPIOE_OTYPER, VAL_GPIOE_OSPEEDR, VAL_GPIOE_PUPDR,
     VAL_GPIOE_ODR, VAL_GPIOE_AFRL, VAL_GPIOE_AFRH},
    {VAL_GPIOF_MODER, VAL_GPIOF_OTYPER, VAL_GPIOF_OSPEEDR, VAL_GPIOF_PUPDR,
     VAL_GPIOF_ODR, VAL_GPIOF_AFRL, VAL_GPIOF_AFRH},
    {VAL_GPIOG_MODER, VAL_GPIOG_OTYPER, VAL_GPIOG_OSPEEDR, VAL_GPIOG_PUPDR,
     VAL_GPIOG_ODR, VAL_GPIOG_AFRL, VAL_GPIOG_AFRH},
    {VAL_GPIOH_MODER, VAL_GPIOH_OTYPER, VAL_GPIOH_OSPEEDR, VAL_GPIOH_PUPDR,
     VAL_GPIOH_ODR, VAL_GPIOH_AFRL, VAL_GPIOH_AFRH},
    {VAL_GPIOI_MODER, VAL_GPIOI_OTYPER, VAL_GPIOI_OSPEEDR, VAL_GPIOI_PUPDR,
     VAL_GPIOI_ODR, VAL_GPIOI_AFRL, VAL_GPIOI_AFRH}
};
#endif


void __early_init(void) {
    stm32_clock_init();
}


#if HAL_USE_SDC
bool sdc_lld_is_card_inserted(SDCDriver *sdcp) {

    (void)sdcp;
    return true;
}

bool sdc_lld_is_write_protected(SDCDriver *sdcp) {

    (void)sdcp;
    return false;
}
#endif


void led_sdcard(bool en)
{
    if (en) {
        palSetPad(GPIOB, GPIOB_LED_SDCARD);
    } else {
        palClearPad(GPIOB, GPIOB_LED_SDCARD);
    }
}


void led_heartbeat(bool en)
{
    if (en) {
        palSetPad(GPIOB, GPIOB_LED_HEARTBEAT);
    } else {
        palClearPad(GPIOB, GPIOB_LED_HEARTBEAT);
    }
}

void led_error(bool en)
{
    if (en) {
        palSetPad(GPIOB, GPIOB_LED_ERR);
    } else {
        palClearPad(GPIOB, GPIOB_LED_ERR);
    }
}

void pwr_sensors(bool en)
{
    if (en) {
        palClearPad(GPIOA, GPIOA_SENSOR_SHDN);
    } else {
        palSetPad(GPIOA, GPIOA_SENSOR_SHDN);
    }
}
void pwr_sdcard(bool en)
{
    if (en) {
        palClearPad(GPIOA, GPIOA_SDCARD_SHDN);
    } else {
        palSetPad(GPIOA, GPIOA_SDCARD_SHDN);
    }
}

void pwr_gps(bool en)
{
    if (en) {
        palClearPad(GPIOC, GPIOC_GPS_SHDN);
    } else {
        palSetPad(GPIOC, GPIOC_GPS_SHDN);
    }
}

void pwr_5V(bool en)
{
    if (en) {
        palSetPad(GPIOB, GPIOB_SHDN_5V);
    } else {
        palClearPad(GPIOB, GPIOB_SHDN_5V);
    }
}


#define IR_PWM_CH 3
#define IR_PWM_FREQ 16000000
#define IR_PWM_PERIOD 421 // 16000000/38000
void IR_pwm(bool en)
{
    if (en) {
        pwmEnableChannel(&PWMD3, IR_PWM_CH, IR_PWM_PERIOD/2);
    } else {
        pwmEnableChannel(&PWMD3, IR_PWM_CH, 0);
    }
}


void board_init(void) {
    // TIM3_CH3
    static PWMConfig pwmcfg = {
        IR_PWM_FREQ,
        IR_PWM_PERIOD,
        NULL,         /* No callback */
        {
            {PWM_OUTPUT_DISABLED, NULL},
            {PWM_OUTPUT_DISABLED, NULL},
            {PWM_OUTPUT_ACTIVE_HIGH, NULL},
            {PWM_OUTPUT_DISABLED, NULL}
        },
        0,
        0
    };

    pwmStart(&PWMD3, &pwmcfg);
}

