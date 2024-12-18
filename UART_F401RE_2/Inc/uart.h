/*
 * uart.h
 *
 *  Created on: Dec 18, 2024
 *      Author: jjate
 */


#ifndef UART_H_
#define UART_H_

#include <stdint.h>

// Define GPIO and UART constants
#define GPIOAEN (1U << 0)
#define UART2EN (1U << 17)
#define SYS_FREQ 16000000
#define APB1_CLK SYS_FREQ
#define UART_BAUDRATE 115200

// Function prototypes
void uart2_write(int ch);
void uart2_tx_init(void);
uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t Baudrate);

#endif /* UART_H_ */
