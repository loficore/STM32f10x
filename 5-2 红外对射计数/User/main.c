#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "CountSensor.h"

int main()
{
	OLED_Init();
	CountSensor_Init();
	
	OLED_ShowString(1,1,"Count: ");
	while(1)
	{
		
		OLED_ShowNum(1,7,CountSensor_GetCount(),5);
	}
}//所有STM32工程都得在最后留一行


