/*
ejercicio2.c
Compilación: gcc -o ejercicio2 ejercicio2.c
Trabajo con llamadas al sistema del Sistema de Archivos "POSIX 2.10 compliant"

Implementa un programa que realice la siguiente funcionalidad:
El programa acepta como argumento el nombre de un archivo 
(pathname), lo abre y lo lee en bloques de tamaño 80 Bytes, 
y crea un nuevo archivo de salida, salida.txt, en el que 
debe aparecer la siguiente información:

Bloque 1
	Aquí van los primeros 80 Bytes del archivo pasado como argumento.
Bloque 2
	Aquí van los siguientes 80 Bytes del archivo pasado como argumento.
...

Bloque n
	Aquí van los siguientes 80 Bytes del archivo pasado como argumento.
*/

#include<unistd.h>  /* POSIX Standard: 2.10 Symbolic Constants <unistd.h> */
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
#include<fcntl.h>

int MAX_LECT = 80;
int MAX_BLOQUE = 15;

int main(int argc, char *argv[]){
	int fich_lec, fich_esc;
	char buff[MAX_LECT];
	int leidos;
	int cont=1;
	char bloque[MAX_BLOQUE];

	// Si le paso 1 argumento (ejercicio2 <fich>) abre <fich>
	if (argc==2){
		if( (fich_lec=open(argv[1],O_RDONLY))<0 ){
			printf("\nError %d en open",errno);
			perror("\nError en open del argumento argv[1]");
			exit(EXIT_FAILURE);
		} else{
			printf("Utilizando el fichero %s como archivo de entrada\n", argv[1]);
		}	
	}
	else{
		// Asigno a fich_lect la entrada estándar (teclado)
		printf( "Utilizando la entrada estándar como entrada:\n");
		fflush(stdout);
		fich_lec=STDIN_FILENO;
	}

	// Crea el archivo de salida
	if( (fich_esc=open("salida.txt",O_CREAT|O_TRUNC|O_WRONLY,S_IRUSR|S_IWUSR))<0 ){
		printf("\nError %d en open",errno);
		perror("\nError en open de salida.txt");
		exit(EXIT_FAILURE);
	}

	/* read(int fd, void *buf, size_t count);

	read() intenta leer hasta count bytes desde el 
	descriptor de archivo fd al búfer empezando por buf.
	*/
	while( (leidos=read(fich_lec, buff, MAX_LECT))>0 ){
		// escribe en bloque la cadena pasada como parámetro
		sprintf(bloque, "\nBloque %d\n",cont);

		/*write(int fd, const void *buf, size_t count);

		write() escribe hasta #count# bytes desde el buffer que comienza 
		en buf al archivo al que se refiere el descriptor de archivo fd
		*/
		if( write(fich_esc, bloque, strlen(bloque))<0 ){
			printf("\nError %d en primer write: bloque %d",errno,cont);
			perror("\nError en el primer write (línea de bloque n)");
			exit(EXIT_FAILURE);
		}

		if( write(fich_esc, buff, leidos)<0 ){
			printf("\nError %d en segundo write: bloque %d",errno,cont);
			perror("\nError en el segundo write (línea de escritura de bytes)");
			exit(EXIT_FAILURE);
		}

		cont++;
	}

	close( fich_lec );
	close( fich_esc );

	return EXIT_SUCCESS;
}
