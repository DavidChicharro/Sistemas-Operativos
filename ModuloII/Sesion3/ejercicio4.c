/*
ejercicio4.c
Compilación: gcc -o ejercicio4 ejercicio4.c

Implementa un programa que lance cinco procesos hijo. 
Cada uno de ellos se identificará en la salida estándar, 
mostrando un mensaje del tipo 'Soy el hijo PID'.
El proceso padre simplemente tendrá que esperar la 
finalización de todos sus hijos y cada vez que detecte 
la finalización de uno de sus hijos escribirá en la 
salida estándar un mensaje del tipo:

	Acaba de finalizar mi hijo con <PID>
	Sólo me quedan <NUM_HIJOS> hijos vivos

*/

#include <sys/types.h>	//Primitive system data types for abstraction of implementation-dependent data types.
						//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include <unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>	// Needed for wait
#include <sys/wait.h>	// Needed for wait

const int NPROCS = 5;

int main(int argc, char *argv[]){
	int i, num_hijos = 0;
	pid_t childpid;
	int estado;

	for ( i=1 ; i<=NPROCS ; i++) {
		if ( (childpid=fork()) < 0 ) {
			printf("Error %d al crear el hijo %d\n",errno,i);
			perror("Error en la creación del hijo\n");
			exit(EXIT_FAILURE);
		}else
			num_hijos++;

		// si es un hijo termino
		if (childpid == 0){
			printf("Soy el hijo: %d\n", getpid());
			exit(estado);
		}
	}

	for( i=0 ; i<NPROCS ; i++){
		wait(&estado);
		num_hijos--;
		printf("\nAcaba de finalizar el proceso %d\n", childpid);

		if(num_hijos>0)
			printf("Sólo me quedan %d hijos vivos\n", num_hijos);
		else
			printf("No me quedan hijos vivos\n\n");
	}

	return EXIT_SUCCESS;
}