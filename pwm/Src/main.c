#include <stdint.h>
#include "stm32f4xx.h"

// Function to configure PWM with desired frequency and duty cycle
void PWM_Init(uint32_t frequency, float duty_cycle) {
	uint32_t timer_clk = 16000000;
	uint32_t prescaler;
	uint32_t auto_reload;

	// Calculate prescaler and auto-reload values for desired frequency
	prescaler = 10 - 1; // Fixed prescaler for simplicity
	auto_reload = (timer_clk / (prescaler + 1)) / frequency - 1;

	// Enable clock access for GPIOA
	RCC->AHB1ENR |= 0x01;
	// Enable clock access for TIM2
	RCC->APB1ENR |= 0x01;

	// Configure PA5 as alternate function (TIM2_CH1)
	GPIOA->MODER |= 0x00000800;  // Set PA5 to alternate function mode
	GPIOA->AFR[0] |= 0x00100000; // Set alternate function for TIM2_CH1

	// Configure TIM2 for PWM
	TIM2->PSC = prescaler;          // Set prescaler
	TIM2->ARR = auto_reload;        // Set auto-reload value (frequency)
	TIM2->CNT = 0;                  // Reset counter
	TIM2->CCMR1 = 0x0060;           // Set PWM mode 1 on CH1
	TIM2->CCER = 1;                 // Enable CH1 output
	TIM2->CCR1 = (uint32_t) (auto_reload * duty_cycle / 100); // Set duty cycle
	TIM2->CR1 = 1;                  // Enable the timer
}

int main(void) {
	uint32_t frequency = 2000; // Desired frequency in Hz
	float duty_cycle = 50;  // Desired duty cycle in percentage

	// Initialize PWM with specified frequency and duty cycle
	PWM_Init(frequency, duty_cycle);

	while (1) {
		// Main loop
	}
}
