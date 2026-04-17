#include "main.h"
#include "stdbool.h"

void setup_pins(); // init pin for LED
void setup_timer();

TIM_HandleTypeDef htim2; // timer peripheral struct
volatile bool toggleLED = false; // var needs volatile since it can change asynchronously

int main(void) {
	HAL_Init();
	setup_pins();
	setup_timer();

	while (1) {
		if (toggleLED) {
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
			toggleLED = false;
		}
	}
}

void setup_timer(void) {
	// configure timer
	htim2.Instance = TIM2; // physical timer addr
	htim2.Init.Prescaler = 160 - 1; // 16 MHZ / 160 = 100,000 Hz (1 MHz)
	htim2.Init.Period = 100000 - 1; // 1 MHz / 100,000 = 1 Hz (1 second)

	__HAL_RCC_TIM2_CLK_ENABLE(); // enable peripheral clock on APB1 bus (16 MHz)
	HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(TIM2_IRQn); // enable TIM2 interrupt at NVIC level
	HAL_TIM_Base_Init(&htim2);
	HAL_TIM_Base_Start_IT(&htim2); // start timer in interrupt mode
}

void setup_pins(void) {
	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Pin = GPIO_PIN_5;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET); // init LED to "off"
}

// handle Timer's ISR
void TIM2_IRQHandler(void) {
	HAL_TIM_IRQHandler(&htim2); // HAL handles peripheral-level code and calls callback
}

// Tim's ISR's callback
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim) {
	if (htim->Instance == TIM2) {
		toggleLED = true;
	}
}

