/*
ejercicio2.c
Compilación: gcc -o ejercicio2 ejercicio2.c

 Reescribir el programa que implemente un encauzamiento de dos órdenes 
pero utilizando fcntl. Este programa admitirá tres argumentos. 
	- El primer y tercer argumento serán órdenes de Linux.
	- El segundo argumento será el carácter "|"

El programa deberá hacer la redirección de la salida de la orden indicada 
por el primer argumento hacia el cauce, y redireccionar la entrada estándar 
de la segunda orden desde el cauce.

Por ejemplo, para simular el encauzamiento ls|sort, ejecutaríamos:
	$> ./ejercicio2 ls "|" sort

*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
	char *orden_linux_1, *orden_linux_2;
	char *cauce;
	pid_t PID;
	int fd[2];

	if(argc != 4) {
		perror("Uso: ./ejercicio2 <orden> [\"|\"] <orden>\n");
		exit(EXIT_FAILURE);
	}

	orden_linux_1 = argv[1];
	cauce = argv[2];
	orden_linux_2 = argv[3];
	

	if(strcmp(cauce, "|") == 0) {
		pipe(fd); // Llamada al sistema para crear un cauce sin nombre

		if ( (PID=fork()) <0 ) {
			perror("Error en fork");
			exit(EXIT_FAILURE);
		}
		if (PID == 0) { // Proceso hijo
			//Cierre del descriptor de lectura en el proceso hijo
			close(fd[0]);
			close(STDOUT_FILENO);

			if (fcntl(fd[1], F_DUPFD, STDOUT_FILENO) == -1 ){
				perror ("Fallo en fcntl (hijo)");
				exit(EXIT_FAILURE);
			}

			execlp(orden_linux_1,orden_linux_1,NULL);
		}
		else { // Proceso padre
			//Cierre del descriptor de escritura en el proceso padre
			close(fd[1]);
			close(STDIN_FILENO);
			
			if (fcntl(fd[0], F_DUPFD, STDIN_FILENO) == -1 ){
				perror ("Fallo en fcntl (padre)");
				exit(EXIT_FAILURE);
			}

			execlp(orden_linux_2,orden_linux_2,NULL);
		}
	} else {
		perror("Debe introducir \"|\" con las comillas como segundo argumento\n");
		exit(EXIT_FAILURE);
	}

	return EXIT_SUCCESS;
}