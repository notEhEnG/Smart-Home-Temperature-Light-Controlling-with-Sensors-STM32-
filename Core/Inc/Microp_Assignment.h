#ifndef __MICROP_ASSIGNMENT_H
#define __MICROP_ASSIGNMENT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"  // HAL library for STM32F4
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_adc.h"

// Add other HAL headers if required
// #include "stm32f4xx_hal_tim.h"   // For Timer
// #include "stm32f4xx_hal_uart.h"  // For UART

// Macros for LED control
#define FAN_LED_PIN GPIO_PIN_0       // Fan LED is on PB0
#define FAN_LED_PORT GPIOB

#define LIGHT_LED_PIN GPIO_PIN_1     // Light LED is on PB1
#define LIGHT_LED_PORT GPIOB

// ADC Input Pin
#define LIGHT_SENSOR_PIN GPIO_PIN_1  // Analog input on PA1
#define LIGHT_SENSOR_PORT GPIOA

// Function Prototypes
void Error_Handler(void);

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
