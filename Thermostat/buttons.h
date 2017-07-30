/*
 * This file is part of AVRThermostat.
 *
 * (c) Artyom Protaskin <a.protaskin@gmail.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

#ifndef BUTTONS_H
#define BUTTONS_H

/**
 * Usage:
 *
 *		if (button_is_pressed(&PORTA, PA1)) {
 *			// Do something
 *		}
 */
uint8_t button_is_pressed(const volatile uint8_t *pin, const uint8_t mask);

/**
 * Usage:
 *
 *		if (button_is_pressed(&PORTA, PA1)) {
 *			// Do something
 *			while (!button_is_released(&PORTA, PA1));
 *		}
 */
uint8_t button_is_released(const volatile uint8_t *pin, const uint8_t mask);

/**
 * Usage:
 *
 *		uint8_t reset;
 *
 *		for (;;) {
 *			reset = 1;
 *			if (button_is_pressed(&PORTA, PA1)) {
 *				do {
 *					// Do something
 *				} while (button_being_pressed(&PORTA, PA1, &reset));
 *			}
 *		}
 */
uint8_t button_being_pressed(const volatile uint8_t *pin, const uint8_t mask, uint8_t *reset);

#endif /* BUTTONS_H */
