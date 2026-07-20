#
#   Copyright (c) 2026 Sam (sjbeaumont)
#   SPDX-License-Identifier: MIT
#   Distributed under the terms of the MIT License.
#

# compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -O2

# program name
TARGET = kwic

# src files and objs
SRCS = kwic.c flags.c other.c
OBJS = kwic.o flags.o other.o

# rule (make)
all: $(TARGET)

# glue .o
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# .c -> .o
kwic.o: kwic.c include/other.h include/flags.h
	$(CC) $(CFLAGS) -c kwic.c

flags.o: flags.c include/flags.h include/other.h
	$(CC) $(CFLAGS) -c flags.c

other.o: other.c include/other.h
	$(CC) $(CFLAGS) -c other.c

# cleanup (make clean)
clean:
	rm -f $(OBJS) $(TARGET)