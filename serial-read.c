#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

#include "pm1006.h"

int main(int argc, char **argv) {
  int dev = fileno(stdin);
  if (argc > 1) {
    struct termios termios_p;
    dev = open(argv[1], O_RDONLY);
    if (dev < 0) {
      perror("open");
      exit(EXIT_FAILURE);      
    }
    if (tcgetattr(dev, &termios_p) < 0) {
      perror("tcgetattr");
      exit(EXIT_FAILURE);
    }
    if (cfsetispeed(&termios_p, B9600) < 0) {
      perror("cfsetispeed");
      exit(EXIT_FAILURE);
    }
    cfmakeraw(&termios_p);
  } else {
    printf("# Reading from stdin. When redirecting input you might\n"
           "# want to set tty parameters, e.g., for ttyUSB0:\n"
           "# stty -F /dev/ttyUSB0 9600 cs8 -cstopb -parenb raw\n");
  }

  while (1) {
    pm1006_data_t pm_data;
    uint8_t buf[20];
    ssize_t res = read(dev, buf, sizeof(buf));
    if (res > 0) {
      printf("received: ");
      for (size_t i = 0; i < (size_t)res; i++) {
        printf("%02x ", buf[i]);
      }
      printf("\n");
      if (!pm1006_check_header(buf, res) || !pm1006_check_sum(buf, res)) {
        printf("NOT OK\n");
        continue;
      }

      if (pm1006_parse_values(buf, res, &pm_data)) {
        if (pm_data.valid & VALUE_PM1)
          printf("pm1: %u\n", pm_data.pm1);
        if (pm_data.valid & VALUE_PM25)
          printf("pm2.5: %u\n", pm_data.pm25);
        if (pm_data.valid & VALUE_PM10)
          printf("pm10: %u\n", pm_data.pm10);
      }
    }
  }

  return 0;
}
