/*
tarea4.c
Compilación: gcc -o tarea4 tarea4.c

Trabajo con llamadas al sistema del Subsistema de Procesos "POSIX 2.10 compliant"
Prueba el programa tal y como está. Después, elimina los comentarios (1) y pruébalo de nuevo.
*/

#include<sys/types.h>	//Primitive system data types for abstraction of implementation-dependent data types.
						//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include<unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>

int global=6;
char buf[]="cualquier mensaje de salida\n";

int main(int argc, char *argv[]){
	int var;
	pid_t pid;

	var=88;
	if(write(STDOUT_FILENO,buf,sizeof(buf)+1) != sizeof(buf)+1) {
		perror("\nError en write");
		exit(EXIT_FAILURE);
	}
	//(1)if(setvbuf(stdout,NULL,_IONBF,0)) {
	//	perror("\nError en setvbuf");
	//}
	printf("\nMensaje previo a la ejecución de fork");

	if( (pid=fork())<0 ) {
		perror("\nError en el fork");
		exit(EXIT_FAILURE);
	}
	else if(pid==0) {  
		//proceso hijo ejecutando el programa
		global++;
		var++;
	} else  //proceso padre ejecutando el programa
	
	sleep(1);
	printf("\npid= %d, global= %d, var= %d\n", getpid(),global,var);

	exit(EXIT_SUCCESS);
}

/*
 *  En primer lugar escribe el contenido de 'buf' en pantalla.
 *
 *  A continuación crea el proceso hijo, el cual aumenta en 1
 * el valor de la variable global 'global' y el de la variable
 * local al main 'var'. Imprime por pantalla su PID y los valores
 * de ambas variables modificadas.
 *
 *  El proceso padre simplemente realiza la impresión por pantalla
 * de las variables
 */