CC = gcc
CFLAGS = -Wall -Wextra

build:
	$(CC) $(CFLAGS) -o copy2 copy2.c

debug:

	$(CC) $(CFLAGS) -g -o copy2 copy2.c

memcheck: debug
	valgrind --leak-check=full ./copy2 source.txt target.txt

clean:
	rm -f copy2
