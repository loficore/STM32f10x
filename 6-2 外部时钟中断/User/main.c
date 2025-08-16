#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"

uint16_t Num = 0;

int main()
{
	OLED_Init();
	Timer_Init();
	
	while(1)
	{
		Num = Get_CNT_Counter();

		OLED_ShowSignedNum(1,1,Timer_Count,5);
		OLED_ShowSignedNum(2,1,Num,5);	
	}
}//所有STM32工程都得在最后留一行
