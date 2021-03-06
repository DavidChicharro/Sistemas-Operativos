/*
ejercicio5.c
Compilación: gcc -o ejercicio5 ejercicio5.c

 Implementa una modificación sobre el anterior programa (ejercicio4)
en la que el proceso padre espera primero a los hijos creados en orden 
impar (1º,3º,5º) y después a los hijos pares (2º y 4º).

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
	int PIDs[NPROCS];
	int estado;

	if(setvbuf(stdout,NULL,_IONBF,0)) {
		perror("\nError en setvbuf");
	}

	for ( i=1 ; i<=NPROCS ; i++) {
		if ( (PIDs[i-1]=fork()) < 0 ) {
			printf("Error %d al crear el hijo %d\n",errno,i);
			perror("Error en la creación del hijo\n");
			exit(EXIT_FAILURE);
		}else
			num_hijos++;

		// si es un hijo termino
		if (PIDs[i-1] == 0){
			printf("Soy el hijo %d: %d\n", i, getpid());
			exit(estado);
		}
	}

	sleep(2);

	for( i=0 ; i<NPROCS ; i+=2){
		waitpid(PIDs[i],&estado,0);
		num_hijos--;
		printf("\nAcaba de finalizar el proceso %d\n", PIDs[i]);

		if(num_hijos>0)
			printf("Sólo me quedan %d hijos vivos\n", num_hijos);
		else
			printf("No me quedan hijos vivos\n\n");
	}

	for( i=1 ; i<NPROCS ; i+=2){
		waitpid(PIDs[i],&estado,0);
		num_hijos--;
		printf("\nAcaba de finalizar el proceso %d\n", PIDs[i]);

		if(num_hijos>0)
			printf("Sólo me quedan %d hijos vivos\n", num_hijos);
		else
			printf("No me quedan hijos vivos\n\n");
	}

	return EXIT_SUCCESS;
}