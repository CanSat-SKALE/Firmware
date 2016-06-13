#ifndef _BOARD_H_
#define _BOARD_H_

#define BOARD_NAME                  "SKALE - Glider"


#if !defined(STM32_LSECLK)
#define STM32_LSECLK                0
#endif

#define STM32_HSECLK                16000000

#define STM32_VDD                   330

#define STM32F405xx



/*
 * IO pins assignments.
 */
#define GPIOA_XBEE_CTS              0 // UART2
#define GPIOA_XBEE_RTS              1 // UART2
#define GPIOA_XBEE_TX               2 // UART2
#define GPIOA_XBEE_RX               3 // UART2
#define GPIOA_NC_4                  4
#define GPIOA_NC_5                  5
#define GPIOA_SHDN_5V               6 // active low
#define GPIOA_SERVO_PWM             7 // timer14 ch1
#define GPIOA_NC_8                  8
#define GPIOA_GPS_TX                9 // UART1
#define GPIOA_GPS_RX                10 // UART1
#define GPIOA_NC_11                 11
#define GPIOA_NC_12                 12
#define GPIOA_SWDIO                 13
#define GPIOA_SWDCLK                14
#define GPIOA_NC_15                 15

#define GPIOB_IR_LED_PWM            0 // TIM3_CH3
#define GPIOB_BUZZER_PWM            1 // TIM1_CH3N
#define GPIOB_NC_2                  2
#define GPIOB_LED_HEARTBEAT         3
#define GPIOB_LED_ERR               4
#define GPIOB_LED_SDCARD            5
#define GPIOB_I2C1_SCL              6
#define GPIOB_I2C1_SDA              7
#define GPIOB_NC_8                  8
#define GPIOB_NC_9                  9
#define GPIOB_CAMERA_TX             10 // UART3
#define GPIOB_CAMERA_RX             11 // UART3
#define GPIOB_INT_MPU               12
#define GPIOB_INT_H3LIS             13
#define GPIOB_INT_HMC               14
#define GPIOB_XBEE_SLEEP_RQ         15

#define GPIOC_ADC_PITOT             0 // (10k, 15k) -> 0.6
#define GPIOC_ADC_VBAT              1 // (10k, NC) -> 1
#define GPIOC_ADC_5V                2 // (10k, 15k) -> 0.6
#define GPIOC_NC_3                  3
#define GPIOC_GPS_SHDN              4
#define GPIOC_SDCARD_SHDN           5
#define GPIOC_DEBUG_TX              6 // UART6
#define GPIOC_DEBUT_RX              7 // UART6
#define GPIOC_SDIO_D0               8
#define GPIOC_SDIO_D1               9
#define GPIOC_SDIO_D2               10
#define GPIOC_SDIO_D3               11
#define GPIOC_SDIO_CK               12
#define GPIOC_NC_13                 13
#define GPIOC_NC_14                 14
#define GPIOC_NC_15                 15

#define GPIOD_SDIO_CMD              2

#define GPIOH_OSC_IN                0
#define GPIOH_OSC_OUT               1

/*
 * I/O ports initial setup, this configuration is established soon after reset
 * in the initialization code.
 * Please refer to the STM32 Reference Manual for details.
 */
#define PIN_MODE_INPUT(n)           (0U << ((n) * 2))
#define PIN_MODE_OUTPUT(n)          (1U << ((n) * 2))
#define PIN_MODE_ALTERNATE(n)       (2U << ((n) * 2))
#define PIN_MODE_ANALOG(n)          (3U << ((n) * 2))
#define PIN_ODR_LOW(n)              (0U << (n))
#define PIN_ODR_HIGH(n)             (1U << (n))
#define PIN_OTYPE_PUSHPULL(n)       (0U << (n))
#define PIN_OTYPE_OPENDRAIN(n)      (1U << (n))
#define PIN_OSPEED_2M(n)            (0U << ((n) * 2))
#define PIN_OSPEED_25M(n)           (1U << ((n) * 2))
#define PIN_OSPEED_50M(n)           (2U << ((n) * 2))
#define PIN_OSPEED_100M(n)          (3U << ((n) * 2))
#define PIN_PUPDR_FLOATING(n)       (0U << ((n) * 2))
#define PIN_PUPDR_PULLUP(n)         (1U << ((n) * 2))
#define PIN_PUPDR_PULLDOWN(n)       (2U << ((n) * 2))
#define PIN_AFIO_AF(n, v)           ((v##U) << ((n % 8) * 4))


// GPIO A

#define VAL_GPIOA_MODER     ( PIN_MODE_INPUT(     GPIOA_XBEE_CTS        )       \
                            | PIN_MODE_INPUT(     GPIOA_XBEE_RTS        )       \
                            | PIN_MODE_ALTERNATE( GPIOA_XBEE_TX         )       \
                            | PIN_MODE_ALTERNATE( GPIOA_XBEE_RX         )       \
                            | PIN_MODE_INPUT(     GPIOA_NC_4            )       \
                            | PIN_MODE_INPUT(     GPIOA_NC_5            )       \
                            | PIN_MODE_OUTPUT(    GPIOA_SHDN_5V         )       \
                            | PIN_MODE_OUTPUT( GPIOA_SERVO_PWM       )       \
                            | PIN_MODE_INPUT(     GPIOA_NC_8            )       \
                            | PIN_MODE_ALTERNATE( GPIOA_GPS_TX          )       \
                            | PIN_MODE_ALTERNATE( GPIOA_GPS_RX          )       \
                            | PIN_MODE_INPUT(     GPIOA_NC_11           )       \
                            | PIN_MODE_INPUT(     GPIOA_NC_12           )       \
                            | PIN_MODE_ALTERNATE( GPIOA_SWDIO           )       \
                            | PIN_MODE_ALTERNATE( GPIOA_SWDCLK          )       \
                            | PIN_MODE_INPUT(     GPIOA_NC_15           ) )

#define VAL_GPIOA_OTYPER    ( PIN_OTYPE_PUSHPULL( GPIOA_XBEE_CTS        )   \
                            | PIN_OTYPE_PUSHPULL( GPIOA_XBEE_RTS        )   \
                            | PIN_OTYPE_PUSHPULL( GPIOA_XBEE_TX         )   \
                            | PIN_OTYPE_PUSHPULL( GPIOA_XBEE_RX         )   \
                            | PIN_OTYPE_PUSHPULL( GPIOA_NC_4            )   \
                            | PIN_OTYPE_PUSHPULL( GPIOA_NC_5            )   \
                            | PIN_OTYPE_PUSHPULL( GPIOA_SHDN_5V         )   \
                            | PIN_OTYPE_PUSHPULL( GPIOA_SERVO_PWM       )   \
                            | PIN_OTYPE_PUSHPULL( GPIOA_NC_8            )   \
                            | PIN_OTYPE_PUSHPULL( GPIOA_GPS_TX          )   \
                            | PIN_OTYPE_PUSHPULL( GPIOA_GPS_RX          )   \
                            | PIN_OTYPE_PUSHPULL( GPIOA_NC_11           )   \
                            | PIN_OTYPE_PUSHPULL( GPIOA_NC_12           )   \
                            | PIN_OTYPE_PUSHPULL( GPIOA_SWDIO           )   \
                            | PIN_OTYPE_PUSHPULL( GPIOA_SWDCLK          )   \
                            | PIN_OTYPE_PUSHPULL( GPIOA_NC_15           ) )

#define VAL_GPIOA_OSPEEDR   ( PIN_OSPEED_100M( GPIOA_XBEE_CTS           )      \
                            | PIN_OSPEED_100M( GPIOA_XBEE_RTS           )      \
                            | PIN_OSPEED_100M( GPIOA_XBEE_TX            )      \
                            | PIN_OSPEED_100M( GPIOA_XBEE_RX            )      \
                            | PIN_OSPEED_100M( GPIOA_NC_4               )      \
                            | PIN_OSPEED_100M( GPIOA_NC_5               )      \
                            | PIN_OSPEED_100M( GPIOA_SHDN_5V            )      \
                            | PIN_OSPEED_100M( GPIOA_SERVO_PWM          )      \
                            | PIN_OSPEED_100M( GPIOA_NC_8               )      \
                            | PIN_OSPEED_100M( GPIOA_GPS_TX             )      \
                            | PIN_OSPEED_100M( GPIOA_GPS_RX             )      \
                            | PIN_OSPEED_100M( GPIOA_NC_11              )      \
                            | PIN_OSPEED_100M( GPIOA_NC_12              )      \
                            | PIN_OSPEED_100M( GPIOA_SWDIO              )      \
                            | PIN_OSPEED_100M( GPIOA_SWDCLK             )      \
                            | PIN_OSPEED_100M( GPIOA_NC_15              ) )

#define VAL_GPIOA_PUPDR     ( PIN_PUPDR_PULLUP(   GPIOA_XBEE_CTS        )   \
                            | PIN_PUPDR_FLOATING( GPIOA_XBEE_RTS        )   \
                            | PIN_PUPDR_FLOATING( GPIOA_XBEE_TX         )   \
                            | PIN_PUPDR_PULLUP(   GPIOA_XBEE_RX         )   \
                            | PIN_PUPDR_PULLDOWN( GPIOA_NC_4            )   \
                            | PIN_PUPDR_PULLDOWN( GPIOA_NC_5            )   \
                            | PIN_PUPDR_FLOATING( GPIOA_SHDN_5V         )   \
                            | PIN_PUPDR_FLOATING( GPIOA_SERVO_PWM       )   \
                            | PIN_PUPDR_PULLDOWN( GPIOA_NC_8            )   \
                            | PIN_PUPDR_FLOATING( GPIOA_GPS_TX          )   \
                            | PIN_PUPDR_PULLUP(   GPIOA_GPS_RX          )   \
                            | PIN_PUPDR_PULLDOWN( GPIOA_NC_11           )   \
                            | PIN_PUPDR_PULLDOWN( GPIOA_NC_12           )   \
                            | PIN_PUPDR_PULLUP(   GPIOA_SWDIO           )   \
                            | PIN_PUPDR_PULLDOWN( GPIOA_SWDCLK          )   \
                            | PIN_PUPDR_PULLDOWN( GPIOA_NC_15           ) )

#define VAL_GPIOA_ODR       ( PIN_ODR_LOW( GPIOA_XBEE_CTS        )          \
                            | PIN_ODR_LOW( GPIOA_XBEE_RTS        )          \
                            | PIN_ODR_LOW( GPIOA_XBEE_TX         )          \
                            | PIN_ODR_LOW( GPIOA_XBEE_RX         )          \
                            | PIN_ODR_LOW( GPIOA_NC_4            )          \
                            | PIN_ODR_LOW( GPIOA_NC_5            )          \
                            | PIN_ODR_LOW( GPIOA_SHDN_5V         )          \
                            | PIN_ODR_LOW( GPIOA_SERVO_PWM       )          \
                            | PIN_ODR_LOW( GPIOA_NC_8            )          \
                            | PIN_ODR_LOW( GPIOA_GPS_TX          )          \
                            | PIN_ODR_LOW( GPIOA_GPS_RX          )          \
                            | PIN_ODR_LOW( GPIOA_NC_11           )          \
                            | PIN_ODR_LOW( GPIOA_NC_12           )          \
                            | PIN_ODR_LOW( GPIOA_SWDIO           )          \
                            | PIN_ODR_LOW( GPIOA_SWDCLK          )          \
                            | PIN_ODR_LOW( GPIOA_NC_15           ) )

#define VAL_GPIOA_AFRL      ( PIN_AFIO_AF( GPIOA_XBEE_CTS       ,  7)      \
                            | PIN_AFIO_AF( GPIOA_XBEE_RTS       ,  7)      \
                            | PIN_AFIO_AF( GPIOA_XBEE_TX        ,  7)      \
                            | PIN_AFIO_AF( GPIOA_XBEE_RX        ,  7)      \
                            | PIN_AFIO_AF( GPIOA_NC_4           ,  0)      \
                            | PIN_AFIO_AF( GPIOA_NC_5           ,  0)      \
                            | PIN_AFIO_AF( GPIOA_SHDN_5V        ,  0)      \
                            | PIN_AFIO_AF( GPIOA_SERVO_PWM      ,  9) )
#define VAL_GPIOA_AFRH      ( PIN_AFIO_AF( GPIOA_NC_8           ,  0)      \
                            | PIN_AFIO_AF( GPIOA_GPS_TX         ,  7)      \
                            | PIN_AFIO_AF( GPIOA_GPS_RX         ,  7)      \
                            | PIN_AFIO_AF( GPIOA_NC_11          ,  0)      \
                            | PIN_AFIO_AF( GPIOA_NC_12          ,  0)      \
                            | PIN_AFIO_AF( GPIOA_SWDIO          ,  0)      \
                            | PIN_AFIO_AF( GPIOA_SWDCLK         ,  0)      \
                            | PIN_AFIO_AF( GPIOA_NC_15          ,  0) )


// GPIO B

#define VAL_GPIOB_MODER     ( PIN_MODE_ALTERNATE( GPIOB_IR_LED_PWM       )       \
                            | PIN_MODE_ALTERNATE( GPIOB_BUZZER_PWM       )       \
                            | PIN_MODE_INPUT(     GPIOB_NC_2             )       \
                            | PIN_MODE_OUTPUT(    GPIOB_LED_HEARTBEAT    )       \
                            | PIN_MODE_OUTPUT(    GPIOB_LED_ERR          )       \
                            | PIN_MODE_OUTPUT(    GPIOB_LED_SDCARD       )       \
                            | PIN_MODE_ALTERNATE( GPIOB_I2C1_SCL         )       \
                            | PIN_MODE_ALTERNATE( GPIOB_I2C1_SDA         )       \
                            | PIN_MODE_INPUT(     GPIOB_NC_8             )       \
                            | PIN_MODE_INPUT(     GPIOB_NC_9             )       \
                            | PIN_MODE_ALTERNATE( GPIOB_CAMERA_TX        )       \
                            | PIN_MODE_ALTERNATE( GPIOB_CAMERA_RX        )       \
                            | PIN_MODE_INPUT(     GPIOB_INT_MPU          )       \
                            | PIN_MODE_INPUT(     GPIOB_INT_H3LIS        )       \
                            | PIN_MODE_INPUT(     GPIOB_INT_HMC          )       \
                            | PIN_MODE_OUTPUT(    GPIOB_XBEE_SLEEP_RQ    ) )

#define VAL_GPIOB_OTYPER    ( PIN_OTYPE_PUSHPULL(  GPIOB_IR_LED_PWM      )   \
                            | PIN_OTYPE_PUSHPULL(  GPIOB_BUZZER_PWM      )   \
                            | PIN_OTYPE_PUSHPULL(  GPIOB_NC_2            )   \
                            | PIN_OTYPE_PUSHPULL(  GPIOB_LED_HEARTBEAT   )   \
                            | PIN_OTYPE_PUSHPULL(  GPIOB_LED_ERR         )   \
                            | PIN_OTYPE_PUSHPULL(  GPIOB_LED_SDCARD      )   \
                            | PIN_OTYPE_OPENDRAIN( GPIOB_I2C1_SCL        )   \
                            | PIN_OTYPE_OPENDRAIN( GPIOB_I2C1_SDA        )   \
                            | PIN_OTYPE_PUSHPULL(  GPIOB_NC_8            )   \
                            | PIN_OTYPE_PUSHPULL(  GPIOB_NC_9            )   \
                            | PIN_OTYPE_PUSHPULL(  GPIOB_CAMERA_TX       )   \
                            | PIN_OTYPE_PUSHPULL(  GPIOB_CAMERA_RX       )   \
                            | PIN_OTYPE_PUSHPULL(  GPIOB_INT_MPU         )   \
                            | PIN_OTYPE_PUSHPULL(  GPIOB_INT_H3LIS       )   \
                            | PIN_OTYPE_PUSHPULL(  GPIOB_INT_HMC         )   \
                            | PIN_OTYPE_PUSHPULL(  GPIOB_XBEE_SLEEP_RQ   ) )

#define VAL_GPIOB_OSPEEDR   ( PIN_OSPEED_100M( GPIOB_IR_LED_PWM      )      \
                            | PIN_OSPEED_100M( GPIOB_BUZZER_PWM      )      \
                            | PIN_OSPEED_100M( GPIOB_NC_2            )      \
                            | PIN_OSPEED_100M( GPIOB_LED_HEARTBEAT   )      \
                            | PIN_OSPEED_100M( GPIOB_LED_ERR         )      \
                            | PIN_OSPEED_100M( GPIOB_LED_SDCARD      )      \
                            | PIN_OSPEED_100M( GPIOB_I2C1_SCL        )      \
                            | PIN_OSPEED_100M( GPIOB_I2C1_SDA        )      \
                            | PIN_OSPEED_100M( GPIOB_NC_8            )      \
                            | PIN_OSPEED_100M( GPIOB_NC_9            )      \
                            | PIN_OSPEED_100M( GPIOB_CAMERA_TX       )      \
                            | PIN_OSPEED_100M( GPIOB_CAMERA_RX       )      \
                            | PIN_OSPEED_100M( GPIOB_INT_MPU         )      \
                            | PIN_OSPEED_100M( GPIOB_INT_H3LIS       )      \
                            | PIN_OSPEED_100M( GPIOB_INT_HMC         )      \
                            | PIN_OSPEED_100M( GPIOB_XBEE_SLEEP_RQ   ) )

#define VAL_GPIOB_PUPDR     ( PIN_PUPDR_FLOATING( GPIOB_IR_LED_PWM      )   \
                            | PIN_PUPDR_FLOATING( GPIOB_BUZZER_PWM      )   \
                            | PIN_PUPDR_PULLDOWN( GPIOB_NC_2            )   \
                            | PIN_PUPDR_FLOATING( GPIOB_LED_HEARTBEAT   )   \
                            | PIN_PUPDR_FLOATING( GPIOB_LED_ERR         )   \
                            | PIN_PUPDR_FLOATING( GPIOB_LED_SDCARD      )   \
                            | PIN_PUPDR_PULLUP(   GPIOB_I2C1_SCL        )   \
                            | PIN_PUPDR_PULLUP(   GPIOB_I2C1_SDA        )   \
                            | PIN_PUPDR_PULLDOWN( GPIOB_NC_8            )   \
                            | PIN_PUPDR_PULLDOWN( GPIOB_NC_9            )   \
                            | PIN_PUPDR_FLOATING( GPIOB_CAMERA_TX       )   \
                            | PIN_PUPDR_PULLUP(   GPIOB_CAMERA_RX       )   \
                            | PIN_PUPDR_FLOATING( GPIOB_INT_MPU         )   \
                            | PIN_PUPDR_FLOATING( GPIOB_INT_H3LIS       )   \
                            | PIN_PUPDR_FLOATING( GPIOB_INT_HMC         )   \
                            | PIN_PUPDR_FLOATING( GPIOB_XBEE_SLEEP_RQ   ) )

#define VAL_GPIOB_ODR       ( PIN_ODR_LOW( GPIOB_IR_LED_PWM      )          \
                            | PIN_ODR_LOW( GPIOB_BUZZER_PWM      )          \
                            | PIN_ODR_LOW( GPIOB_NC_2            )          \
                            | PIN_ODR_LOW( GPIOB_LED_HEARTBEAT   )          \
                            | PIN_ODR_LOW( GPIOB_LED_ERR         )          \
                            | PIN_ODR_LOW( GPIOB_LED_SDCARD      )          \
                            | PIN_ODR_LOW( GPIOB_I2C1_SCL        )          \
                            | PIN_ODR_LOW( GPIOB_I2C1_SDA        )          \
                            | PIN_ODR_LOW( GPIOB_NC_8            )          \
                            | PIN_ODR_LOW( GPIOB_NC_9            )          \
                            | PIN_ODR_LOW( GPIOB_CAMERA_TX       )          \
                            | PIN_ODR_LOW( GPIOB_CAMERA_RX       )          \
                            | PIN_ODR_LOW( GPIOB_INT_MPU         )          \
                            | PIN_ODR_LOW( GPIOB_INT_H3LIS       )          \
                            | PIN_ODR_LOW( GPIOB_INT_HMC         )          \
                            | PIN_ODR_LOW( GPIOB_XBEE_SLEEP_RQ   ) )

#define VAL_GPIOB_AFRL      ( PIN_AFIO_AF( GPIOB_IR_LED_PWM      ,  2)      \
                            | PIN_AFIO_AF( GPIOB_BUZZER_PWM      ,  1)      \
                            | PIN_AFIO_AF( GPIOB_NC_2            ,  0)      \
                            | PIN_AFIO_AF( GPIOB_LED_HEARTBEAT   ,  0)      \
                            | PIN_AFIO_AF( GPIOB_LED_ERR         ,  0)      \
                            | PIN_AFIO_AF( GPIOB_LED_SDCARD      ,  0)      \
                            | PIN_AFIO_AF( GPIOB_I2C1_SCL        ,  4)      \
                            | PIN_AFIO_AF( GPIOB_I2C1_SDA        ,  4) )
#define VAL_GPIOB_AFRH      ( PIN_AFIO_AF( GPIOB_NC_8            ,  0)      \
                            | PIN_AFIO_AF( GPIOB_NC_9            ,  0)      \
                            | PIN_AFIO_AF( GPIOB_CAMERA_TX       ,  7)      \
                            | PIN_AFIO_AF( GPIOB_CAMERA_RX       ,  7)      \
                            | PIN_AFIO_AF( GPIOB_INT_MPU         ,  0)      \
                            | PIN_AFIO_AF( GPIOB_INT_H3LIS       ,  0)      \
                            | PIN_AFIO_AF( GPIOB_INT_HMC         ,  0)      \
                            | PIN_AFIO_AF( GPIOB_XBEE_SLEEP_RQ   ,  0) )


// GPIO C

#define VAL_GPIOC_MODER     ( PIN_MODE_ANALOG(    GPIOC_ADC_PITOT      )       \
                            | PIN_MODE_ANALOG(    GPIOC_ADC_VBAT       )       \
                            | PIN_MODE_ANALOG(    GPIOC_ADC_5V         )       \
                            | PIN_MODE_INPUT(     GPIOC_NC_3           )       \
                            | PIN_MODE_OUTPUT(    GPIOC_GPS_SHDN       )       \
                            | PIN_MODE_OUTPUT(    GPIOC_SDCARD_SHDN    )       \
                            | PIN_MODE_ALTERNATE( GPIOC_DEBUG_TX       )       \
                            | PIN_MODE_ALTERNATE( GPIOC_DEBUT_RX       )       \
                            | PIN_MODE_ALTERNATE( GPIOC_SDIO_D0        )       \
                            | PIN_MODE_ALTERNATE( GPIOC_SDIO_D1        )       \
                            | PIN_MODE_ALTERNATE( GPIOC_SDIO_D2        )       \
                            | PIN_MODE_ALTERNATE( GPIOC_SDIO_D3        )       \
                            | PIN_MODE_ALTERNATE( GPIOC_SDIO_CK        )       \
                            | PIN_MODE_INPUT(     GPIOC_NC_13          )       \
                            | PIN_MODE_INPUT(     GPIOC_NC_14          )       \
                            | PIN_MODE_INPUT(     GPIOC_NC_15          ) )

#define VAL_GPIOC_OTYPER    ( PIN_OTYPE_PUSHPULL( GPIOC_ADC_PITOT      )   \
                            | PIN_OTYPE_PUSHPULL( GPIOC_ADC_VBAT       )   \
                            | PIN_OTYPE_PUSHPULL( GPIOC_ADC_5V         )   \
                            | PIN_OTYPE_PUSHPULL( GPIOC_NC_3           )   \
                            | PIN_OTYPE_PUSHPULL( GPIOC_GPS_SHDN       )   \
                            | PIN_OTYPE_PUSHPULL( GPIOC_SDCARD_SHDN    )   \
                            | PIN_OTYPE_PUSHPULL( GPIOC_DEBUG_TX       )   \
                            | PIN_OTYPE_PUSHPULL( GPIOC_DEBUT_RX       )   \
                            | PIN_OTYPE_PUSHPULL( GPIOC_SDIO_D0        )   \
                            | PIN_OTYPE_PUSHPULL( GPIOC_SDIO_D1        )   \
                            | PIN_OTYPE_PUSHPULL( GPIOC_SDIO_D2        )   \
                            | PIN_OTYPE_PUSHPULL( GPIOC_SDIO_D3        )   \
                            | PIN_OTYPE_PUSHPULL( GPIOC_SDIO_CK        )   \
                            | PIN_OTYPE_PUSHPULL( GPIOC_NC_13          )   \
                            | PIN_OTYPE_PUSHPULL( GPIOC_NC_14          )   \
                            | PIN_OTYPE_PUSHPULL( GPIOC_NC_15          ) )

#define VAL_GPIOC_OSPEEDR   ( PIN_OSPEED_100M( GPIOC_ADC_PITOT      )      \
                            | PIN_OSPEED_100M( GPIOC_ADC_VBAT       )      \
                            | PIN_OSPEED_100M( GPIOC_ADC_5V         )      \
                            | PIN_OSPEED_100M( GPIOC_NC_3           )      \
                            | PIN_OSPEED_100M( GPIOC_GPS_SHDN       )      \
                            | PIN_OSPEED_100M( GPIOC_SDCARD_SHDN    )      \
                            | PIN_OSPEED_100M( GPIOC_DEBUG_TX       )      \
                            | PIN_OSPEED_100M( GPIOC_DEBUT_RX       )      \
                            | PIN_OSPEED_100M( GPIOC_SDIO_D0        )      \
                            | PIN_OSPEED_100M( GPIOC_SDIO_D1        )      \
                            | PIN_OSPEED_100M( GPIOC_SDIO_D2        )      \
                            | PIN_OSPEED_100M( GPIOC_SDIO_D3        )      \
                            | PIN_OSPEED_100M( GPIOC_SDIO_CK        )      \
                            | PIN_OSPEED_100M( GPIOC_NC_13          )      \
                            | PIN_OSPEED_100M( GPIOC_NC_14          )      \
                            | PIN_OSPEED_100M( GPIOC_NC_15          ) )

#define VAL_GPIOC_PUPDR     ( PIN_PUPDR_FLOATING( GPIOC_ADC_PITOT      )   \
                            | PIN_PUPDR_FLOATING( GPIOC_ADC_VBAT       )   \
                            | PIN_PUPDR_FLOATING( GPIOC_ADC_5V         )   \
                            | PIN_PUPDR_PULLDOWN( GPIOC_NC_3           )   \
                            | PIN_PUPDR_FLOATING( GPIOC_GPS_SHDN       )   \
                            | PIN_PUPDR_FLOATING( GPIOC_SDCARD_SHDN    )   \
                            | PIN_PUPDR_FLOATING( GPIOC_DEBUG_TX       )   \
                            | PIN_PUPDR_PULLUP(   GPIOC_DEBUT_RX       )   \
                            | PIN_PUPDR_PULLUP(   GPIOC_SDIO_D0        )   \
                            | PIN_PUPDR_PULLUP(   GPIOC_SDIO_D1        )   \
                            | PIN_PUPDR_PULLUP(   GPIOC_SDIO_D2        )   \
                            | PIN_PUPDR_PULLUP(   GPIOC_SDIO_D3        )   \
                            | PIN_PUPDR_PULLUP(   GPIOC_SDIO_CK        )   \
                            | PIN_PUPDR_PULLDOWN( GPIOC_NC_13          )   \
                            | PIN_PUPDR_PULLDOWN( GPIOC_NC_14          )   \
                            | PIN_PUPDR_PULLDOWN( GPIOC_NC_15          ) )

#define VAL_GPIOC_ODR       ( PIN_ODR_LOW(  GPIOC_ADC_PITOT      )          \
                            | PIN_ODR_LOW(  GPIOC_ADC_VBAT       )          \
                            | PIN_ODR_LOW(  GPIOC_ADC_5V         )          \
                            | PIN_ODR_LOW(  GPIOC_NC_3           )          \
                            | PIN_ODR_HIGH( GPIOC_GPS_SHDN       )          \
                            | PIN_ODR_HIGH( GPIOC_SDCARD_SHDN    )          \
                            | PIN_ODR_LOW(  GPIOC_DEBUG_TX       )          \
                            | PIN_ODR_LOW(  GPIOC_DEBUT_RX       )          \
                            | PIN_ODR_LOW(  GPIOC_SDIO_D0        )          \
                            | PIN_ODR_LOW(  GPIOC_SDIO_D1        )          \
                            | PIN_ODR_LOW(  GPIOC_SDIO_D2        )          \
                            | PIN_ODR_LOW(  GPIOC_SDIO_D3        )          \
                            | PIN_ODR_LOW(  GPIOC_SDIO_CK        )          \
                            | PIN_ODR_LOW(  GPIOC_NC_13          )          \
                            | PIN_ODR_LOW(  GPIOC_NC_14          )          \
                            | PIN_ODR_LOW(  GPIOC_NC_15          ) )

#define VAL_GPIOC_AFRL      ( PIN_AFIO_AF( GPIOC_ADC_PITOT      ,  0)      \
                            | PIN_AFIO_AF( GPIOC_ADC_VBAT       ,  0)      \
                            | PIN_AFIO_AF( GPIOC_ADC_5V         ,  0)      \
                            | PIN_AFIO_AF( GPIOC_NC_3           ,  0)      \
                            | PIN_AFIO_AF( GPIOC_GPS_SHDN       ,  0)      \
                            | PIN_AFIO_AF( GPIOC_SDCARD_SHDN    ,  0)      \
                            | PIN_AFIO_AF( GPIOC_DEBUG_TX       ,  8)      \
                            | PIN_AFIO_AF( GPIOC_DEBUT_RX       ,  8) )
#define VAL_GPIOC_AFRH      ( PIN_AFIO_AF( GPIOC_SDIO_D0        , 12)      \
                            | PIN_AFIO_AF( GPIOC_SDIO_D1        , 12)      \
                            | PIN_AFIO_AF( GPIOC_SDIO_D2        , 12)      \
                            | PIN_AFIO_AF( GPIOC_SDIO_D3        , 12)      \
                            | PIN_AFIO_AF( GPIOC_SDIO_CK        , 12)      \
                            | PIN_AFIO_AF( GPIOC_NC_13          ,  0)      \
                            | PIN_AFIO_AF( GPIOC_NC_14          ,  0)      \
                            | PIN_AFIO_AF( GPIOC_NC_15          ,  0) )


// GPIO D

#define VAL_GPIOD_MODER     ( PIN_MODE_ALTERNATE( GPIOD_SDIO_CMD ) )

#define VAL_GPIOD_OTYPER    ( PIN_OTYPE_PUSHPULL( GPIOD_SDIO_CMD ) )

#define VAL_GPIOD_OSPEEDR   ( PIN_OSPEED_100M( GPIOD_SDIO_CMD ) )

#define VAL_GPIOD_PUPDR     ( PIN_PUPDR_PULLUP( GPIOD_SDIO_CMD ) )

#define VAL_GPIOD_ODR       ( PIN_ODR_LOW( GPIOD_SDIO_CMD ) )

#define VAL_GPIOD_AFRL      ( PIN_AFIO_AF( GPIOD_SDIO_CMD,  12) )

#define VAL_GPIOD_AFRH      ( 0 )


// GPIO E

#define VAL_GPIOE_MODER     ( 0 )

#define VAL_GPIOE_OTYPER    ( 0 )

#define VAL_GPIOE_OSPEEDR   ( 0 )

#define VAL_GPIOE_PUPDR     ( 0 )

#define VAL_GPIOE_ODR       ( 0 )

#define VAL_GPIOE_AFRL      ( 0 )

#define VAL_GPIOE_AFRH      ( 0 )


// GPIO F

#define VAL_GPIOF_MODER     ( 0 )

#define VAL_GPIOF_OTYPER    ( 0 )

#define VAL_GPIOF_OSPEEDR   ( 0 )

#define VAL_GPIOF_PUPDR     ( 0 )

#define VAL_GPIOF_ODR       ( 0 )

#define VAL_GPIOF_AFRL      ( 0 )

#define VAL_GPIOF_AFRH      ( 0 )


// GPIO G

#define VAL_GPIOG_MODER     ( 0 )

#define VAL_GPIOG_OTYPER    ( 0 )

#define VAL_GPIOG_OSPEEDR   ( 0 )

#define VAL_GPIOG_PUPDR     ( 0 )

#define VAL_GPIOG_ODR       ( 0 )

#define VAL_GPIOG_AFRL      ( 0 )

#define VAL_GPIOG_AFRH      ( 0 )


// GPIO H

#define VAL_GPIOH_MODER     ( PIN_MODE_INPUT( GPIOH_OSC_IN      )           \
                            | PIN_MODE_INPUT( GPIOH_OSC_OUT     ) )

#define VAL_GPIOH_OTYPER    ( PIN_OTYPE_PUSHPULL( GPIOH_OSC_IN      )       \
                            | PIN_OTYPE_PUSHPULL( GPIOH_OSC_OUT     ) )

#define VAL_GPIOH_OSPEEDR   ( PIN_OSPEED_100M( GPIOH_OSC_IN      )          \
                            | PIN_OSPEED_100M( GPIOH_OSC_OUT     ) )

#define VAL_GPIOH_PUPDR     ( PIN_PUPDR_FLOATING( GPIOH_OSC_IN      )       \
                            | PIN_PUPDR_FLOATING( GPIOH_OSC_OUT     ) )

#define VAL_GPIOH_ODR       ( PIN_ODR_LOW( GPIOH_OSC_IN      )              \
                            | PIN_ODR_LOW( GPIOH_OSC_OUT     ) )

#define VAL_GPIOH_AFRL      ( PIN_AFIO_AF( GPIOH_OSC_IN    , 0)             \
                            | PIN_AFIO_AF( GPIOH_OSC_OUT   , 0) )

#define VAL_GPIOH_AFRH      ( 0 )


// GPIO I

#define VAL_GPIOI_MODER     ( 0 )

#define VAL_GPIOI_OTYPER    ( 0 )

#define VAL_GPIOI_OSPEEDR   ( 0 )

#define VAL_GPIOI_PUPDR     ( 0 )

#define VAL_GPIOI_ODR       ( 0 )

#define VAL_GPIOI_AFRL      ( 0 )

#define VAL_GPIOI_AFRH      ( 0 )


#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif

#define chstdout (BaseSequentialStream*)&SD6

#define boardInit() board_init()

void board_init(void);


void led_sdcard(bool en);
void led_heartbeat(bool en);
void led_error(bool en);

void pwr_sdcard(bool en);
void pwr_gps(bool en);
void pwr_5V(bool en);

void IR_pwm(bool en);

#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */

#endif /* _BOARD_H_ */
