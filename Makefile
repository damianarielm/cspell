all:
	gcc main.c tablahash.c cadena.c sugerencias.c -o spell -g
clean:
	rm spell
