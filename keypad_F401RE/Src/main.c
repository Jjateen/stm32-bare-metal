#include <stdint.h>
#include <stdio.h>

// GPIOC base address and register offsets
#define GPIOC_BASE          0x40020800
#define RCC_AHB1ENR         (*(volatile uint32_t *)0x40023830)

#define GPIOC_MODER         (*(volatile uint32_t *)(GPIOC_BASE + 0x00))
#define GPIOC_PUPDR         (*(volatile uint32_t *)(GPIOC_BASE + 0x0C))
#define GPIOC_IDR           (*(volatile uint32_t *)(GPIOC_BASE + 0x10))
#define GPIOC_ODR           (*(volatile uint32_t *)(GPIOC_BASE + 0x14))

// Constants
#define ROWS                4
#define COLS                4
#define GPIOC_CLOCK_ENABLE  (1 << 2)

void delay(void) {
    for (volatile uint32_t i = 0; i < 400000; i++);
}

int main(void) {
    // Enable GPIOC peripheral clock
    RCC_AHB1ENR |= GPIOC_CLOCK_ENABLE;

    // Configure ROW pins (PC0-PC3) as output and COLUMN pins (PC4-PC7) as input with pull-up resistors
    GPIOC_MODER &= 0xFFFF0000; // Clear lower 16 bits
    GPIOC_MODER |= 0x00000055; // Set PC0-PC3 as output

    GPIOC_PUPDR &= 0xFFFF0000; // Clear lower 16 bits
    GPIOC_PUPDR |= 0x00005500; // Enable pull-up resistors for PC4-PC7

    while (1) {
        // Scan each row
        for (int row = 0; row < ROWS; row++) {
            GPIOC_ODR |= 0x0F;            // Set all rows high
            GPIOC_ODR &= ~(1 << row);     // Set the current row low

            // Check each column
            for (int col = 0; col < COLS; col++) {
                if (!(GPIOC_IDR & (1 << (col + 4)))) { // Check column input
                    delay(); // De-bounce delay
                    printf("%d \n", row * COLS + col + 1); // Print key number
                }
            }
        }
    }
}
