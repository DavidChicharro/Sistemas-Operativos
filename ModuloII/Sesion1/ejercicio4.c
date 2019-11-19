/*
ejercicio4.c
Compilación: gcc -o ejercicio4 ejercicio4.c

Trabajo con llamadas al sistema del Sistema de Archivos "POSIX 2.10 compliant"

Define una macro en lenguaje C que tenga la misma funcionalidad que la macro
S_ISREG(mode) usando para ello los flags definidos en <sys/stat.h> para el 
campo st_mode de la struct stat, y comprueba que funciona en un programa simple. 

*/


#include<unistd.h>  /* POSIX Standard: 2.10 Symbolic Constants <unistd.h>
		     */
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>  /* Primitive system data types for abstraction	\
			   of implementation-dependent data types.
			   POSIX Standard: 2.6 Primitive System Data Types
			   <sys/types.h>
		       */
#include<sys/stat.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>

//S_IFMT = 0170000
//S_IFREG = 0100000
/*
 * en st_mode los flags son:
 *	S_IFMT = 0170000 -> máscara de bits para campos de bit del tipo de archivo
 *	S_IFREG = 0100000 -> archivo regular
 */

#define	FLAG_REG 0100000	// flag de st_mode para archivos regulares
#define MACRO_S_ISREG(mode) ((mode & S_IFMT) == FLAG_REG)	// macro

int main(int argc, char *argv[]){
	int i;
	struct stat atributos;
	char tipoArchivo[30];

	if(argc<2) {
		printf("\nSintaxis de ejecucion: tarea2 [<nombre_archivo>]+\n\n");
		exit(EXIT_FAILURE);
	}

	for(i=1 ; i<argc ; i++) {
		printf("%s: ", argv[i]);
		if(lstat(argv[i],&atributos) < 0) {
			printf("\nError al intentar acceder a los atributos de %s",argv[i]);
			perror("\nError en lstat");
		}
		else {
			if(MACRO_S_ISREG(atributos.st_mode))
				printf("archivo regular\n");
			else
				printf("no es archivo regular\n");
		}
	}

	return EXIT_SUCCESS;
}