#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include "delay.h"
#include <stdbool.h>
#include "ngat_timer3.h"
void config_usart(void);
void test(void);
void function_nutOne(void);
typedef struct Button{
	int ReadOne;
	int cntOne;
	bool one;
};
extern struct Button button;

