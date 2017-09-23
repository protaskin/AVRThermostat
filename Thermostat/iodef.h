/*
 * This file is part of AVRThermostat.
 *
 * (c) Artyom Protaskin <a.protaskin@gmail.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

#ifndef IODEF_H
#define IODEF_H

// Buttons
#define BUTTONS_DDR      DDRB
#define BUTTONS_PORT     PORTB
#define BUTTONS_PIN      PINB
#define MINUS_BUTTON_BIT PB1
#define PLUS_BUTTON_BIT  PB2
#define SET_BUTTON_BIT   PB3
#define RESET_BUTTON_BIT PB4

// LED
#define LED_DDR  DDRC
#define LED_PORT PORTC
#define LED_PIN  PINC
#define LED_BIT  PC0

// Relay
#define RELAY_DDR  DDRC
#define RELAY_PORT PORTC
#define RELAY_PIN  PINC
#define RELAY_BIT  PC1


// Display digits
#define DISPLAY_DIGITS_DDR  DDRC
#define DISPLAY_DIGITS_PORT PORTC
#define DISPLAY_DIGITS_PIN  PINC

#define DISPLAY_1_BIT PC3
#define DISPLAY_2_BIT PC5
#define DISPLAY_3_BIT PC4
#define DISPLAY_4_BIT PC2

// Display segments
#define DISPLAY_SEGMENTS_DDR  DDRD
#define DISPLAY_SEGMENTS_PORT PORTD
#define DISPLAY_SEGMENTS_PIN  PIND

#define DISPLAY_A_BIT  PD2
#define DISPLAY_B_BIT  PD0
#define DISPLAY_C_BIT  PD4
#define DISPLAY_D_BIT  PD6
#define DISPLAY_E_BIT  PD7
#define DISPLAY_F_BIT  PD1
#define DISPLAY_G_BIT  PD3
#define DISPLAY_DP_BIT PD5

// DS18B20
#define DS18B20_DDR  DDRB
#define DS18B20_PORT PORTB
#define DS18B20_PIN  PINB
#define DS18B20_BIT  PB0

#endif /* IODEF_H */
