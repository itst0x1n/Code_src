/*
 * ledblink.c
 *
 *  Created on: Aug 1, 2024
 *      Author: pasha
 */
#include "stm32f4xx_hal.h"
#include "ledblink.h"
#include "cmsis_os.h"


void ledBlink(int blinkTime, int pin, GPIO_TypeDef* pinType){
	HAL_GPIO_TogglePin(pinType, pin);
	osDelay(blinkTime);
 }

