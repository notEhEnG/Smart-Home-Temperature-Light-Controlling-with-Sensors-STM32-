#ifndef DHT11_H
#define DHT11_H

#include "stm32f4xx_hal.h"
#include <stdint.h>

// Define the GPIO port and pin connected to the DHT11 sensor
#define DHT11_PORT GPIOB
#define DHT11_PIN GPIO_PIN_0

// Timing constraints for DHT11 communication
#define DHT11_START_SIGNAL_LOW_TIME 18  // milliseconds
#define DHT11_TIMEOUT 100  // microseconds

typedef struct {
    float Temperature;
    float Humidity;
} DHT11_Data_t;

/**
 * @brief Initialize the GPIO pin for the DHT11 sensor.
 */
void DHT11_Init(void);

/**
 * @brief Read data from the DHT11 sensor.
 * @return Temperature in Celsius (if successful) or -1.0f (if there is an error).
 */
float DHT11_ReadTemperature(void);

/**
 * @brief Read humidity from the DHT11 sensor.
 * @return Humidity in percentage (if successful) or -1.0f (if there is an error).
 */
float DHT11_ReadHumidity(void);

#endif // DHT11_H
