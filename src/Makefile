CC      := gcc
CFLAGS  := -Wconversion -Wpedantic -Wall -Wextra -g -O2 -I "../includes/"
LDFLAGS := -ltiff -lm

SRC     := main.c preprocessor.c tiff_helpers.c filename_utils.c debug_utils.c image.c math_helper.c ofm_helper.c ofm.c
OBJ     := $(SRC:.c=.o)
TARGET  := main

MISC	:= *.ppm

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET) $(MISC)
