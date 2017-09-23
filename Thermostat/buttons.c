/*
 * This file is part of AVRThermostat.
 *
 * (c) Artyom Protaskin <a.protaskin@gmail.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

#include <stdbool.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/io.h>

#include "buttons.h"

bool button_is_pressed(const volatile uint8_t * const pin, const uint8_t bit)
{
	uint8_t count;

	if (*pin & _BV(bit)) {
		return false;
	}

	count = 0;
	for (uint8_t i = 0; i < 10 || count; i++) {
		_delay_ms(5);

		if (*pin & _BV(bit)) {
			count = 0;
		} else if (++count == 10) {
			return true;
		}
	}

	return false;
}

bool button_is_released(const volatile uint8_t * const pin, const uint8_t bit)
{
	return (*pin & _BV(bit));
}

static uint8_t calc_pressed_button_delay(const bool reset)
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

bool button_being_pressed(const volatile uint8_t * const pin, const uint8_t bit, bool * const reset)
{
	uint8_t delay;
	bool released;

	released = false;
	delay = calc_pressed_button_delay(*reset);
	for (uint8_t i = 0; i < delay && !released; i++) {
		released = (*pin & _BV(bit));
		_delay_ms(1);
	}

	*reset = released;

	return !released;
}
