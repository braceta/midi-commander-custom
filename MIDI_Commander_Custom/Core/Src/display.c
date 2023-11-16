/*
 * display.c
 *
 *  Created on: 8 Jul 2021
 *      Author: D Harvie
 */
#include "main.h"
#include "flash_midi_settings.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "ssd1306.h"

void display_init(void) {
	ssd1306_Init();

	ssd1306_SetCursor(5, 22);
	//    ssd1306_WriteString(FIRMWARE_VERSION, Font_7x10, White);
	ssd1306_WriteString("Braceta Build 5", Font_7x10, White);

	// A little animation

	for (int i = 0; i < 11; i++) {
		ssd1306_SetCursor(i * 11, 0);
		ssd1306_WriteString("#", Font_11x18, White);
		ssd1306_SetCursor(i * 11, 46);
		ssd1306_WriteString("#", Font_11x18, White);

		ssd1306_UpdateScreen();
		HAL_Delay(50);
	}

	__NOP();
}

void display_setConfigName(void) {
	ssd1306_SetCursor(10, 34);
	for (int i = 0; i < 16; i++) {
		ssd1306_WriteChar(pGlobalSettings[16 + i], Font_7x10, White);
	}
	ssd1306_UpdateScreen();
}

const int SNAP_PERCENTAGE = 5;
char* getSnappedAdcValueInPercent(uint32_t value) {

	int percentage = (value * 100) / 4096;
	char *bufferPadded = (char*) malloc(4);

	if (percentage > 100 - SNAP_PERCENTAGE - 3) {
		snprintf(bufferPadded, 4, "100");
		return bufferPadded;
	}
	if (percentage < SNAP_PERCENTAGE) {
		snprintf(bufferPadded, 4, "  0");
		return bufferPadded;

	}

	if(percentage>=10) {
		snprintf(bufferPadded, 4, " %d", percentage);
	} else {
		snprintf(bufferPadded, 4, "  %d", percentage);
	}

//		int remainder = percentage % SNAP_PERCENTAGE;
//		int finalValue =
//				remainder < 3 ?
//						(percentage / SNAP_PERCENTAGE) * SNAP_PERCENTAGE :
//						((percentage + SNAP_PERCENTAGE) / SNAP_PERCENTAGE)
//								* SNAP_PERCENTAGE;
//		snprintf(buffer, 9, "%d%%", finalValue);

	return bufferPadded;
}

uint16_t getAdcValueInInterval(uint16_t value, uint16_t interval) {
	return (value * interval) / 4096;
}

void display_expPedalsNumbers(uint32_t adcValue1, uint32_t adcValue2) {
	ssd1306_Fill(Black);

	char *value1 = getSnappedAdcValueInPercent(adcValue1);
	char *value2 = getSnappedAdcValueInPercent(adcValue2);

	ssd1306_SetCursor(30, 10);
	ssd1306_WriteString("Exp Pedals", Font_7x10, White);

	ssd1306_SetCursor(30, 20);
	ssd1306_WriteString(value1, Font_11x18, White);

	ssd1306_SetCursor(30, 40);
	ssd1306_WriteString(value2, Font_11x18, White);

	ssd1306_UpdateScreen();
	free(value1);
	free(value2);
}

void display_debugMsg(char *message) {
	ssd1306_SetCursor(5, 0);
	ssd1306_WriteString(message, Font_6x8, White);
	ssd1306_UpdateScreen();

}
void display_setBankName(uint8_t bankNumber) {
	uint8_t *pString = pBankStrings + (24 * bankNumber);

	ssd1306_Fill(Black);

	ssd1306_SetCursor(10, 15);
	for (int i = 0; i < 8; i++) {
		ssd1306_WriteChar((char) *pString++, Font_11x18, White);
	}

	ssd1306_SetCursor(10, 35);
	for (int i = 0; i < 16; i++) {
		ssd1306_WriteChar((char) *pString++, Font_6x8, White);
	}

    ssd1306_UpdateScreen();
}

void display_fillRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h,
		SSD1306_COLOR color) {
	for (uint8_t i = y; i < y + h; i++) {
		ssd1306_Line(x, i, x + w, i, color);
	}
}

uint16_t barWidth = 5;
uint16_t displayWith = 126;

void display_fillBar(uint16_t xPos, uint16_t adcValue) {
	uint16_t x = xPos + 1;
	uint16_t height = 63;

	uint16_t padding = 1;
	uint16_t y = 0;

	ssd1306_DrawRectangle(x, y, x + barWidth, height, White);

	uint16_t barHeight = getAdcValueInInterval(adcValue, 64);
	if (barHeight > 3) {
		display_fillRect(x + padding, y + padding, barWidth - padding - 1,
				height - 2, Black);
		display_fillRect(x + padding + 1, height - barHeight - padding + 1,
				barWidth - padding - 3, barHeight - padding, White);
	}
	if(barHeight <= 3) {
		display_fillRect(x + padding, y + padding, barWidth - padding - 1,
				height - 2, Black);
	}

}

void display_exp1(uint16_t adcValue) {
	display_fillBar(displayWith-(barWidth*2)-2,adcValue);
}

void display_exp2(uint16_t adcValue) {
	display_fillBar(displayWith-barWidth,adcValue);
}

void display_exp_pedals(uint16_t adcValue1, uint16_t adcValue2) {
//	display_exp1(barHeight1);
	display_exp2(adcValue1);

	char value[5] = "";
	snprintf(value, 5, "%04d",adcValue1);

	ssd1306_SetCursor(95, 0);
	ssd1306_WriteString(value, Font_6x8, White);
//
//	char *value2 = getSnappedAdcValueInPercent(barHeight2);
//	ssd1306_SetCursor(30, 40);
//	ssd1306_WriteString(value2, Font_6x8, White);

	ssd1306_UpdateScreen();
}

