#include "lista.h"
#include <stdlib.h>

const int EXITO =  0;
const int FALLO = -1;


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
  if( !lista ) return FALLO;

  nodo_t* nodo = malloc( sizeof(nodo_t) );
  if( !nodo ) return FALLO;

  nodo->elemento = elemento;
  nodo->siguiente = NULL;

  if( !lista->nodo_fin )
    lista->nodo_fin = nodo;

  if( lista->nodo_inicio )
    nodo->siguiente = lista->nodo_inicio;

  lista->nodo_inicio = nodo;

  lista->cantidad ++;

  return EXITO;
}

/*
 * Devuelve el nodo en la posicion indicada, donde 0 es el primer
 * elemento.
 *
 * Si no existe dicha posicion devuelve NULL.
 */
nodo_t* nodo_en_posicion( lista_t* lista, size_t posicion ){
  if(!lista) return NULL;
  if( posicion >= lista->cantidad ) return NULL;

  nodo_t* nodo = lista->nodo_inicio;
  for( int i=0 ; i < posicion ; i++ ){
    if(!nodo) return NULL;
    nodo = nodo->siguiente;
  }

  return nodo;
}

int lista_insertar(lista_t* lista, void* elemento){

  if( !lista ) return FALLO;

  nodo_t* nodo = malloc( sizeof(nodo_t) );
  if( !nodo ) return FALLO;

  nodo->elemento = elemento;
  nodo->siguiente = NULL;

  if( !lista->nodo_inicio )
    lista->nodo_inicio = nodo;

  if( lista->nodo_fin )
    lista->nodo_fin->siguiente = nodo;

  lista->nodo_fin = nodo;

  lista->cantidad ++;

  return EXITO;
}

int lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion){

  if(!lista) return FALLO;
  if( posicion > lista->cantidad ) posicion = lista->cantidad;

  if( posicion == 0 ) return lista_insertar_inicio( lista, elemento );
  if( posicion == lista->cantidad ) return lista_insertar( lista, elemento );

  nodo_t* nodo_anterior = nodo_en_posicion(lista, posicion-1);

  nodo_t* nuevo_nodo = malloc( sizeof(nodo_t) );
  if( !nuevo_nodo ) return FALLO;
  nuevo_nodo->elemento = elemento;
  nuevo_nodo->siguiente = nodo_anterior->siguiente;
  nodo_anterior->siguiente = nuevo_nodo;

  return EXITO;
}

int lista_borrar(lista_t* lista){
  if(!lista) return FALLO;
  if( lista->cantidad == 0 ) return FALLO;

  if( lista->cantidad == 1 ){
      free( lista->nodo_inicio );
      lista->nodo_inicio = lista->nodo_fin = NULL;
      lista->cantidad--;
      return EXITO;
  }

  nodo_t* anteultimo = nodo_en_posicion( lista, lista->cantidad-2 );
  if( anteultimo->siguiente != lista->nodo_fin ) return FALLO;

  free( anteultimo->siguiente );
  lista->nodo_fin = anteultimo;
  anteultimo->siguiente = NULL;
  lista->cantidad--;

  return EXITO;
}

int lista_borrar_de_posicion(lista_t* lista, size_t posicion){
  if(!lista) return FALLO;
  if( lista->cantidad == 0 ) return FALLO;
  if( posicion >= lista->cantidad ) posicion = lista->cantidad-1;

  if( posicion == lista->cantidad-1 ) return lista_borrar( lista );
  if( posicion == 0 ){
    nodo_t* aux = lista->nodo_inicio;
    lista->nodo_inicio = lista->nodo_inicio->siguiente;
    free( aux );
    lista->cantidad--;
    return EXITO;
  }

  nodo_t* nodo_anterior = nodo_en_posicion( lista , posicion-1 );
  nodo_t* nodo = nodo_anterior->siguiente;
  nodo_anterior->siguiente = nodo->siguiente;
  free( nodo );
  lista->cantidad--;

  return EXITO;
}

void* lista_elemento_en_posicion(lista_t* lista, size_t posicion){
  if( !lista ) return NULL;
  if( posicion >= lista->cantidad ) return NULL;
  if( posicion == lista->cantidad-1 ) return lista_ultimo(lista);

  nodo_t* nodo = nodo_en_posicion( lista, posicion );
  if( !nodo ) return NULL;

  return nodo->elemento;
}

void* lista_ultimo(lista_t* lista){
  if( !lista ) return NULL;
  if( !lista->nodo_fin ) return NULL;
  return lista->nodo_fin->elemento;
}

bool lista_vacia(lista_t* lista){
  if( !lista ) return false;

  if( !lista->cantidad ) return true;
  return false;
}

size_t lista_elementos(lista_t* lista){
  if(!lista) return (size_t)EXITO;
  return lista->cantidad;
}

int lista_apilar(lista_t* lista, void* elemento){
  return lista_insertar_inicio( lista, elemento );
}

int lista_desapilar(lista_t* lista){
  return lista_borrar_de_posicion( lista, 0 );
}

void* lista_tope(lista_t* lista){
  return lista_elemento_en_posicion(lista,0);
}

int lista_encolar(lista_t* lista, void* elemento){
  return lista_insertar( lista, elemento );
}

int lista_desencolar(lista_t* lista){
  return lista_borrar_de_posicion(lista,0);
}

void* lista_primero(lista_t* lista){
  return lista_elemento_en_posicion(lista,0);
}

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
  return (size_t)EXITO;
}
