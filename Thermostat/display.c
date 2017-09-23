/*
 * This file is part of AVRThermostat.
 *
 * (c) Artyom Protaskin <a.protaskin@gmail.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

#include <stdint.h>
#include <avr/io.h>

#include "display.h"

const uint8_t display_digits_map[] = {
	DISPLAY_4,
	DISPLAY_3,
	DISPLAY_2,
	DISPLAY_1
};

const uint8_t display_numbers_map[] = {
	DISPLAY_A | DISPLAY_B | DISPLAY_C | DISPLAY_D | DISPLAY_E | DISPLAY_F, // 0
	DISPLAY_B | DISPLAY_C, // 1
	DISPLAY_A | DISPLAY_B | DISPLAY_D | DISPLAY_E | DISPLAY_G, // 2
	DISPLAY_A | DISPLAY_B | DISPLAY_C | DISPLAY_D | DISPLAY_G, // 3
	DISPLAY_B | DISPLAY_C | DISPLAY_F | DISPLAY_G, // 4
	DISPLAY_A | DISPLAY_C | DISPLAY_D | DISPLAY_F | DISPLAY_G, // 5
	DISPLAY_A | DISPLAY_C | DISPLAY_D | DISPLAY_E | DISPLAY_F | DISPLAY_G, // 6
	DISPLAY_A | DISPLAY_B | DISPLAY_C, // 7
	DISPLAY_A | DISPLAY_B | DISPLAY_C | DISPLAY_D | DISPLAY_E | DISPLAY_F | DISPLAY_G, // 8
	DISPLAY_A | DISPLAY_B | DISPLAY_C | DISPLAY_D | DISPLAY_F | DISPLAY_G // 9
};

uint8_t display_register[DISPLAY_DIGITS_COUNT];
uint8_t display_register_index;

void display_init(void)
{
	DISPLAY_SEGMENTS_DDR |= DISPLAY_SEGMENTS_MASK;
	DISPLAY_SEGMENTS_PORT &= ~DISPLAY_SEGMENTS_MASK;

	DISPLAY_DIGITS_DDR &= ~DISPLAY_DIGITS_MASK;
	DISPLAY_DIGITS_PORT &= ~DISPLAY_DIGITS_MASK;
}

void display_show(void)
{
	DISPLAY_SEGMENTS_PORT = display_register[display_register_index];
	DISPLAY_DIGITS_DDR |= display_digits_map[display_register_index];
}

void display_hide(void)
{
	DISPLAY_SEGMENTS_PORT = DISPLAY_CHAR_BLANK;
	DISPLAY_DIGITS_DDR &= ~display_digits_map[display_register_index];
}

void display_next(void)
{
	display_register_index++;

	if (display_register_index == DISPLAY_DIGITS_COUNT) {
		display_register_index = 0;
	}
}

void display_drop_register(void)
{
	display_register_index = 0;

	for (uint8_t i = 0; i < DISPLAY_DIGITS_COUNT; i++) {
		display_register[i] = DISPLAY_CHAR_BLANK;
	}
}
