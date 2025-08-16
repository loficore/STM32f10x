#include "Timer.h"

uint16_t Timer_Count=0;

/* @brief  定时器初始化
*  @retval 无
*  @note   这里使用的是外部时钟
*/
void Timer_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    

    //其实应该最好使用浮空输出，但是上拉输入也可以
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    TIM_ETRClockMode2Config(TIM2,TIM_ExtTRGPSC_OFF,TIM_ExtTRGPolarity_NonInverted,0x0F);//注意TIM2的ETR引脚固定为PA0，无法随意更改


    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

    TIM_TimeBaseStructure.TIM_Prescaler=1 - 1;
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period=10 - 1;
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_RepetitionCounter= 0;
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);

    TIM_ClearFlag(TIM2, TIM_IT_Update);
    //设置为更新中断
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
    NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;

    NVIC_Init(&NVIC_InitStructure);

    TIM_Cmd(TIM2,ENABLE);
}

/*  @brief  获取计数器的值
 *  @retval 返回计数器的值
 *  @note   无
 */
uint16_t Get_CNT_Counter()
{
    return TIM_GetCounter(TIM2);
}

/* @brief  定时器中断处理函数
*  @retval 无
*  @note   无
*/
void TIM2_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)
    {
        Timer_Count++;
        TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
    }
}
