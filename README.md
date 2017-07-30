# AVRThermostat

AVRThermostat is, as the name implies, a programmable thermostat, which is built
on

* Atmel AVR ATmega8A microcontroller,

* digital thermometer DS18B20 by Maxim Integrated,

* four-digit seven-segment led display with common cathode (like CC56-12 or
FYQ-5641A),

and uses a relay to control a heater or fan. The device can be used as a simple
thermometer as well. The sensor measures temperatures from -55°C to +125°C
with ±0.5°C accuracy from -10°C to +85°C.

The thermostat has 4 buttons (Plus, Minus, Set, Reset) that are used to set up
parameters--the setpoint and the zone (delta). The longer you hold the 
Plus/Minus button, the faster a parameter increases/decreases. The Reset button
is used to set the standard value to a parameter, also to switch off the
thermostat mode. Parameters are saved in EEPROM after editing.

The Plus/Minus buttons also are used to adjust the display brightness when
the device is not in the mode of editing of a parameter.

Two leds indicate the state of the relay. If the device is not in the thermostat
mode, then both leds do not light.

If the device cannot establish connection with the sensor, the display shows
an error.

## Schematics and PCB Layout r3.0

A KiCad project, which includes a schematics and PCB layout, is located in
[the Design directory](Design/). **Please be aware that the project is made from
scratch and I have not yet used the new PCB layout myself, therefore it may have
errors.**

### Schematics

![Schematics r3.0](http://artyom.protaskin.ru/storage/avrthermostat/pictures/avrthermostat-schematics-r30.png?2)

### PCB 3D Model

![PCB 3D Model r3.0](http://artyom.protaskin.ru/storage/avrthermostat/pictures/avrthermostat-3dmodel-r30.png?2)

## Versioning

For transparency and insight into our release cycle, and for striving to
maintain backwards compatibility, AVRThermostat will be maintained under the
Semantic Versioning guidelines as much as possible.

For more information on SemVer, please visit http://semver.org/

## License

Copyright 2014-2017 Artyom Protaskin

Licensed under the MIT License:

http://opensource.org/licenses/MIT
