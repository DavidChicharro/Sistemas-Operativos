/*
tarea10.c
Compilación: gcc -o tarea10 tarea10.c

*/

#include <stdio.h>
#include <signal.h>

static int s_recibida=0;

static void handler (int signum){
	printf("\n Nueva acción del manejador \n");
	s_recibida++;
}

int main(){
	struct sigaction sa;
	sa.sa_handler = handler;	// establece el manejador a handler
	sigemptyset(&sa.sa_mask);	// inicializa a vacío 

	//Reiniciar las funciones que hayan sido interrumpidas por un manejador 
	sa.sa_flags = SA_RESTART; 

	if (sigaction(SIGINT, &sa, NULL) == -1){
		printf("error en el manejador");
	}

	// Finalizará cuando haya recibido 3 señales
	while(s_recibida<3);
}