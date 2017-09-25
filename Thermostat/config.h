/*
 * This file is part of AVRThermostat.
 *
 * (c) Artyom Protaskin <a.protaskin@gmail.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

#ifndef CONFIG_H
#define CONFIG_H

// Limits
#define ZERO_TEMP 0
#define MIN_TEMP 0xFC90 // -55
#define MAX_TEMP 0x07D0 // 125
#define MIN_ZONE 0x0001 // 1/16
#define MAX_ZONE 0x0640 // 100
#define MIN_BRIGHTNESS 1
#define MAX_BRIGHTNESS 15

// Default values
#define DEFAULT_TASK 0x0140 // 20
#define DEFAULT_ZONE 0x0008 // 0.5
#define DEFAULT_BRIGHTNESS 7 // 1/2
#define DEFAULT_ACTION 0
#define DEFAULT_CHECKSUM 0x95

// Error bit offsets
#define CONFIG_BAD_TASK_BIT 0
#define CONFIG_BAD_ZONE_BIT 1
#define CONFIG_BAD_BRIGHTNESS_BIT 2
#define CONFIG_BAD_ACTION_BIT 3
#define CONFIG_BAD_CHECKSUM_BIT 4

#include <stdint.h>

extern uint16_t task;
extern uint16_t zone;
extern uint8_t brightness;
extern uint8_t action;

uint8_t config_read(void);

uint8_t config_update(void);

#endif /* CONFIG_H */
