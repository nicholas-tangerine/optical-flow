CC      := gcc
CFLAGS  := -Wpedantic -Wall -Wextra -g -O2
LDFLAGS := -ltiff

SRC     := main.c preprocessor.c tiff_io.c filename_utils.c
OBJ     := $(SRC:.c=.o)
TARGET  := main

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
