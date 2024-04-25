#include "button.h"
struct Button button;
char buffer[1000];
void config_usart(void)
{
	button.cntOne=0;
	RCC->APB1ENR |= (1<<17); // usart2 
	RCC->APB2ENR |= (1<<2); // gpioa 
	GPIOA->CRL = 0x43448B48; // pa0,pa2,pa3,pa6 output 
	GPIOA->ODR |= (1<<0)|(1<<3);
	
	USART2->BRR=3750; // 9600 baud 
	USART2->CR1 |= (1<<13)|(1<<3)|(1<<2); // enable usart , transmistion enable, receive enable  
	
}
void sendByte(unsigned char c)
{
	USART2->DR =c;
	while((USART2->SR&(1<<6))==0);
	USART2->SR &= ~(1<<6);
}
void test(void)
{
	sprintf(buffer,"%s","test");
	int j=0;
	while(buffer[j]!='\0')
	{
		sendByte(buffer[j]);
		j++;
	}
	sendByte('\n');
	sendByte('\r');
}
int readInput(int bit)
{
	if((GPIOA->IDR&(1<<bit))==0)
		return 0;
	else 
		return 1;
}
void function_nutOne(void)
{
	button.ReadOne=readInput(0);
	if(!button.ReadOne)
	{
		button.one=true;
		return;
	}
	if(button.one)
	{
		button.cntOne+=1;
		button.one=false;
	}
	
}