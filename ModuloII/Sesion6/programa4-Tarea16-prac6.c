/*
Programa donde un proceso padre crea una proyección que se 
utiliza para almacenar un valor. El padre asignará valor a 
cnt y el hijo solo leerá el valor asignado por el padre (se 
hace así -sólo lectura en el hijo- para evitar condiciones 
de carrera y así evitar tener que introducir un mecanismo de 
sincronización para acceder al contador). También se puede 
ver cómo el archivo contiene el valor modificado del padre.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#define MMAPSIZE 1

int main (int argc, char *argv[]) {
	off_t len;
	char bufer='a';
	char *cnt;
	int fd;

	umask(0);
	fd = open("Archivo_p4", O_RDWR|O_CREAT|O_TRUNC, S_IRWXU);
	if (fd == -1) {
		perror("El archivo existe");
		exit(EXIT_FAILURE);
	}
	write(fd, &bufer, sizeof(char));

	cnt = (char *) mmap (0, MMAPSIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	if (cnt == MAP_FAILED) {
		printf("Fallo el mapeo\n");
		return EXIT_FAILURE;
	}
	if (close (fd) == -1) {
		printf("Error al cerrar el archivo\n");
		return EXIT_FAILURE;
	}

	if (fork() == 0) { /* hijo */
		sleep(2);
		printf("El valor de cnt es: %s\n", cnt);
		exit(EXIT_SUCCESS);
	}
	/* padre */
	strcpy(cnt, "b");
	
	exit(EXIT_SUCCESS);
}