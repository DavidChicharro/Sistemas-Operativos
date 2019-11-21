/*
ejercicio4.c
Compilación: gcc -o ejercicio4 ejercicio4.c

 Implementación del programa del ejercicio 3 
utilizando la llamada al sistema nftw.

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>		// Needed for DIR
#include <errno.h>
#include <sys/stat.h>
#include <string.h>

#include <ftw.h>

// Variables globales
int arch_permisos = 0;
int esp_ocup = 0;

int visitar(const char *path, const struct stat *stat, 
  int flags, struct FTW *ftw){

  	if ( S_ISREG(stat->st_mode) 
			&& (stat->st_mode & S_IXGRP) 
			&& (stat->st_mode & S_IXOTH) ){

  		arch_permisos += 1;
  		esp_ocup += stat->st_size;

		printf("Path: %s   Modo: %o  i-nodo: %lu\n", path, stat->st_mode, stat->st_ino);
  	}

	return 0;
}

int main(int argc, char *argv[]){
	
	printf("Los i-nodos son:\n");

	if (nftw(argc >= 2 ? argv[1] : ".", visitar, 10, 0) != 0){
		printf("\nSintaxis de ejecución: ejercicio4 [<nom_directorio>]\n\n");
		perror("Error en nftw");
	}

	printf("\nExisten %d archivos regulares con permiso x para grupo y otros\n",arch_permisos);
	printf("El tamaño total ocupado por dichos archivos es %d bytes\n\n",esp_ocup);

	return EXIT_SUCCESS;
}