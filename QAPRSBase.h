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
 * @brief Nagłówki dla klasy QAPRSBase
 */

#ifndef QAPRSBASE_H_
#define QAPRSBASE_H_

#include "QAPRSCommon.h"

/**
 * @brief Klasa bazowa do nadawania APRS
 * @details Klasa słuzy jako baza do podimplemntacji generowania AFSK.
 */
class QAPRSBase {
private:
	/**
	 * @brief suma kontrolna pakietu
	 */
	uint16_t ax25CRC;
	/**
	 * @brief ilosć bajtów synchronizacyjnych do nadania przed zawartoscią pakietu
	 */
	static const uint8_t ax25HeaderFlagFieldCount1200 = 25;
	/**
	 * @brief ilosć bajtów synchronizacyjnych do nadania przed zawartoscią pakietu
	 */
	static const uint8_t ax25HeaderFlagFieldCount300 = 45;
	/**
	 * @brief ilosć bajtów synchronizacyjnych do nadania przed zawartoscią pakietu
	 */
	uint8_t ax25HeaderFlagFieldCount;
	/**
	 * @brief Flaga
	 * @details <http://www.tapr.org/pub_ax25.html#2.2.1>
	 */
	static const uint8_t ax25FlagFieldValue = 0x7E;
	/**
	 * @brief Czas wysyłania podedynczego tonu. W us.
	 * @details Czas calkowity powinien wynosic 833us. Wartosć podana tutaj uwzględnia zwłokę związaną z wywoływaniem
	 * funkcji itp.
	 */
#if F_CPU == 16000000L
	static const uint16_t toneSendTime1200 = 815;
#elif F_CPU == 8000000UL
	static const uint16_t toneSendTime1200 = 785;
#else
	//static const uint16_t toneSendTime1200 = 1000000/1200;
#endif
	/**
	 * @brief Czas wysyłania podedynczego tonu. W ms.
	 * @details Czas calkowity powinien wynosic 4*833ms. Wartosć podana tutaj uwzględnia zwłokę związaną z wywoływaniem
	 * funkcji itp.
	 */
	static const uint16_t toneSendTime300 = 815 + 3 * 833;
	/**
	 * @brief Czas oczekiwania na zwolnienie kanału.
	 * @details Co 100ms sprawdzamy czy można już nadawać @see canTransmit
	 */
	static const uint16_t channelFreeWaitingMS = 1; // 2000 ms
	/**
	 * @brief Domylslny czas pomiędzy włączeniem nadawania a rozpoczęciem generowania AFSK
	 */
	static const uint16_t defaultTxDelay = 1; // 300 ms
	/**
	 * @brief Pin Arduino na którym ustawiamy logiczną 1 w momencie nadawania
	 */
	int8_t txEnablePin;
	/**
	 * @brief Bufor tymczasowy
	 */
	uint8_t tmpData[255];
	/**
	 * @brief Opóźnienie w ms pomiędzy ustawieniem stanu wysokiego na wyjsciu txEnablePin a rozpoczęciem generowania AFSK
	 */
	uint16_t txDelay;
	/**
	 * @brief
	 */
	char from_addr[6];
	/**
	 * @brief
	 */
	uint8_t from_ssid;
	/**
	 * @brief
	 */
	char to_addr[6];
	/**
	 * @brief
	 */
	uint8_t to_ssid;
	/**
	 * @brief
	 */
	char* relays[3*7];

	uint8_t canTransmit();
	void ax25SendHeaderBegin();
	void ax25SendByte(uint8_t byte);
	void ax25SendFooter();
	void ax25CalcCRC(uint8_t ls_bit);
	void parseRelays(const char * relays, char * dst);
protected:
	/**
	 * @brief Pin Arduino [we] który musi być w stanie niskim (lub wysokim, jesli numer jest ujemny) aby rozpocząć nadawanie.
	 */
	int8_t sensePin;
	/**
	 * @brief Obecnie generowany ton
	 */
	QAPRSSendingTone currentTone;
	/**
	 * @brief Obecnie używany wariant
	 */
	QAPRSVariant variant;

	void initializeRadio();
	void enableTransmission();
	void disableTranssmision();

	void toggleTone();
	void initializeTimer1();
	void delayuSeconds(uint16_t us);
	void doTxDelay();
public:
	QAPRSBase() {};
	QAPRSReturnCode send(char * buffer);
	QAPRSReturnCode send(char * buffer, size_t length);
	QAPRSReturnCode send(char * from_addr, uint8_t from_ssid, char * to_addr, uint8_t to_ssid, char * packet_content);
	QAPRSReturnCode send(char * from_addr, uint8_t from_ssid, char * to_addr, uint8_t to_ssid, char * relays, char * packet_content);
	QAPRSReturnCode send(char * from_addr, uint8_t from_ssid, char * to_addr, uint8_t to_ssid, char * relays, char * packet_content, size_t length);
	QAPRSReturnCode sendData(char * buffer);
	QAPRSReturnCode sendData(char * buffer, size_t length);

	void init(int8_t sensePin, int8_t txEnablePin);
	void init(int8_t sensePin, int8_t txEnablePin, char * from_addr, uint8_t from_ssid, char * to_addr, uint8_t to_ssid, char * relays);

	void setTxDelay(uint16_t txDelay);
	void timerInterruptHandler();
	void setFromAddress(char * from_addr, uint8_t from_ssid);
	void setToAddress(char * to_addr, uint8_t to_ssid);
	void setRelays(char * relays);
	void setVariant(QAPRSVariant variant = QAPRSVHF);

private:
  static const uint16_t toneSendTime = 833;

	static const uint16_t toneSendTime1200 = 795;
  static const uint16_t MarkTimerValue = 393;
  static const uint16_t SpaceTimerValue = 202;
  void togglePin();
  uint8_t pin;
public:
  uint8_t enabled;
  uint16_t timer1StartValue;
	uint16_t _toneSendTime;
};

/**
 * @brief Przesuń bajt o 1 bit w lewo. Używane w nagłówku ax.25
 */
#define SHIFT_BYTE(x) (x << 1)

#endif /* QAPRSBASE_H_ */
