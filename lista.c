#include "lista.h"
#include <stdlib.h>
#include <stdio.h> // printf - borrar luego


lista_t* lista_crear(){

  lista_t* lista = malloc( sizeof( lista_t ) );
  if( !lista ) return NULL;

  lista->cantidad = 0;
  lista->nodo_inicio = NULL;
  lista->nodo_fin = NULL;

  return lista;
}

/*
 * Inserta un elemento al inicio de la lista.
 * Devuelve 0 si pudo insertar o -1 si no pudo.
 */
int lista_insertar_inicio(lista_t* lista, void* elemento){
  if( !lista ) return -1;

  nodo_t* nodo = malloc( sizeof(nodo_t) );
  if( !nodo ) return -1;

  nodo->elemento = elemento;
  nodo->siguiente = NULL;

  if( !lista->nodo_fin )
    lista->nodo_fin = nodo;

  if( lista->nodo_inicio )
    nodo->siguiente = lista->nodo_inicio;

  lista->nodo_inicio = nodo;

  lista->cantidad ++;

  return 0;
}

int lista_insertar(lista_t* lista, void* elemento){

  if( !lista ) return -1;

  nodo_t* nodo = malloc( sizeof(nodo_t) );
  if( !nodo ) return -1;

  nodo->elemento = elemento;
  nodo->siguiente = NULL;

  if( !lista->nodo_inicio )
    lista->nodo_inicio = nodo;

  if( lista->nodo_fin )
    lista->nodo_fin->siguiente = nodo;

  lista->nodo_fin = nodo;

  lista->cantidad ++;

  return 0;
}

/*
 * Inserta un elemento en la posicion indicada, donde 0 es insertar
 * como primer elemento y 1 es insertar luego del primer elemento.
 * En caso de no existir la posicion indicada, lo inserta al final.
 * Devuelve 0 si pudo insertar o -1 si no pudo.
 */
int lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion){

  if(!lista) return -1;
  if( posicion > lista->cantidad ) return -1;

  if( posicion == 0 ) return lista_insertar_inicio( lista, elemento );
  if( posicion == lista->cantidad ) return lista_insertar( lista, elemento );

  nodo_t* nodo_anterior = lista->nodo_inicio;

  for( int i=0 ; i < posicion-1 ; i++ ){
    if(!nodo_anterior) return-1;
    nodo_anterior = nodo_anterior->siguiente;
  }

  nodo_t* nuevo_nodo = malloc( sizeof(nodo_t) );
  if( !nuevo_nodo ) return -1;
  nuevo_nodo->elemento = elemento;
  nuevo_nodo->siguiente = nodo_anterior->siguiente;
  nodo_anterior->siguiente = nuevo_nodo;

  return 0;
}

/*
 * Quita de la lista el elemento que se encuentra en la ultima posición.
 * Devuelve 0 si pudo eliminar o -1 si no pudo.
 */
int lista_borrar(lista_t* lista){
  return 0;
}

/*
 * Quita de la lista el elemento que se encuentra en la posición
 * indicada, donde 0 es el primer elemento.
 * En caso de no existir esa posición se intentará borrar el último
 * elemento.
 * Devuelve 0 si pudo eliminar o -1 si no pudo.
 */
int lista_borrar_de_posicion(lista_t* lista, size_t posicion){
  return 0;
}

/*
 * Devuelve el elemento en la posicion indicada, donde 0 es el primer
 * elemento.
 *
 * Si no existe dicha posicion devuelve NULL.
 */
void* lista_elemento_en_posicion(lista_t* lista, size_t posicion){
  return NULL;
}

/*
 * Devuelve el último elemento de la lista o NULL si la lista se
 * encuentra vacía.
 */
void* lista_ultimo(lista_t* lista){
  return NULL;
}

/*
 * Devuelve true si la lista está vacía o false en caso contrario.
 */
bool lista_vacia(lista_t* lista){
  return false;
}

/*
 * Devuelve la cantidad de elementos almacenados en la lista.
 */
size_t lista_elementos(lista_t* lista){
  return 0;
}

/*
 * Apila un elemento.
 * Devuelve 0 si pudo o -1 en caso contrario.
 */
int lista_apilar(lista_t* lista, void* elemento){
  return 0;
}

/*
 * Desapila un elemento.
 * Devuelve 0 si pudo desapilar o -1 si no pudo.
 */
int lista_desapilar(lista_t* lista){
  return 0;
}

/*
 * Devuelve el elemento en el tope de la pila o NULL
 * en caso de estar vacía.
 */
void* lista_tope(lista_t* lista){
  return NULL;
}

/*
 * Encola un elemento.
 * Devuelve 0 si pudo encolar o -1 si no pudo.
 */
int lista_encolar(lista_t* lista, void* elemento){
  return 0;
}

/*
 * Desencola un elemento.
 * Devuelve 0 si pudo desencolar o -1 si no pudo.
 */
int lista_desencolar(lista_t* lista){
  return 0;
}

/*
 * Devuelve el primer elemento de la cola o NULL en caso de estar
 * vacía.
 */
void* lista_primero(lista_t* lista){
  return NULL;
}

/*
 * Libera la memoria reservada por la lista.
 */
void lista_destruir(lista_t* lista){

  if( !lista ) return;

  nodo_t* nodo_i = lista->nodo_inicio;
  nodo_t* nodo_aux = NULL;

  while ( nodo_i ) {
    nodo_aux = nodo_i;
    nodo_i = nodo_i->siguiente;
    free( nodo_aux );
  }

  free( lista );

  return;
}

/*
 * Crea un iterador para una lista. El iterador creado es válido desde
 * el momento de su creación hasta que no haya mas elementos por
 * recorrer o se modifique la lista iterada (agregando o quitando
 * elementos de la lista).
 *
 * Al momento de la creación, el iterador queda listo para devolver el
 * primer elemento utilizando lista_iterador_elemento_actual.
 *
 * Devuelve el puntero al iterador creado o NULL en caso de error.
 */
lista_iterador_t* lista_iterador_crear(lista_t* lista){
  return NULL;
}

/*
 * Devuelve true si hay mas elementos sobre los cuales iterar o false
 * si no hay mas.
 */
bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador){
  return false;
}

/*
 * Avanza el iterador al siguiente elemento.
 * Devuelve true si pudo avanzar el iterador o false en caso de
 * que no queden elementos o en caso de error.
 *
 * Una vez llegado al último elemento, si se invoca a
 * lista_iterador_elemento_actual, el resultado siempre será NULL.
 */
bool lista_iterador_avanzar(lista_iterador_t* iterador){
  return false;
}

/*
 * Devuelve el elemento actual del iterador o NULL en caso de que no
 * exista dicho elemento o en caso de error.
 */
void* lista_iterador_elemento_actual(lista_iterador_t* iterador){
  return NULL;
}

/*
 * Libera la memoria reservada por el iterador.
 */
void lista_iterador_destruir(lista_iterador_t* iterador){
  return;
}

/*
 * Iterador interno. Recorre la lista e invoca la funcion con cada elemento de
 * la misma. Dicha función puede devolver true si se deben seguir recorriendo
 * elementos o false si se debe dejar de iterar elementos.
 *
 * La función retorna la cantidad de elementos iterados o 0 en caso de error.
 */
size_t lista_con_cada_elemento(lista_t* lista, bool (*funcion)(void*, void*), void *contexto){
  return 0;
}
