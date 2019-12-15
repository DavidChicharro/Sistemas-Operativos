/*
ejercicio3.c
Compilación: gcc -o ejercicio3 ejercicio3.c

 Programa que verifica que, efectivamente, el
kernel comprueba que puede darse una situación 
de interbloqueo en el bloqueo de archivos.

*/

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main (int argc, char *argv[]) {
	struct flock cerrojo;
	char *fichero;
	int fd;

	if(argc != 2){
		perror("Uso: ./ejercicio3 <fichero>\n");
		exit(EXIT_FAILURE);
	}

	fichero = argv[1];	
	
	if( (fd=open(fichero,O_RDWR )) < 0 ){
		perror("\nError al abrir el fichero");
		exit(EXIT_FAILURE);
	}

	//Establecer cerrojo
	cerrojo.l_type = F_WRLCK;
	cerrojo.l_whence = SEEK_SET;
	cerrojo.l_start = 0;
	cerrojo.l_len = 0;	//Bloquear el archivo entero

	//Intentamos un bloqueo de escritura del archivo
	printf("Intentando bloquear %s\n", fichero);

	//Si el bloqueo no tiene éxito 
	if( fcntl(fd, F_SETLKW, &cerrojo) == EDEADLK ) {		
		//Si el cerrojo falla, se imprime el siguiente mensaje
		printf("El fichero %s ha producido EDEADLK\n", fichero);
	}

	//Ahora el bloqueo tiene éxito y podemos procesar el archivo
	printf ("Procesando el archivo %s\n", fichero);

	//Sleep para que dé tiempo a relanzar el programa
	sleep(10);

	//Una vez finalizado el trabajo, desbloqueamos el archivo
	cerrojo.l_type = F_UNLCK;
	cerrojo.l_whence = SEEK_SET;
	cerrojo.l_start = 0;
	cerrojo.l_len = 0;

	if( fcntl(fd, F_SETLKW, &cerrojo) == -1 ) {
		perror ("Error al desbloquear el archivo");
	}
	
	printf("\nFichero %s liberado\n",fichero);

	return EXIT_SUCCESS;
}
