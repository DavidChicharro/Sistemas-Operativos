MKDIR = mkdir
REMOVE = rm -r
BIN = bin

all:
	$(MKDIR) $(BIN)
	gcc -o bin/productorFIFO productorFIFO.c
	gcc -o bin/consumidorFIFO consumidorFIFO.c	
	gcc -o bin/tarea6 tarea6.c
	gcc -o bin/tarea7 tarea7.c
	gcc -o bin/tarea8 tarea8.c
	gcc -o bin/maestro_ej5 maestro_ej5.c
	gcc -o bin/esclavo_ej5 esclavo_ej5.c -lm

clean:
	$(REMOVE) $(BIN)

