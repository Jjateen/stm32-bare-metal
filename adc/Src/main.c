#include <stdint.h>
#include <stdio.h>

uint32_t *pAHB1ENR = (uint32_t*) 0x40023830;
uint32_t *pAPB2ENR = (uint32_t*) 0x40023844;
uint32_t *pGIPOMODER = (uint32_t*) 0x40020000;
uint32_t *pADC_SR = (uint32_t*) 0x40012000;
uint32_t *pADC_CR2 = (uint32_t*) 0x40012008;
uint32_t *pADC_SQR3 = (uint32_t*) 0x40012034;
uint32_t *pADC_DR = (uint32_t*) 0x4001204c;
uint16_t analogValue;
void ADC_Init();
void delay();
void ADC_Init() {
	*pAHB1ENR |= 1; //enable the clock access for GPIOA
	*pAPB2ENR |= 0X100; //enable the clock access for ADC1
	*pGIPOMODER |= 0XC; //CONFIGURE GPIOA FOR ANALOG
	*pADC_CR2 = 0;
	*pADC_SQR3 = 1;
	*pADC_CR2 |= 1;
}

void delay() {
	for (uint32_t i = 0; i < 300000; i++);
}

int main(void) {
	printf("Display ADC Value \n");
	ADC_Init();

	while (1) {
		//start the ADC conversion
		*pADC_CR2 |= 0x40000000;
		while (!(*pADC_SR & 2)) {
		} //wait till the end of conversion
		analogValue = *pADC_DR;
		printf("Display ADC Value  %d\n", analogValue);
		delay();
	}
	for (;;);
}
