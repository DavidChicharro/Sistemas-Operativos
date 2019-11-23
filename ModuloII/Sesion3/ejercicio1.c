/*
ejercicio1.c
Compilación: gcc -o ejercicio1 ejercicio1.c

 Implementa un programa en C que tenga como argumento un número entero.
Este programa debe crear un proceso hijo que se encargará de comprobar 
si dicho número es un número par o impar e informará al usuario con un 
mensaje que se enviará por la salida estándar. A su vez, el proceso padre 
comprobará si dicho número es divisible por 4, e informará si lo es o no
usando igualmente la salida estándar.

*/

#include<sys/types.h>	//Primitive system data types for abstraction of implementation-dependent data types.
						//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include<unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>


int main(int argc, char *argv[]){
	int numero;
	pid_t pid;

	if(argc != 2){
		printf("\nSintaxis de ejecución: ejercicio1 <número>\n\n");
		exit(EXIT_FAILURE);
	}

	numero = atoi(argv[1]);

	if( (pid=fork())<0 ) {
		perror("\nError en el fork");
		exit(EXIT_FAILURE);
	}
	else if(pid==0) {  
		//proceso hijo ejecutando el programa
		if( (numero%2)==0 )
			printf("El número %d es par\n", numero);
		else
			printf("El número %d es impar\n", numero);
	} else{
		//proceso padre ejecutando el programa
		if( (numero%4)==0 )
			printf("El número %d es divisible por 4\n", numero);
		else
			printf("El número %d no es divisible por 4\n", numero);
	}
		
	exit(EXIT_SUCCESS);
}
