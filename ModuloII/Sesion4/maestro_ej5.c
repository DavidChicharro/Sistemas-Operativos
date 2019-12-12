/*
maestro_ej5.c
Compilación: gcc -o maestro_ej5 maestro_ej5.c

 Cálculo de los números primos que hay en un intervalo. 
Será necesario construir dos programas, maestro y esclavo. 
Ten en cuenta la siguiente especificación:

 1. El intervalo de números naturales donde calcular los número primos se pasará como
argumento al programa maestro. El maestro creará dos procesos esclavos y dividirá el
intervalo en dos subintervalos de igual tamaño pasando cada subintervalo como argumen-
to a cada programa esclavo. Por ejemplo, si al maestro le proporcionamos el intervalo 
entre 1000 y 2000, entonces un esclavo debe calcular y devolver los números primos com-
prendidos en el subintervalo entre 1000 y 1500, y el otro esclavo entre 1501 y 2000. 
El maestro creará dos cauces sin nombre y se encargará de su redirección para comuni-
carse con los procesos esclavos. El maestro irá recibiendo y mostrando en pantalla 
(también uno a uno) los números primos calculados por los esclavos en orden creciente.

 2. El programa esclavo tiene como argumentos el extremo inferior y superior del inter-
 valo sobre el que buscará números primos. Para identificar un número primo utiliza el
siguiente método concreto: un número n es primo si no es divisible por ningún k tal que
2 < k <= sqrt(n).
 El esclavo envía al maestro cada primo encontrado como un dato entero (4 bytes) que 
escribe en la salida estándar, la cuál se tiene que encontrar redireccionada a un cauce 
sin nombre. Los dos cauces sin nombre necesarios, cada uno para comunicar cada esclavo 
con el maestro, los creará el maestro inicialmente. Una vez que un esclavo haya calculado 
y enviado (uno a uno) al maestro todos los primos en su correspondiente intervalo terminará.

*/

#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[]){
	pid_t PID[2];
	int fd1[2];
	int fd2[2];
	char ini1[6], fin1[6], ini2[6], fin2[6];
	int inicio, fin, mitad;
	int bytes_leidos;
	int buffer;

	if (argc != 3){
		perror("Uso: ./maestro_ej5 <inicio> <fin>\n");
		exit(EXIT_FAILURE);
	}

	inicio = atoi(argv[1]);
	fin = atoi(argv[2]);

	mitad = inicio + ((fin - inicio) / 2);

	sprintf(ini1, "%d", inicio);
	sprintf(fin1, "%d", mitad);
	sprintf(ini2, "%d", mitad+1);
	sprintf(fin2, "%d", fin);

	pipe(fd1);
	pipe(fd2);

	if ( (PID[0]=fork())<0 ) {
		perror("Error en el fork");
		exit(EXIT_FAILURE);
	}
	if(PID[0] == 0) { // hijo 1
		close(fd1[0]);

		dup2(fd1[1],STDOUT_FILENO);
		execl("./esclavo_ej5", "esclavo_ej5", ini1, fin1, NULL);
	}
	else { // Proceso padre
		close(fd1[1]);
		while( (bytes_leidos = read(fd1[0],&buffer,sizeof(int))) == 4 ){
			printf("%d\n", buffer);
			if(bytes_leidos<0)
				printf("Error al leer el primo [1]\n");
		}
		close(fd1[0]);

		if ( (PID[1]=fork())<0 ) { // hijo 2
			perror("Error en el fork");
			exit(EXIT_FAILURE);
		}
		if(PID[1] == 0) {
			close(fd2[0]);

			dup2(fd2[1],STDOUT_FILENO);
			execl("./esclavo_ej5", "esclavo_ej5", ini2, fin2, NULL);
		}
		else{
			close(fd2[1]);
			while( (bytes_leidos = read(fd2[0],&buffer,sizeof(int))) > 0 ){
				printf("%d\n", buffer);
				if(bytes_leidos<0)
					printf("Error al leer el primo [2]\n");
			}
			close(fd2[0]);
		}
	}

	return EXIT_SUCCESS;
}