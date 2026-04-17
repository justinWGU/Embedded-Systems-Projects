#include "main.h"
#include "stdbool.h"

void setup_pins(void);
bool soundBuzzer = false;

int main(void) {
	HAL_Init();
	setup_pins();

	while(1) {
		if (soundBuzzer) {
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_12);
			soundBuzzer = false;
		}
	}
}

void setup_pins(void) {
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	// init button as interrupt source
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
	GPIO_InitStruct.Pin = GPIO_PIN_13;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	// enable interrupt at nvic level
	HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

	// init buzzer pin
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pin = GPIO_PIN_12;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);

}

void EXTI15_10_IRQHandler(void) {
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
}

void HAL_GPIO_EXTI_Callback (uint16_t GPIO_Pin) {
	if (GPIO_Pin == GPIO_PIN_13) {
		soundBuzzer = true;
	}
}


