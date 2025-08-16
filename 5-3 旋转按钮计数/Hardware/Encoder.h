#ifndef _ENCODER_H__
#define _ENCODER_H__

#include "stm32f10x.h"

void Encoder_Init(void);
int16_t Encoder_GetCount(void);
void EXTI0_IRQHandler(void);
void EXTI15_10_IRQHandler(void);

#endif
