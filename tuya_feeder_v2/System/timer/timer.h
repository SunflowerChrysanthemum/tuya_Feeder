#ifndef __TIMER_H
#define __TIMER_H

#include "stm32f10x.h"
#include "stdint.h"
#include "HX711.h"
#include "protocol.h"

extern uint8_t total_weight;
extern uint8_t tub_weight;
extern uint8_t flag_auto, flag_small, flag_middle, flag_big;

void timer2_Init(void);
void timer3_Init(void);
void Rotate_value(uint8_t val);

#endif
