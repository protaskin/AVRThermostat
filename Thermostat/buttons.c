/*
 * This file is part of AVRThermostat.
 *
 * (c) Artyom Protaskin <a.protaskin@gmail.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

#include <stddef.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/io.h>

#include "buttons.h"

uint8_t button_is_pressed(const volatile uint8_t * const pin, const uint8_t mask)
{
	uint8_t count;

	if (*pin & (1 << mask)) {
		return 0;
	}

	count = 0;
	for (size_t i = 0; i < 10 || count; i++) {
		_delay_ms(5);

		if (*pin & (1 << mask)) {
			count = 0;
		} else if (++count == 10) {
			return 1;
		}
	}

	return 0;
}

uint8_t button_is_released(const volatile uint8_t * const pin, const uint8_t mask)
{
	return (*pin & (1 << mask));
}

static uint8_t calc_pressed_button_delay(const uint8_t reset)
{
	static uint8_t count;
	static uint8_t compare;
	static uint8_t delay;

	if (reset) {
		count = 0;
		compare = 8;
		delay = 255; // 0xFF
	}

	if (compare && count++ == compare) {
		count = 0;
		compare *= 2;
		delay /= 2;
	}

	return delay;
}

uint8_t button_being_pressed(const volatile uint8_t * const pin, const uint8_t mask, uint8_t * const reset)
{
	uint8_t delay;
	uint8_t released;

	released = 0;
	delay = calc_pressed_button_delay(*reset);
	for (size_t i = 0; i < delay && !released; i++) {
		released = (*pin & (1 << mask));
		_delay_ms(1);
	}

	*reset = released;

	return !released;
}
