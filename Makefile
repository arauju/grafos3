main: GRAFOmatriz.c FILA.c main.c
	gcc -O3 GRAFOmatriz.c FILA.c main.c -o main

clean :
	rm main

