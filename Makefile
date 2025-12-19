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

OBJDIR = build
OUTDIR = out

OBJ = $(patsubst %.c,$(OBJDIR)/%.o,$(SRC))

OUT = $(OUTDIR)/apibuddy

all: $(OUT)

$(OUT): $(OBJ)
	@mkdir -p $(OUTDIR)
	$(CC) $(OBJ) -o $(OUT) $(LDFLAGS)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(OUTDIR)

.PHONY: all clean
