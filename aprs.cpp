//
// Created by Admin on 2017-01-09.
//

#include "aprs.h"
#include "QAPRSBase.h"
#include "stdio.h"
#include "ublox.h"
#include "config.h"

#if !defined(__OPTIMIZE__)
#error "APRS Works only when optimization enabled at level at least -O2"
#endif
QAPRSBase qaprs;

void aprs_init(){
  qaprs.init(0, 0, (char *) APRS_CALLSIGN, (const uint8_t) APRS_SSID, (char *) "APZQAP", '0', (char *) "WIDE1-1,WIDE2-1");

}

void aprs_timer_handler() {
  qaprs.timerInterruptHandler();
}

uint8_t aprs_is_active() {
  return qaprs.enabled;
}

void calcDMH(long x, int8_t* degrees, uint8_t* minutes, uint8_t* h_minutes) {
  uint8_t sign = (uint8_t) (x > 0 ? 1 : 0);
  if (!sign) {
    x = -(x);
  }
  *degrees = (int8_t) (x / 1000000);
  x = x - (*degrees * 1000000);
  x = (x) * 60 / 10000;
  *minutes = (uint8_t) (x / 100);
  *h_minutes = (uint8_t) (x - (*minutes * 100));
  if (!sign) {
    *degrees = -*degrees;
  }
}

void aprs_test(){
  char packet_buffer[128];
  sprintf(packet_buffer,
          (":TEST1234567890")
  );
  qaprs.sendData(packet_buffer);
}

void aprs_send_position(GPSEntry gpsData, int8_t temperature, uint16_t voltage) {
  char packet_buffer[128];
  int8_t la_degrees, lo_degrees;
  uint8_t la_minutes, la_h_minutes, lo_minutes, lo_h_minutes;

  calcDMH(gpsData.lat_raw/10, &la_degrees, &la_minutes, &la_h_minutes);
  calcDMH(gpsData.lon_raw/10, &lo_degrees, &lo_minutes, &lo_h_minutes);

  static uint16_t aprs_packet_counter = 0;
  aprs_packet_counter ++;

  sprintf(packet_buffer,
          ("!%02d%02d.%02u%c/%03d%02u.%02u%cO/A=%06ld/P%dS%dT%dV%d%s"),
          abs(la_degrees), la_minutes, la_h_minutes,
          la_degrees > 0 ? 'N' : 'S',
          abs(lo_degrees), lo_minutes, lo_h_minutes,
          lo_degrees > 0 ? 'E' : 'W',
          (gpsData.alt_raw/1000) * 3280 / 1000,
          aprs_packet_counter,
          gpsData.sats_raw,
          temperature,
          voltage,
          APRS_COMMENT
  );
  qaprs.sendData(packet_buffer);
}

void aprs_change_tone_time(uint16_t x) {
  qaprs._toneSendTime = x;
}

void t(){
//  // nadanie paketu typu komentarz
//  packet_buffer = ":TEST TEST TEST de SQ5RWU";
//  // zmiana adresu źródłowego i ssida
//  QAPRS.setFromAddress("SQ5R", '1');
//  QAPRS.sendData(packet_buffer);
//  // nadanie pakietu z pozycja i symbolem wahadlowca
//  packet_buffer = "!5215.68N/02057.48ES#";
//  // zmiana adresu źródłowego, ssida i ścieżki
//  QAPRS.setFromAddress("SQ5RWU", '2');
//  QAPRS.setRelays("WIDE2-2");
//  QAPRS.sendData(packet_buffer);
//  // nadanie danych pogodowych bez pozycji
//  packet_buffer = "_07071805c025s009g008t030r000p000P000h00b10218";
//  // zmiana ścieżki
//  QAPRS.setRelays("WIDE1-1");
//  QAPRS.sendData(packet_buffer);
//  delay(5000);
}
