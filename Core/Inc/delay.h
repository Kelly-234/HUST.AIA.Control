#ifndef __DELAY_H
#define __DELAY_H

#include "def.h"
#include "init.h"
#include "view.h"
#include "control.h"
#include "model.h"
#include "stm32g4xx_it.h"
void delay_init(uint8_t SYSCLK);
void delay_ms(uint16_t nms);
void delay_us(uint32_t nus);

#endif 