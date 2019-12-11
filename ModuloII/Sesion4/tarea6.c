/*
tarea6.c
Compilación: gcc -o tarea6 tarea6.c

Trabajo con llamadas al sistema del Subsistema de Procesos y Cauces conforme a POSIX 2.10
*/

#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>

int main(int argc, char *argv[]){
	int fd[2], numBytes;
	pid_t PID;
	char mensaje[]= "\nEl primer mensaje transmitido por un cauce!!\n";
	char buffer[80];

	/* pipe() crea una tubería, un canal de datos unidireccional 
	 * que puede utilizarse para la comunicación entre procesos.
	 * El array 'pipefd' se utiliza para devolver dos descriptores 
	 * de archivo que se refieren a los extremos de la tubería. 
	 * pipefd[0] se refiere al extremo de lectura de la tubería. 
	 * pipefd[1] se refiere al extremo de escritura de la tubería.
	 * Los datos escritos en el extremo de escritura de la tubería 
	 * son almacenados por el núcleo hasta que se leen en el extremo 
	 * de lectura de la tubería.
	 */
	pipe(fd); // Llamada al sistema para crear un cauce sin nombre

	if ( (PID=fork()) <0 ) {
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (PID == 0) {
		//Cierre del descriptor de lectura en el proceso hijo
		close(fd[0]);
		// Enviar el mensaje a traves del cauce usando el descriptor de escritura
		write(fd[1], mensaje, strlen(mensaje)+1);
		exit(EXIT_SUCCESS);
	}
	else { // Estoy en el proceso padre porque PID != 0
		//Cerrar el descriptor de escritura en el proceso padre
		close(fd[1]);
		//Leer datos desde el cauce.
		numBytes = read(fd[0], buffer, sizeof(buffer));
		printf("\nEl numero de bytes recibidos es: %d",numBytes);
		printf("\nLa cadena enviada a traves del cauce es: %s", buffer);
	}

	return EXIT_SUCCESS;
}

/*
En primer lugar pipe(fd) crea un cauce sin nombre; al pasarle 'fd'
como parámetro se asigna por defecto el modo lectura a fd[0] y el 
modo escritura a fd[1].

Con la orden fork se crea un proceso hijo, el cual cierra el descriptor
de lectura fd[0] y posteriormente escribe un mensaje a través del cauce 
en el descriptor de escritura fd[1].

El proceso padre cierra el descriptor de escritura fd[1] y lee del cauce 
lo que ha escrito el hijo con el descriptor de lectura fd[0], imprimiendo 
por pantalla dicho mensaje y el número de bytes que ocupa.

*/