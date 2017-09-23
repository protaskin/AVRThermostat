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
	DISPLAY_4_MASK,
	DISPLAY_3_MASK,
	DISPLAY_2_MASK,
	DISPLAY_1_MASK
};

const uint8_t display_numbers_map[] = {
	DISPLAY_CHAR_0,
	DISPLAY_CHAR_1,
	DISPLAY_CHAR_2,
	DISPLAY_CHAR_3,
	DISPLAY_CHAR_4,
	DISPLAY_CHAR_5,
	DISPLAY_CHAR_6,
	DISPLAY_CHAR_7,
	DISPLAY_CHAR_8,
	DISPLAY_CHAR_9
};

uint8_t display_register[DISPLAY_REGISTER_SIZE];
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

	if (display_register_index == DISPLAY_REGISTER_SIZE) {
		display_register_index = 0;
	}
}

void display_drop_register(void)
{
	display_register_index = 0;

	for (uint8_t i = 0; i < DISPLAY_REGISTER_SIZE; i++) {
		display_register[i] = DISPLAY_CHAR_BLANK;
	}
}
