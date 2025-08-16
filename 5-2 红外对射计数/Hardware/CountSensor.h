#ifndef __COUNT_SENSOR_H
#define __COUNT_SENSOR_H

#include "stm32f10x.h"

extern uint16_t count;

void CountSensor_Init(void);
uint16_t CountSensor_GetCount(void);
void EXTI9_5_IRQHandler(void);



#endif
