#include <stdint.h>
#include "stm32f4xx.h"
//PB6 (TX) - BT RX
//PB7 (RX) - BT TX
//PA5 - Relay Din
void UART_Init();
char UART_Read();
void UART_Write(char data);

char UART_Read() {
	while (!(USART1->SR & 0X0020)) {
	}
	return USART1->DR;

}

void UART_Write(char data) {
	while (!(USART1->SR & 0X0080)) {
	}
	USART1->DR = (data & 0xff);
}

void UART_Init() {
	//enable the clock access for GPIOA,GPIOB
	RCC->AHB1ENR |= (1U << 0); //GPIO A
	RCC->AHB1ENR |= (1U << 1); //GPIO B
	RCC->APB2ENR |= (1U << 4); //USART1

	//SET ALT FUNCTION FOR PB6->TX AND PB7-RX
	GPIOB->MODER |= (1U << 13);
	GPIOB->MODER &= ~(1U << 12);
	GPIOB->MODER |= (1U << 15);
	GPIOB->MODER &= ~(1U << 14);

	//SET PA5 IS OUTPUT CONNECTED TO RELAY
	GPIOA->MODER |= (1U << 10);
	GPIOA->MODER &= ~(1U << 11);

	GPIOB->AFR[0] |= (1U << 24);
	GPIOB->AFR[0] |= (1U << 25);
	GPIOB->AFR[0] |= (1U << 26);
	GPIOB->AFR[0] &= ~(1U << 27);

	GPIOB->AFR[0] |= (1U << 28);
	GPIOB->AFR[0] |= (1U << 29);
	GPIOB->AFR[0] |= (1U << 30);
	GPIOB->AFR[0] &= ~(1U << 31);

	USART1->CR1 |= (1U << 13);
	USART1->CR1 |= (1U << 2);
	USART1->CR1 |= (1U << 3);

	USART1->BRR = 0X0683; //9600 BAUD RATE
}

int main(void) {
	char Data;
	UART_Init();
	while (1) {
		Data = UART_Read();
		if (Data == 'A') {
			GPIOA->ODR &= ~(1U << 5);
			UART_Write(Data);
		} else {
			GPIOA->ODR |= (1U << 5);
			UART_Write(Data);
		}
	}
}
