# pm1006

Parser for the Cubic PM1006 serial protocol. The PM1006 is built into
the IKEA Vindriktning air quality sensor. This utility may be used to
read the data frames sent by the pm1006 over the serial line.

## Building

```
$ make
```

## Running

You can test with a USB-to-serial converter, e.g., CH-341 UART.

```
$ ./serial-read /dev/ttyUSB0
```

Note that the tty parameters are set to 9600 baud, 8N1, in raw
mode. If you use input redirection, you might need to do this manually:

```
$ stty -F /dev/ttyUSB0 9600 cs8 -cstopb -parenb raw
```
