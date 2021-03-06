EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:display
LIBS:atmel
LIBS:maxim
LIBS:switches
LIBS:diode
LIBS:relays
LIBS:conn
LIBS:Thermostat-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Thermostat on ATmega8A, DS18B20 and 7-segment Display"
Date "2017-10-07"
Rev "3.1"
Comp "Artyom Protaskin"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L DS18B20 U2
U 1 1 597C1476
P 5200 2900
F 0 "U2" H 5050 3150 50  0000 C CNN
F 1 "DS18B20" H 5200 2650 50  0000 C CNN
F 2 "TO_SOT_Packages_THT:TO-92_Molded_Narrow" H 5050 3150 50  0001 C CNN
F 3 "" H 5050 3150 50  0001 C CNN
	1    5200 2900
	1    0    0    -1  
$EndComp
$Comp
L ATMEGA8-16PU U1
U 1 1 597C18C7
P 3200 4300
F 0 "U1" H 2450 5600 50  0000 L BNN
F 1 "ATMEGA8-16PU" H 3700 2850 50  0000 L BNN
F 2 "Housings_DIP:DIP-28_W7.62mm" H 3200 4300 50  0001 C CIN
F 3 "" H 3200 4300 50  0001 C CNN
	1    3200 4300
	1    0    0    -1  
$EndComp
$Comp
L SW_Push SW1
U 1 1 597C1A38
P 6250 2700
F 0 "SW1" H 6300 2800 50  0000 L CNN
F 1 "SW_Push" H 6250 2640 50  0000 C CNN
F 2 "Buttons_Switches_THT:SW_PUSH_6mm_h5mm" H 6250 2900 50  0001 C CNN
F 3 "" H 6250 2900 50  0001 C CNN
	1    6250 2700
	1    0    0    -1  
$EndComp
$Comp
L SW_Push SW2
U 1 1 597C1ABA
P 6250 3000
F 0 "SW2" H 6300 3100 50  0000 L CNN
F 1 "SW_Push" H 6250 2940 50  0000 C CNN
F 2 "Buttons_Switches_THT:SW_PUSH_6mm_h5mm" H 6250 3200 50  0001 C CNN
F 3 "" H 6250 3200 50  0001 C CNN
	1    6250 3000
	1    0    0    -1  
$EndComp
$Comp
L SW_Push SW3
U 1 1 597C1AED
P 6250 3300
F 0 "SW3" H 6300 3400 50  0000 L CNN
F 1 "SW_Push" H 6250 3240 50  0000 C CNN
F 2 "Buttons_Switches_THT:SW_PUSH_6mm_h5mm" H 6250 3500 50  0001 C CNN
F 3 "" H 6250 3500 50  0001 C CNN
	1    6250 3300
	1    0    0    -1  
$EndComp
$Comp
L SW_Push SW4
U 1 1 597C1B1C
P 6250 3600
F 0 "SW4" H 6300 3700 50  0000 L CNN
F 1 "SW_Push" H 6250 3540 50  0000 C CNN
F 2 "Buttons_Switches_THT:SW_PUSH_6mm_h5mm" H 6250 3800 50  0001 C CNN
F 3 "" H 6250 3800 50  0001 C CNN
	1    6250 3600
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 597C1B3F
P 4500 3000
F 0 "R3" V 4580 3000 50  0000 C CNN
F 1 "4.7k" V 4500 3000 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 4430 3000 50  0001 C CNN
F 3 "" H 4500 3000 50  0001 C CNN
	1    4500 3000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR01
U 1 1 597C1FB7
P 6500 3650
F 0 "#PWR01" H 6500 3400 50  0001 C CNN
F 1 "GND" H 6500 3500 50  0000 C CNN
F 2 "" H 6500 3650 50  0001 C CNN
F 3 "" H 6500 3650 50  0001 C CNN
	1    6500 3650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 597C261C
P 4850 3050
F 0 "#PWR02" H 4850 2800 50  0001 C CNN
F 1 "GND" H 4850 2900 50  0000 C CNN
F 2 "" H 4850 3050 50  0001 C CNN
F 3 "" H 4850 3050 50  0001 C CNN
	1    4850 3050
	1    0    0    -1  
$EndComp
$Comp
L 1N4148 D1
U 1 1 597C2A03
P 5100 4950
F 0 "D1" H 5100 5050 50  0000 C CNN
F 1 "1N4148" H 5100 4850 50  0000 C CNN
F 2 "Diodes_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 5100 4775 50  0001 C CNN
F 3 "" H 5100 4950 50  0001 C CNN
	1    5100 4950
	0    1    1    0   
$EndComp
$Comp
L +5V #PWR03
U 1 1 597C2BBF
P 4500 2750
F 0 "#PWR03" H 4500 2600 50  0001 C CNN
F 1 "+5V" H 4500 2890 50  0000 C CNN
F 2 "" H 4500 2750 50  0001 C CNN
F 3 "" H 4500 2750 50  0001 C CNN
	1    4500 2750
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR04
U 1 1 597C2D7E
P 3200 2350
F 0 "#PWR04" H 3200 2200 50  0001 C CNN
F 1 "+5V" H 3200 2490 50  0000 C CNN
F 2 "" H 3200 2350 50  0001 C CNN
F 3 "" H 3200 2350 50  0001 C CNN
	1    3200 2350
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 597C2ED1
P 1600 2850
F 0 "R2" V 1680 2850 50  0000 C CNN
F 1 "4.7k" V 1600 2850 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 1530 2850 50  0001 C CNN
F 3 "" H 1600 2850 50  0001 C CNN
	1    1600 2850
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 597C2F28
P 1400 3050
F 0 "R1" V 1480 3050 50  0000 C CNN
F 1 "330" V 1400 3050 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 1330 3050 50  0001 C CNN
F 3 "" H 1400 3050 50  0001 C CNN
	1    1400 3050
	0    1    1    0   
$EndComp
$Comp
L C C4
U 1 1 597C2F93
P 1600 3250
F 0 "C4" H 1625 3350 50  0000 L CNN
F 1 "100nF" H 1625 3150 50  0000 L CNN
F 2 "Capacitors_THT:C_Disc_D4.3mm_W1.9mm_P5.00mm" H 1638 3100 50  0001 C CNN
F 3 "" H 1600 3250 50  0001 C CNN
	1    1600 3250
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR05
U 1 1 597C3311
P 1600 2650
F 0 "#PWR05" H 1600 2500 50  0001 C CNN
F 1 "+5V" H 1600 2790 50  0000 C CNN
F 2 "" H 1600 2650 50  0001 C CNN
F 3 "" H 1600 2650 50  0001 C CNN
	1    1600 2650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR06
U 1 1 597C34B0
P 1600 3450
F 0 "#PWR06" H 1600 3200 50  0001 C CNN
F 1 "GND" H 1600 3300 50  0000 C CNN
F 2 "" H 1600 3450 50  0001 C CNN
F 3 "" H 1600 3450 50  0001 C CNN
	1    1600 3450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR07
U 1 1 597C3B8E
P 3200 5850
F 0 "#PWR07" H 3200 5600 50  0001 C CNN
F 1 "GND" H 3200 5700 50  0000 C CNN
F 2 "" H 3200 5850 50  0001 C CNN
F 3 "" H 3200 5850 50  0001 C CNN
	1    3200 5850
	1    0    0    -1  
$EndComp
Text GLabel 1200 3050 0    60   Input ~ 0
RESET
$Comp
L R R4
U 1 1 597C4550
P 5000 5550
F 0 "R4" V 5080 5550 50  0000 C CNN
F 1 "4.7k" V 5000 5550 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 4930 5550 50  0001 C CNN
F 3 "" H 5000 5550 50  0001 C CNN
	1    5000 5550
	0    1    1    0   
$EndComp
$Comp
L GND #PWR08
U 1 1 597C45EB
P 5500 5800
F 0 "#PWR08" H 5500 5550 50  0001 C CNN
F 1 "GND" H 5500 5650 50  0000 C CNN
F 2 "" H 5500 5800 50  0001 C CNN
F 3 "" H 5500 5800 50  0001 C CNN
	1    5500 5800
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR09
U 1 1 597C54E7
P 5500 4550
F 0 "#PWR09" H 5500 4400 50  0001 C CNN
F 1 "+5V" H 5500 4690 50  0000 C CNN
F 2 "" H 5500 4550 50  0001 C CNN
F 3 "" H 5500 4550 50  0001 C CNN
	1    5500 4550
	1    0    0    -1  
$EndComp
$Comp
L TIANBO-HJR-4102-L RL1
U 1 1 597C568A
P 5700 4950
F 0 "RL1" H 6250 5100 50  0000 L CNN
F 1 "TIANBO-HJR-4102-L" H 6250 5000 50  0000 L CNN
F 2 "Relays_THT:Relay_SPDT_HJR-4102" H 5700 4950 50  0001 C CNN
F 3 "" H 5700 4950 50  0000 C CNN
	1    5700 4950
	1    0    0    -1  
$EndComp
$Comp
L CC56-12 AFF1
U 1 1 597C5AE4
P 9400 5250
F 0 "AFF1" H 9400 6000 50  0000 C CNN
F 1 "CC56-12" H 9400 5900 50  0000 C CNN
F 2 "Displays_7-Segment:CC56-12GWA" H 8900 5250 50  0001 C CNN
F 3 "" H 8900 5250 50  0001 C CNN
	1    9400 5250
	1    0    0    -1  
$EndComp
Entry Wire Line
	4400 4200 4500 4300
Entry Wire Line
	4400 4300 4500 4400
Entry Wire Line
	4400 4400 4500 4500
Entry Wire Line
	4400 4600 4500 4700
Entry Wire Line
	4400 4700 4500 4800
Entry Wire Line
	4400 4800 4500 4900
Entry Wire Line
	4400 4900 4500 5000
Entry Wire Line
	4400 5000 4500 5100
Entry Wire Line
	4400 5100 4500 5200
Entry Wire Line
	4400 5200 4500 5300
Entry Wire Line
	4400 5300 4500 5400
Text Label 4200 4100 0    60   ~ 0
CC4
Text Label 4200 4200 0    60   ~ 0
CC1
Text Label 4200 4300 0    60   ~ 0
CC3
Text Label 4200 4400 0    60   ~ 0
CC2
Text Label 4300 4600 0    60   ~ 0
B
Text Label 4300 4700 0    60   ~ 0
F
Text Label 4300 4800 0    60   ~ 0
A
Text Label 4300 4900 0    60   ~ 0
G
Text Label 4300 5000 0    60   ~ 0
C
Text Label 4250 5100 0    60   ~ 0
DP
Text Label 4300 5200 0    60   ~ 0
D
Text Label 4300 5300 0    60   ~ 0
E
Entry Wire Line
	4400 4100 4500 4200
Entry Wire Line
	9100 6100 9200 6200
Entry Wire Line
	9200 6100 9300 6200
Entry Wire Line
	9300 6100 9400 6200
Entry Wire Line
	9400 6100 9500 6200
Entry Wire Line
	9500 6100 9600 6200
Entry Wire Line
	9600 6100 9700 6200
Entry Wire Line
	9700 6100 9800 6200
Entry Wire Line
	9800 6100 9900 6200
Text Label 9100 6050 1    60   ~ 0
A
Text Label 9200 6050 1    60   ~ 0
B
Text Label 9300 6050 1    60   ~ 0
C
Text Label 9400 6050 1    60   ~ 0
D
Text Label 9500 6050 1    60   ~ 0
E
Text Label 9600 6050 1    60   ~ 0
F
Text Label 9700 6050 1    60   ~ 0
G
Entry Wire Line
	8600 4200 8700 4300
Entry Wire Line
	9100 4200 9200 4300
Entry Wire Line
	9600 4200 9700 4300
Entry Wire Line
	10100 4200 10200 4300
Text Label 8700 4550 1    60   ~ 0
CC1
Text Label 9200 4550 1    60   ~ 0
CC2
Text Label 9700 4550 1    60   ~ 0
CC3
Text Label 10200 4550 1    60   ~ 0
CC4
Entry Bus Bus
	8100 6100 8200 6200
$Comp
L LED D2
U 1 1 597D93EB
P 7500 4800
F 0 "D2" H 7500 4900 50  0000 C CNN
F 1 "LED" H 7500 4700 50  0000 C CNN
F 2 "LEDs:LED_D3.0mm" H 7500 4800 50  0001 C CNN
F 3 "" H 7500 4800 50  0001 C CNN
	1    7500 4800
	0    -1   -1   0   
$EndComp
$Comp
L LED D3
U 1 1 597D969A
P 7500 5200
F 0 "D3" H 7500 5300 50  0000 C CNN
F 1 "LED" H 7500 5100 50  0000 C CNN
F 2 "LEDs:LED_D3.0mm" H 7500 5200 50  0001 C CNN
F 3 "" H 7500 5200 50  0001 C CNN
	1    7500 5200
	0    -1   -1   0   
$EndComp
$Comp
L R R6
U 1 1 597D9711
P 7750 5000
F 0 "R6" V 7830 5000 50  0000 C CNN
F 1 "680" V 7750 5000 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 7680 5000 50  0001 C CNN
F 3 "" H 7750 5000 50  0001 C CNN
	1    7750 5000
	1    0    0    -1  
$EndComp
$Comp
L R R5
U 1 1 597D97A6
P 7500 4400
F 0 "R5" V 7580 4400 50  0000 C CNN
F 1 "330" V 7500 4400 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 7430 4400 50  0001 C CNN
F 3 "" H 7500 4400 50  0001 C CNN
	1    7500 4400
	1    0    0    -1  
$EndComp
$Comp
L R R7
U 1 1 597D9982
P 7500 5600
F 0 "R7" V 7580 5600 50  0000 C CNN
F 1 "330" V 7500 5600 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 7430 5600 50  0001 C CNN
F 3 "" H 7500 5600 50  0001 C CNN
	1    7500 5600
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR010
U 1 1 597DAEB2
P 7500 4200
F 0 "#PWR010" H 7500 4050 50  0001 C CNN
F 1 "+5V" H 7500 4340 50  0000 C CNN
F 2 "" H 7500 4200 50  0001 C CNN
F 3 "" H 7500 4200 50  0001 C CNN
	1    7500 4200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR011
U 1 1 597DB396
P 7500 5800
F 0 "#PWR011" H 7500 5550 50  0001 C CNN
F 1 "GND" H 7500 5650 50  0000 C CNN
F 2 "" H 7500 5800 50  0001 C CNN
F 3 "" H 7500 5800 50  0001 C CNN
	1    7500 5800
	1    0    0    -1  
$EndComp
Text Notes 6600 2700 0    60   ~ 0
Minus
Text Notes 6600 3000 0    60   ~ 0
Plus
Text Notes 6600 3300 0    60   ~ 0
Set
Text Notes 6600 3600 0    60   ~ 0
Reset
$Comp
L Screw_Terminal_1x03 J8
U 1 1 597C8FAD
P 6000 4400
F 0 "J8" H 6000 4750 50  0000 C TNN
F 1 "Screw_Terminal_1x03" V 5850 4400 50  0000 C TNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_Pheonix_MKDS1.5-3pol" H 6000 4075 50  0001 C CNN
F 3 "" H 5975 4500 50  0001 C CNN
	1    6000 4400
	0    1    1    0   
$EndComp
$Comp
L BC547 Q1
U 1 1 597CB28D
P 5400 5550
F 0 "Q1" H 5600 5625 50  0000 L CNN
F 1 "BC547" H 5600 5550 50  0000 L CNN
F 2 "TO_SOT_Packages_THT:TO-92_Molded_Narrow" H 5600 5475 50  0001 L CIN
F 3 "" H 5400 5550 50  0001 L CNN
	1    5400 5550
	1    0    0    -1  
$EndComp
Text GLabel 4250 3700 2    60   Input ~ 0
SCK
Text GLabel 4600 3700 2    60   Output ~ 0
MISO
Text GLabel 5000 3700 2    60   Input ~ 0
MOSI
$Comp
L CONN_01X01_MALE J2
U 1 1 597DE506
P 9300 2250
F 0 "J2" H 9300 2325 50  0000 C CNN
F 1 "CONN_01X01_MALE" H 9300 2150 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x01_Pitch2.54mm" H 9300 2250 50  0001 C CNN
F 3 "" H 9300 2250 50  0001 C CNN
	1    9300 2250
	-1   0    0    1   
$EndComp
$Comp
L CONN_01X01_MALE J3
U 1 1 597DE63B
P 9300 2500
F 0 "J3" H 9300 2575 50  0000 C CNN
F 1 "CONN_01X01_MALE" H 9300 2400 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x01_Pitch2.54mm" H 9300 2500 50  0001 C CNN
F 3 "" H 9300 2500 50  0001 C CNN
	1    9300 2500
	-1   0    0    1   
$EndComp
$Comp
L CONN_01X01_MALE J4
U 1 1 597DE67C
P 9300 2900
F 0 "J4" H 9300 2975 50  0000 C CNN
F 1 "CONN_01X01_MALE" H 9300 2800 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x01_Pitch2.54mm" H 9300 2900 50  0001 C CNN
F 3 "" H 9300 2900 50  0001 C CNN
	1    9300 2900
	-1   0    0    1   
$EndComp
$Comp
L CONN_01X01_MALE J5
U 1 1 597DE6BF
P 9300 3150
F 0 "J5" H 9300 3225 50  0000 C CNN
F 1 "CONN_01X01_MALE" H 9300 3050 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x01_Pitch2.54mm" H 9300 3150 50  0001 C CNN
F 3 "" H 9300 3150 50  0001 C CNN
	1    9300 3150
	-1   0    0    1   
$EndComp
$Comp
L CONN_01X01_MALE J6
U 1 1 597DE704
P 9300 3400
F 0 "J6" H 9300 3475 50  0000 C CNN
F 1 "CONN_01X01_MALE" H 9300 3300 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x01_Pitch2.54mm" H 9300 3400 50  0001 C CNN
F 3 "" H 9300 3400 50  0001 C CNN
	1    9300 3400
	-1   0    0    1   
$EndComp
Text GLabel 8850 3400 0    60   Output ~ 0
SCK
Text GLabel 8850 3150 0    60   Input ~ 0
MISO
Text GLabel 8850 2900 0    60   Output ~ 0
MOSI
$Comp
L +5V #PWR012
U 1 1 597E0F0B
P 8800 2200
F 0 "#PWR012" H 8800 2050 50  0001 C CNN
F 1 "+5V" H 8800 2340 50  0000 C CNN
F 2 "" H 8800 2200 50  0001 C CNN
F 3 "" H 8800 2200 50  0001 C CNN
	1    8800 2200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR013
U 1 1 597E0FFC
P 8800 2550
F 0 "#PWR013" H 8800 2300 50  0001 C CNN
F 1 "GND" H 8800 2400 50  0000 C CNN
F 2 "" H 8800 2550 50  0001 C CNN
F 3 "" H 8800 2550 50  0001 C CNN
	1    8800 2550
	1    0    0    -1  
$EndComp
Text Notes 9050 1950 0    60   ~ 0
ISP
$Comp
L CONN_01X01_MALE J7
U 1 1 597E56C6
P 9300 3650
F 0 "J7" H 9300 3725 50  0000 C CNN
F 1 "CONN_01X01_MALE" H 9300 3550 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x01_Pitch2.54mm" H 9300 3650 50  0001 C CNN
F 3 "" H 9300 3650 50  0001 C CNN
	1    9300 3650
	-1   0    0    1   
$EndComp
Text GLabel 8850 3650 0    60   Output ~ 0
RESET
$Comp
L C C2
U 1 1 597E7192
P 2250 1400
F 0 "C2" H 2275 1500 50  0000 L CNN
F 1 "100nF" H 2275 1300 50  0000 L CNN
F 2 "Capacitors_THT:C_Disc_D4.3mm_W1.9mm_P5.00mm" H 2288 1250 50  0001 C CNN
F 3 "" H 2250 1400 50  0001 C CNN
	1    2250 1400
	1    0    0    -1  
$EndComp
Text Label 9800 6050 1    60   ~ 0
DP
$Comp
L +5V #PWR014
U 1 1 597F1995
P 3200 1150
F 0 "#PWR014" H 3200 1000 50  0001 C CNN
F 1 "+5V" H 3200 1290 50  0000 C CNN
F 2 "" H 3200 1150 50  0001 C CNN
F 3 "" H 3200 1150 50  0001 C CNN
	1    3200 1150
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR015
U 1 1 597F1BCA
P 3200 1650
F 0 "#PWR015" H 3200 1400 50  0001 C CNN
F 1 "GND" H 3200 1500 50  0000 C CNN
F 2 "" H 3200 1650 50  0001 C CNN
F 3 "" H 3200 1650 50  0001 C CNN
	1    3200 1650
	1    0    0    -1  
$EndComp
$Comp
L BARREL_JACK J1
U 1 1 597F1524
P 1250 1400
F 0 "J1" H 1250 1595 50  0000 C CNN
F 1 "BARREL_JACK" H 1250 1245 50  0000 C CNN
F 2 "Connectors:BARREL_JACK" H 1250 1400 50  0001 C CNN
F 3 "" H 1250 1400 50  0001 C CNN
	1    1250 1400
	1    0    0    -1  
$EndComp
NoConn ~ 2300 3900
NoConn ~ 2300 4100
$Comp
L +5V #PWR016
U 1 1 597C8F51
P 2150 3350
F 0 "#PWR016" H 2150 3200 50  0001 C CNN
F 1 "+5V" H 2150 3490 50  0000 C CNN
F 2 "" H 2150 3350 50  0001 C CNN
F 3 "" H 2150 3350 50  0001 C CNN
	1    2150 3350
	1    0    0    -1  
$EndComp
NoConn ~ 2300 3500
NoConn ~ 2300 3600
$Comp
L C C3
U 1 1 597CD1F0
P 3350 2600
F 0 "C3" H 3375 2700 50  0000 L CNN
F 1 "100nF" H 3375 2500 50  0000 L CNN
F 2 "Capacitors_THT:C_Disc_D4.3mm_W1.9mm_P5.00mm" H 3388 2450 50  0001 C CNN
F 3 "" H 3350 2600 50  0001 C CNN
	1    3350 2600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR017
U 1 1 597CE50E
P 3350 2800
F 0 "#PWR017" H 3350 2550 50  0001 C CNN
F 1 "GND" H 3350 2650 50  0000 C CNN
F 2 "" H 3350 2800 50  0001 C CNN
F 3 "" H 3350 2800 50  0001 C CNN
	1    3350 2800
	1    0    0    -1  
$EndComp
$Comp
L CP C1
U 1 1 597C5AC0
P 1900 1400
F 0 "C1" H 1925 1500 50  0000 L CNN
F 1 "47uF" H 1925 1300 50  0000 L CNN
F 2 "Capacitors_THT:CP_Radial_D5.0mm_P2.00mm" H 1938 1250 50  0001 C CNN
F 3 "" H 1900 1400 50  0001 C CNN
	1    1900 1400
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG018
U 1 1 597C91BD
P 2750 1150
F 0 "#FLG018" H 2750 1225 50  0001 C CNN
F 1 "PWR_FLAG" H 2750 1300 50  0000 C CNN
F 2 "" H 2750 1150 50  0001 C CNN
F 3 "" H 2750 1150 50  0001 C CNN
	1    2750 1150
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG019
U 1 1 597C92DA
P 2750 1550
F 0 "#FLG019" H 2750 1625 50  0001 C CNN
F 1 "PWR_FLAG" H 2750 1700 50  0000 C CNN
F 2 "" H 2750 1550 50  0001 C CNN
F 3 "" H 2750 1550 50  0001 C CNN
	1    2750 1550
	1    0    0    -1  
$EndComp
Connection ~ 6500 3600
Connection ~ 6500 3300
Connection ~ 6500 3000
Wire Wire Line
	4500 2800 4900 2800
Wire Wire Line
	4700 2900 4900 2900
Connection ~ 4500 3200
Connection ~ 4500 2800
Connection ~ 1600 3050
Wire Wire Line
	1600 2700 1600 2650
Wire Wire Line
	3200 5850 3200 5800
Wire Wire Line
	5500 5750 5500 5800
Wire Wire Line
	5150 5550 5200 5550
Wire Wire Line
	5100 5100 5100 5300
Wire Wire Line
	5100 5300 5500 5300
Wire Wire Line
	5500 5250 5500 5350
Connection ~ 5500 5300
Wire Wire Line
	5500 4550 5500 4650
Wire Wire Line
	5500 4600 5100 4600
Wire Wire Line
	5100 4600 5100 4800
Connection ~ 5500 4600
Wire Wire Line
	1250 3050 1200 3050
Wire Wire Line
	1550 3050 2300 3050
Wire Wire Line
	1600 3000 1600 3100
Wire Wire Line
	1600 3450 1600 3400
Wire Wire Line
	4200 4400 4400 4400
Wire Wire Line
	4200 4600 4400 4600
Wire Wire Line
	4200 4700 4400 4700
Wire Wire Line
	4200 4800 4400 4800
Wire Wire Line
	4200 4900 4400 4900
Wire Wire Line
	4200 5000 4400 5000
Wire Wire Line
	4200 5100 4400 5100
Wire Wire Line
	4200 5200 4400 5200
Wire Wire Line
	4200 5300 4400 5300
Wire Wire Line
	4200 4300 4400 4300
Wire Wire Line
	4200 4200 4400 4200
Wire Wire Line
	4200 4100 4400 4100
Wire Bus Line
	4500 4200 4500 6200
Wire Wire Line
	8700 4300 8700 4550
Wire Wire Line
	9200 4300 9200 4550
Wire Wire Line
	9700 4300 9700 4550
Wire Wire Line
	10200 4300 10200 4550
Wire Wire Line
	6450 3000 6500 3000
Wire Wire Line
	6450 3300 6500 3300
Wire Wire Line
	6450 3600 6500 3600
Wire Wire Line
	6500 2700 6450 2700
Wire Wire Line
	4500 2750 4500 2850
Wire Bus Line
	8100 6100 8100 4200
Wire Bus Line
	8100 4200 10100 4200
Wire Wire Line
	7500 5350 7500 5450
Wire Wire Line
	7500 4550 7500 4650
Connection ~ 7500 4600
Connection ~ 7500 5400
Wire Wire Line
	7500 4950 7500 5050
Wire Wire Line
	7500 4200 7500 4250
Wire Wire Line
	7500 5750 7500 5800
Connection ~ 7500 5000
Wire Wire Line
	6500 2700 6500 3650
Wire Wire Line
	5850 3000 6050 3000
Wire Wire Line
	5750 2700 6050 2700
Wire Wire Line
	4700 3200 4700 2900
Wire Wire Line
	4500 3200 4500 3150
Wire Wire Line
	4200 3200 4700 3200
Wire Wire Line
	5750 3300 5750 2700
Wire Wire Line
	5850 3400 5850 3000
Wire Wire Line
	6050 3300 5950 3300
Wire Wire Line
	5950 3300 5950 3500
Wire Wire Line
	7250 5000 7500 5000
Wire Wire Line
	4250 3700 4200 3700
Wire Wire Line
	4600 3700 4550 3700
Wire Wire Line
	4550 3700 4550 3600
Wire Wire Line
	5000 3700 4950 3700
Wire Wire Line
	4950 3700 4950 3500
Connection ~ 4950 3500
Wire Wire Line
	4200 3300 5750 3300
Wire Wire Line
	4200 3400 5850 3400
Wire Wire Line
	5950 3500 4200 3500
Wire Wire Line
	4200 3600 6050 3600
Connection ~ 4550 3600
Wire Wire Line
	8850 3400 9000 3400
Wire Wire Line
	8850 3150 9000 3150
Wire Wire Line
	8850 2900 9000 2900
Wire Wire Line
	8800 2550 8800 2500
Wire Wire Line
	8800 2500 9000 2500
Wire Wire Line
	4800 4000 4800 5550
Wire Wire Line
	4800 4000 4200 4000
Wire Wire Line
	8850 3650 9000 3650
Wire Wire Line
	9800 5950 9800 6100
Wire Wire Line
	9700 5950 9700 6100
Wire Wire Line
	9600 5950 9600 6100
Wire Wire Line
	9500 5950 9500 6100
Wire Wire Line
	9400 6100 9400 5950
Wire Wire Line
	9300 6100 9300 5950
Wire Wire Line
	9200 6100 9200 5950
Wire Wire Line
	9100 6100 9100 5950
Wire Wire Line
	2250 1600 2250 1550
Wire Wire Line
	1900 1600 1900 1550
Connection ~ 1900 1600
Connection ~ 2250 1600
Wire Wire Line
	2250 1200 2250 1250
Wire Wire Line
	1900 1200 1900 1250
Connection ~ 2250 1200
Connection ~ 1900 1200
Wire Wire Line
	1550 1400 1550 1600
Connection ~ 1550 1500
Wire Wire Line
	1550 1300 1550 1200
Wire Wire Line
	1550 1600 3200 1600
Wire Wire Line
	1550 1200 3200 1200
Wire Wire Line
	7500 5400 7750 5400
Wire Wire Line
	7750 5400 7750 5150
Wire Wire Line
	7500 4600 7750 4600
Wire Wire Line
	7750 4600 7750 4850
Wire Wire Line
	8800 2250 9000 2250
Wire Wire Line
	8800 2200 8800 2250
Wire Wire Line
	2150 3400 2300 3400
Wire Wire Line
	2150 3350 2150 3400
Wire Wire Line
	2300 3050 2300 3200
Wire Wire Line
	3350 2750 3350 2800
Wire Wire Line
	3350 2450 3350 2400
Wire Wire Line
	3350 2400 3200 2400
Connection ~ 3200 2400
Wire Wire Line
	3200 2350 3200 2900
Wire Wire Line
	4900 3000 4850 3000
Wire Wire Line
	4850 3000 4850 3050
Wire Wire Line
	3200 1200 3200 1150
Wire Wire Line
	2750 1150 2750 1200
Connection ~ 2750 1200
Wire Wire Line
	2750 1600 2750 1550
Wire Wire Line
	3200 1600 3200 1650
Connection ~ 2750 1600
Wire Wire Line
	6200 5300 5900 5300
Wire Wire Line
	5900 5300 5900 5250
Wire Wire Line
	4800 5550 4850 5550
Wire Wire Line
	7250 3900 7250 5000
Wire Wire Line
	4200 3900 7250 3900
Wire Bus Line
	4500 6200 9900 6200
Wire Wire Line
	5800 4600 5800 4650
Wire Wire Line
	6000 4600 6000 4650
Wire Wire Line
	6200 4600 6200 5300
Text Notes 550  7700 0    60   ~ 0
Fuses ("0" means programmed):\n1. CKSEL3:0 = 0100 (enabling the Internal Calibrated RC Oscillator @ 8 MHz);\n2. BODEN = 0, BODLEVEL = 0, SUT1:0 = 00 (enabling the Internal Brown-out Detector).\n\nNotes:\n1. D2 is a green LED (heating is disabled), D3 is a red LED (heating is enabled).
$EndSCHEMATC
