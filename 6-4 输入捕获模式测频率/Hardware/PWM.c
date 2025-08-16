#include "stm32f10x.h"

/*
* @brief  PWM初始化
* @param  None
* @retval None
*/
void PWM_Init(void)
{

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

    //使用PA0是因为PA0是TIM2的通道1的引脚，也就是GPIO和TIM2共用这个引脚
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

    /*配置时钟源*/
	TIM_InternalClockConfig(TIM2);		//选择TIM2为内部时钟，若不调用此函数，TIM默认也为内部时钟

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period=1000 - 1;//ARR
    TIM_TimeBaseStructure.TIM_Prescaler=72 - 1;//PSC
    TIM_TimeBaseStructure.TIM_RepetitionCounter= 0;
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);

    TIM_OCInitTypeDef TIM_OCInitStruct;
    TIM_OCStructInit(&TIM_OCInitStruct);

    TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM1;
    TIM_OCInitStruct.TIM_OCNPolarity=TIM_OCNPolarity_High;
    TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;
    TIM_OCInitStruct.TIM_Pulse=0;//CCR

    // 启用PWM通道1
    TIM_OC1Init(TIM2, &TIM_OCInitStruct);

    TIM_Cmd(TIM2,ENABLE);
}

/*
* @brief  PWM设置占空比
* @param  compare:占空比
* @retval None
*/
void PWM_SetCCR(uint32_t compare)
{
    TIM_SetCompare1(TIM2,compare);
}

/*
* @brief  PWM设置时钟分频
* @param  prescaler:时钟分频
* @retval None
* @note 注意此函数不处理prescaler-1的逻辑，请自行-1.否则会影响实际设置的值
* @warning 预分频范围:0-65535，不能为0
*/
void PWM_SetPrescaler(uint32_t prescaler)
{
    TIM_PrescalerConfig(TIM2, prescaler, TIM_PSCReloadMode_Immediate);  
}
