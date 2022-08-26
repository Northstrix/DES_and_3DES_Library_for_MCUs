Changes in the fork <b>DES_and_3DES_Library_for_MCUs </b> by <b>Northstrix</b>:
1) Made it compatible with the ESP32, Raspberry Pi Pico, and STM32F103C8T6 by removing several unused lines;
2) Removed unused examples and added the new ones.



Please see the full documentation at http://spaniakos.github.io/ArduinoDES

DES_Library
===========

This project is a fork from ArduinoDES project that implements a DES and Triple DES encryption and
decryption library for the Arduino and Rpi.

I've made some changes so that this library can be used and compiled in ESP8266 Sming Framework 
based projects.

For the original library and instructions, please refer to https://github.com/Octoate/ArduinoDES.git

Usage
=====

It is possible to encrypt and decrypt messages with the DES or Triples DES crypto algorithms.
Have a look at the example code for more information.

To use in Sming framework, just copy the DES.cpp file for the **app** directory, and the include files **DES.h** and **DES_config.h** for the **include** directory.

On the main application include the DES.h file, and the encryption and decryption API is now available.

```
#include <SmingCore/SmingCore.h>
#include <DES.h>
```

Under the directory **examples_ESP8266** there is a example **application.cpp* file that mimics the original example.

License
=======

Library for DES and 3DES encryption and decryption
Ported to the Arduino platform 2013 by Tim Riemann

Original version taken from the AVR-Crypto-Lib
(http://www.das-labor.org/wiki/AVR-Crypto-Lib)
Copyright (C) 2006-2010  Daniel Otte (daniel.otte@rub.de)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
