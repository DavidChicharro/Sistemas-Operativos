/*
tarea9.c
Compilación: gcc -o tarea9 tarea9.c

Este programa ignora las interrupciones por teclado.

*/

#include <stdio.h>
#include <signal.h>

int main(){
	struct sigaction sa;
	sa.sa_handler = SIG_IGN;	// ignora la señal
	sigemptyset(&sa.sa_mask);	// inicializa a vacío

	//Reiniciar las funciones que hayan sido interrumpidas por un manejador 
	sa.sa_flags = SA_RESTART; 

	/*
	 * La llamada al sistema sigaction se emplea para 
	 * cambiar la acción tomada por un proceso cuando
	 * recibe una determinada señal.
	 */
	if (sigaction(SIGINT, &sa, NULL) == -1){
		printf("error en el manejador");
	}

	while(1);
}
