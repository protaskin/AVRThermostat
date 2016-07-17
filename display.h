/*
 * This file is part of AVRThermostat.
 *
 * (c) Artyom Protaskin <a.protaskin@gmail.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

#ifndef DISPLAY_H
#define DISPLAY_H

// Digits

#define DISPLAY_DIGITS_DDR  DDRC
#define DISPLAY_DIGITS_PIN  PINC
#define DISPLAY_DIGITS_PORT PORTC

#define DISPLAY_DIGITS_COUNT 4

#define DISPLAY_1 (1 << PC3)
#define DISPLAY_2 (1 << PC4)
#define DISPLAY_3 (1 << PC5)
#define DISPLAY_4 (1 << PC2)

#define DISPLAY_DIGITS_MASK (DISPLAY_1 | DISPLAY_2 | DISPLAY_3 | DISPLAY_4)

// Segments

#define DISPLAY_SEGMENTS_DDR  DDRD
#define DISPLAY_SEGMENTS_PIN  PIND
#define DISPLAY_SEGMENTS_PORT PORTD

#define DISPLAY_A  (1 << PD2)
#define DISPLAY_B  (1 << PD0)
#define DISPLAY_C  (1 << PD4)
#define DISPLAY_D  (1 << PD6)
#define DISPLAY_E  (1 << PD7)
#define DISPLAY_F  (1 << PD1)
#define DISPLAY_G  (1 << PD3)
#define DISPLAY_DP (1 << PD5)

#define DISPLAY_SEGMENTS_MASK (DISPLAY_A | DISPLAY_B | DISPLAY_C | DISPLAY_D | \
							   DISPLAY_E | DISPLAY_F | DISPLAY_G | DISPLAY_DP)

#define DISPLAY_CHAR_BLANK 0x00
#define DISPLAY_CHAR_POINT DISPLAY_DP
#define DISPLAY_CHAR_MINUS DISPLAY_G


extern const uint8_t display_numbers_map[10];

extern uint8_t display_register[DISPLAY_DIGITS_COUNT];
extern uint8_t display_register_index;

void display_init(void);
void display_show(void);
void display_hide(void);
void display_next(void);
void display_drop_register(void);

#endif /* DISPLAY_H */
