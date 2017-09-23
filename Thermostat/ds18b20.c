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
#include <avr/interrupt.h>
#include <avr/io.h>

#include "ds18b20.h"

/**
 * Инициализирует процесс связи с датчиком.
 * Возвращает 1 если датчик подключен и готов к работе, 0 в противном случае.
 */
uint8_t ds18b20_init(void) // 1162 мкс
{
	uint8_t rval;

	// Обнуление линии
	// Заключается в подтягивании линии к нижнему уровню в течение минимум 480 мкс
	cli();
	DS18B20_PORT &= ~_BV(DS18B20_BIT);
	DS18B20_DDR |= _BV(DS18B20_BIT);
	sei();
	_delay_us(480);
	cli();
	DS18B20_DDR &= ~_BV(DS18B20_BIT);

	// Прием импульса присутствия
	_delay_us(60); // Ожидание ответа в течение 15-60 мкс
	rval = ((DS18B20_PIN & _BV(DS18B20_BIT)) == 0);

	// Ожидание готовности датчика
	sei();
	_delay_us(420);

	return rval;
}

/**
 * Считывает байт.
 */
uint8_t ds18b20_read_byte(void) // 685 мкс
{
	uint8_t rval = 0;

	for (size_t i = 0; i < 8; i++) { // 578,25 мкс
		// Инициализация слота времени
		// Каждый слот времени длится минимум 60 мкс
		cli();
		DS18B20_DDR |= _BV(DS18B20_BIT);
		_delay_us(1); // Низкий уровень в течение 1-15 мкс
		DS18B20_DDR &= ~_BV(DS18B20_BIT);
		_delay_us(2); // Выходные данные достоверны в течение 15 мкс после низкого уровня
		rval |= (DS18B20_PIN & _BV(DS18B20_BIT)) << i;
		_delay_us(60);
		sei();
	}

	return rval;
}

/**
 * Записывает байт.
 */
void ds18b20_write_byte(const uint8_t data) // 728,63 мкс
{
	for (size_t i = 0; i < 8; i++) {
		// Инициализация слота времени
		cli();
		DS18B20_DDR |= _BV(DS18B20_BIT);
		_delay_us(1); // Низкий уровень в течение 1-15 мкс
		if (data & _BV(i)) {
			// При передаче 1 необходимо вновь подтянуть линию к высокому уровню
			DS18B20_DDR &= ~_BV(DS18B20_BIT);
		}
		_delay_us(60);
		DS18B20_DDR &= ~_BV(DS18B20_BIT);
		sei();
	}
}

/**
 * Считывает регистр температуры и запускает температурное преобразование.
 */
uint16_t ds18b20_read_temp(void)
{
	uint16_t rval;
	uint8_t temp_L, temp_H;

	if (!ds18b20_init()) { // Инициализация
		return DS18B20_ERROR;
	}

	ds18b20_write_byte(0xCC); // Проверка кода датчика (пропуск)
	ds18b20_write_byte(0xBE); // Чтение памяти
	temp_L = ds18b20_read_byte();
	temp_H = ds18b20_read_byte();

	rval = (temp_H << 8) | temp_L;

	ds18b20_init();
	ds18b20_write_byte(0xCC); // Проверка кода датчика
	ds18b20_write_byte(0x44); // Запуск температурного преобразования

	return rval;
}
