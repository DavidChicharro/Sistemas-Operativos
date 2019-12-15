/*
ejercicio4.c
Compilación: gcc -o ejercicio4 ejercicio4.c

 Programa que se asegura que sólo hay una instancia de él en
ejecución en un momento dado. El programa, una vez que ha 
establecido el mecanismo para asegurar que sólo una instancia 
se ejecuta, entrará en un bucle infinito que nos permitirá
comprobar que no podemos lanzar más ejecuciones del mismo. 
En la construcción de este deberemos asegurarnos de que el 
archivo a bloquear no contiene inicialmente nada escrito en
una ejecución anterior que pudo quedar por una caída del sistema.

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

int main(int argc, char *argv[]){
	char *fichero;
	char *pid;
	struct flock cerrojo;
	struct stat st;
	int fd;

	if(argc != 2){
		perror("Uso: ./ejercicio4 <fichero>\n");
		exit(EXIT_FAILURE);
	}

	fichero = argv[1];

	if( (fd=open(fichero, O_WRONLY | O_CREAT, S_IRWXU)) < 0 ) {
		perror("Error al abrir el archivo");
		exit(EXIT_FAILURE);
	}

	cerrojo.l_type = F_WRLCK;
	cerrojo.l_whence = SEEK_SET;
	cerrojo.l_start = 0;
	cerrojo.l_len = 0;
	cerrojo.l_pid = getpid();

	// Bloquear el fichero completo
	if( fcntl(fd, F_SETLK, &cerrojo) == -1 ){
		perror("Error: el programa ya está en ejecución con el cerrojo establecido");
		exit(EXIT_FAILURE);
	}

	// Comprobar si existe el fichero
	if( stat(fichero, &st) == -1 ){
		perror("Error en stat");
		exit(EXIT_FAILURE);
	}

	if (st.st_size != 0){
		printf("Error: otro proceso no ha finalizado correctamente el fichero; bórralo");
		exit(EXIT_FAILURE);
	}

	sprintf(pid, "%d", getpid());

	if ( write(fd, pid, strlen(pid)) == -1 ){
		perror("Error: escribiendo en el cerrojo");
		exit(EXIT_FAILURE);
	}

	printf("Cerrojo establecido correctamente.\nIntenta ejecutar de nuevo el programa en otro terminal para comprobar que no se puede\n");
	printf("Para finalizar pulsa <Enter>");
	fgetc(stdin);

	if ( close(fd) == -1 ){
		perror("Error en close");
		exit(EXIT_FAILURE);
	}
	// Borrar el fichero
	if ( unlink(fichero) == -1 ){
		perror("Error en unlink");
		exit(EXIT_FAILURE);
	}

	return EXIT_SUCCESS;
}