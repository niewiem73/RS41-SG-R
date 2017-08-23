//
// Created by Admin on 2017-01-09.
//

#ifndef RS41HUP_APRS_H
#define RS41HUP_APRS_H

#ifdef __cplusplus
#include <stdint.h>
#include <stdlib.h>
#include "ublox.h"

extern "C" {
#endif
  void aprs_init();
  void aprs_timer_handler();
  uint8_t aprs_is_active();
  void aprs_send_position(GPSEntry gpsData, int8_t temperature, uint16_t voltage);
  void aprs_change_tone_time(uint16_t x);
  void aprs_test();
#ifdef __cplusplus
};
#endif
#endif //RS41HUP_APRS_H
