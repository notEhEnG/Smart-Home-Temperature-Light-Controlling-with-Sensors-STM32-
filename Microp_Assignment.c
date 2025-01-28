#include "Microp_Assignment.h"
#include "DHT11.h"  // Custom DHT11 library

// Thresholds
#define TEMP_THRESHOLD 30.0f  // Celsius
#define LIGHT_THRESHOLD 200   // ADC value

// Function prototypes
void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_ADC1_Init(void);
float Read_Temperature(void);
uint16_t Read_Light(void);
void Control_Fan(float temperature);
void Control_Light(uint16_t light_value);

// Global variables
ADC_HandleTypeDef hadc1;

int main(void) {
    // Initialize HAL Library
    HAL_Init();
    // Configure system clock
    SystemClock_Config();
    // Initialize peripherals
    MX_GPIO_Init();
    MX_ADC1_Init();

    float temperature;
    uint16_t light_value;

    while (1) {
        // Read sensors
        temperature = Read_Temperature();
        light_value = Read_Light();

        // Control outputs
        Control_Fan(temperature);
        Control_Light(light_value);

        HAL_Delay(1000);  // Delay for 1 second
    }
}

void MX_GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Enable GPIO clocks
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // Configure PB0 and PB1 as output for LEDs (Fan and Light)
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void MX_ADC1_Init(void) {
    ADC_ChannelConfTypeDef sConfig = {0};

    // Enable ADC1 clock
    __HAL_RCC_ADC1_CLK_ENABLE();

    // Configure ADC1
    hadc1.Instance = ADC1;
    hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
    hadc1.Init.Resolution = ADC_RESOLUTION_12B;
    hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc1.Init.ScanConvMode = DISABLE;  // Scan mode disabled
    hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
    hadc1.Init.ContinuousConvMode = ENABLE;  // Continuous conversion mode
    hadc1.Init.DiscontinuousConvMode = DISABLE;
    hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    hadc1.Init.DMAContinuousRequests = DISABLE;
    HAL_ADC_Init(&hadc1);

    // Configure ADC channel
    sConfig.Channel = ADC_CHANNEL_1;  // Channel 1 on PA1
    sConfig.Rank = 1;  // Rank 1 (replaces ADC_REGULAR_RANK_1)
    sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;
    HAL_ADC_ConfigChannel(&hadc1, &sConfig);

    // Start ADC
    HAL_ADC_Start(&hadc1);
}



float Read_Temperature(void) {
    DHT11_Init();  // Initialize DHT11
    return DHT11_ReadTemperature();  // Read temperature from DHT11
}

uint16_t Read_Light(void) {
    // Wait for ADC conversion to complete
    HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
    // Return ADC conversion result
    return HAL_ADC_GetValue(&hadc1);
}

void Control_Fan(float temperature) {
    if (temperature >= TEMP_THRESHOLD) {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);  // Turn on Fan LED
    } else {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);  // Turn off Fan LED
    }
}

void Control_Light(uint16_t light_value) {
    if (light_value < LIGHT_THRESHOLD) {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);  // Turn on Light LED
    } else {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);  // Turn off Light LED
    }
}

void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    // Configure main internal regulator output voltage
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    // Initialize RCC Oscillators
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLM = 16;
    RCC_OscInitStruct.PLL.PLLN = 336;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
    RCC_OscInitStruct.PLL.PLLQ = 7;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }

    // Initialize CPU, AHB, and APB busses clocks
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK |
                                  RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
        Error_Handler();
    }
}

void Error_Handler(void) {
    while (1) {
        // Stay here for debugging
    	// printf("Temperature: %.2f°C\n", temperature);

    }
}


