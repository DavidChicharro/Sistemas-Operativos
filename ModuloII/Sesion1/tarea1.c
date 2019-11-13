/*
tarea1.c
Compilación: gcc -o tarea1 tarea1.c
Trabajo con llamadas al sistema del Sistema de Archivos ''POSIX 2.10 compliant''
Probar tras la ejecución del programa: $>cat archivo y $> od -c archivo
*/
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>  	/* Primitive system data types for abstraction\
			   of implementation-dependent data types.
			   POSIX Standard: 2.6 Primitive System Data Types
			   <sys/types.h>
			*/
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>

char buf1[]="abcdefghij";
char buf2[]="ABCDEFGHIJ";

int main(int argc, char *argv[]){
	int fd;
	/*int open(const char *pathname, int flags);

	La llamada de sistema open() abre el archivo especificado por pathname. 
	Si el archivo especificado no existe, puede ser creado opcionalmente 
	(si O_CREAT está especificado en flags) por open().
	*/
	if( (fd=open("archivo",O_CREAT|O_TRUNC|O_WRONLY,S_IRUSR|S_IWUSR))<0 ) {
		printf("\nError %d en open",errno);
		perror("\nError en open");
		exit(EXIT_FAILURE);
	}

	/*write(int fd, const void *buf, size_t count);

	write() escribe hasta #count# bytes desde el buffer que comienza 
	en buf al archivo al que se refiere el descriptor de archivo fd
	*/
	if(write(fd,buf1,10) != 10) {
		perror("\nError en primer write");
		exit(EXIT_FAILURE);
	}

	/*lseek(int fd, off_t offset, int whence);
	
	lseek() reposiciona el desplazamiento del archivo de la descripción del 
	archivo abierto asociado con el descriptor de archivo fd al argumento 
	offset de acuerdo con la directiva de donde procede de la siguiente manera:

	SEEK_SET	El desplazamiento del archivo se establece en offset bytes
	SEEK_CUR	El desplazamiento del archivo se establece en su ubicación actual más los offset bytes
	SEEK_END	El desplazamiento del archivo se establece en el tamaño del archivo más los offset bytes
	*/
	if(lseek(fd,40,SEEK_SET) < 0) {
		perror("\nError en lseek");
		exit(EXIT_FAILURE);
	}

	if(write(fd,buf2,10) != 10) {
		perror("\nError en segundo write");
		exit(EXIT_FAILURE);
	}

	return EXIT_SUCCESS;
}
/*
abcdefghijABCDEFGHIJ
*/

/*
0000000   a   b   c   d   e   f   g   h   i   j  \0  \0  \0  \0  \0  \0
0000020  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0
0000040  \0  \0  \0  \0  \0  \0  \0  \0   A   B   C   D   E   F   G   H
0000060   I   J
0000062
*/
