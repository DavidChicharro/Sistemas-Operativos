/*
tarea12.c
Compilación: gcc -o tarea12 tarea12.c

 El programa crea una máscara donde sólo se añade la señal SIGTERM.
Aplica la máscara y con ello bloquea la señal SIGTERM.
Duerme durante 10 segundos y si durante este tiempo recibe la señal
SIGTERM, no reaccionará porque está bloqueada; Una vez termina de 
"dormir", desbloquea la señal SIGTERM, reanudando la máscara antigua 
y comprobando si la variable signal_recibida está activada, lo cual
quiere decir que ha recibido la señal SIGTERM mientras dormía, en 
cuyo caso mostrará un mensaje indicándolo; si no, no mostrará nada.

*/

#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

static int signal_recibida = 0;

static void manejador (int sig){
	signal_recibida = 1;
}

int main (int argc, char *argv[]){
	sigset_t conjunto_mascaras;
	sigset_t conj_mascaras_original;
	struct sigaction act;
	//Iniciamos a 0 todos los elementos de la estructura act 
	memset(&act, 0, sizeof(act));

	act.sa_handler = manejador;

	if (sigaction(SIGTERM, &act, 0)) {
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
    
	//Iniciamos un nuevo conjunto de mascaras
	sigemptyset(&conjunto_mascaras);
	//Añadimos SIGTERM al conjunto de mascaras
	sigaddset(&conjunto_mascaras, SIGTERM);

	//Bloqueamos SIGTERM
	if(sigprocmask(SIG_BLOCK, &conjunto_mascaras, &conj_mascaras_original) < 0) {
		perror("primer sigprocmask");
		exit(EXIT_FAILURE);
	}

	sleep(10);

	//Restauramos la señal – desbloqueamos SIGTERM
	if(sigprocmask(SIG_SETMASK, &conj_mascaras_original, NULL) < 0) {
		perror("segundo sigprocmask");
		exit(EXIT_FAILURE);
	}

	sleep(1);

	if(signal_recibida)
 		printf ("\nSeñal recibida\n");
	exit(EXIT_SUCCESS);
}
