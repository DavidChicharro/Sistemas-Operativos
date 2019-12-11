/*
tarea8.c
Compilación: gcc -o tarea8 tarea8.c

Programa ilustrativo del uso de pipes y la redirección de entrada y
salida estándar: "ls | sort", utilizando la llamada dup2.
*/

#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

int main(int argc, char *argv[]){
	int fd[2];
	pid_t PID;

	pipe(fd); // Llamada al sistema para crear un pipe

	if ( (PID= fork())<0) {
		perror("Error en el fork");
		exit(EXIT_FAILURE);
	}
	if(PID == 0) { // ls
		//Cerrar el descriptor de lectura de cauce en el proceso hijo
		close(fd[0]);

		/*
		 * A diferencia de tarea7.c, el hijo no cierra la 
		 * salida estándar para dejar la entrada del descriptor 
		 * de lectura del hijo libre, porque la orden dup2 ya 
		 * se encarga de hacer en una misma orden lo que antes
		 * suponía hacer dos: close y dup
		 */

		//Duplicar el descriptor de escritura en cauce en el descriptor
		//correspondiente a la salida estandr (stdout), cerrado previamente en
		//la misma operacion
		dup2(fd[1],STDOUT_FILENO);
		execlp("ls","ls",NULL);
	}
	else { // sort. Proceso padre porque PID != 0.
		//Cerrar el descriptor de escritura en cauce situado en el proceso padre
		close(fd[1]);

		/*
		 * No se cierra tampoco la entrada estándar del proceso padre
		 * porque se realiza un dup2
		 */

		//Duplicar el descriptor de lectura de cauce en el descriptor
		//correspondiente a la entrada estándar (stdin), cerrado previamente en
		//la misma operación
		dup2(fd[0],STDIN_FILENO);
		execlp("sort","sort",NULL);
	}

	return EXIT_SUCCESS;
}



