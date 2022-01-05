/*
 * Copyright (C) 2022 Olaf Bergmann
 *
 * SPDX-License-Identifier: MIT
 */

#include "pm1006.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

pm1006_value_t pm1006_parse_values(const uint8_t *data,
                                   size_t maxlen,
                                   pm1006_data_t *result) {
  assert(data);
  assert(result);

  memset(result, 0, sizeof(pm1006_data_t));

  enum { DF3 = 5, DF4, DF5, DF6, DF7, DF8, DF9, DF10, DF11, DF12 };

  if (maxlen > DF4) {
    result->pm25 = (data[DF3] << 8) + data[DF4];
    result->valid |= VALUE_PM25;
  }
  if (maxlen > DF8) {
    result->pm1 = (data[DF7] << 8) + data[DF8];
    result->valid |= VALUE_PM1;
  }
  if (maxlen > DF12) {
    result->pm10 = (data[DF11] << 8) + data[DF12];
    result->valid |= VALUE_PM10;
  }
  return result->valid;
}

int pm1006_check_header(const uint8_t *data, size_t length) {
  return length >= 3 &&
    (data[0] == 0x16 && data[1] == 0x11 && data[2] == 0x0b);
}

int pm1006_check_sum(const uint8_t *data, size_t length) {
  uint8_t checksum = 0;
  while(length--) {
    checksum += *data++;
  }
  return checksum == 0;
}
