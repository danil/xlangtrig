all:
	gcc -Wall -O2 xlangtrig.c -o xlangtrig -lX11

clean:
	rm --force xlangtrig
