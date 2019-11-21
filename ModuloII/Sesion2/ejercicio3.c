/*
ejercicio3.c
Compilación: gcc -o ejercicio3 ejercicio3.c

 Programa una nueva orden que recorra la jerarquía de 
subdirectorios existentes a partir de uno dado como 
argumento y devuelva la cuenta de todos aquellos archivos 
regulares que tengan permiso de ejecución para el grupo y 
para otros. Además del nombre de los archivos encontrados, 
deberá devolver sus números de inodo y la suma total de 
espacio ocupado por dichos archivos. El formato de la nueva 
orden será:

	$> ./ejercicio3 <pathname>

donde <pathname> especifica la ruta del directorio a partir 
del cual queremos que empiece a analizar la estructura del 
árbol de subdirectorios. En caso de que no se le de argumento, 
tomará como punto de partida el directorio actual. Ejemplo de 
la salida después de ejecutar el programa:

	Los i-nodos son:
	./a.out 55
	./bin/ej 123
	./bin/ej2 87
	...
	Existen 24 archivos regulares con permiso x para grupo y otros
	El tamaño total ocupado por dichos archivos es 2345674 bytes

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>		// Needed for DIR
#include <errno.h>
#include <sys/stat.h>
#include "string.h"


void recorreDirectorio(char path_dir[], int *arch_permisos, int *esp_ocup){
	DIR *directorio;
	struct dirent *archivo;
	struct stat atributos;
	char ruta_archivo[300];
	char nom_directorio[300];

	// Comprobar que existe el directorio
	if ( (directorio = opendir(path_dir)) == NULL){
		printf("Error %d al abrir el directorio %s.\n", errno, path_dir);
		perror("\nError en opendir\n");
		exit(EXIT_FAILURE);
	}

	while( (archivo = readdir(directorio)) != NULL){
		sprintf(ruta_archivo, "%s/%s", path_dir, archivo->d_name);

		// Acceso a datos del archivo
		if(stat(ruta_archivo,&atributos) < 0) {
			printf("\nError %d al intentar acceder a los atributos de %s",errno,ruta_archivo);
			perror("\nError en stat");
			exit(EXIT_FAILURE);
		}

		if ( S_ISREG(atributos.st_mode) 
			&& (atributos.st_mode & S_IXGRP) 
			&& (atributos.st_mode & S_IXOTH) ){

			*arch_permisos += 1;
			*esp_ocup += atributos.st_size;

			printf("%s  %lu\n", ruta_archivo, atributos.st_ino);
		
		}else if( S_ISDIR(atributos.st_mode) ){
			sprintf(nom_directorio, "%s", archivo->d_name);

			if( strcmp(nom_directorio, ".")!=0 && strcmp(nom_directorio, "..")!=0)
				recorreDirectorio(nom_directorio, arch_permisos, esp_ocup);
		}
	}

	if( closedir(directorio) != 0){
		printf("Error %d al cerrar el directorio %s\n",errno,path_dir);
		perror("Error en closedir");
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char *argv[]){
	int arch_permisos = 0;
	int esp_ocup = 0;

	if(argc != 2){
		printf("\nSintaxis de ejecución: ejercicio3 [<nom_directorio>]\n\n");
		exit(EXIT_FAILURE);
	}

	printf("Los i-nodos son:\n");
	recorreDirectorio(argv[1], &arch_permisos, &esp_ocup);

	printf("\nExisten %d archivos regulares con permiso x para grupo y otros\n",arch_permisos);
	printf("El tamaño total ocupado por dichos archivos es %d bytes\n\n",esp_ocup);

	return EXIT_SUCCESS;
}