/*
ejercicio3.c
Compilación: gcc -o ejercicio3 ejercicio3.c

 Indica qué tipo de jerarquías de procesos se generan mediante 
la ejecución de cada uno de los siguientes fragmentos de código.
Comprueba tu solución implementando un código para generar 20 
procesos en cada caso, en donde cada proceso imprima su PID y el 
del padre, PPID.

*/

#include <sys/types.h>	//Primitive system data types for abstraction of implementation-dependent data types.
						//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include <unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]){
	int i;
	int nprocs=20;
	pid_t childpid;

	/*
	 * Jerarquía de procesos tipo 1
	 */
	for ( i=1 ; i<=nprocs ; i++) {
		if ( (childpid=fork()) == -1) {
			fprintf(stderr, "Could not create child %d: %s\n",i,strerror(errno));
			exit(EXIT_FAILURE);
		}

		if (childpid)
			break;

		if (childpid == 0){
			printf("Hijo: %d  -- Padre:%d\n", getpid(), getppid() );
		}
	}
	sleep(2);
	printf("\n");

	/*
	 * Jerarquía de procesos tipo 2
	 */
	for (i=1 ; i<=nprocs ; i++) {
		if ((childpid=fork()) == -1) {
			fprintf(stderr, "Could not create child %d: %s\n",i,strerror(errno));
			exit(EXIT_FAILURE);
		}

		if (!childpid)
			break;
	}
	
	if (childpid == 0){
		printf("Hijo: %d  -- Padre:%d\n", getpid(), getppid() );
	}

	sleep(1);
	return EXIT_SUCCESS;
}