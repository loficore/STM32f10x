#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"

int main()
{
	OLED_Init();
	Timer_Init();
	
	while(1)
	{
		OLED_ShowSignedNum(1,1,Timer_Count,5);
		OLED_ShowSignedNum(2,1,TIM_GetCounter(TIM2),5);	
	}
}//所有STM32工程都得在最后留一行
