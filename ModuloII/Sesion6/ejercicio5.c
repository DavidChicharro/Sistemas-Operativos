/*
ejercicio5.c
Compilación: gcc -o ejercicio5 ejercicio5.c

 Programa, similar a la orden cp, que utiliza, para su implementación, 
la llamada al sistema mmap() y una función de C que permite copiar 
memoria, como por ejemplo memcpy(). Para conocer el tamaño del archivo 
origen se puede utilizar stat() y para establecer el tamaño del archivo 
destino se puede usar ftruncate().

*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/mman.h>

int main(int argc, char **argv) {
	int	fd;
	char *origen, *destino;
	char *ptr, *ptr2;
	struct stat st;
	int copia;

	if (argc != 3){
		printf("Uso: ./ejercicio5 <origen> <destino>\n");
		exit(EXIT_FAILURE);
	}

	origen = argv[1];
	destino = argv[2];

	// Abrir el archivo de origen
	if ( (fd = open(origen, O_RDONLY)) < 0 ){
		perror("Error en open");
		exit(EXIT_FAILURE);
	}

	// Recuperar información sobre el archivo apuntado
	if ( (fstat(fd, &st)) < 0 ){
		perror("Error en stat");
		exit(EXIT_FAILURE);
	}

	// Comprobar si es un archivo regular
	if(!S_ISREG(st.st_mode)){
		printf("No es regular");
		exit(EXIT_FAILURE);
	}

	// Crear el mapa de memoria del archivo origen
	ptr = (char*) mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	close(fd);

	if (ptr == MAP_FAILED){
		perror("Error en mmap");
		exit(EXIT_FAILURE);
	}

	// Crear al archivo destino
	if ( (copia=open(destino, O_RDWR|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)) < 0 ){
		perror("Error al crear fichero destino");
		exit(EXIT_FAILURE);
	}

	if ( (ftruncate(copia, st.st_size)) < 0 ){
		perror("Error en ftruncate");
		exit(EXIT_FAILURE);
	}

	// Crear el mapa de memoria del archivo destino
	ptr2 = (char*) mmap(NULL, st.st_size, PROT_WRITE, MAP_SHARED, copia, 0);

	if (ptr2 == MAP_FAILED){
		perror("En mmap");
		exit(EXIT_FAILURE);
	}

	close(copia);
	// Copiar el mapa de memoria origen en el de destino
	memcpy(ptr2, ptr, st.st_size);

	return EXIT_SUCCESS;
}