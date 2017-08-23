/*
	Copyright (C) 2013 Lukasz Nidecki SQ5RWU

    This file is part of ArduinoQAPRS.

    ArduinoQAPRS is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    ArduinoQAPRS is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with ArduinoQAPRS; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

    Ten plik jest częścią ArduinoQAPRS.

    ArduinoQAPRS jest wolnym oprogramowaniem; możesz go rozprowadzać dalej
    i/lub modyfikować na warunkach Powszechnej Licencji Publicznej GNU,
    wydanej przez Fundację Wolnego Oprogramowania - według wersji 2 tej
    Licencji lub (według twojego wyboru) którejś z późniejszych wersji.

    Niniejszy program rozpowszechniany jest z nadzieją, iż będzie on
    użyteczny - jednak BEZ JAKIEJKOLWIEK GWARANCJI, nawet domyślnej
    gwarancji PRZYDATNOŚCI HANDLOWEJ albo PRZYDATNOŚCI DO OKREŚLONYCH
    ZASTOSOWAŃ. W celu uzyskania bliższych informacji sięgnij do
    Powszechnej Licencji Publicznej GNU.

    Z pewnością wraz z niniejszym programem otrzymałeś też egzemplarz
    Powszechnej Licencji Publicznej GNU (GNU General Public License);
    jeśli nie - napisz do Free Software Foundation, Inc., 59 Temple
    Place, Fifth Floor, Boston, MA  02110-1301  USA

 */

/**
 * @file
 * @brief Wspóldzielone definicje
 */

#ifndef QAPRSCOMMON_H_
#define QAPRSCOMMON_H_

#include <stdint.h>
#include <stddef.h>
#include <string.h>

/**
 * @brief Wyniki zwracane przez metodę send
 */
enum QAPRSReturnCode {
	QAPRSReturnOK = 0,         //!< Powodzenie
	QAPRSReturnError = 1,      //!< Nieokreslony błąd
	QAPRSReturnErrorTimeout = 2//!< Timeout w oczekiwaniu na nadawanie
};

/**
 * @brief Generowane znaczniki
 */
enum QAPRSSendingTone {
	QAPRSMark = 1,	//!< Mark (1200Hz)
	QAPRSSpace = 2	//!< Space (2200Hz)
};

/**
 * @brief Generowane znaczniki
 */
enum QAPRSVariant {
	QAPRSVHF = 1,	//!< VHF - 1200bodów, 1200Hz/2200Hz
	QAPRSHF = 2	//!< HF - 300bodów, 1600Hz/1800Hz
};

/**
 * @brief Struktura definująca podstawową ramkę ax.25 (bez realyów)
 */
typedef struct {
	char to[6]; 			//!< Odbiorca pakietu [znak]
	uint8_t to_ssid;		//!< SSID odbiorcy pakietu
	char from[6];			//!< Nadawca pakietu [znak]
	uint8_t from_ssid;		//!< SSID nadawcy pakietu
	uint8_t control_field;	//!< Pole kontrolne ustawiane zawsze na 0x03 - UI @see http://www.tapr.org/pub_ax25.html#2.3.4.2
	uint8_t protocolID;		//!< Id protokolu zawsze 0xf0 - bez warstwy 3 OSI @see http://www.tapr.org/pub_ax25.html#2.2.4
	char packet_content[];	//!< Zawartosć pakietu. Dane APRS
} ax25BaseFrame;

/**
 * @brief Struktura definiujaca poczatek ramki ax.25
 */
typedef struct {
	char to[6]; 			//!< Odbiorca pakietu [znak]
	uint8_t to_ssid;		//!< SSID odbiorcy pakietu
	char from[6];			//!< Nadawca pakietu [znak]
	uint8_t from_ssid;		//!< SSID nadawcy pakietu
} ax25CustomFrameHeader;



#endif /* QAPRSCOMMON_H_ */
