//PC0 -PC7  --D0-D7 IN LCD
//PB5 -RS
//PB6 -RW
//PB7 -EN

#include <stdint.h>
uint32_t *pAHB1ENR = (uint32_t*) 0x40023830;
uint32_t *pAPB2ENR = (uint32_t*) 0x40023844;
uint32_t *pGPIOB_MODER = (uint32_t*) 0x40020400;
uint32_t *pGPIOC_MODER = (uint32_t*) 0x40020800;
uint32_t *pGPIOB_ODR = (uint32_t*) 0x40020414;
uint32_t *pGPIOC_ODR = (uint32_t*) 0x40020814;
uint32_t *pGPIOB_BSRR = (uint32_t*) 0x40020418;
uint32_t *pGPIOC_BSRR = (uint32_t*) 0x40020818;

#define RS 0x20 //0010 0000
#define RW 0x40 //0100 0000
#define EN 0x80  //1000 0000

unsigned char Message[] = ("Car");
void GPIO_Init(void);
void LCD_Command(unsigned char command);
void LCD_Data(unsigned char data);
void LCD_Init(void);
void delayMs(int delay);

int main(void) {
	LCD_Init();
	for (;;)
		;
}

void GPIO_Init(void) {
	*pAHB1ENR |= 0X06;
	*pGPIOB_MODER |= 0X5400;
	*pGPIOC_MODER |= 0X00005555;
	*pGPIOB_BSRR = 0X00C; //SET EN AND RW LOW

}
void LCD_Command(unsigned char command) {
	// RS=0  RW=0
	*pGPIOB_BSRR = (RS | RW) << 16;
	*pGPIOC_ODR = command;
	*pGPIOB_BSRR = EN; //ENABLE EN
	delayMs(0);
	*pGPIOB_BSRR = EN << 16; //clear EN
	//delayMs(30);
}

void LCD_Data(unsigned char data) {
	//RS=1 ,RW=0
	*pGPIOB_BSRR = RS;
	*pGPIOB_BSRR = RW << 16;
	*pGPIOC_ODR = data;
	*pGPIOB_BSRR = EN; //ENABLE EN
	delayMs(30);
	*pGPIOB_BSRR = EN << 16; //clear EN
	delayMs(30);
}

void LCD_Init(void) {
	unsigned char i = 0;

	GPIO_Init();
	LCD_Command(0x38); //set b it data mode
	delayMs(20);
	LCD_Command(0x0c); //set b it data mode
	delayMs(20);
	LCD_Command(0x06); //move the cursor right
	delayMs(20);
	LCD_Command(0x01); //clear screen move cursor home
	delayMs(20);
	delayMs(5000);

	LCD_Command(0x80); //turn display
	delayMs(20);
	while (Message[i] != '\0') {
		LCD_Data(Message[i]);
		i++;
	}
	delayMs(50);
	LCD_Command(0xC0); //turn display
	delayMs(20);
}
void delayMs(int delay) {
	int i;
	for (; delay > 0; delay--) {
		for (i = 0; i < 3195; i++) {}
	}
}
