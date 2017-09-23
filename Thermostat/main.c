/*
 * This file is part of AVRThermostat.
 *
 * (c) Artyom Protaskin <a.protaskin@gmail.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

// Configuration

#define BUTTONS_DDR      DDRB
#define BUTTONS_PORT     PORTB
#define BUTTONS_PIN      PINB
#define MINUS_BUTTON_BIT PB1
#define PLUS_BUTTON_BIT  PB2
#define SET_BUTTON_BIT   PB3
#define RESET_BUTTON_BIT PB4

#define BUTTONS_MASK ((1 << MINUS_BUTTON_BIT) | (1 << PLUS_BUTTON_BIT) | \
                      (1 << SET_BUTTON_BIT) | (1 << RESET_BUTTON_BIT))

#define LED_DDR  DDRC
#define LED_PORT PORTC
#define LED_PIN  PINC
#define LED_BIT  PC0

#define RELAY_DDR  DDRC
#define RELAY_PORT PORTC
#define RELAY_PIN  PINC
#define RELAY_BIT  PC1

#define DEFAULT_TASK 0x0140 // 20
#define DEFAULT_ZONE 0x0008 // 0.5
#define DEFAULT_BRIGHTNESS 7 // 1/2

// End of configuration

#define IDLE_ACTION         0
#define SHOW_TEMP_ACTION    1
#define CONTROL_TEMP_ACTION 2

#define DISPLAY_CHAR_A (DISPLAY_A | DISPLAY_B | DISPLAY_C | DISPLAY_E | DISPLAY_F | DISPLAY_G)
#define DISPLAY_CHAR_D (DISPLAY_B | DISPLAY_C | DISPLAY_D | DISPLAY_E | DISPLAY_G)
#define DISPLAY_CHAR_E (DISPLAY_A | DISPLAY_D | DISPLAY_E | DISPLAY_F | DISPLAY_G)
#define DISPLAY_CHAR_L (DISPLAY_D | DISPLAY_E | DISPLAY_F)
#define DISPLAY_CHAR_O (DISPLAY_A | DISPLAY_B | DISPLAY_C | DISPLAY_D | DISPLAY_E | DISPLAY_F)
#define DISPLAY_CHAR_R (DISPLAY_E | DISPLAY_G)

#define ZERO_TEMP 0
#define MIN_TEMP 0xFC90 // -55
#define MAX_TEMP 0x07D0 // 125
#define MIN_ZONE 0x0001 // 1/16
#define MAX_ZONE 0x0640 // 100
#define MIN_BRIGHTNESS 1
#define MAX_BRIGHTNESS 15

#include <stddef.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "buttons.h"
#include "display.h"
#include "ds18b20.h"

uint8_t action;
uint8_t brightness;
uint16_t temp;
uint16_t task;
uint16_t zone;
uint8_t EEMEM ee_brightness = DEFAULT_BRIGHTNESS;
uint16_t EEMEM ee_task = DEFAULT_TASK;
uint16_t EEMEM ee_zone = DEFAULT_ZONE;

const uint8_t * const numbers = display_numbers_map;

/**
 * Разбивает значение, считанное из температурного регистра на рязряды и
 * заполняет регистр дисплея.
 */
void fill_display_register(uint16_t temp)
{
	uint8_t sign, integer, fractal;

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
	integer = (temp & 0x07F0) >> 4;

	// Выделение дробной части
	fractal = (temp & 0x0F) * 625 / 100;
	fractal = fractal / 10 + (fractal % 10 >= 5);

	// Заполнение регистра дисплея
	if (integer >= 100) {
		display_register[3] = numbers[1];
	} else if (sign && integer >= 10) {
		display_register[3] = DISPLAY_CHAR_MINUS;
	} else {
		display_register[3] = DISPLAY_CHAR_BLANK;
	}

	if (integer >= 10) {
		display_register[2] = numbers[integer % 100 / 10];
	} else if (sign) {
		display_register[2] = DISPLAY_CHAR_MINUS;
	} else {
		display_register[2] = DISPLAY_CHAR_BLANK;
	}

	display_register[1] = numbers[integer % 10] | DISPLAY_CHAR_POINT;
	display_register[0] = numbers[fractal];
}

/**
 * Считывает содержимое температурного регистра. Вызывается 1 раз в 2 с.
 */
ISR(TIMER1_COMPA_vect)
{
	uint16_t trigger_on;
	uint16_t trigger_off;

	temp = ds18b20_read_temp();
	if (action & SHOW_TEMP_ACTION) {
		fill_display_register(temp);
	}

	if (action & CONTROL_TEMP_ACTION) {
		trigger_on = task - zone / 2;
		trigger_off = task + zone / 2;

		// If temp >= MIN_TEMP is true, temp is negative,
		// If temp <= MAX_TEMP is true, temp is positive.
		if (temp >= MIN_TEMP) {
			if (trigger_on <= MAX_TEMP || temp <= trigger_on) {
				LED_PORT |= (1 << LED_BIT);
				RELAY_PORT |= (1 << RELAY_BIT);
			} else if (trigger_off >= MIN_TEMP && temp >= trigger_off) {
				LED_PORT &= ~(1 << LED_BIT);
				RELAY_PORT &= ~(1 << RELAY_BIT);
			}
		} else {
			if (trigger_on <= MAX_TEMP && temp <= trigger_on) {
				LED_PORT |= (1 << LED_BIT);
				RELAY_PORT |= (1 << RELAY_BIT);
			} else if (trigger_off >= MIN_TEMP || temp >= trigger_off) {
				LED_PORT &= ~(1 << LED_BIT);
				RELAY_PORT &= ~(1 << RELAY_BIT);
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

void show_temp()
{
	action = SHOW_TEMP_ACTION;

	for (;;) {
		if (button_is_pressed(&BUTTONS_PIN, MINUS_BUTTON_BIT)) {
			if (brightness > MIN_BRIGHTNESS) {
				eeprom_update_byte(&ee_brightness, --brightness);
			}
			while (!button_is_released(&BUTTONS_PIN, MINUS_BUTTON_BIT));
		} else if (button_is_pressed(&BUTTONS_PIN, PLUS_BUTTON_BIT)) {
			if (brightness < MAX_BRIGHTNESS) {
				eeprom_update_byte(&ee_brightness, ++brightness);
			}
			while (!button_is_released(&BUTTONS_PIN, PLUS_BUTTON_BIT));
		} else if (button_is_pressed(&BUTTONS_PIN, SET_BUTTON_BIT)) {
			while (!button_is_released(&BUTTONS_PIN, SET_BUTTON_BIT));
			return;
		}
	}
}

void change_task()
{
	uint8_t reset;

	action = IDLE_ACTION;
	fill_display_register(task);

	for (;;) {
		reset = 1;
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
			eeprom_update_word(&ee_task, task);
			while (!button_is_released(&BUTTONS_PIN, SET_BUTTON_BIT));
			return;
		} else if (button_is_pressed(&BUTTONS_PIN, RESET_BUTTON_BIT)) {
			task = DEFAULT_TASK;
			fill_display_register(task);
			while (!button_is_released(&BUTTONS_PIN, RESET_BUTTON_BIT));
		}
	}
}

void change_zone()
{
	uint8_t reset;

	action = IDLE_ACTION;
	fill_display_register(zone);

	for (;;) {
		reset = 1;
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
			eeprom_update_word(&ee_zone, zone);
			while (!button_is_released(&BUTTONS_PIN, SET_BUTTON_BIT));
			return;
		} else if (button_is_pressed(&BUTTONS_PIN, RESET_BUTTON_BIT)) {
			zone = DEFAULT_ZONE;
			fill_display_register(zone);
			while (!button_is_released(&BUTTONS_PIN, RESET_BUTTON_BIT));
		}
	}
}

void control_temp()
{
	action = SHOW_TEMP_ACTION | CONTROL_TEMP_ACTION;
	fill_display_register(temp);

	LED_DDR |= (1 << LED_BIT);
	LED_PORT &= ~(1 << LED_BIT); // Включение индикации

	for (;;) {
		if (button_is_pressed(&BUTTONS_PIN, MINUS_BUTTON_BIT)) {
			if (brightness > MIN_BRIGHTNESS) {
				eeprom_update_byte(&ee_brightness, --brightness);
			}
			while (!button_is_released(&BUTTONS_PIN, MINUS_BUTTON_BIT));
		} else if (button_is_pressed(&BUTTONS_PIN, PLUS_BUTTON_BIT)) {
			if (brightness < MAX_BRIGHTNESS) {
				eeprom_update_byte(&ee_brightness, ++brightness);
			}
			while (!button_is_released(&BUTTONS_PIN, PLUS_BUTTON_BIT));
		} else if (button_is_pressed(&BUTTONS_PIN, RESET_BUTTON_BIT)) {
			action = SHOW_TEMP_ACTION;
			LED_DDR &= ~(1 << LED_BIT);
			LED_PORT &= ~(1 << LED_BIT);
			RELAY_PORT &= ~(1 << RELAY_BIT); // Выключение индикации и управления
			while (!button_is_released(&BUTTONS_PIN, RESET_BUTTON_BIT));
			return;
		}
	}
}

int main()
{
	// Enable internal pull-up resistors
	BUTTONS_PORT |= BUTTONS_MASK;

	// Конфигурация портов в/в
	RELAY_DDR = (1 << RELAY_BIT);

	// Конфигурация 16-битного счетчика
	OCR1AH = 0x3D;
	OCR1AL = 0x08; // Счет до 15625
	// WGM12 = 1 для сброса при совпадении (режим CTC)
	// CS12 = 1 и CS10 = 1 для предварительного деления на 1024
	TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10);
	TIMSK |= (1 << OCIE1A); // Включение прерывания по совпадению

	// Конфигурация 8-битного счетчика
	OCR2 = 0x18; // Счет до 25
	// WGM21 = 1 для сброса при совпадении (режим CTC)
	// CS21 = 1 и CS20 = 1 для предварительного деления на 32
	TCCR2 = (1 << WGM21) | (1 << CS21) | (1 << CS20);
	TIMSK |= (1 << OCIE2); // Включение прерывания по совпадению

	// Инициализация дисплея
	display_init();

	// Отображение сообщения загрузки
	display_register[3] = DISPLAY_CHAR_L;
	display_register[2] = DISPLAY_CHAR_O;
	display_register[1] = DISPLAY_CHAR_A;
	display_register[0] = DISPLAY_CHAR_D;

	sei();

	// Сразу запускаем температурное преобразование, чтобы избежать чтения
	// значения +85 oC, записанного в температурный регистр датчика при подаче
	// питания
	ds18b20_read_temp();

	// Чтение параметров из EEPROM
	task = eeprom_read_word(&ee_task);
	if (task > MAX_TEMP && task < MIN_TEMP) {
		task = DEFAULT_TASK;
	}

	zone = eeprom_read_word(&ee_zone);
	if (zone > MAX_ZONE || zone < MIN_ZONE) {
		zone = DEFAULT_ZONE;
	}

	brightness = eeprom_read_byte(&ee_brightness);
	if (brightness > MAX_BRIGHTNESS || brightness < MIN_BRIGHTNESS) {
		brightness = DEFAULT_BRIGHTNESS;
	}

	for (;;) {
		show_temp();
		change_task();
		change_zone();
		control_temp();
	}
}
