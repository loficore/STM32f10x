#ifndef _PWM_H_
#define _PWM_H_ 

void PWM_Init(void);
void PWM_SetCCR(uint32_t compare);
void PWM_SetPrescaler(uint32_t prescaler);

#endif
