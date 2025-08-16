#include "stm32f10x.h"

void IC_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOA,&GPIO_InitStructure);

    TIM_InternalClockConfig(TIM3);

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period=65536 - 1;//ARR
    TIM_TimeBaseStructure.TIM_Prescaler=72 - 1;//PSC
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;            //重复计数器，高级定时器才会用到

    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);

    TIM_ICInitTypeDef TIM_ICInitStruct;
    TIM_ICInitStruct.TIM_Channel = TIM_Channel_1;
    TIM_ICInitStruct.TIM_ICFilter = 0xF;
    TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Rising;
    TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;

    TIM_ICInit(TIM3, &TIM_ICInitStruct);
    
    TIM_SelectInputTrigger(TIM3,TIM_TS_TI1FP1);
    TIM_SelectSlaveMode(TIM3,TIM_SlaveMode_Reset);

    TIM_Cmd(TIM3,ENABLE);
}

uint32_t IC_GetFrequency(void)
{
    return 1000000 / TIM_GetCapture1(TIM3);
}

