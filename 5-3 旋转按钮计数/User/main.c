#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Encoder.h"

int main()
{
	OLED_Init();
	Encoder_Init();

	int16_t Num = 0;
	int16_t Encoder_Count_Temp = 0;
	
	OLED_ShowString(1,1,"Count: ");
	OLED_ShowString(2,1,"Encoder: ");
	while(1)
	{
		Encoder_Count_Temp = 0; // 初始化临时计数值		
		Encoder_Count_Temp = Encoder_GetCount(); // 获取编码器计数值
		if(Encoder_Count_Temp != 0) // 如果计数值不为0
		{
			Num += Encoder_Count_Temp; // 累加计数值
		}
		OLED_ShowSignedNum(2,10,Encoder_Count_Temp,5); // 调试数据
		OLED_ShowSignedNum(1,7,Num,5);
		Delay_ms(50); // 延时100毫秒
	}
}//所有STM32工程都得在最后留一行


