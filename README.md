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

**Ejercicio 1** - _consumidorFIFO.c & productorFIFO.c_

En primer lugar hay que ejecutar el ``consumidor``, que creará un archivo FIFO (_ComunicacionFIFO_) y quedará a la espera de recibir un mensaje del ``productor``. A continuación, en otro terminal, habrá que ejecutar el ``productor`` con un único argumento, que será un mensaje; dicho mensaje aparecerá en el terminal del  ``consumidor``. Para terminar la ejecución el  ``productor`` tendrá que enviar como argumento el mensaje  _fin_.


**Ejercicio 2** - _tarea6.c_

``pipe(fd)`` crea un cauce sin nombre; al pasarle `fd` como parámetro se asigna por defecto el modo lectura a _fd[0]_ y el modo escritura a _fd[1]_.

Con la orden ``fork`` se crea un proceso hijo, el cual cierra el descriptor de lectura _fd[0]_ y posteriormente escribe un mensaje a través del cauce en el descriptor de escritura _fd[1]_.

El proceso padre cierra el descriptor de escritura _fd[1]_ y lee del cauce lo que ha escrito el hijo con el descriptor de lectura _fd[0]_, imprimiendo por pantalla dicho mensaje y el número de bytes que ocupa.


**Ejercicio 3** - _tarea7.c_

Programa ilustrativo del uso de pipes y la redirección de entrada y salida estándar simulando la orden: ``ls | sort``.


**Ejercicio 4** - _tarea8.c_

La ejecución de este programa realiza la misma acción que en el ejercicio anterior, ``ls | sort``, pero  en lugar de realizar primero el cierre del descriptor de archivo `close(fd)` y después la duplicación del descriptor `dup(fd)`, ambas órdenes se combinan en una sola: ``dup2(int oldfd, int newfd);``


**Ejercicio 5** - _maestro_ej5.c & esclavo_ej5.c_

Cálculo de números primos en un intervalo utilizando cauces sin nombre.


## Sesión 5

Llamadas al sistema para gestión y control de señales

**_tarea9.c_**

Este programa ignora las interrupciones por teclado `Ctrl+C`. Para poder interrumpirlo habría que, por ejemplo, ejecutar la orden ``kill -9 <PID>`` desde otro terminal (se puede consultar el *\<PID>* con la orden `top`).

**_tarea10.c_**

El programa establece un manejador para las señales recibidas (interrupciones de teclado `Ctrl+C`), finalizando cuando recibe tres.

**Ejercicio 1** - _envioSignal.c & reciboSignal.c_

En primer lugar hay que ejecutar ``reciboSignal`` para que quede a la espera de recibir una señal en segundo plano. Después, ejecutar ``envioSignal [012] <PID>``, donde _\<PID>_ es el identificador de proceso de ``reciboSignal``, el cual se puede consultar con la orden `top`. Según la orden enviada (0, 1 ó 2), terminará el proceso o se mostrará un mensaje u otro en el terminal donde se ejecuta ``reciboSignal``; los mensajes mostrados por _1_ y _2_ se pueden configurar en en la función `static void sig_USR_hdlr(int sigNum)` de ``reciboSignal``.

El funcionamiento de cada sección del código se especifica en los comentarios del mismo.


**Ejercicio 2** - _contador.c_

Maneja cualquier señal recibida y muestra cuántas veces ha recibido dicha señal.


**Ejercicio 3**

Suspende la ejecución del proceso actual hasta que se reciba la señal _SIGUSR1_. Para comprobar su correcto funcionamiento ejecutar `./ejercicio3 &` y una vez obtenido su PID, ejecutar el programa _envioSignal_ del _Ejercicio 1_ para enviar la señal _SIGUSR1_: `./envioSignal 1 <PID ejercicio3>`.


**Ejercicio 4** - _tarea12.c_

El programa crea una máscara donde sólo se añade la señal _SIGTERM_. Aplica la máscara y con ello bloquea la señal _SIGTERM_. Duerme durante 10 segundos y si durante este tiempo recibe dicha señal, no reaccionará porque está bloqueada; Una vez termina de "dormir", desbloquea la señal _SIGTERM_, reanudando la máscara antigua y comprobando si la variable signal_recibida está activada, lo cual quiere decir que ha recibido la señal _SIGTERM_ mientras dormía, en cuyo caso mostrará un mensaje indicándolo; si no, no mostrará nada.
Al igual que en el ejercicio anterior se puede enviar _SIGTERM_ ejecutando `./tarea12 &` para obtener su PID y `./envioSignal 0 <PID tarea12>` para enviar la señal _SIGTERM_.


## Sesión 6

Control de archivos y archivos proyectados en memoria

**Ejercicio 1** 

Crear un archivo de texto con varias líneas con texto de prueba y ejecutar `./ejercicio1 sort "<" prueba.txt`.


**Ejercicio 2**

Ejecutar `./ejercicio2 ls "|" sort`.


**Ejercicio 3**

Con el mismo archivo de texto del _Ejercicio 1_ ejecutar el mismo programa `ejercicio3` en dos terminales distintos con la misma orden: `./ejercicio3 prueba.txt`. Esto hará que se bloquee el acceso al archivo desde el primer proceso lanzado y hasta que no se desbloquee en uno no aparecerá por pantalla en el otro terminal la línea "_Procesando el archivo prueba.txt_".


**Ejercicio 4**

Ejecutar `./ejercicio4 bloq_ej4`, donde el primer argumento _bloq\_ej4_ será el nombre del archivo, que no tiene porqué existir previamente. En otro terminal ejecutar el mismo comando para comprobar que no se puede ejecutar otra instancia al estar el cerrojo establecido en la primera ejecución.


**Ejercicio 5**

La ejecución de este programa `./ejercicio5 <arch_orig> <arch_destino>` supone lo mismo que realizar en Linux la orden `cp <arch_orig> <arch_destino>`. El archivo de destino lo crea el programa si no existe.
