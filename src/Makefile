CC      := gcc
CFLAGS  := -Wpedantic -Wall -Wextra -O2
LDFLAGS := -ltiff

SRC     := main.c preprocessor.c
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
