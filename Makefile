CC := gcc
TARGET := tetris

SRC := $(wildcard *.c)
OBJ := $(SRC:.c=.o)
HEADERS := main.h

CFLAGS := -Wall -Wextra -std=c11
PKG_CONFIG ?= pkg-config

RAYLIB_CFLAGS := $(shell $(PKG_CONFIG) --cflags raylib 2>/dev/null)
RAYLIB_LIBS := $(shell $(PKG_CONFIG) --libs raylib 2>/dev/null)

# Fallback Linux si pkg-config ne trouve pas raylib.
ifeq ($(strip $(RAYLIB_LIBS)),)
RAYLIB_LIBS := -lraylib -lm -lpthread -ldl -lrt -lX11
endif

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(RAYLIB_LIBS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(RAYLIB_CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)

re: clean all

.PHONY: all run clean re
