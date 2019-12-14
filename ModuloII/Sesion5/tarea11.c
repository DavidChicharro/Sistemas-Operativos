/*
tarea11.c
Compilaci�n: gcc -o tarea11 tarea11.c

 Programa que suspende la ejecuci�n del proceso 
actual hasta que reciba una se�al distinta de SIGUSR1

*/

#include <stdio.h>
#include <signal.h>

int main(){
	sigset_t new_mask;

	/* inicializar la nueva mascara de se�ales */
	sigemptyset(&new_mask);

	sigaddset(&new_mask, SIGUSR1);

	/*esperar a cualquier se�al excepto SIGUSR1 */
	sigsuspend(&new_mask);

}