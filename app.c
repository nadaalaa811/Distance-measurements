/*
 * app.c
 *
 *  Created on: Oct 13, 2022
 *      Author: Nada
 */
#include "lcd.h"
#include <avr/io.h>        /* To use the SREG register */
#include "HC_SR04_sensor.h"

int main() {
	uint16 distance = 0;
	SREG |= (1 << 7); /* Enable Global Interrupt I-Bit */
	LCD_init();
	Ultrasonic_init();
	LCD_displayString("Distance = ");
	while (1) {
		distance = Ultrasonic_readDistance(); /*Get calculated distance*/
		/* Display continuously on LCD screen */
		if (g_edgeCount == 3) {
			g_edgeCount = 0; /*To start detecting next high time*/
			LCD_moveCursor(2, 0);
			if (distance >= 100) {
				LCD_intgerToString(distance);
				LCD_displayString(" cm");
			} else if (distance >= 10) {
				LCD_intgerToString(distance);
				/* In case the digital value is two or one digits print space in the next digit place */
				LCD_displayString(" cm ");

			} else {
				LCD_intgerToString(distance);
				/* In case the digital value is two or one digits print space in the next digit place */
				LCD_displayString(" cm  ");
			}
		}
	}
	return 0;
}

