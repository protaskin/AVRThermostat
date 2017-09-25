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
#include <util/crc16.h>
#include <avr/eeprom.h>

#include "config.h"

uint16_t task;
uint16_t zone;
uint8_t brightness;
uint8_t action;

uint16_t EEMEM ee_task = DEFAULT_TASK;
uint16_t EEMEM ee_zone = DEFAULT_ZONE;
uint8_t EEMEM ee_brightness = DEFAULT_BRIGHTNESS;
uint8_t EEMEM ee_action = DEFAULT_ACTION;
uint8_t EEMEM ee_checksum = DEFAULT_CHECKSUM;

static uint8_t calc_crc8(uint8_t crc, const void * const data, uint8_t len)
{
	while (len--) {
		crc = _crc_ibutton_update(crc, *(uint8_t *) (data + len)); // TODO
	}

	return crc;
}

static uint8_t config_calc_checksum(void)
{
	uint8_t crc = 0;

	crc = calc_crc8(crc, &task, sizeof task);
	crc = calc_crc8(crc, &zone, sizeof zone);
	crc = calc_crc8(crc, &brightness, sizeof brightness);
	crc = calc_crc8(crc, &action, sizeof action);

	return crc;
}

uint8_t config_read(void)
{
	uint8_t error = 0;
	uint8_t checksum;

	task = eeprom_read_word(&ee_task);
	if (task > MAX_TEMP && task < MIN_TEMP) {
		task = DEFAULT_TASK;
		error |= _BV(CONFIG_BAD_TASK_BIT);
	}

	zone = eeprom_read_word(&ee_zone);
	if (zone > MAX_ZONE || zone < MIN_ZONE) {
		zone = DEFAULT_ZONE;
		error |= _BV(CONFIG_BAD_ZONE_BIT);
	}

	brightness = eeprom_read_byte(&ee_brightness);
	if (brightness > MAX_BRIGHTNESS || brightness < MIN_BRIGHTNESS) {
		brightness = DEFAULT_BRIGHTNESS;
		error |= _BV(CONFIG_BAD_BRIGHTNESS_BIT);
	}

	action = eeprom_read_byte(&ee_action);

	checksum = config_calc_checksum();
	if (checksum != eeprom_read_byte(&ee_checksum)) {
		error |= _BV(CONFIG_BAD_CHECKSUM_BIT);
	}

	return error;
}

uint8_t config_update(void)
{
	uint8_t error = 0;
	uint8_t checksum;
	bool recalc_checksum = false;

	if (task != eeprom_read_word(&ee_task)) {
		recalc_checksum = true;
		eeprom_write_word(&ee_task, task);
		if (task != eeprom_read_word(&ee_task)) {
			error |= _BV(CONFIG_BAD_TASK_BIT);
		}
	}

	if (zone != eeprom_read_word(&ee_zone)) {
		recalc_checksum = true;
		eeprom_write_word(&ee_zone, zone);
		if (zone != eeprom_read_word(&ee_zone)) {
			error |= _BV(CONFIG_BAD_ZONE_BIT);
		}
	}

	if (brightness != eeprom_read_byte(&ee_brightness)) {
		recalc_checksum = true;
		eeprom_write_byte(&ee_brightness, brightness);
		if (brightness != eeprom_read_byte(&ee_brightness)) {
			error |= _BV(CONFIG_BAD_BRIGHTNESS_BIT);
		}
	}

	if (action != eeprom_read_byte(&ee_action)) {
		recalc_checksum = true;
		eeprom_write_byte(&ee_action, action);
		if (action != eeprom_read_byte(&ee_action)) {
			error |= _BV(CONFIG_BAD_ACTION_BIT);
		}
	}

	if (recalc_checksum) {
		checksum = config_calc_checksum();
		eeprom_write_byte(&ee_checksum, checksum);
		if (checksum != eeprom_read_byte(&ee_checksum)) {
			error |= _BV(CONFIG_BAD_CHECKSUM_BIT);
		}
	}

	return error;
}
