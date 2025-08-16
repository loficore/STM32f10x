#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"
#include "Encoder.h"

int8_t overflow_flag = 0;//占空比溢出标记

int main()
{
	OLED_Init();
	PWM_Init();
	Encoder_Init();//忘记加了

	PWM_SetCCR(500);
	PWM_SetPrescaler(72 - 1);

	// OLED_ShowString(2,1,"The current duty");
	OLED_ShowChar(3,3,'.');
	OLED_ShowChar(3,7,'%');
	//11.111%
	
	while(1)
	{
		int16_t Count = Encoder_PWM_Control();
	    
		overflow_flag = PWM_Voltage_Control(Count);

		if(overflow_flag)
		{
			OLED_ShowString(4,1,"Overflow!TOO HIGH!");
			Delay_ms(20);
			OLED_ShowString(4,1,"                ");
		}
		else if(overflow_flag == -1)
		{
			OLED_ShowString(4,1,"Overflow!TOO LOW!");
			Delay_ms(20);
			OLED_ShowString(4,1,"                ");
		}
		else
		{
			OLED_ShowString(4,1,"No Overflow");
		}

		OLED_ShowSignedNum(2,1,Count,5);

	    OLED_ShowNum(3,1,PWM_GetCompare()/100,2);
		OLED_ShowNum(3,4,PWM_GetCompare()%100,3);
		Delay_ms(100);
	}
}//所有STM32工程都得在最后留一行
