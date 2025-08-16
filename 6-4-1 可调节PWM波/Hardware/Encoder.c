#include "stm32f10x.h"
#include "Delay.h"

int16_t Encoder_Count = 0; // 编码器计数值

/**
  * @brief  Encoder_Init
  * @note   初始化编码器
  * @param  None
  * @retval None
  */
void Encoder_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
    
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource10);

	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line0 | EXTI_Line10;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStructure);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

/*
* @brief  Encoder_GetCount
* @note   返回编码器计数值
* @param  None
*/
int16_t Encoder_GetCount(void)
{
	int16_t temp = Encoder_Count; // 获取当前计数值
	Encoder_Count = 0; // 清零计数值
	return temp; // 返回编码器计数值
}

int16_t Encoder_PWM_Control(void)
{
	uint16_t arr_value = TIM2->ARR;
	int16_t temp = Encoder_GetCount() * 5;

	if(temp > arr_value)
	{
		return arr_value;
	}
	else if(temp < -arr_value)
	{
		return -arr_value;
	}
	else
	{
		return temp;
	}
}

/*
* @brief  EXTI0_IRQHandler
* @note   This function handles the EXTI Line0 interrupt request.
* @param  None
*/
void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line0) == SET)
	{
		uint8_t b_level = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10);
		if (b_level == 0) Encoder_Count++; // 正转（A相下降沿时B相为低电平）
		else Encoder_Count--; // 反转（A相下降沿时B相为高电平）
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

/*
* @brief  EXTI15_10_IRQHandler
* @note   This function handles the EXTI Line10 interrupt request.
* @param  None
*/
void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line10) == SET)
	{
		uint8_t a_level = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0);
		if (a_level == 0) Encoder_Count--; // 反转（B相下降沿时A相为低电平）
		else Encoder_Count++;              // 正转（B相下降沿时A相为高电平）
		EXTI_ClearITPendingBit(EXTI_Line10);
	}
}
