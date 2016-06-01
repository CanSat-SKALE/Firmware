#ifndef _BOARD_H_
#define _BOARD_H_

#define BOARD_NAME                  "SKALE - Container"


#if !defined(STM32_LSECLK)
#define STM32_LSECLK                0
#endif

#define STM32_HSECLK                16000000

#define STM32_VDD                   330

#define STM32F405xx



/*
 * IO pins assignments.
 */
#define GPIOA_NC_0                  0
#define GPIOA_NC_1                  1
#define GPIOA_NC_2                  2
#define GPIOA_NC_3                  3
#define GPIOA_IR_RECEIVER           4
#define GPIOA_NC_5                  5
#define GPIOA_SERVO_2               6 // TIM3CH1
#define GPIOA_SERVO_1               7 // TIM3CH2
#define GPIOA_NC_8                  8
#define GPIOA_NC_9                  9
#define GPIOA_NC_10                 10
#define GPIOA_NC_11                 11
#define GPIOA_NC_12                 12
#define GPIOA_SWDIO                 13
#define GPIOA_SWDCLK                14
#define GPIOA_RESISTOR_4            15

#define GPIOB_NC_0                  0
#define GPIOB_NC_1                  1
#define GPIOB_NC_2                  2
#define GPIOB_LED_HEARTBEAT         3
#define GPIOB_NC_4                  4
#define GPIOB_LED_ERR               5
#define GPIOB_I2C1_SCL              6
#define GPIOB_I2C1_SDA              7
#define GPIOB_NC_8                  8
#define GPIOB_NC_9                  9
#define GPIOB_I2C2_SCL              10
#define GPIOB_I2C2_SDA              11
#define GPIOB_INT_H3LIS             12
#define GPIOB_INT_LP                13
#define GPIOB_INT_MPU               14
#define GPIOB_SENSOR_SHDN           15

#define GPIOC_NC_0                  0
#define GPIOC_ADC_VBAT              1
#define GPIOC_NC_2                  2
#define GPIOC_NC_3                  3
#define GPIOC_NC_4                  4
#define GPIOC_NC_5                  5
#define GPIOC_DEBUG_TX              6
#define GPIOC_DEBUT_RX              7
#define GPIOC_NC_8                  8
#define GPIOC_NC_9                  9
#define GPIOC_RESISTOR_3            10
#define GPIOC_RESISTOR_2            11
#define GPIOC_RESISTOR_1            12
#define GPIOC_NC_13                 13
#define GPIOC_NC_14                 14
#define GPIOC_NC_15                 15

#define GPIOD_NC_2                  2

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

#define VAL_GPIOA_MODER     ( PIN_MODE_INPUT(     GPIOA_NC_0            )       \
                            | PIN_MODE_INPUT(     GPIOA_NC_1            )       \
                            | PIN_MODE_INPUT(     GPIOA_NC_2            )       \
                            | PIN_MODE_INPUT(     GPIOA_NC_3            )       \
                            | PIN_MODE_INPUT(     GPIOA_IR_RECEIVER     )       \
                            | PIN_MODE_INPUT(     GPIOA_NC_5            )       \
                            | PIN_MODE_ALTERNATE( GPIOA_SERVO_2         )       \
                            | PIN_MODE_ALTERNATE( GPIOA_SERVO_1         )       \
                            | PIN_MODE_INPUT(     GPIOA_NC_8            )       \
                            | PIN_MODE_INPUT(     GPIOA_NC_9            )       \
                            | PIN_MODE_INPUT(     GPIOA_NC_10           )       \
                            | PIN_MODE_INPUT(     GPIOA_NC_11           )       \
                            | PIN_MODE_INPUT(     GPIOA_NC_12           )       \
                            | PIN_MODE_ALTERNATE( GPIOA_SWDIO           )       \
                            | PIN_MODE_ALTERNATE( GPIOA_SWDCLK          )       \
                            | PIN_MODE_OUTPUT(    GPIOA_RESISTOR_4      ) )

#define VAL_GPIOA_OTYPER    ( PIN_OTYPE_PUSHPULL( GPIOA_NC_0            )   \
                            | PIN_OTYPE_PUSHPULL( GPIOA_NC_1            )   \
                            | PIN_OTYPE_PUSHPULL( GPIOA_NC_2            )   \
                            | PIN_OTYPE_PUSHPULL( GPIOA_NC_3            )   \
                            | PIN_OTYPE_PUSHPULL( GPIOA_IR_RECEIVER     )   \
                            | PIN_OTYPE_PUSHPULL( GPIOA_NC_5            )   \
                            | PIN_OTYPE_PUSHPULL( GPIOA_SERVO_2         )   \
                            | PIN_OTYPE_PUSHPULL( GPIOA_SERVO_1         )   \
                            | PIN_OTYPE_PUSHPULL( GPIOA_NC_8            )   \
                            | PIN_OTYPE_PUSHPULL( GPIOA_NC_9            )   \
                            | PIN_OTYPE_PUSHPULL( GPIOA_NC_10           )   \
                            | PIN_OTYPE_PUSHPULL( GPIOA_NC_11           )   \
                            | PIN_OTYPE_PUSHPULL( GPIOA_NC_12           )   \
                            | PIN_OTYPE_PUSHPULL( GPIOA_SWDIO           )   \
                            | PIN_OTYPE_PUSHPULL( GPIOA_SWDCLK          )   \
                            | PIN_OTYPE_PUSHPULL( GPIOA_RESISTOR_4      ) )

#define VAL_GPIOA_OSPEEDR   ( PIN_OSPEED_100M( GPIOA_NC_0               )      \
                            | PIN_OSPEED_100M( GPIOA_NC_1               )      \
                            | PIN_OSPEED_100M( GPIOA_NC_2               )      \
                            | PIN_OSPEED_100M( GPIOA_NC_3               )      \
                            | PIN_OSPEED_100M( GPIOA_IR_RECEIVER        )      \
                            | PIN_OSPEED_100M( GPIOA_NC_5               )      \
                            | PIN_OSPEED_100M( GPIOA_SERVO_2            )      \
                            | PIN_OSPEED_100M( GPIOA_SERVO_1            )      \
                            | PIN_OSPEED_100M( GPIOA_NC_8               )      \
                            | PIN_OSPEED_100M( GPIOA_NC_9               )      \
                            | PIN_OSPEED_100M( GPIOA_NC_10              )      \
                            | PIN_OSPEED_100M( GPIOA_NC_11              )      \
                            | PIN_OSPEED_100M( GPIOA_NC_12              )      \
                            | PIN_OSPEED_100M( GPIOA_SWDIO              )      \
                            | PIN_OSPEED_100M( GPIOA_SWDCLK             )      \
                            | PIN_OSPEED_100M( GPIOA_RESISTOR_4         ) )

#define VAL_GPIOA_PUPDR     ( PIN_PUPDR_PULLDOWN( GPIOA_NC_0            )   \
                            | PIN_PUPDR_PULLDOWN( GPIOA_NC_1            )   \
                            | PIN_PUPDR_PULLDOWN( GPIOA_NC_2            )   \
                            | PIN_PUPDR_PULLDOWN( GPIOA_NC_3            )   \
                            | PIN_PUPDR_FLOATING( GPIOA_IR_RECEIVER     )   \
                            | PIN_PUPDR_PULLDOWN( GPIOA_NC_5            )   \
                            | PIN_PUPDR_FLOATING( GPIOA_SERVO_2         )   \
                            | PIN_PUPDR_FLOATING( GPIOA_SERVO_1         )   \
                            | PIN_PUPDR_PULLDOWN( GPIOA_NC_8            )   \
                            | PIN_PUPDR_PULLDOWN( GPIOA_NC_9            )   \
                            | PIN_PUPDR_PULLDOWN( GPIOA_NC_10           )   \
                            | PIN_PUPDR_PULLDOWN( GPIOA_NC_11           )   \
                            | PIN_PUPDR_PULLDOWN( GPIOA_NC_12           )   \
                            | PIN_PUPDR_PULLUP(   GPIOA_SWDIO           )   \
                            | PIN_PUPDR_PULLDOWN( GPIOA_SWDCLK          )   \
                            | PIN_PUPDR_FLOATING( GPIOA_RESISTOR_4      ) )

#define VAL_GPIOA_ODR       ( PIN_ODR_LOW( GPIOA_NC_0            )          \
                            | PIN_ODR_LOW( GPIOA_NC_1            )          \
                            | PIN_ODR_LOW( GPIOA_NC_2            )          \
                            | PIN_ODR_LOW( GPIOA_NC_3            )          \
                            | PIN_ODR_LOW( GPIOA_IR_RECEIVER     )          \
                            | PIN_ODR_LOW( GPIOA_NC_5            )          \
                            | PIN_ODR_LOW( GPIOA_SERVO_2         )          \
                            | PIN_ODR_LOW( GPIOA_SERVO_1         )          \
                            | PIN_ODR_LOW( GPIOA_NC_8            )          \
                            | PIN_ODR_LOW( GPIOA_NC_9            )          \
                            | PIN_ODR_LOW( GPIOA_NC_10           )          \
                            | PIN_ODR_LOW( GPIOA_NC_11           )          \
                            | PIN_ODR_LOW( GPIOA_NC_12           )          \
                            | PIN_ODR_LOW( GPIOA_SWDIO           )          \
                            | PIN_ODR_LOW( GPIOA_SWDCLK          )          \
                            | PIN_ODR_LOW( GPIOA_RESISTOR_4      ) )

#define VAL_GPIOA_AFRL      ( PIN_AFIO_AF( GPIOA_NC_0           ,  0)      \
                            | PIN_AFIO_AF( GPIOA_NC_1           ,  0)      \
                            | PIN_AFIO_AF( GPIOA_NC_2           ,  0)      \
                            | PIN_AFIO_AF( GPIOA_NC_3           ,  0)      \
                            | PIN_AFIO_AF( GPIOA_IR_RECEIVER    ,  0)      \
                            | PIN_AFIO_AF( GPIOA_NC_5           ,  0)      \
                            | PIN_AFIO_AF( GPIOA_SERVO_2        ,  2)      \
                            | PIN_AFIO_AF( GPIOA_SERVO_1        ,  2) )
#define VAL_GPIOA_AFRH      ( PIN_AFIO_AF( GPIOA_NC_8           ,  0)      \
                            | PIN_AFIO_AF( GPIOA_NC_9           ,  0)      \
                            | PIN_AFIO_AF( GPIOA_NC_10          ,  0)      \
                            | PIN_AFIO_AF( GPIOA_NC_11          ,  0)      \
                            | PIN_AFIO_AF( GPIOA_NC_12          ,  0)      \
                            | PIN_AFIO_AF( GPIOA_SWDIO          ,  0)      \
                            | PIN_AFIO_AF( GPIOA_SWDCLK         ,  0)      \
                            | PIN_AFIO_AF( GPIOA_RESISTOR_4     ,  0) )


// GPIO B

#define VAL_GPIOB_MODER     ( PIN_MODE_INPUT(     GPIOB_NC_0             )       \
                            | PIN_MODE_INPUT(     GPIOB_NC_1             )       \
                            | PIN_MODE_INPUT(     GPIOB_NC_2             )       \
                            | PIN_MODE_OUTPUT(    GPIOB_LED_HEARTBEAT    )       \
                            | PIN_MODE_INPUT(     GPIOB_NC_4             )       \
                            | PIN_MODE_OUTPUT(    GPIOB_LED_ERR          )       \
                            | PIN_MODE_ALTERNATE( GPIOB_I2C1_SCL         )       \
                            | PIN_MODE_ALTERNATE( GPIOB_I2C1_SDA         )       \
                            | PIN_MODE_INPUT(     GPIOB_NC_8             )       \
                            | PIN_MODE_INPUT(     GPIOB_NC_9             )       \
                            | PIN_MODE_ALTERNATE( GPIOB_I2C2_SCL         )       \
                            | PIN_MODE_ALTERNATE( GPIOB_I2C2_SDA         )       \
                            | PIN_MODE_INPUT(     GPIOB_INT_H3LIS        )       \
                            | PIN_MODE_INPUT(     GPIOB_INT_LP           )       \
                            | PIN_MODE_INPUT(     GPIOB_INT_MPU          )       \
                            | PIN_MODE_OUTPUT(    GPIOB_SENSOR_SHDN      ) )

#define VAL_GPIOB_OTYPER    ( PIN_OTYPE_PUSHPULL(  GPIOB_NC_0            )   \
                            | PIN_OTYPE_PUSHPULL(  GPIOB_NC_1            )   \
                            | PIN_OTYPE_PUSHPULL(  GPIOB_NC_2            )   \
                            | PIN_OTYPE_PUSHPULL(  GPIOB_LED_HEARTBEAT   )   \
                            | PIN_OTYPE_PUSHPULL(  GPIOB_NC_4            )   \
                            | PIN_OTYPE_PUSHPULL(  GPIOB_LED_ERR         )   \
                            | PIN_OTYPE_OPENDRAIN( GPIOB_I2C1_SCL        )   \
                            | PIN_OTYPE_OPENDRAIN( GPIOB_I2C1_SDA        )   \
                            | PIN_OTYPE_PUSHPULL(  GPIOB_NC_8            )   \
                            | PIN_OTYPE_PUSHPULL(  GPIOB_NC_9            )   \
                            | PIN_OTYPE_OPENDRAIN( GPIOB_I2C2_SCL        )   \
                            | PIN_OTYPE_OPENDRAIN( GPIOB_I2C2_SDA        )   \
                            | PIN_OTYPE_PUSHPULL(  GPIOB_INT_H3LIS       )   \
                            | PIN_OTYPE_PUSHPULL(  GPIOB_INT_LP          )   \
                            | PIN_OTYPE_PUSHPULL(  GPIOB_INT_MPU         )   \
                            | PIN_OTYPE_PUSHPULL(  GPIOB_SENSOR_SHDN     ) )

#define VAL_GPIOB_OSPEEDR   ( PIN_OSPEED_100M( GPIOB_NC_0            )      \
                            | PIN_OSPEED_100M( GPIOB_NC_1            )      \
                            | PIN_OSPEED_100M( GPIOB_NC_2            )      \
                            | PIN_OSPEED_100M( GPIOB_LED_HEARTBEAT   )      \
                            | PIN_OSPEED_100M( GPIOB_NC_4            )      \
                            | PIN_OSPEED_100M( GPIOB_LED_ERR         )      \
                            | PIN_OSPEED_100M( GPIOB_I2C1_SCL        )      \
                            | PIN_OSPEED_100M( GPIOB_I2C1_SDA        )      \
                            | PIN_OSPEED_100M( GPIOB_NC_8            )      \
                            | PIN_OSPEED_100M( GPIOB_NC_9            )      \
                            | PIN_OSPEED_100M( GPIOB_I2C2_SCL        )      \
                            | PIN_OSPEED_100M( GPIOB_I2C2_SDA        )      \
                            | PIN_OSPEED_100M( GPIOB_INT_H3LIS       )      \
                            | PIN_OSPEED_100M( GPIOB_INT_LP          )      \
                            | PIN_OSPEED_100M( GPIOB_INT_MPU         )      \
                            | PIN_OSPEED_100M( GPIOB_SENSOR_SHDN     ) )

#define VAL_GPIOB_PUPDR     ( PIN_PUPDR_PULLDOWN( GPIOB_NC_0            )   \
                            | PIN_PUPDR_PULLDOWN( GPIOB_NC_1            )   \
                            | PIN_PUPDR_PULLDOWN( GPIOB_NC_2            )   \
                            | PIN_PUPDR_FLOATING( GPIOB_LED_HEARTBEAT   )   \
                            | PIN_PUPDR_PULLDOWN( GPIOB_NC_4            )   \
                            | PIN_PUPDR_FLOATING( GPIOB_LED_ERR         )   \
                            | PIN_PUPDR_PULLUP(   GPIOB_I2C1_SCL        )   \
                            | PIN_PUPDR_PULLUP(   GPIOB_I2C1_SDA        )   \
                            | PIN_PUPDR_PULLDOWN( GPIOB_NC_8            )   \
                            | PIN_PUPDR_PULLDOWN( GPIOB_NC_9            )   \
                            | PIN_PUPDR_PULLUP(   GPIOB_I2C2_SCL        )   \
                            | PIN_PUPDR_PULLUP(   GPIOB_I2C2_SDA        )   \
                            | PIN_PUPDR_FLOATING( GPIOB_INT_H3LIS       )   \
                            | PIN_PUPDR_FLOATING( GPIOB_INT_LP          )   \
                            | PIN_PUPDR_FLOATING( GPIOB_INT_MPU         )   \
                            | PIN_PUPDR_FLOATING( GPIOB_SENSOR_SHDN     ) )

#define VAL_GPIOB_ODR       ( PIN_ODR_LOW( GPIOB_NC_0            )          \
                            | PIN_ODR_LOW( GPIOB_NC_1            )          \
                            | PIN_ODR_LOW( GPIOB_NC_2            )          \
                            | PIN_ODR_LOW( GPIOB_LED_HEARTBEAT   )          \
                            | PIN_ODR_LOW( GPIOB_NC_4            )          \
                            | PIN_ODR_LOW( GPIOB_LED_ERR         )          \
                            | PIN_ODR_LOW( GPIOB_I2C1_SCL        )          \
                            | PIN_ODR_LOW( GPIOB_I2C1_SDA        )          \
                            | PIN_ODR_LOW( GPIOB_NC_8            )          \
                            | PIN_ODR_LOW( GPIOB_NC_9            )          \
                            | PIN_ODR_LOW( GPIOB_I2C2_SCL        )          \
                            | PIN_ODR_LOW( GPIOB_I2C2_SDA        )          \
                            | PIN_ODR_LOW( GPIOB_INT_H3LIS       )          \
                            | PIN_ODR_LOW( GPIOB_INT_LP          )          \
                            | PIN_ODR_LOW( GPIOB_INT_MPU         )          \
                            | PIN_ODR_HIGH(GPIOB_SENSOR_SHDN     ) )

#define VAL_GPIOB_AFRL      ( PIN_AFIO_AF( GPIOB_NC_0            ,  0)      \
                            | PIN_AFIO_AF( GPIOB_NC_1            ,  0)      \
                            | PIN_AFIO_AF( GPIOB_NC_2            ,  0)      \
                            | PIN_AFIO_AF( GPIOB_LED_HEARTBEAT   ,  0)      \
                            | PIN_AFIO_AF( GPIOB_NC_4            ,  0)      \
                            | PIN_AFIO_AF( GPIOB_LED_ERR         ,  0)      \
                            | PIN_AFIO_AF( GPIOB_I2C1_SCL        ,  4)      \
                            | PIN_AFIO_AF( GPIOB_I2C1_SDA        ,  4) )
#define VAL_GPIOB_AFRH      ( PIN_AFIO_AF( GPIOB_NC_8            ,  0)      \
                            | PIN_AFIO_AF( GPIOB_NC_9            ,  0)      \
                            | PIN_AFIO_AF( GPIOB_I2C2_SCL        ,  4)      \
                            | PIN_AFIO_AF( GPIOB_I2C2_SDA        ,  4)      \
                            | PIN_AFIO_AF( GPIOB_INT_H3LIS       ,  0)      \
                            | PIN_AFIO_AF( GPIOB_INT_LP          ,  0)      \
                            | PIN_AFIO_AF( GPIOB_INT_MPU         ,  0)      \
                            | PIN_AFIO_AF( GPIOB_SENSOR_SHDN     ,  0) )


// GPIO C

#define VAL_GPIOC_MODER     ( PIN_MODE_INPUT(     GPIOC_NC_0           )       \
                            | PIN_MODE_ANALOG(    GPIOC_ADC_VBAT       )       \
                            | PIN_MODE_INPUT(     GPIOC_NC_2           )       \
                            | PIN_MODE_INPUT(     GPIOC_NC_3           )       \
                            | PIN_MODE_INPUT(     GPIOC_NC_4           )       \
                            | PIN_MODE_INPUT(     GPIOC_NC_5           )       \
                            | PIN_MODE_ALTERNATE( GPIOC_DEBUG_TX       )       \
                            | PIN_MODE_ALTERNATE( GPIOC_DEBUT_RX       )       \
                            | PIN_MODE_INPUT(     GPIOC_NC_8           )       \
                            | PIN_MODE_INPUT(     GPIOC_NC_9           )       \
                            | PIN_MODE_OUTPUT(    GPIOC_RESISTOR_3     )       \
                            | PIN_MODE_OUTPUT(    GPIOC_RESISTOR_2     )       \
                            | PIN_MODE_OUTPUT(    GPIOC_RESISTOR_1     )       \
                            | PIN_MODE_INPUT(     GPIOC_NC_13          )       \
                            | PIN_MODE_INPUT(     GPIOC_NC_14          )       \
                            | PIN_MODE_INPUT(     GPIOC_NC_15          ) )

#define VAL_GPIOC_OTYPER    ( PIN_OTYPE_PUSHPULL( GPIOC_NC_0           )   \
                            | PIN_OTYPE_PUSHPULL( GPIOC_ADC_VBAT       )   \
                            | PIN_OTYPE_PUSHPULL( GPIOC_NC_2           )   \
                            | PIN_OTYPE_PUSHPULL( GPIOC_NC_3           )   \
                            | PIN_OTYPE_PUSHPULL( GPIOC_NC_4           )   \
                            | PIN_OTYPE_PUSHPULL( GPIOC_NC_5           )   \
                            | PIN_OTYPE_PUSHPULL( GPIOC_DEBUG_TX       )   \
                            | PIN_OTYPE_PUSHPULL( GPIOC_DEBUT_RX       )   \
                            | PIN_OTYPE_PUSHPULL( GPIOC_NC_8           )   \
                            | PIN_OTYPE_PUSHPULL( GPIOC_NC_9           )   \
                            | PIN_OTYPE_PUSHPULL( GPIOC_RESISTOR_3     )   \
                            | PIN_OTYPE_PUSHPULL( GPIOC_RESISTOR_2     )   \
                            | PIN_OTYPE_PUSHPULL( GPIOC_RESISTOR_1     )   \
                            | PIN_OTYPE_PUSHPULL( GPIOC_NC_13          )   \
                            | PIN_OTYPE_PUSHPULL( GPIOC_NC_14          )   \
                            | PIN_OTYPE_PUSHPULL( GPIOC_NC_15          ) )

#define VAL_GPIOC_OSPEEDR   ( PIN_OSPEED_100M( GPIOC_NC_0           )      \
                            | PIN_OSPEED_100M( GPIOC_ADC_VBAT       )      \
                            | PIN_OSPEED_100M( GPIOC_NC_2           )      \
                            | PIN_OSPEED_100M( GPIOC_NC_3           )      \
                            | PIN_OSPEED_100M( GPIOC_NC_4           )      \
                            | PIN_OSPEED_100M( GPIOC_NC_5           )      \
                            | PIN_OSPEED_100M( GPIOC_DEBUG_TX       )      \
                            | PIN_OSPEED_100M( GPIOC_DEBUT_RX       )      \
                            | PIN_OSPEED_100M( GPIOC_NC_8           )      \
                            | PIN_OSPEED_100M( GPIOC_NC_9           )      \
                            | PIN_OSPEED_100M( GPIOC_RESISTOR_3     )      \
                            | PIN_OSPEED_100M( GPIOC_RESISTOR_2     )      \
                            | PIN_OSPEED_100M( GPIOC_RESISTOR_1     )      \
                            | PIN_OSPEED_100M( GPIOC_NC_13          )      \
                            | PIN_OSPEED_100M( GPIOC_NC_14          )      \
                            | PIN_OSPEED_100M( GPIOC_NC_15          ) )

#define VAL_GPIOC_PUPDR     ( PIN_PUPDR_PULLDOWN( GPIOC_NC_0           )   \
                            | PIN_PUPDR_FLOATING( GPIOC_ADC_VBAT       )   \
                            | PIN_PUPDR_PULLDOWN( GPIOC_NC_2           )   \
                            | PIN_PUPDR_PULLDOWN( GPIOC_NC_3           )   \
                            | PIN_PUPDR_PULLDOWN( GPIOC_NC_4           )   \
                            | PIN_PUPDR_PULLDOWN( GPIOC_NC_5           )   \
                            | PIN_PUPDR_FLOATING( GPIOC_DEBUG_TX       )   \
                            | PIN_PUPDR_PULLUP(   GPIOC_DEBUT_RX       )   \
                            | PIN_PUPDR_PULLDOWN( GPIOC_NC_8           )   \
                            | PIN_PUPDR_PULLDOWN( GPIOC_NC_9           )   \
                            | PIN_PUPDR_FLOATING( GPIOC_RESISTOR_3     )   \
                            | PIN_PUPDR_FLOATING( GPIOC_RESISTOR_2     )   \
                            | PIN_PUPDR_FLOATING( GPIOC_RESISTOR_1     )   \
                            | PIN_PUPDR_PULLDOWN( GPIOC_NC_13          )   \
                            | PIN_PUPDR_PULLDOWN( GPIOC_NC_14          )   \
                            | PIN_PUPDR_PULLDOWN( GPIOC_NC_15          ) )

#define VAL_GPIOC_ODR       ( PIN_ODR_LOW(  GPIOC_NC_0           )          \
                            | PIN_ODR_LOW(  GPIOC_ADC_VBAT       )          \
                            | PIN_ODR_LOW(  GPIOC_NC_2           )          \
                            | PIN_ODR_LOW(  GPIOC_NC_3           )          \
                            | PIN_ODR_LOW(  GPIOC_NC_4           )          \
                            | PIN_ODR_LOW(  GPIOC_NC_5           )          \
                            | PIN_ODR_LOW(  GPIOC_DEBUG_TX       )          \
                            | PIN_ODR_LOW(  GPIOC_DEBUT_RX       )          \
                            | PIN_ODR_LOW(  GPIOC_NC_8           )          \
                            | PIN_ODR_LOW(  GPIOC_NC_9           )          \
                            | PIN_ODR_LOW(  GPIOC_RESISTOR_3     )          \
                            | PIN_ODR_LOW(  GPIOC_RESISTOR_2     )          \
                            | PIN_ODR_LOW(  GPIOC_RESISTOR_1     )          \
                            | PIN_ODR_LOW(  GPIOC_NC_13          )          \
                            | PIN_ODR_LOW(  GPIOC_NC_14          )          \
                            | PIN_ODR_LOW(  GPIOC_NC_15          ) )

#define VAL_GPIOC_AFRL      ( PIN_AFIO_AF( GPIOC_NC_0           ,  0)      \
                            | PIN_AFIO_AF( GPIOC_ADC_VBAT       ,  0)      \
                            | PIN_AFIO_AF( GPIOC_NC_2           ,  0)      \
                            | PIN_AFIO_AF( GPIOC_NC_3           ,  0)      \
                            | PIN_AFIO_AF( GPIOC_NC_4           ,  0)      \
                            | PIN_AFIO_AF( GPIOC_NC_5           ,  0)      \
                            | PIN_AFIO_AF( GPIOC_DEBUG_TX       ,  8)      \
                            | PIN_AFIO_AF( GPIOC_DEBUT_RX       ,  8) )
#define VAL_GPIOC_AFRH      ( PIN_AFIO_AF( GPIOC_NC_8           ,  0)      \
                            | PIN_AFIO_AF( GPIOC_NC_9           ,  0)      \
                            | PIN_AFIO_AF( GPIOC_RESISTOR_3     ,  0)      \
                            | PIN_AFIO_AF( GPIOC_RESISTOR_2     ,  0)      \
                            | PIN_AFIO_AF( GPIOC_RESISTOR_1     ,  0)      \
                            | PIN_AFIO_AF( GPIOC_NC_13          ,  0)      \
                            | PIN_AFIO_AF( GPIOC_NC_14          ,  0)      \
                            | PIN_AFIO_AF( GPIOC_NC_15          ,  0) )


// GPIO D

#define VAL_GPIOD_MODER     ( PIN_MODE_ALTERNATE( GPIOD_NC_2 ) )

#define VAL_GPIOD_OTYPER    ( PIN_OTYPE_PUSHPULL( GPIOD_NC_2 ) )

#define VAL_GPIOD_OSPEEDR   ( PIN_OSPEED_100M( GPIOD_NC_2 ) )

#define VAL_GPIOD_PUPDR     ( PIN_PUPDR_PULLUP( GPIOD_NC_2 ) )

#define VAL_GPIOD_ODR       ( PIN_ODR_LOW( GPIOD_NC_2 ) )

#define VAL_GPIOD_AFRL      ( PIN_AFIO_AF( GPIOD_NC_2,  0) )

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


void led_heartbeat(bool en);
void led_error(bool en);

void pwr_sensors(bool en);
void heat_resistor_1(bool en);
void heat_resistor_2(bool en);
void heat_resistor_3(bool en);
void heat_resistor_4(bool en);

#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */

#endif /* _BOARD_H_ */
