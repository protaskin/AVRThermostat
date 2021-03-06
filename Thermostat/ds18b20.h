/*
 * This file is part of AVRThermostat.
 *
 * (c) Artyom Protaskin <a.protaskin@gmail.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

#ifndef DS18B20_H
#define DS18B20_H

#include <stdbool.h>
#include <stdint.h>

#include "iodef.h"

#define DS18B20_ERROR 0xA800

bool ds18b20_init(void);
uint8_t ds18b20_read_byte(void);
void ds18b20_write_byte(uint8_t data);
uint16_t ds18b20_read_temp(void);

#endif /* DS18B20_H */
