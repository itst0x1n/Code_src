/*
 * ledblink.h
 *
 *  Created on: Aug 1, 2024
 *      Author: pasha
 */

#ifndef LEDBLINK_H_
#define LEDBLINK_H_


typedef struct ledBlink{
	uint16_t blinkTime;
	uint16_t pin;
	GPIO_TypeDef* pinType;
}LedBlink;



void ledBlink(LedBlink *blink);


#endif /* LEDBLINK_H_ */
