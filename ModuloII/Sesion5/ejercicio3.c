/*
ejercicio3.c
Compilación: gcc -o ejercicio3 ejercicio3.c

 Programa que suspende la ejecución del proceso 
actual hasta que se reciba la señal SIGUSR1.

*/

#include <stdio.h>
#include <signal.h>

int main(){
	sigset_t new_mask;

	/* inicializar la nueva mascara de señales */
	sigemptyset(&new_mask);

	/* inicializa set al completo incluyendo todas las señales*/
	sigfillset(&new_mask);

	/* elimina de set la señal SIGUSR1*/
	sigdelset(&new_mask, SIGUSR1);

	/*esperar a la señal SIGUSR1 */
	sigsuspend(&new_mask);

}