
#include <stdint.h>


int main(void)
{
	uint32_t *AHB1ENR  =(uint32_t*)0x40023830;
	uint32_t *MODER  =(uint32_t*)0x40020000;
	uint32_t *ODR  =(uint32_t*)0x40020014;


	*AHB1ENR |=0x01;
	*MODER &=0xFFFFF3FF;

	*MODER |=0x00000400;

	*ODR|=0x20;
	for(;;);
}
