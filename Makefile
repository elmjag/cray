cray: main.c graphics.c
	$(CC) -g -o cray -I/usr/include/SDL2 -D_REENTRANT main.c graphics.c -lSDL2

clean:
	rm -f cray
