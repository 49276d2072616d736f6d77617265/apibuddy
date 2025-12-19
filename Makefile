CC = gcc

CFLAGS = -Wall -Wextra -Iinclude
LDFLAGS =

SRC = \
	main.c \
	core/libc.c \
	core/nums.c \
	core/printf.c \
	core/http/http.c \
	core/parsing/markdown.c

OBJ = $(SRC:.c=.o)

OUT = apibuddy

all: $(OUT)

$(OUT): $(OBJ)
	$(CC) $(OBJ) -o $(OUT) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(OUT)

.PHONY: all clean
