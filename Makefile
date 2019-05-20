all:
	gcc main.c tablahash.c cadena.c -lm -o spell
clean:
	rm spell
