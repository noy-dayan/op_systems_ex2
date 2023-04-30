CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic

all: cmp copy codecA.so codecB.so encode decode stshell

cmp: cmp.c
	$(CC) $(CFLAGS) -o $@ $<

copy: copy.c
	$(CC) $(CFLAGS) -o $@ $<

codecA.so: codecA.c
	$(CC) $(CFLAGS) -fPIC -shared -o $@ $<

codecB.so: codecB.c
	$(CC) $(CFLAGS) -fPIC -shared -o $@ $<

encode: encode.c
	$(CC) $(CFLAGS) -fPIC -ldl -o $@ $<

decode: decode.c
	$(CC) $(CFLAGS) -fPIC -ldl -o $@ $<

stshell: stshell.c
	$(CC) -Wall -o $@ $<

clean:
	rm -f *.so cmp copy encode decode stshell
