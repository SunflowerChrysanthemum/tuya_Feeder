#ifndef __SYS_H
#define __SYS_H	 

#include "stm32f10x.h"
#include "delay.h"
#include "usart.h"


typedef void(*pctr) (void);

void NVIC_Config(void);

#endif
