/*
ejercicio7.c
Compilación: gcc -o ejercicio7 ejercicio7.c

 Escribe un programa que acepte como argumentos el nombre de un programa,
sus argumentos si los tiene y, opcionalmente, la cadena "bg". El programa 
deberá ejecutar el programa pasado como primer argumento en foreground si 
no se especifica la cadena "bg" y en background en caso contrario. Si el 
programa tiene argumentos hay que ejecutarlo con éstos.

*/

#include <unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

int main(int argc, char *argv[]){
	pid_t pid;
	int estado;
	int background;
	int num_parametros;
	char *nom_programa;
	char parametros[100];
	int i;

	if(argc < 2){
		printf("\nSintaxis de ejecución: ejercicio7 <nom_programa> [<args>] [bg]\n\n");
		exit(EXIT_FAILURE);
	}

	// Si se escribe "bg" como último argumento, se escribe un 1 en la variable background
	background = strcmp(argv[argc-1],"bg")==0 ? 1:0;
	// Si se escribe "bg" entonces el número de parámetros será argc-3 (ejecución, programa y bg)
	num_parametros = background==1 ? argc-1:argc;
	nom_programa = argv[1];

	strcpy(parametros,"");
	for(i=2 ; i<num_parametros ; i++){
		strcat(parametros, argv[i]);
		strcat(parametros, " ");
	}

	if(background==1){
		if( (pid=fork())<0 ) {
			perror("\nError en el fork");
			exit(EXIT_FAILURE);
		}else if(pid != 0)
			exit(EXIT_SUCCESS);

		printf("Ejecutando en background\n");		
	}else
		printf("Ejecutando en foreground\n");

	if( (execl(nom_programa,parametros,parametros,NULL)<0)) {
		perror("\nError en el execl");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}

/*
 * Ejecutar ./ejercicio7 bucle 200
 * y
 * ./ejercicio7 bucle 200 bg
 * para comprobar la diferencia de ejecución entre ambas
 *
 */