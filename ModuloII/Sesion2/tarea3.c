/*
tarea3.c
Compilación: gcc -o tarea3 tarea3.c

Trabajo con llamadas al sistema del Sistema de Archivos "POSIX 2.10 compliant"
Este programa fuente está pensado para que se cree primero un programa con la parte
 de CREACION DE ARCHIVOS y se haga un ls -l para fijarnos en los permisos y entender
 la llamada umask.
En segundo lugar (una vez creados los archivos) hay que crear un segundo programa
 con la parte de CAMBIO DE PERMISOS para comprender el cambio de permisos relativo
 a los permisos que actualmente tiene un archivo frente a un establecimiento de permisos
 absoluto.
*/

#include<sys/types.h>	//Primitive system data types for abstraction of implementation-dependent data types.
						//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include<unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include<sys/stat.h>
#include<fcntl.h>		//Needed for open
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>

int main(int argc, char *argv[]){
	int fd1,fd2;
	struct stat atributos;

	/*
	 * Crea un archivo, "archivo1", con permisos r-x para el grupo
	 * ¿Por qué r-x si establecemos	S_IRGRP|S_IWGRP|S_IXGRP?
	 * En octal = 040|020|010 = 070 --> binario = 000-111-000
	 * Como umask=0022 -> 070&(¬0022)=050 -> 000-101-000 = r-x
	 */
	//CREACION DE ARCHIVOS
	if( (fd1=open("archivo1",O_CREAT|O_TRUNC|O_WRONLY,S_IRGRP|S_IWGRP|S_IXGRP))<0) {
		printf("\nError %d en open(archivo1,...)",errno);
		perror("\nError en open");
		exit(EXIT_FAILURE);
	}
	// Establece la máscara a 0 (anteriormente=0022)
	umask(0);

	/*
	 * Crea un archivo, "archivo2", con permisos rwx para el grupo
	 * Esta vez sí tiene dichos permisos, puesto que umask=0
	 * Como umask=0000 -> 070&(¬0000)=070 -> 000-111-000 = rwx
	 */
	if( (fd2=open("archivo2",O_CREAT|O_TRUNC|O_WRONLY,S_IRGRP|S_IWGRP|S_IXGRP))<0) {
		printf("\nError %d en open(archivo2,...)",errno);
		perror("\nError en open");
		exit(EXIT_FAILURE);
	}

	/** ---------------------------------------------------------
		El código escrito hasta aquí se puede ejecutar
		 comentando lo que se encuentra de aquí en adelante
		 para comprobar que ocurre lo explicado en comentarios
	----------------------------------------------------------**/

	/* int stat(const char *pathname, struct stat *statbuf);

		Devuelve información sobre un archivo en el búfer al que 
		apunta statbuf y recupera información sobre el archivo al 
		que apunta el pathname;
	*/
	//CAMBIO DE PERMISOS
	if(stat("archivo1",&atributos) < 0) {
		printf("\nError al intentar acceder a los atributos de archivo1");
		perror("\nError en stat");
		exit(EXIT_FAILURE);
	}

	/*
	 * Cambia (quita) el permiso de ejecución para el grupo.
	 * 050&(¬010)=040 -> 000-100-000
	 * quedando así sólo con permiso de lectura para el grupo.
	 *
	 * Después hace un OR lógico de 40|2000 = 2040, de manera
	 * que activa el bit de 'setgid'. Activa la asignación del 
	 * GID del propietario al GID efectivo del proceso que
	 * ejecute el archivo. Esto significa que el gurpo que
	 * ejecute el archivo va a tener los mismos permisos que
	 * quien lo creó. Resultado: ----r-S---
	 */
	if(chmod("archivo1", (atributos.st_mode & ~S_IXGRP) | S_ISGID) < 0) {
		perror("\nError en chmod para archivo1");
		exit(EXIT_FAILURE);
	}

	/*
	 * Cambia los permisos del archivo con OR lógicos: 700|040|020|004
	 * Pasa de tener los permisos 000-111-000 a 111-110-100
	 */
	if(chmod("archivo2",S_IRWXU | S_IRGRP | S_IWGRP | S_IROTH) < 0) {
		perror("\nError en chmod para archivo2");
		exit(EXIT_FAILURE);
	}

	return EXIT_SUCCESS;
}
