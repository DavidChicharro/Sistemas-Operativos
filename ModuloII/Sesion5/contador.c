/*
contador.c
Compilación: gcc -o contador contador.c

 Escribe un programa en C llamado contador, tal que cada vez que 
reciba una señal que se pueda manejar, muestre por pantalla la 
señal y el número de veces que se ha recibido ese tipo de señal, 
y un mensaje inicial indicando las señales que no puede manejar. 

*/

#include <stdio.h>
#include <signal.h>
#include <errno.h>

/*
 * Número de señales existentes
 * Consultar 'man 7 signal'
 */
#define SIGNAL_SIZE 31
static int s_recibida[SIGNAL_SIZE];

static void handler (int signum){
	if( signum>=1 && signum<=SIGNAL_SIZE){
		s_recibida[signum-1]++;
		printf("La señal %d se ha recibido %d veces\n", signum, s_recibida[signum-1]);
	}else
		printf("No puedo manejar la señal %d\n", signum);	
}

int main(){
	struct sigaction sa;
	sa.sa_handler = handler;	// establece el manejador a handler

	/*
	 * int sigfillset(sigset_t *set);
	 *
	 * sigfillset() inicializa set al completo, incluyendo todas las señales.
	 */
	sigfillset(&sa.sa_mask);

	//Reiniciar las funciones que hayan sido interrumpidas por un manejador 
	sa.sa_flags = SA_RESTART;

	for (int i=1; i<=SIGNAL_SIZE; i++)
		if (sigaction(i, &sa, NULL) == -1)
			printf("No puedo manejar la señal %d\n",i);

	while(1);
}