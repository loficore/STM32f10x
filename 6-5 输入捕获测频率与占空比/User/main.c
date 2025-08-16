#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "IC.h"
#include "PWM.h"

int main()
{
	OLED_Init();
	PWM_Init();
	IC_Init();

	PWM_SetCCR(500);
	PWM_SetPrescaler(72 - 1);

	// OLED_ShowString(2,1,"The current duty");
	// OLED_ShowChar(3,3,'.');
	// OLED_ShowChar(3,5,'%');
	//11.111%
	
	while(1)
	{
		OLED_ShowNum(2,1,IC_GetFrequency(),4);
		OLED_ShowNum(3,1,IC_GetDutyCycle(),2);
	}
}//所有STM32工程都得在最后留一行
