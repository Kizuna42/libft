# Test runner for libft (not part of the 42 submission).
# Builds every source together with the tests under ASan/UBSan.

CC ?= cc
ROOT = ..
CFLAGS = -Wall -Wextra -Werror -g -I$(ROOT) \
	-fsanitize=address,undefined -fno-sanitize-recover=all

SRCS = $(wildcard $(ROOT)/src/*/*.c)
BIN = test_libft

all: test

$(BIN): test_main.c $(SRCS) $(ROOT)/libft.h
	$(CC) $(CFLAGS) -DTEST_BONUS test_main.c $(SRCS) -o $(BIN)

test: $(BIN)
	./$(BIN)

clean:
	rm -f $(BIN)

.PHONY: all test clean
