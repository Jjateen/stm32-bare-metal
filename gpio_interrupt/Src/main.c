#include <stdint.h>
#include <stdio.h>

//enable ahb1 bus for gpio
uint32_t volatile *pAHBIENR =(uint32_t*)0x40023830;
//enable apb2 bus for exti

uint32_t volatile *pAPB2ENR =(uint32_t*)0x40023844;

uint32_t volatile *pGPIOC =(uint32_t*)0x40020800;

uint32_t volatile *pEXTIPR =(uint32_t*)0x40013c14;
uint32_t volatile *pEXTIMR =(uint32_t*)0x40013c00;
uint32_t volatile *pEXTIFTSR =(uint32_t*)0x40013c0c;
uint32_t volatile *pSYSCFG_EXTICR4=(uint32_t*)0x40013814;

uint32_t *pNVIC_ISER1=(uint32_t*)0xe000e104;

void Button_Init(void)
{
	*pAHBIENR |=(1U<<2);

	*pAPB2ENR  |=(1U<<14);

	*pSYSCFG_EXTICR4 |=(1U<<5);

	*pEXTIFTSR |=(1U<<13);
	*pEXTIMR |=(1U<<13);
	*pNVIC_ISER1 |=(1U<<8);

}

int main(void)
{
    /* Loop forever */
	Button_Init();
	while(1)
	{

	}

}

void EXTI15_10_IRQHandler(void)
{
	printf("Button is pressed \n");
	*pEXTIPR |=(1U<<13);
}
