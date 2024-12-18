#include <stdint.h>

// Constants for SysTick and GPIO configurations
#define SYSTICK_LOAD_VALUE 16000       // 1ms delay: delay_required * 16MHz
#define CTRL_ENABLE (1U << 0)          // Enable SysTick
#define CTRL_CLKSRC (1U << 2)          // Use processor clock
#define CTRL_COUNTFLAG (1U << 16)      // SysTick timer flag

#define GPIOAEN (1U << 0)              // Enable clock for GPIOA
#define LED (1U << 5)                  // Pin 5 for LED

// SysTick registers
uint32_t *pSTCSR = (uint32_t *)0xe000e010;  // Control and Status Register
uint32_t *pSTRVR = (uint32_t *)0xe000e014;  // Reload Value Register
uint32_t *pSTCVR = (uint32_t *)0xe000e018;  // Current Value Register

// GPIO registers
uint32_t *pAHB1ENR = (uint32_t *)0x40023830;    // AHB1 Enable Register
uint32_t *pGPIOAMODER = (uint32_t *)0x40020000; // GPIOA Mode Register
uint32_t *pGPIOAODR = (uint32_t *)0x40020014;   // GPIOA Output Data Register

// Delay function using SysTick
void systickdelayms(int delay)
{
    *pSTRVR = SYSTICK_LOAD_VALUE - 1;  // Set reload value
    *pSTCSR = CTRL_ENABLE | CTRL_CLKSRC; // Enable SysTick with clock source
    for (int i = 0; i < delay; i++) {
        while ((*pSTCSR & CTRL_COUNTFLAG) == 0); // Wait for timer flag
    }
    *pSTCSR = 0;  // Disable SysTick
}

int main(void)
{
    *pAHB1ENR |= GPIOAEN;             // Enable GPIOA clock
    *pGPIOAMODER |= (1U << 10);       // Set PA5 as output
    *pGPIOAMODER &= ~(1U << 11);

    while (1) {
        *pGPIOAODR ^= LED;           // Toggle LED
        systickdelayms(500);         // 500ms delay
    }
}
