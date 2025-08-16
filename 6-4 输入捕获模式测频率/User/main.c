#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"
#include "IC.h"

uint16_t i = 0;

int main()
{
	OLED_Init();
	PWM_Init();
	IC_Init();

	PWM_SetCCR(500);
	PWM_SetPrescaler(72 - 1);
	
	OLED_ShowString(2,1,"Freq:000000Hz");
	
	while(1)
	{
		OLED_ShowNum(2, 6, IC_GetFrequency(), 6);
		Delay_ms(50);
	}
}//所有STM32工程都得在最后留一行
