#include "DHT11.h"
#include <string.h>  // For memset

static void DHT11_SetPinOutput(void);
static void DHT11_SetPinInput(void);
static uint8_t DHT11_ReadByte(void);
static uint8_t DHT11_CheckResponse(void);

void DHT11_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Initialize GPIO for DHT11
    __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitStruct.Pin = DHT11_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(DHT11_PORT, &GPIO_InitStruct);

    // Ensure the pin is HIGH initially
    HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, GPIO_PIN_SET);
}

float DHT11_ReadTemperature(void) {
    uint8_t buffer[5] = {0};

    // Send start signal
    DHT11_SetPinOutput();
    HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, GPIO_PIN_RESET);
    HAL_Delay(DHT11_START_SIGNAL_LOW_TIME);
    HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, GPIO_PIN_SET);
    HAL_Delay(1);

    // Switch to input mode and wait for response
    DHT11_SetPinInput();
    if (!DHT11_CheckResponse()) {
        return -1.0f;  // Error
    }

    // Read 5 bytes from DHT11
    for (int i = 0; i < 5; i++) {
        buffer[i] = DHT11_ReadByte();
    }

    // Verify checksum
    uint8_t checksum = buffer[0] + buffer[1] + buffer[2] + buffer[3];
    if (checksum != buffer[4]) {
        return -1.0f;  // Error
    }

    // Extract temperature
    return (float)buffer[2];
}

float DHT11_ReadHumidity(void) {
    uint8_t buffer[5] = {0};

    // Send start signal
    DHT11_SetPinOutput();
    HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, GPIO_PIN_RESET);
    HAL_Delay(DHT11_START_SIGNAL_LOW_TIME);
    HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, GPIO_PIN_SET);
    HAL_Delay(1);

    // Switch to input mode and wait for response
    DHT11_SetPinInput();
    if (!DHT11_CheckResponse()) {
        return -1.0f;  // Error
    }

    // Read 5 bytes from DHT11
    for (int i = 0; i < 5; i++) {
        buffer[i] = DHT11_ReadByte();
    }

    // Verify checksum
    uint8_t checksum = buffer[0] + buffer[1] + buffer[2] + buffer[3];
    if (checksum != buffer[4]) {
        return -1.0f;  // Error
    }

    // Extract humidity
    return (float)buffer[0];
}

static void DHT11_SetPinOutput(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = DHT11_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(DHT11_PORT, &GPIO_InitStruct);
}

static void DHT11_SetPinInput(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = DHT11_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(DHT11_PORT, &GPIO_InitStruct);
}

static uint8_t DHT11_CheckResponse(void) {
    uint32_t timeout = DHT11_TIMEOUT;

    // Wait for the sensor to pull the line low
    while (HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN) == GPIO_PIN_SET) {
        if (timeout-- == 0) {
            return 0;  // No response
        }
    }

    timeout = DHT11_TIMEOUT;
    // Wait for the sensor to pull the line high
    while (HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN) == GPIO_PIN_RESET) {
        if (timeout-- == 0) {
            return 0;  // No response
        }
    }

    return 1;  // Response detected
}

static uint8_t DHT11_ReadByte(void) {
    uint8_t data = 0;

    for (int i = 0; i < 8; i++) {
        // Wait for the pin to go high
        while (HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN) == GPIO_PIN_RESET);

        // Wait for 40us to determine the bit value
        HAL_Delay(1);  // Roughly 40us delay
        if (HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN) == GPIO_PIN_SET) {
            data |= (1 << (7 - i));  // Set the bit
        }

        // Wait for the pin to go low
        while (HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN) == GPIO_PIN_SET);
    }

    return data;
}
