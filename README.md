# RS41HUP (Ham Use Project)
Firmware for RS41 for HAM use
It is posible to recycle RS41-SGP sondes for amateur radio use without any electrical changes. You just have to build a new firmware (this one) and apply it via a cheap adaptor "ST-Linkv2". Modified sonde now transmits on defineable frequenca in 70cm band GPS and telemetry data in FSK RTTY format which is used by HAB projects and additionally it transmits APRS packets on a seperately defineable TX frequency.

Released under GPL v2


# Windows:

Use:
https://www.wyzbee.com/download/Utilities/Software/CoIDE-1.7.8.exe

And:
https://launchpad.net/gcc-arm-embedded/5.0/5-2016-q3-update/+download/gcc-arm-none-eabi-5_4-2016q3-20160926-win32.exe


# Linux:
cd into main folder

cmake .

make

# Configuration
All configs in ```config.h```

* ```CALLSIGN``` RTTY callsign
* ```APRS_CALLSIGN``` APRS callsign, 6 characters. If your callsign is shorter add spaces
* ```APRS_SSID``` APRS SSID
* ```APRS_COMMENT``` APRS comment
* ```RTTY_TO_APRS_RATIO``` number of RTTY frames between each APRS frame
* ```RTTY_FREQUENCY``` RTTY frequency in MHz
* ```APRS_FREQUENCY``` APRS frequency in MHz
* ```RTTY_DEVIATION``` RTTY shift configurable in 270Hz steps
* ```RTTY_SPEED``` RTTY speed in bauds
* ```RTTY_7BIT``` Use 7 bit RTTY
* ```RTTY_USE_2_STOP_BITS``` use 2 stop bits
* ```TX_POWER``` Power 0-7, (7 means 42.95 mW@434.150 MHz measured on E4406A)
* ```TX_DELAY``` Delay between frames in milliseconds
* ```ALLOW_DISABLE_BY_BUTTON``` Allow disabling device using button


Have a nice day ;)

#Changelog
 * 14.12.2016 - Reverse engineeded connections, initial hard work, resulting in working RTTY by SQ7FJB
 * 07.01.2017 - GPS now using proprietiary UBLOX protocol, more elastic code to set working frequency by SQ5RWU
 * 23.01.2017 - Test APRS code, small fixes in GPS code by SQ5RWU
 * 06.06.2017 - APRS code fix, some code cleanup
 * June 2017 - starting with Linux support, making configuration more flexible by DF8OE


#TODO
 * Adding support for EmbiTZ IDE
 * Adding support for platform independent IDE Eclipse
 * More APRS config options
 * Temperature and moisture sensor
 * Pressure sensor
 * implementing protocol for using external devices on extension header
 * Configuration via extension header (serial connection) without need for reflashing firmware
 * Possibly add configuration "wireless" using RFID loop present in sonde
