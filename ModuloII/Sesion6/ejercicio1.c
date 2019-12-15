/*
ejercicio1.c
Compilación: gcc -o ejercicio1 ejercicio1.c

Programa que admite T argumentos done:
	- El primer argumento será una orden de Linux.
	- El segundo, uno de los siguientes caracteres "<" o ">".
	- El tercero, el nombre de un archivo (que puede existir o no).

El programa ejecutará la orden que se especifica como argumento primero 
e implementará la redirección especificada por el segundo argumento hacia
el archivo indicado en el tercer argumento.

Por ejemplo, si deseamos redireccionar la entrada estándar de sort 
desde un archivo temporal, ejecutaríamos:
	$> ./ejercicio1 sort "<" temporal

*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
	char *orden_linux;
	char *redr;
	char *archivo;
	int fd;

	if(argc != 4) {
		perror("Uso: ./ejercicio1 <orden> [\"<\"|\">\"] <archivo>\n");
		exit(EXIT_FAILURE);
	}

	orden_linux = argv[1];
	redr = argv[2];
	archivo = argv[3];

	if(strcmp(redr, "<") == 0) {
		//Redirección de entrada
		if( (fd=open(archivo, O_RDONLY)) <0 ){
			printf("\nError %d en open 1",errno);
			perror("\nError en open 1");
			exit(EXIT_FAILURE);
		}
		close(STDIN_FILENO);
		if( fcntl(fd, F_DUPFD, STDIN_FILENO) == -1 )
			perror("Fallo en fcntl");

	} else if(strcmp(redr, ">") == 0) {
		//Redirección de salida
		if( (fd=open(archivo, O_CREAT|O_WRONLY)) <0 ){
			printf("\nError %d en open 2",errno);
			perror("\nError en open 2");
			exit(EXIT_FAILURE);
		}
		close(STDOUT_FILENO);
		if( fcntl(fd, F_DUPFD, STDOUT_FILENO) == -1 )
			perror("Fallo en fcntl");

	} else {
		perror("Debe introducir \"<\" o \">\" con las comillas como segundo argumento\n");
		exit(EXIT_FAILURE);
	}

	//Ejecución del comando de Linux
	if( execlp(orden_linux,"",NULL) < 0 ) {
		perror("Error en el execlp\n");
		exit(EXIT_FAILURE);
	}

	//Cierre del descriptor de archivo
	close(fd);

	return EXIT_SUCCESS;
}