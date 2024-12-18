#include <stdint.h>

// Define macros for register addresses
#define RCC_AHB1ENR  (*(volatile uint32_t*)0x40023830)  // RCC AHB1 peripheral clock enable register
#define GPIOA_MODER  (*(volatile uint32_t*)0x40020000)  // GPIOA mode register
#define GPIOA_ODR    (*(volatile uint32_t*)0x40020014)  // GPIOA output data register

// Define bit positions for clarity
#define GPIOA_EN_BIT  (0)       // GPIOA enable bit in RCC_AHB1ENR
#define GPIOA_PIN5    (5)       // GPIOA pin 5 (LED pin)
#define GPIOA_PIN5_MODER_POS (10) // GPIOA pin 5 mode position in MODER register

// Simple delay function
void delay(void)
{
    for (uint32_t i = 0; i < 1500000; i++);
}

int main(void)
{
    // Enable GPIOA clock
    RCC_AHB1ENR |= (1 << GPIOA_EN_BIT);

    // Configure GPIOA pin 5 as output
    GPIOA_MODER &= ~(0x3 << GPIOA_PIN5_MODER_POS); // Clear mode bits for pin 5
    GPIOA_MODER |= (0x1 << GPIOA_PIN5_MODER_POS);  // Set pin 5 as output

    while (1)
    {
        // Turn on the LED (set pin 5 high)
        GPIOA_ODR |= (1 << GPIOA_PIN5);
        delay();

        // Turn off the LED (set pin 5 low)
        GPIOA_ODR &= ~(1 << GPIOA_PIN5);
        delay();
    }
}