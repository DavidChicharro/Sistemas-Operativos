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

	/* int setvbuf(FILE *stream, char *buf, int mode, size_t size);
	
	La función setvbuf() se puede usar en cualquier flujo abierto 
	para cambiar su búfer. El argumento de modo debe ser una de las 
	siguientes tres macros:
		_IONBF unbuffered
		_IOLBF line buffered
		_IOFBF fully buffered
	
	Excepto para los archivos sin búfer, el argumento 'buf' debe apuntar a 
	un búfer de al menos 'size' bytes de longitud; este búfer se usará en 
	lugar del búfer actual. Si el argumento buf es NULL, solo se ve afectado
	el modo; se asignará un nuevo búfer en la siguiente operación de lectura
	o escritura. La función setvbuf() sólo se puede usar después de abrir una
	secuencia y antes de que se hayan realizado otras operaciones en ella.
	*/
	if(setvbuf(stdout,NULL,_IONBF,0)) {
		perror("\nError en setvbuf");
	}
	
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
