CFLAGS = -Iinclude -std=gnu99 -O3

%.o: %.c
	$(CC) $(CFLAGS) -c $<

SRC_C = $(wildcard *.c)

OBJ = $(SRC_C:.c=.o)

vincenty: $(OBJ)
	$(CC) -o $@ $+ -lm

.PHONY: clean
clean:
	rm -f *.o vincenty
