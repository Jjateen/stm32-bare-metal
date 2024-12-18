/*
 * uart.c
 *
 *  Created on: Dec 18, 2024
 *      Author: jjate
 */

#include "uart.h"

// Register definitions for GPIOA and USART2
#define GPIOA_BASE 0x40020000
#define USART2_BASE 0x40004400
#define RCC_BASE 0x40023800

// Peripheral Register Offsets
#define RCC_AHB1ENR_OFFSET 0x30
#define RCC_APB1ENR_OFFSET 0x40
#define GPIOA_MODER_OFFSET 0x00
#define GPIOA_AFRL_OFFSET 0x20
#define USART_SR_OFFSET 0x00
#define USART_DR_OFFSET 0x04
#define USART_BRR_OFFSET 0x08
#define USART_CR1_OFFSET 0x0C

// Register pointers
volatile uint32_t *portaAHB1ENR = (uint32_t *)(RCC_BASE + RCC_AHB1ENR_OFFSET);
volatile uint32_t *apb1enr = (uint32_t *)(RCC_BASE + RCC_APB1ENR_OFFSET);
volatile uint32_t *gpioa_moder = (uint32_t *)(GPIOA_BASE + GPIOA_MODER_OFFSET);
volatile uint32_t *gpioa_afrl = (uint32_t *)(GPIOA_BASE + GPIOA_AFRL_OFFSET);
volatile uint32_t *usart2_sr = (uint32_t *)(USART2_BASE + USART_SR_OFFSET);
volatile uint32_t *usart2_dr = (uint32_t *)(USART2_BASE + USART_DR_OFFSET);
volatile uint32_t *usart2_brr = (uint32_t *)(USART2_BASE + USART_BRR_OFFSET);
volatile uint32_t *usart2_cr1 = (uint32_t *)(USART2_BASE + USART_CR1_OFFSET);

/**
 * Redirect `printf` to UART by writing to UART's transmit function.
 */
int __io_putchar(int ch) {
    uart2_write(ch);
    return ch;
}

/**
 * Initialize UART2 for transmission on PA2 (TX pin).
 */
void uart2_tx_init(void) {
    // Enable clock access to GPIOA
    *portaAHB1ENR |= GPIOAEN;

    // Set PA2 mode to Alternate Function Mode
    *gpioa_moder &= ~(1U << 4); // Clear bit 4
    *gpioa_moder |= (1U << 5);  // Set bit 5

    // Set PA2 alternate function type to UART_TX (AF7)
    *gpioa_afrl |= (1U << 8);  // AFRL[11:8] = 0111
    *gpioa_afrl |= (1U << 9);
    *gpioa_afrl |= (1U << 10);
    *gpioa_afrl &= ~(1U << 11);

    // Enable clock access to USART2
    *apb1enr |= UART2EN;

    // Set baud rate
    *usart2_brr = compute_uart_bd(APB1_CLK, UART_BAUDRATE);

    // Configure transfer direction and enable UART
    *usart2_cr1 |= 0x08;  // Enable TE (Transmit Enable)
    *usart2_cr1 |= 0x2000; // Enable USART (UE)
}

/**
 * Compute UART baud rate based on peripheral clock and baud rate.
 *
 * @param PeriphClk Peripheral clock frequency.
 * @param Baudrate Desired baud rate.
 * @return Calculated baud rate register value.
 */
uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t Baudrate) {
    return (uint16_t)((PeriphClk + (Baudrate / 2U)) / Baudrate);
}

/**
 * Write a character to the UART.
 *
 * @param ch Character to send.
 */
void uart2_write(int ch) {
    // Wait until the transmit data register is empty
    while (!(*usart2_sr & 0x0080)) {
        // Spin until TXE (Transmit Data Register Empty) is set
    }

    // Write the character to the data register
    *usart2_dr = (ch & 0xFF);
}
