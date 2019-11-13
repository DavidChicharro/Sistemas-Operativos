/*
ejercicio2_mod.c
Compilación: gcc -o ejercicio2_mod ejercicio2_mod.c

Modificación adicional. 
¿Cómo tendrías que modificar el programa para que una vez
finalizada la escritura en el archivo de salida y antes de 
cerrarlo, pudiésemos indicar en su primera línea el número 
de etiquetas ''Bloque i'' escritas de forma que tuviese la 
siguiente apariencia?:

El número de bloques es <nº_bloques>
Bloque 1
// Aquí van los primeros 80 Bytes del archivo pasado como argumento.
Bloque 2
// Aquí van los siguientes 80 Bytes del archivo pasado como argumento.
...
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
int MAX_CONT_BLOQ = 35;

int main(int argc, char *argv[]){
	int fich_lec, fich_esc;
	char buff[MAX_LECT];
	int leidos;
	int cont=1;
	char bloque[MAX_BLOQUE];
	char cont_num_bloques[MAX_CONT_BLOQ];

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
		printf( "Utilizando la entrada estándar como entrada: ");
		fflush(stdout);
		fich_lec=STDIN_FILENO;
	}

	// Crea el archivo de salida
	if( (fich_esc=open("salida_mod.txt",O_CREAT|O_TRUNC|O_WRONLY,S_IRUSR|S_IWUSR))<0 ){
		printf("\nError %d en open",errno);
		perror("\nError en open de salida_mod.txt");
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
	// reposiciona el desplazamiento MAX_CONT_BLOQ para que a continuación se escriba el contenido del archivo
	if( lseek(fich_esc,MAX_CONT_BLOQ,SEEK_SET) < 0) {
		perror("\nError en primer lseek");
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

	sprintf(cont_num_bloques, "El número de bloques es %d", cont-1);
	if( lseek(fich_esc,0,SEEK_SET) < 0) {
		perror("\nError en segundo lseek");
		exit(EXIT_FAILURE);
	}
	if( write(fich_esc, cont_num_bloques, strlen(cont_num_bloques)) <0 ){
		printf("\nError %d en último write: contador núm. bloques.",errno);
		perror("\nError en el último write (contador núm. bloques)");
		exit(EXIT_FAILURE);
	}

	close( fich_lec );
	close( fich_esc );

	return EXIT_SUCCESS;
}