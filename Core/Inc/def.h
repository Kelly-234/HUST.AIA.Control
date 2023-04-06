#ifndef __DEF_H
#define __DEF_H

#include "stm32g4xx_hal.h"
#include "spi_tftlcd.h"

#define LCD_RST_Pin GPIO_PIN_4
#define LCD_RST_GPIO_Port GPIOA
#define LCD_RS_Pin GPIO_PIN_6
#define LCD_RS_GPIO_Port GPIOA

#define KEYS_PUSHING0 (!HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1))
#define KEYS_PUSHING1 (!HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0))
#define KEYS_PUSHING2 (!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3))
#define KEYS_PUSHING3 (!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4))

#define KEYON 1
#define KEYOFF 0

#endif