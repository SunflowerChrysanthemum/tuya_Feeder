#ifndef __HX711_H
#define	__HX711_H

#include "stm32f10x.h"
#include "delay.h"
#include <stdlib.h>
#include <string.h>

#define GapValue				100.01
#define MEDIAN_LEN 				5
#define MEDIAN 					(MEDIAN_LEN / 2)

#define HX711_CLK_SET			GPIO_SetBits(GPIOB,GPIO_Pin_6)
#define HX711_CLK_CLR			GPIO_ResetBits(GPIOB,GPIO_Pin_6)

#define HX711_DT_SET			GPIO_SetBits(GPIOB,GPIO_Pin_7)
#define HX711_DT_CLR			GPIO_ResetBits(GPIOB,GPIO_Pin_7)
#define HX711_DT_CHECK			GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7)


extern u32 Weight_Maopi;


void HX711_Init(void);
u32 HX711_Read(void);
void HX711_Maoqi(void);
float Get_Weight(void);
float KalmanFilter(float inData);

void bubbleSort(float *arr, uint8_t len);
float MedianFilter(float newData);

void print_buffer(void);

#endif
