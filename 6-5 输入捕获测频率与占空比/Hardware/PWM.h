#ifndef _PWM_H_
#define _PWM_H_ 
#define PWM_Compare_MIN 0

void PWM_Init(void);
void PWM_SetCCR(uint32_t compare);
void PWM_SetPrescaler(uint32_t prescaler);
int8_t PWM_Voltage_Control(int32_t compare_change);
uint32_t PWM_GetCompare(void);

#endif
