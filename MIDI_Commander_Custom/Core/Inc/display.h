/*
 * display.h
 *
 *  Created on: 8 Jul 2021
 *      Author: D Harvie
 */

#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_
//#include "ssd1306.h"

void display_init(void);
void display_setConfigName(void);
void display_setBankName(uint8_t bankNumber);
void display_expPedalsNumbers(uint32_t adcValue1, uint32_t adcValue2);
void display_debugMsg(char* message);
void display_fillBar(int16_t xArg, int16_t barHeight);
//void display_fillRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, SSD1306_COLOR color);
void display_exp1(uint16_t barHeight);
void display_exp2(uint16_t barHeight);
void display_exp_pedals(uint16_t barHeight1, uint16_t barHeight2);

// Util functions
uint16_t getAdcValueInInterval(uint16_t value, uint16_t interval);

#endif /* INC_DISPLAY_H_ */
