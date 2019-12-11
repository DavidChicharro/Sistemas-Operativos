# Sistemas Operativos
## Grado en Ingeniería Informática (UGR). Curso 2019-2020

Asignatura de **Sistemas Operativos**, 2º curso del Grado en Ingeniería Informática de la Universidad de Granada (UGR)

## Sesión 1

Llamadas al sistema para el Sistema de Archivos (parte 1).


## Sesión 2

Llamadas al sistema para el Sistema de Archivos (Parte 2)


## Sesión 3

Llamadas al sistema para el Control de Procesos


## Sesión 4

Comunicación entre procesos utilizando cauces

**Ejercicio 1**

Para la ejecución del ejercicio 1 hay que compilar los archivos ``consumidorFIFO.c`` y ``productorFIFO.c``. En primer lugar hay que ejecutar el ``consumidor``, que creará un archivo FIFO (_ComunicacionFIFO_) y quedará a la espera de recibir un mensaje del ``productor``. A continuación, en otro terminal, habrá que ejecutar el ``productor`` con un único argumento, que será un mensaje; dicho mensaje aparecerá en el terminal del  ``consumidor``. Para terminar la ejecución el  ``productor`` tendrá que enviar como argumento el mensaje  _fin_.


**Ejercicio 2** - _tarea6.c_

En primer lugar ``pipe(fd)`` crea un cauce sin nombre; al pasarle `fd` como parámetro se asigna por defecto el modo lectura a _fd[0]_ y el modo escritura a _fd[1]_.

Con la orden ``fork`` se crea un proceso hijo, el cual cierra el descriptor de lectura _fd[0]_ y posteriormente escribe un mensaje a través del cauce en el descriptor de escritura _fd[1]_.

El proceso padre cierra el descriptor de escritura _fd[1]_ y lee del cauce lo que ha escrito el hijo con el descriptor de lectura _fd[0]_, imprimiendo por pantalla dicho mensaje y el número de bytes que ocupa.
