#include "ngat_timer3.h"
#include "button.h"
void SetSystem72Mhz(void)
{
	// NHAN 9 VOI TAN SO 
	RCC->CFGR |= (7<<18); // or RCC->CFGR |= RCC_CFGR_PLLMULL9;
	// CHIA CHO 1.5 
	RCC->CFGR &= ~ (1<<22);
	// SET HSEON 
	RCC->CR |= (1<<16);
	// WAIT HSERDY 
	while((RCC->CR & RCC_CR_HSERDY)==0);
	// PLL FOR MODE HSE 
	RCC->CFGR |= (1<<16);
	
	// TUONG TU VOI HSE TA KICH HOAT PLLON VA CHO NO READY
	RCC->CR |= RCC_CR_PLLON;
	while((RCC->CR & RCC_CR_PLLRDY)==0);
	//Flash pre-fetch enable and wait-state=2
	  //0WS: 0-24MHz
	  //1WS: 24-48MHz
	  //2WS: 48-72MHz
	FLASH->ACR |= FLASH_ACR_PRFTBE|FLASH_ACR_LATENCY_1;
	 //Select PLL as main System Clock source
	RCC->CFGR &= ~ RCC_CFGR_SW;
	RCC->CFGR |= RCC_CFGR_SW_PLL;
	//Wait until PLL system source is active
	while((RCC->CFGR & RCC_CFGR_SWS)!=RCC_CFGR_SWS_PLL);
	
	// AHB DIV1
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;
	// APB1 DIV 2
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;
	// APP2 DIV 1
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;
	// ADC PSC = 6 , 2X6 = 12 
	RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;
	
	// khong anh xa lai ma pin CHO TIM2 
	AFIO->MAPR |= AFIO_MAPR_TIM2_REMAP_NOREMAP;
}
void TIM3_IRQHandler(void)
{
	if(TIM3->SR & TIM_SR_UIF)
	{
		if(button.cntOne==1)
		{
			GPIOA->ODR ^= (1<<6);
		}
		//GPIOA->ODR ^= (1<<6);
		TIM3->SR &= ~TIM_SR_UIF;
	}
}
void ConfigureTimer3(void)
{
	RCC->APB1ENR |= (1<<1); // timer 3 
	TIM3->PSC = 7199; 
	TIM3->ARR = 999; // 0.1s 
	TIM3->DIER |= (1<<0); // enable interrupt timer 3
	TIM3->SR &= ~(1<<0); // clear co ngat 
	NVIC_EnableIRQ(TIM3_IRQn); 
	TIM3->CR1 |= (1<<0); // enable interrupt timer 3 
}