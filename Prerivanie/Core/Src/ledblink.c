/*
 * ledblink.c
 *
 *  Created on: Aug 1, 2024
 *      Author: pasha
 */
#include "stm32f4xx_hal.h"
#include "ledblink.h"
#include "cmsis_os.h"



void ledBlink(LedBlink *blink){
	HAL_GPIO_TogglePin(blink -> pinType, blink -> pin);
	osDelay(blink -> blinkTime);
 }


