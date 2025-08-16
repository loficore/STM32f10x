#ifndef _TIMER_H_
#define _TIMER_H_ 

#include "stm32f10x.h"

extern uint16_t Timer_Count;

void Timer_Init(void);
void TIM2_IRQHandler(void);

#endif
