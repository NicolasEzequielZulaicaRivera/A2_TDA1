# TDA: LISTA , PILA , COLA


## Funcionamiento

  Se crea la libreria **lista.h** con el objetivo de implementar los tipos de datos abstractos **Lista simplemente enlazada** , **Pila** y **Cola**
  
  Se define la estructura `lista_t`, capaz de funcionar como cualquiera de los tres tipos, y la estructura `lista_iterador` para recorrer la lista
  
  ### Lista simplemente enlazada
  descripcion
  
  Para ello se implementan las siguientes funciones :
  
  
  ### Pila
  
  ### Cola
  

  Para ello se implementan las siguientes estructuras :
  * `Pokemon`
  * `Arrecife`
  * `Acuario`

  Y las siguientes funcionalidades:
  * `crear_arrecife` : reserva memoria para el arrecife y carga los pokemones de un archivo dado
  * `crear_acuario` : reserva memoria para el acuario
  * `transladar_pokemon` : trasnlada los pokemones que cumplan un criterio dado de un arrecife a un acuario
  * `censar_arrecife` : muestra los pokemon contenidos en un arrecife
  * `guardar_datos_acuario` : exporta un listado de pokemones de un acuario
  * `liberar_acuario` : libera la memoria reservada para un acuario
  * `liberar_arrecife` :  libera la memoria reservada para un arrecife

  Queda a libertad del usuario crear las funciones de *visualizacion* y *seleccion* de pokemones.

  **Importante :** Las funciones implementadas reservan *memoria dinamica* para la utilizacion de las estructuras, por lo que es imperativo que esta se libere antes de finalizar el programa.
  Esto se realiza mediante el uso de las funciones `liberar_acuario` y `liberar_arrecife` para *todos* los acuarios y arrecifes creados en su programa.

  Se añade el archivo **main.c** como ejemplo de implementacion de la libreria.

## Compilacion y Ejecution

  Habiendo incluido la libreria en su programa o descargado el main.c proveido, puede compilarlo con la siguiente linea en la terminal :

  ` gcc *.c -Wall -Werror -Wconversion -std=c99 -o nombre_programa `
  > usaremos el compilador gcc nativo a cualquier distribucion linux para compilar todos los archivos c (\*.c)
    en el directorio, empleando diversos *flags* para prevenir errores,
    queda a discrecion del usuario elegir el nombre del programa

  Luego puede ejecutar el programa con la siguiente linea:

  `./nombre_programa`

  Cabe aclarar que la terminal debe encontrarse en el directorio donde se encuentran los archivos del programa para poder llevar su compilacion y ejecucion a cabo.

  Se recomienda  emplear un **makefile** para agilizar estas tareas.
  Se añade en los archivos un makefile que nos permitira usar la linea `make run` que compilara (de ser necesario) y ejecutara el programa.
  
### funcionamiento particular de la implementación elegida
(no es necesario detallar función por función, solamente explicar como funciona el código) y por qué se eligió dicha implementación. 

---

## ¿Qué es lo que entendés por una lista? ¿Cuáles son las diferencias entre ser simple o doblemente enlazada?
## ¿Cuáles son las características fundamentales de las Pilas? ¿Y de las Colas?
## ¿Qué es un iterador? ¿Cuál es su función?
## ¿En qué se diferencia un iterador interno de uno externo?
