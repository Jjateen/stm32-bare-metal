#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "stm32f4xx.h"

unsigned char command_basic_1[5] = "AT\r\n"; // BASIC
unsigned char command_basic_2[9] = "AT+RST\r\n"; // BASIC
unsigned char command_ESP_1[14] = "AT+CWMODE=1\r\n"; // WIFI
unsigned char command_ESP_2[14] = "AT+CWQAP\r\n"; // WIFI
unsigned char command_ESP_4[25] = "AT+CWDHCP=1,1\r\n"; // THINGS SPEAK
unsigned char command_ESP_3[50] = "AT+CWJAP=\"your_ssid\",\"your_password\"\r\n"; // WIFI ACCESS
unsigned char command_ESP_5[50] =
		"AT+CIPSTART=\"TCP\",\"184.106.153.149\",80\r\n"; // THINGS SPEAK
unsigned char command_ESP_6[20] = "AT+CIPSEND=64\r\n"; // THINGS SPEAK SEND DATA
unsigned char command_ESP_7[64] = "GET /update?api_key=your_api_key&field1="; // API KEY FIELD1
unsigned char command_ESP_8[9] = "&field2="; // ADDITIONAL FIELD2
unsigned char command_ESP_9[9] = "\r\n\r\n"; // END OF DATA
unsigned char command_ESP_10[20] = "AT+CIPCLOSE\r\n"; // CLOSE CONNECTION
unsigned char data_string[8];

void UART1_Init();
void UART1_Write(char data);
char UART1_Read();
void Delay_ms(int delay);
void integer_to_ascii(unsigned int Val, unsigned char *str);
void Basic_Commands(void);
void Wifi_Conn_Commands(void);
void Wifi_acc(void);
void Thing_Speak_Command_Start(void);
void Init_ESP8266(void);

void Basic_Commands(void) {
	//"AT\r\n"; // BASIC
	printf("%s", command_basic_1);
	Delay_ms(500);
	//"AT+RST\r\n";//BASIC
	printf("%s", command_basic_2);
	Delay_ms(1000);
}

void Wifi_Conn_Commands(void) {
	//"AT+CWMODE=1\r\n";//WIFI
	printf("%s", command_ESP_1);
	Delay_ms(500);
	//"AT+CWQAP\r\n";//WIFI
	printf("%s", command_ESP_2);
	Delay_ms(500);

}

void Wifi_acc(void) {
	//"AT+CWJAP=\"jj\",\"12345678\"\r\n"; // WIFI ACC;
	printf("%s", command_ESP_3);
	Delay_ms(8000);
}

void Thing_Speak_Command_Start(void) {
	//"AT+CWDHCP=1,1\r\n";//THINGS SPEAK
	printf("%s", command_ESP_4);
	Delay_ms(5000);

}

void Data_Commands() {
	//"AT+CIPSTART=\"TCP\",\"184.106.153.149\",80\r\n";
	printf("%s", command_ESP_5);
	Delay_ms(5000);
	//"AT+CIPSEND=64\r\n";
	printf("%s", command_ESP_6);
	Delay_ms(5000);
	//"GET /update?api_key=your_api_key&field1=";
	printf("%s", command_ESP_7);

	printf("%s", data_string);
	//"\r\n\r\n";
	printf("%s", command_ESP_9);
	Delay_ms(1000);
	//"AT+CIPCLOSE\r\n"
	printf("%s", command_ESP_10);
	Delay_ms(5000);
}

void Init_ESP8266(void) {
	Delay_ms(5000);
	Basic_Commands();
	Wifi_Conn_Commands();
}

void integer_to_ascii(unsigned int Val, unsigned char *str) {
	str[0] = Val / 1000 + 0x30;
	Val = Val % 1000;
	str[1] = Val / 100 + 0x30;
	Val = Val % 100;
	str[2] = Val / 10 + 0x30;
	str[3] = Val % 10 + 0x30;
	str[4] = '\0';
}

void Delay_ms(int delay) {
	int i;
	for (; delay > 0; delay--) {
		for (i = 0; i < 3195; i++) {

		}
	}
}

char UART1_Read() {
	while (!(USART1->SR & 0X0020)) {
	}
	return USART1->DR;

}

void UART1_Write(char data) {
	while (!(USART1->SR & 0X0080)) {
	}
	USART1->DR = (data & 0xff);
}

void UART1_Init() {
	//enable the clock access for GPIOA,GPIOB
	RCC->AHB1ENR |= (1U << 1); //GPIO B
	RCC->APB2ENR |= (1U << 4); //USART1

	//SET ALT FUNCTION FOR PB6->TX AND PB7-RX
	GPIOB->MODER |= (1U << 13);
	GPIOB->MODER &= ~(1U << 12);
	GPIOB->MODER |= (1U << 15);
	GPIOB->MODER &= ~(1U << 14);

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

	USART1->BRR = 0X008B; //115200 BAUD RATE
}

int __io_putchar(char ch) {
	UART1_Write(ch);
	return ch;
}

int main(void) {
//	char data;
	unsigned int Data_Adc;
	//UART INITIALIZATION
	UART1_Init();
	//ESP8266 INITIALIZTION
	Init_ESP8266();
	//WIFI ACCOUNT & PASSWORD
	Wifi_acc();
	//THINGSPEAK COMMAND
	Thing_Speak_Command_Start();
	Delay_ms(500);
	Data_Adc = 30;
	//INTEGER TO ASCII
	integer_to_ascii(Data_Adc, data_string);
	//DATA COMMAND
	Data_Commands();
	Delay_ms(500);
	Thing_Speak_Command_Start();
	Delay_ms(500);
	Data_Adc = 60;
	//INTEGER TO ASCII
	integer_to_ascii(Data_Adc, data_string);
	//DATA COMMAND
	Data_Commands();
	Delay_ms(500);
	printf("\n END \n");
	for (;;)
		;
}
