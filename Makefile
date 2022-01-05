# Makefile for serial-read
# Copyright (C) 2022 Olaf Bergmann
# SPDX-License-Identifier: MIT

CFLAGS=-Wall -Wextra -Werror

all: serial-read

serial-read::serial-read.o pm1006.o

.PHONY: clean
clean:
	rm -f serial-read.o pm1006.o serial-read core
