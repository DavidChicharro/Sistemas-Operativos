/*
esclavo_ej5.c
Compilación: gcc -o esclavo_ej5 esclavo_ej5.c -lm

Programa esclavo para el cálculo de números primos

*/

#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>

int es_primo(int k) {
	float limit = sqrt(k);
	int i;
	int es_primo = 1;

	for(i=2 ; i<=limit && es_primo; i++)
		if( k%i == 0 )
			es_primo = 0;

	return es_primo;
}

int main(int argc, char *argv[]){
	int i, int_inf, int_sup;

	//Comprobar el uso correcto del programa
	if(argc != 3) {
		printf("Error en los argumentos.\nEjerución: esclavo <intervalo_inf> <intervalo_sup>\n");
		exit(EXIT_FAILURE);
	}

	int_inf = atoi(argv[1]);
	int_sup = atoi(argv[2]);

	// Si el límite inferior es menor que 2, se iguala a 2
	if(int_inf<2)
		int_inf = 2;

	for (i=int_inf ; i<=int_sup ; i++)
		if(es_primo(i))
			write(STDOUT_FILENO, &i, sizeof(int));

	return EXIT_SUCCESS;
}