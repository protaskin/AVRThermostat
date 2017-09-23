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
bool button_is_pressed(const volatile uint8_t *pin, uint8_t bit);

/**
 * Usage:
 *
 *		if (button_is_pressed(&PORTA, PA1)) {
 *			// Do something
 *			while (!button_is_released(&PORTA, PA1));
 *		}
 */
bool button_is_released(const volatile uint8_t *pin, uint8_t bit);

/**
 * Usage:
 *
 *		bool reset;
 *
 *		for (;;) {
 *			reset = true;
 *			if (button_is_pressed(&PORTA, PA1)) {
 *				do {
 *					// Do something
 *				} while (button_being_pressed(&PORTA, PA1, &reset));
 *			}
 *		}
 */
bool button_being_pressed(const volatile uint8_t *pin, uint8_t bit, bool *reset);

#endif /* BUTTONS_H */
