//
// PROJEKT PTL-FLY01
// Created by SQ2MTG 08-2017
//
#ifndef RS41HUP_CONFIG_H
#define RS41HUP_CONFIG_H

#ifdef USE_EXTERNAL_CONFIG
#include "config_external.h"
#else


//**************RTTY Data Format**********************
// $$<calsign>,<frame>,<hhmmss>,<latitude>,<longitude>,<height>,<radio chip temperature (°C)>,<battery voltage>,<used gps satellites>,<good gps datasets>,<bad gps datasets>,<gps fix>,<CRC>
// $$<znak>,<nr wysłanej ramki RTTY><czas>,<współrzędne Lat + Lon>,<wysokość><temperatura><napięcie baterii><ilośc satelitów GPS><Funkcje GPS><CRC>

//**************config**********************
#define CALLSIGN "PTL-FLY01" // znak nadawany RTTY
#define APRS_CALLSIGN "PTL-FLY01" // znak nadawany APRS min. 6 znakow (jeśli nie dodaj spację)
#define APRS_SSID 'B' // SSID APRS - domyslnie B dla balona

// 0 --> Your primary station usually fixed and message capable
// 1 --> generic additional station, digi, mobile, wx, etc.
// 2 --> generic additional station, digi, mobile, wx, etc.
// 3 --> generic additional station, digi, mobile, wx, etc.
// 4 --> generic additional station, digi, mobile, wx, etc.
// 5 --> Other network sources (Dstar, Iphones, Blackberry's etc)
// 6 --> Special activity, Satellite ops, camping or 6 meters, etc.
// 7 --> walkie talkies, HT's or other human portable
// 8 --> boats, sailboats, RV's or second main mobile
// 9 --> Primary Mobile (usually message capable)
// A --> internet, Igates, echolink, winlink, AVRS, APRN, etc.
// B --> balloons, aircraft, spacecraft, etc.
// C --> APRStt, DTMF, RFID, devices, one-way trackers*, etc.
// D --> Weather stations
// E --> Truckers or generally full time drivers
// F --> generic additional station, digi, mobile, wx, etc.

#define APRS_COMMENT " SP2PTL FLY01 Balon RS41-SG/R "
#define RTTY_TO_APRS_RATIO 3 // czestotliwosc wysyłania ramek APRS - standardowo: 3 x RTTY > 1 x APRS 
//*************TX Frequencies********************
#define RTTY_FREQUENCY  434.525f //Czestotliwosc TX dla RTTY
#define APRS_FREQUENCY  432.500f //Czestotliwosc TX dla APRS

//************RTTY Shift*********************** si4032
#define RTTY_DEVIATION 0x2	// RTTY shift = RTTY_DEVIATION x 270Hz standardowo 0x2 czyli 540Hz

//************RTTY Speed*********************** si4032
#define RTTY_SPEED  50 // RTTY baudrate

//************rtty bits************************ si4032
#define RTTY_7BIT   1 // if 0 --> 5 bits

//************rtty stop bits******************* si4032
#define RTTY_USE_2_STOP_BITS   0

//********* power definition**************************
#define TX_POWER  7 // PWR 0...7 0- MIN ... 7 - MAX
// 0 --> -1dBm
// 1 --> 2dBm
// 2 --> 5dBm
// 3 --> 8dBm
// 4 --> 11dBm
// 5 --> 14dBm
// 6 --> 17dBm
// 7 --> 20dBm
//****************************************************

// Switch sonde ON/OFF via Button
// If this is a flight you might prevent sonde from powered off by button
#define ALLOW_DISABLE_BY_BUTTON 1

//********** Frame Delay in msec**********************
#define TX_DELAY  10000 // standardowo co 10s RTTY , co 30s APRS
#endif

#endif //RS41HUP_CONFIG_H