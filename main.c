/*
 * This file is part of AVRThermostat.
 *
 * (c) Artyom Protaskin <a.protaskin@gmail.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

#define IDLE_ACTION         0
#define SHOW_TEMP_ACTION    1
#define CONTROL_TEMP_ACTION 2

#define DISPLAY_CHAR_A (DISPLAY_A | DISPLAY_B | DISPLAY_C | DISPLAY_E | DISPLAY_F | DISPLAY_G)
#define DISPLAY_CHAR_D (DISPLAY_B | DISPLAY_C | DISPLAY_D | DISPLAY_E | DISPLAY_G)
#define DISPLAY_CHAR_E (DISPLAY_A | DISPLAY_D | DISPLAY_E | DISPLAY_F | DISPLAY_G)
#define DISPLAY_CHAR_L (DISPLAY_D | DISPLAY_E | DISPLAY_F)
#define DISPLAY_CHAR_O (DISPLAY_A | DISPLAY_B | DISPLAY_C | DISPLAY_D | DISPLAY_E | DISPLAY_F)
#define DISPLAY_CHAR_R (DISPLAY_E | DISPLAY_G)

#include <stddef.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "display.h"
#include "ds18b20.h"

uint8_t action;
uint8_t brightness;
uint16_t temp;
uint16_t task;
uint16_t zone;
uint8_t EEMEM ee_brightness = 7; // 1/2
uint16_t EEMEM ee_task = 0x0140; // 20 oC
uint16_t EEMEM ee_zone = 0x0008; // 0,5 oC

const uint8_t *numbers = display_numbers_map;

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

		if (temp >= 0xFC90) {
			if (trigger_on <= 0x07D0 || temp <= trigger_on) {
				PORTC |= (3 << PC0);
			} else if (trigger_off >= 0xFC90 && temp >= trigger_off) {
				PORTC &= ~(3 << PC0);
			}
		} else {
			if (trigger_on <= 0x07D0 && temp <= trigger_on) {
				PORTC |= (3 << PC0);
			} else if (trigger_off >= 0xFC90 || temp >= trigger_off) {
				PORTC &= ~(3 << PC0);
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

void pressed_button_delay(uint8_t *reset)
{
	static uint8_t count;
	static uint8_t compare;
	static uint8_t cycles;
	
	if (*reset) {
		count = 0;
		compare = 0x08;
		cycles = 0xFF;
		*reset = 0;
	}

	if (compare && count++ == compare) {
		count = 0;
		compare *= 2;
		cycles /= 2;
	}

	for (size_t i = 0; i < cycles; i++) {
		_delay_ms(1);
	}
}

void show_temp()
{
	action = SHOW_TEMP_ACTION;

	for (;;) {
		if (~PINB & (1 << PB1)) {
			_delay_ms(200);
			while (~PINB & (1 << PB1));
			if (brightness > 1) {
				brightness--;
				eeprom_update_byte(&ee_brightness, brightness);
			}
		}
		else if (~PINB & (1 << PB2)) {
			_delay_ms(200);
			while (~PINB & (1 << PB2));
			if (brightness < 15) {
				brightness++;
				eeprom_update_byte(&ee_brightness, brightness);
			}
		}
		else if (~PINB & (1 << PB3)) {
			_delay_ms(200);
			while (~PINB & (1 << PB3));
			return;
		}
	}
}

void change_task()
{
	action = IDLE_ACTION;
	fill_display_register(task);

	for (;;) {
		uint8_t reset = 1;
		if (~PINB & (1 << PB1)) {
			while (~PINB & (1 << PB1) && (task <= 0x07D0 || task > 0xFC90)) {
				pressed_button_delay(&reset);
				fill_display_register(--task);
			}
		}
		else if (~PINB & (1 << PB2)) {
			while (~PINB & (1 << PB2) && (task < 0x07D0 || task >= 0xFC90)) {
				pressed_button_delay(&reset);
				fill_display_register(++task);
			}
		}
		else if (~PINB & (1 << PB3)) {
			_delay_ms(200);
			while (~PINB & (1 << PB3));
			eeprom_update_word(&ee_task, task);
			return;
		}
		else if (~PINB & (1 << PB4)) {
			_delay_ms(200);
			while (~PINB & (1 << PB4));
			task = 0x0140; // +20 oC
			fill_display_register(task);
		}
	}
}

void change_zone()
{
	action = IDLE_ACTION;
	fill_display_register(zone);

	for (;;) {
		uint8_t reset = 1;
		if (~PINB & (1 << PB1)) {
			while (~PINB & (1 << PB1) && zone > 0x0001) {
				pressed_button_delay(&reset);
				fill_display_register(--zone);
			}
		}
		else if (~PINB & (1 << PB2)) {
			while (~PINB & (1 << PB2) && zone < 0x0640) {
				pressed_button_delay(&reset);
				fill_display_register(++zone);
			}
		}
		else if (~PINB & (1 << PB3)) {
			_delay_ms(200);
			while (~PINB & (1 << PB3));
			eeprom_update_word(&ee_zone, zone);
			return;
		}
		else if (~PINB & (1 << PB4)) {
			_delay_ms(200);
			while (~PINB & (1 << PB4));
			zone = 0x0008; // 0,5 oC
			fill_display_register(zone);
		}
	}
}

void control_temp()
{
	action = SHOW_TEMP_ACTION | CONTROL_TEMP_ACTION;
	fill_display_register(temp);

	DDRC |= (1 << PC0);
	PORTC &= ~(1 << PC0); // Включение индикации

	for (;;) {
		if (~PINB & (1 << PB1)) {
			_delay_ms(200);
			while (~PINB & (1 << PB1));
			if (brightness > 1) {
				brightness--;
				eeprom_update_byte(&ee_brightness, brightness);
			}
		}
		else if (~PINB & (1 << PB2)) {
			_delay_ms(200);
			while (~PINB & (1 << PB2));
			if (brightness < 15) {
				brightness++;
				eeprom_update_byte(&ee_brightness, brightness);
			}
		}
		else if (~PINB & (1 << PB4)) {
			_delay_ms(200);
			while (~PINB & (1 << PB4));
			DDRC &= ~(1 << PC0);
			PORTC &= ~(3 << PC0); // Выключение индикации и управления
			return;
		}
	}
}

int main()
{
	// Enable internal pull-up resistors
	PORTB |= (1 << PB1) | (1 << PB2) | (1 << PB3) | (1 << PB4);

	// Конфигурация портов в/в
	DDRC = (1 << PC1);

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
	if (task > 0x07D0 && task < 0xFC90) {
		task = 0x0140;
	}

	zone = eeprom_read_word(&ee_zone);
	if (zone > 0x0640 || zone < 0x0001) {
		zone = 0x0008;
	}

	brightness = eeprom_read_byte(&ee_brightness);
	if (brightness > 15 || brightness < 1) {
		brightness = 7;
	}

	for (;;) {
		show_temp();
		change_task();
		change_zone();
		control_temp();
	}
}
