#include "stm32f10x.h"                  // Device header
#include 

void delay_us(uint32_t us)
{
	SysTick->LOAD = us * 72 / 1000;
	SysTick->CTRL |= 0x01;
}
int main()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
    


	while(1)
	{
		
	}
}//所有STM32工程都得在最后留一行
