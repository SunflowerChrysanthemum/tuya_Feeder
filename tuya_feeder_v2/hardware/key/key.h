#ifndef __KEY_H
#define __KEY_H	 
#include "stm32f10x.h"

#define KEY1    GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11) //��ȡ����1


void KEY_Init(void);//IO��ʼ��
void LCD_Init(void);
void LCD_Change(void);

#endif

