#include "stm32f10x.h"                  // Device header
#include "button.h"

int main(void)
{
	delay_init();
	config_usart();
	SetSystem72Mhz();
	ConfigureTimer3();
	while(1)
	{
		function_nutOne();
//		if(button.cntOne==1)
//		{
//			test();
//			DelayMs(1000);
//		}
	}
	
}
