#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"

uint16_t i = 0;

int main()
{
	OLED_Init();
	PWM_Init();
	
	while(1)
	{
		for(i = 0;i < 100;i++)
		{
			PWM_SetCCR(i);
			Delay_ms(10);
		}
		for(i = 100;i > 0;i--)
		{
			PWM_SetCCR(i);
			Delay_ms(10);
		}
	}
}//所有STM32工程都得在最后留一行
