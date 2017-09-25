/*
 * This file is part of AVRThermostat.
 *
 * (c) Artyom Protaskin <a.protaskin@gmail.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

#define TIMER1_SHOW_TEMP_BIT    0
#define TIMER1_CONTROL_TEMP_BIT 1

#include <stdbool.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "buttons.h"
#include "display.h"
#include "config.h"
#include "ds18b20.h"
#include "iodef.h"

static uint8_t timer1_status;
static volatile uint16_t temp = 0xDEAD;

static const uint8_t * const numbers = display_numbers_map;

/**
 * Разбивает значение, считанное из температурного регистра на рязряды и
 * заполняет регистр дисплея.
 */
static void fill_display_register(uint16_t temp)
{
	bool sign;
	uint8_t int_part, frac_numer;

	if (temp == DS18B20_ERROR) {
		display_register[3] = DISPLAY_CHAR_BLANK;
		display_register[2] = DISPLAY_CHAR_E;
		display_register[1] = DISPLAY_CHAR_R;
		display_register[0] = DISPLAY_CHAR_R;
		return;
	}

	// Определение знака
	sign = ((temp & 0xF800) == 0xF800);
	if (sign) {
		// Преобразование из дополнительного представления числа в прямое
		temp = ~temp + 1;
	}

	// Выделение целой части
	int_part = (temp & 0x07F0) >> 4;

	// Выделение дробной части
	frac_numer = (temp & 0x0F) * 625 / 100;
	frac_numer = frac_numer / 10 + (frac_numer % 10 >= 5);

	// Заполнение регистра дисплея
	if (int_part >= 100) {
		display_register[3] = numbers[1];
	} else if (sign && int_part >= 10) {
		display_register[3] = DISPLAY_CHAR_MINUS;
	} else {
		display_register[3] = DISPLAY_CHAR_BLANK;
	}

	if (int_part >= 10) {
		display_register[2] = numbers[int_part % 100 / 10];
	} else if (sign) {
		display_register[2] = DISPLAY_CHAR_MINUS;
	} else {
		display_register[2] = DISPLAY_CHAR_BLANK;
	}

	display_register[1] = numbers[int_part % 10] | DISPLAY_CHAR_POINT;
	display_register[0] = numbers[frac_numer];
}

/**
 * Считывает содержимое температурного регистра. Вызывается 1 раз в 2 с.
 */
ISR(TIMER1_COMPA_vect)
{
	uint16_t trigger_on;
	uint16_t trigger_off;

	temp = ds18b20_read_temp();

	if (timer1_status & _BV(TIMER1_SHOW_TEMP_BIT)) {
		fill_display_register(temp);
	}

	if (timer1_status & _BV(TIMER1_CONTROL_TEMP_BIT)) {
		trigger_on = task - zone / 2;
		trigger_off = task + zone / 2;

		// If temp >= MIN_TEMP is true, temp is negative,
		// If temp <= MAX_TEMP is true, temp is positive.
		if (temp >= MIN_TEMP) {
			if (trigger_on <= MAX_TEMP || temp <= trigger_on) {
				LED_PORT |= _BV(LED_BIT);
				RELAY_PORT |= _BV(RELAY_BIT);
			} else if (trigger_off >= MIN_TEMP && temp >= trigger_off) {
				LED_PORT &= ~_BV(LED_BIT);
				RELAY_PORT &= ~_BV(RELAY_BIT);
			}
		} else {
			if (trigger_on <= MAX_TEMP && temp <= trigger_on) {
				LED_PORT |= _BV(LED_BIT);
				RELAY_PORT |= _BV(RELAY_BIT);
			} else if (trigger_off >= MIN_TEMP || temp >= trigger_off) {
				LED_PORT &= ~_BV(LED_BIT);
				RELAY_PORT &= ~_BV(RELAY_BIT);
			}
		}
	}
}

/**
 * Отображает содержимое регистра дисплея. Вызывается 1 раз в 100 мкс.
 */
ISR(TIMER2_COMP_vect)
{
	static uint8_t i = 0;

	if (i == 0) {
		display_show();
	}

	if (i == brightness) {
		display_hide();
		display_next();
	}

	i++;
	i &= 0x0F; // 16 -> 0
}

static void show_temp()
{
	timer1_status |= _BV(TIMER1_SHOW_TEMP_BIT);
	fill_display_register(temp);

	for (;;) {
		if (button_is_pressed(&BUTTONS_PIN, MINUS_BUTTON_BIT)) {
			if (brightness > MIN_BRIGHTNESS) {
				brightness--;
				config_update();
			}
			while (!button_is_released(&BUTTONS_PIN, MINUS_BUTTON_BIT));
		} else if (button_is_pressed(&BUTTONS_PIN, PLUS_BUTTON_BIT)) {
			if (brightness < MAX_BRIGHTNESS) {
				brightness++;
				config_update();
			}
			while (!button_is_released(&BUTTONS_PIN, PLUS_BUTTON_BIT));
		} else if (button_is_pressed(&BUTTONS_PIN, SET_BUTTON_BIT)) {
			while (!button_is_released(&BUTTONS_PIN, SET_BUTTON_BIT));
			break;
		}
	}

	timer1_status &= ~_BV(TIMER1_SHOW_TEMP_BIT);
}

static void change_task()
{
	bool reset;

	fill_display_register(task);

	for (;;) {
		reset = true;
		if (button_is_pressed(&BUTTONS_PIN, MINUS_BUTTON_BIT)) {
			do {
				if (task <= MAX_TEMP || task > MIN_TEMP) {
					fill_display_register(--task);
				}
			} while (button_being_pressed(&BUTTONS_PIN, MINUS_BUTTON_BIT, &reset));
		} else if (button_is_pressed(&BUTTONS_PIN, PLUS_BUTTON_BIT)) {
			do {
				if (task < MAX_TEMP || task >= MIN_TEMP) {
					fill_display_register(++task);
				}
			} while (button_being_pressed(&BUTTONS_PIN, PLUS_BUTTON_BIT, &reset));
		} else if (button_is_pressed(&BUTTONS_PIN, SET_BUTTON_BIT)) {
			while (!button_is_released(&BUTTONS_PIN, SET_BUTTON_BIT));
			return;
		} else if (button_is_pressed(&BUTTONS_PIN, RESET_BUTTON_BIT)) {
			task = DEFAULT_TASK;
			fill_display_register(task);
			while (!button_is_released(&BUTTONS_PIN, RESET_BUTTON_BIT));
		}
	}
}

static void change_zone()
{
	bool reset;

	fill_display_register(zone);

	for (;;) {
		reset = true;
		if (button_is_pressed(&BUTTONS_PIN, MINUS_BUTTON_BIT)) {
			do {
				if (zone > MIN_ZONE) {
					fill_display_register(--zone);
				}
			} while (button_being_pressed(&BUTTONS_PIN, MINUS_BUTTON_BIT, &reset));
		} else if (button_is_pressed(&BUTTONS_PIN, PLUS_BUTTON_BIT)) {
			do {
				if (zone < MAX_ZONE) {
					fill_display_register(++zone);
				}
			} while (button_being_pressed(&BUTTONS_PIN, PLUS_BUTTON_BIT, &reset));
		} else if (button_is_pressed(&BUTTONS_PIN, SET_BUTTON_BIT)) {
			while (!button_is_released(&BUTTONS_PIN, SET_BUTTON_BIT));
			return;
		} else if (button_is_pressed(&BUTTONS_PIN, RESET_BUTTON_BIT)) {
			zone = DEFAULT_ZONE;
			fill_display_register(zone);
			while (!button_is_released(&BUTTONS_PIN, RESET_BUTTON_BIT));
		}
	}
}

static void control_temp()
{
	timer1_status |= _BV(TIMER1_SHOW_TEMP_BIT) | _BV(TIMER1_CONTROL_TEMP_BIT);
	fill_display_register(temp);

	LED_DDR |= _BV(LED_BIT);
	LED_PORT &= ~_BV(LED_BIT); // Включение индикации

	for (;;) {
		if (button_is_pressed(&BUTTONS_PIN, MINUS_BUTTON_BIT)) {
			if (brightness > MIN_BRIGHTNESS) {
				brightness--;
				config_update();
			}
			while (!button_is_released(&BUTTONS_PIN, MINUS_BUTTON_BIT));
		} else if (button_is_pressed(&BUTTONS_PIN, PLUS_BUTTON_BIT)) {
			if (brightness < MAX_BRIGHTNESS) {
				brightness++;
				config_update();
			}
			while (!button_is_released(&BUTTONS_PIN, PLUS_BUTTON_BIT));
		} else if (button_is_pressed(&BUTTONS_PIN, RESET_BUTTON_BIT)) {
			LED_DDR &= ~_BV(LED_BIT);
			LED_PORT &= ~_BV(LED_BIT);
			RELAY_PORT &= ~_BV(RELAY_BIT); // Выключение индикации и управления
			while (!button_is_released(&BUTTONS_PIN, RESET_BUTTON_BIT));
			break;
		}
	}

	timer1_status &= ~(_BV(TIMER1_SHOW_TEMP_BIT) | _BV(TIMER1_CONTROL_TEMP_BIT));
}

int main()
{
	uint8_t error;

	// Enable internal pull-up resistors
	BUTTONS_PORT |= _BV(MINUS_BUTTON_BIT) | _BV(PLUS_BUTTON_BIT) |
		_BV(SET_BUTTON_BIT) | _BV(RESET_BUTTON_BIT);

	// Конфигурация портов в/в
	RELAY_DDR = _BV(RELAY_BIT);

	// Конфигурация 16-битного счетчика
	OCR1AH = 0x3D;
	OCR1AL = 0x08; // Счет до 15625
	// WGM12 = 1 для сброса при совпадении (режим CTC)
	// CS12 = 1 и CS10 = 1 для предварительного деления на 1024
	TCCR1B = _BV(WGM12) | _BV(CS12) | _BV(CS10);
	TIMSK |= _BV(OCIE1A); // Включение прерывания по совпадению

	// Конфигурация 8-битного счетчика
	OCR2 = 0x18; // Счет до 25
	// WGM21 = 1 для сброса при совпадении (режим CTC)
	// CS21 = 1 и CS20 = 1 для предварительного деления на 32
	TCCR2 = _BV(WGM21) | _BV(CS21) | _BV(CS20);
	TIMSK |= _BV(OCIE2); // Включение прерывания по совпадению

	// Инициализация дисплея
	display_init();

	sei();

	error = config_read();
	if (error) {
		if (error & _BV(CONFIG_BAD_CHECKSUM_BIT)) {
			display_register[3] = DISPLAY_CHAR_BLANK;
			display_register[2] = DISPLAY_CHAR_C;
			display_register[1] = DISPLAY_CHAR_R;
			display_register[0] = DISPLAY_CHAR_C;
		}

		while (!button_is_pressed(&BUTTONS_PIN, RESET_BUTTON_BIT));
		while (!button_is_released(&BUTTONS_PIN, RESET_BUTTON_BIT));
	}

	// Skip the power-on reset value of the temperature
	ds18b20_read_temp();
	while (temp == 0xDEAD) {
		display_register[3] = DISPLAY_CHAR_L;
		display_register[2] = DISPLAY_CHAR_O;
		display_register[1] = DISPLAY_CHAR_A;
		display_register[0] = DISPLAY_CHAR_D;
	}

	while (true) {
		switch (action) {
			case 0:
				config_update();
				show_temp();
				break;
			case 1:
				change_task();
				break;
			case 2:
				change_zone();
				break;
			case 3:
				config_update();
				control_temp();
				break;
		}

		action++;
	}
}
