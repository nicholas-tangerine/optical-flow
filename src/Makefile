CC      := gcc
CFLAGS  := -Wpedantic -Wall -Wextra -ggdb3 -O2
LDFLAGS := -ltiff

SRC     := main.c preprocessor.c tiff_helpers.c filename_utils.c debug_utils.c image.c
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
