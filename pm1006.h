/*
 * Copyright (C) 2022 Olaf Bergmann
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef PM1006_H
#define PM1006_H 1

#include <stddef.h>
#include <stdint.h>

typedef enum {
  VALUE_PM1  = 1,
  VALUE_PM25 = 2,
  VALUE_PM10 = 4,
} pm1006_value_t;

typedef struct {
  uint16_t pm1;
  uint16_t pm25;
  uint16_t pm10;
  pm1006_value_t valid;
} pm1006_data_t;

pm1006_value_t pm1006_parse_values(const uint8_t *data,
                                   size_t maxlen,
                                   pm1006_data_t *result);

int pm1006_check_header(const uint8_t *data, size_t length);

int pm1006_check_sum(const uint8_t *data, size_t length);

#endif /* PM1006_H */
