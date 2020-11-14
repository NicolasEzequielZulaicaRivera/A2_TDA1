#include "lista.h"
#include "pa2m.h"
#include <stdio.h>
#include <string.h>

bool mostrar_elemento(void* elemento, void* contador){
    if(elemento && contador)
        printf("Elemento %i: %c \n", (*(int*)contador)++, *(char*)elemento);
    return true;
}

void mostrar_lista_char(lista_t* lista){
  nodo_t* nodo = lista->nodo_inicio;

  while (nodo) {
    printf(" %c -", *(char*)(nodo->elemento) );
    nodo = nodo->siguiente;
  }
  printf("\n");
}

void probar_operaciones_lista(){
    lista_t* lista = lista_crear();
    char a='a', b='b', c='c', d='d', w='w';

    lista_insertar(lista, &a);
    lista_insertar(lista, &c);
    lista_insertar_en_posicion(lista, &d, 100);
    lista_insertar_en_posicion(lista, &b, 1);
    lista_insertar_en_posicion(lista, &w, 3);

    lista_borrar_de_posicion(lista, 3);

    printf("Elementos en la lista: ");
    for(size_t i=0; i<lista_elementos(lista); i++)
        printf("%c ", *(char*)lista_elemento_en_posicion(lista, i));

    printf("\n\n");

    printf("Imprimo la lista usando el iterador externo: \n");
    lista_iterador_t* it = NULL;

    for(it = lista_iterador_crear(lista);
        lista_iterador_tiene_siguiente(it);
        lista_iterador_avanzar(it))
        printf("%c ", *(char*)lista_iterador_elemento_actual(it));
    printf("\n\n");

    lista_iterador_destruir(it);

    int contador=0;
    size_t elementos_recorridos = 0;
    printf("Imprimo la lista usando el iterador interno: \n");
    elementos_recorridos = lista_con_cada_elemento(lista, mostrar_elemento, (void*)&contador);

    printf("Recorri %lu elementos con el iterador interno y sume %i elementos\n", elementos_recorridos, contador);

    printf("\n");
    lista_destruir(lista);
}
void probar_operaciones_cola(){
    lista_t* cola = lista_crear();

    int numeros[]={1,2,3,4,5,6};

    for(size_t i=0; i<sizeof(numeros)/sizeof(int); i++){
        printf("Encolo %i\n", numeros[i]);
        lista_encolar(cola, &numeros[i]);
    }

    printf("\nDesencolo los numeros y los muestro: ");
    while(!lista_vacia(cola)){
        printf("%i ", *(int*)lista_primero(cola));
        lista_desencolar(cola);
    }
    printf("\n");
    lista_destruir(cola);
}
void probar_operaciones_pila(){
    lista_t* pila = lista_crear();
    char* algo="somtirogla";

    for(int i=0; algo[i]!= 0; i++){
        printf("Apilo %c\n", algo[i]);
        lista_apilar(pila, &algo[i]);
    }

    printf("\nDesapilo y muestro los elementos apilados: ");
    while(!lista_vacia(pila)){
        printf("%c", *(char*)lista_tope(pila));
        lista_desapilar(pila);
    }
    printf("\n");
    lista_destruir(pila);
}
void mini_pruebas_originales(){
  printf("Pruebo que la lista se comporte como lista\n");
  probar_operaciones_lista();

  printf("\nPruebo el comportamiento de cola\n");
  probar_operaciones_cola();

  printf("\nPruebo el comportamiento de pila\n");
  probar_operaciones_pila();
}

void probar_insertar(){

  lista_t* lista = lista_crear();

  int num[5] = {1,2,3,4,5};
  for( int i = 0; i<5; i++ ) lista_insertar( lista, &num[i] );
  pa2m_afirmar(
    lista->cantidad == 5 &&
    *(int*)lista->nodo_inicio->elemento==1 &&
    *(int*)lista->nodo_inicio->siguiente->elemento==2 &&
    *(int*)lista->nodo_inicio->siguiente->siguiente->elemento==3 &&
    *(int*)lista->nodo_inicio->siguiente->siguiente->siguiente->elemento==4 &&
    *(int*)lista->nodo_inicio->siguiente->siguiente->siguiente->siguiente->elemento==5 &&
    *(int*)lista->nodo_fin->elemento==5 ,
    "lista_insertar"
  );

  lista_insertar_en_posicion( lista, &num[4], 0 );
  pa2m_afirmar(
    lista->cantidad == 6 &&
    *(int*)lista->nodo_inicio->elemento==5 &&
    *(int*)lista->nodo_inicio->siguiente->elemento==1 &&
    *(int*)lista->nodo_fin->elemento==5 ,
    "lista_insertar_en_posicion( INICIO )"
  );

  lista_insertar_en_posicion( lista, &num[4], 2 );
  pa2m_afirmar(
    lista->cantidad == 7 &&
    *(int*)lista->nodo_inicio->elemento==5 &&
    *(int*)lista->nodo_inicio->siguiente->elemento==1 &&
    *(int*)lista->nodo_inicio->siguiente->siguiente->elemento==5 &&
    *(int*)lista->nodo_inicio->siguiente->siguiente->siguiente->elemento==2 &&
    *(int*)lista->nodo_fin->elemento==5 ,
    "lista_insertar_en_posicion( N )"
  );

  lista_insertar_en_posicion( lista, &num[0], 10 );
  pa2m_afirmar(
    lista->cantidad == 8 &&
    *(int*)lista->nodo_fin->elemento==1 ,
    "lista_insertar_en_posicion( FIN )"
  );

  lista_destruir( lista );// Checkeada con valgrind
}

void probar_eliminar(){

  lista_t* lista = lista_crear() ;
  int num[5] = {1,2,3,4,5};
  for( int i = 0; i<5; i++ ) lista_insertar( lista, &num[i] );

  lista_borrar( lista );
  pa2m_afirmar(
    lista->cantidad == 4 &&
    *(int*)lista->nodo_inicio->elemento== 1 &&
    *(int*)lista->nodo_inicio->siguiente->elemento == 2 &&
    *(int*)lista->nodo_inicio->siguiente->siguiente->elemento== 3 &&
    *(int*)lista->nodo_inicio->siguiente->siguiente->siguiente->elemento == 4 &&
    *(int*)lista->nodo_fin->elemento == 4 &&
    !lista->nodo_inicio->siguiente->siguiente->siguiente->siguiente ,
    "lista_borrar"
  );

  lista_borrar_de_posicion( lista, 5 );
  pa2m_afirmar(
    lista->cantidad == 3 &&
    *(int*)lista->nodo_inicio->elemento== 1 &&
    *(int*)lista->nodo_inicio->siguiente->elemento == 2 &&
    *(int*)lista->nodo_inicio->siguiente->siguiente->elemento== 3 &&
    *(int*)lista->nodo_fin->elemento== 3 &&
    !lista->nodo_inicio->siguiente->siguiente->siguiente ,
    "lista_borrar_de_posicion( FIN )"
  );

  lista_borrar_de_posicion( lista, 0 );
  pa2m_afirmar(
    lista->cantidad == 2 &&
    *(int*)lista->nodo_inicio->elemento== 2 &&
    *(int*)lista->nodo_inicio->siguiente->elemento == 3 &&
    !lista->nodo_inicio->siguiente->siguiente ,
    "lista_borrar_de_posicion( INICIO )"
  );

  for( int i = 0; i<5; i++ ) lista_insertar( lista, &num[i] ); // 2 3 1 2 3 4 5
  for( int i=0; i<3; i++ ) lista_borrar_de_posicion( lista, 2 ); // 2 3 4 5
  pa2m_afirmar(
    lista->cantidad == 4 &&
    *(int*)lista->nodo_inicio->elemento== 2 &&
    *(int*)lista->nodo_inicio->siguiente->elemento == 3 &&
    *(int*)lista->nodo_inicio->siguiente->siguiente->elemento== 4 &&
    *(int*)lista->nodo_inicio->siguiente->siguiente->siguiente->elemento == 5 &&
    !lista->nodo_inicio->siguiente->siguiente->siguiente->siguiente ,
    "lista_borrar_de_posicion( N )"
  );

  lista_destruir( lista );// Checkeada con valgrind
}

void probar_ver_datos(){

  lista_t* lista = lista_crear() ;
  int num[5] = {1,2,3,4,5};
  for( int i = 0; i<5; i++ ) lista_insertar( lista, &num[i] );

  pa2m_afirmar(
    *(int*)lista_ultimo(lista)==5,
    "lista_ultimo"
  );
  pa2m_afirmar(
    *(int*)lista_elemento_en_posicion(lista,0)==1 &&
    *(int*)lista_elemento_en_posicion(lista,1)==2 &&
    *(int*)lista_elemento_en_posicion(lista,2)==3 &&
    *(int*)lista_elemento_en_posicion(lista,3)==4 &&
    *(int*)lista_elemento_en_posicion(lista,4)==5 ,
    "lista_elemento_en_posicion"
  );

  pa2m_afirmar(
    lista_elementos(lista)==5,
    "lista_elementos"
  );

  pa2m_afirmar(
    !lista_vacia(lista),
    "lista_vacia (NO VACIA)"
  );
  for(int i=0; i<10; i++)
    lista_borrar(lista);

  pa2m_afirmar(
    lista_vacia(lista),
    "lista_vacia (VACIA)"
  );



  lista_destruir( lista );

}

void probar_pila(){
  lista_t* lista = lista_crear();
  int num[5] = {1,2,3,4,5};

  for( int i = 0; i<5; i++ ) lista_apilar( lista, &num[i] );
  pa2m_afirmar(
    lista->cantidad == 5 &&
    *(int*)lista->nodo_inicio->elemento==5 &&
    *(int*)lista->nodo_inicio->siguiente->elemento==4 &&
    *(int*)lista->nodo_inicio->siguiente->siguiente->elemento==3 &&
    *(int*)lista->nodo_inicio->siguiente->siguiente->siguiente->elemento==2 &&
    *(int*)lista->nodo_inicio->siguiente->siguiente->siguiente->siguiente->elemento==1 &&
    *(int*)lista->nodo_fin->elemento==1 ,
    "lista_apilar"
  );

  for( int i = 0; i<2; i++ ) lista_desapilar( lista );
  pa2m_afirmar(
    lista->cantidad == 3 &&
    *(int*)lista->nodo_inicio->elemento==3 &&
    *(int*)lista->nodo_inicio->siguiente->elemento==2 &&
    *(int*)lista->nodo_inicio->siguiente->siguiente->elemento==1 &&
    *(int*)lista->nodo_fin->elemento==1 ,
    "lista_desapilar"
  );

  pa2m_afirmar(
    *(int*)lista_tope( lista ) == 3,
    "lista_tope"
  );

  lista_destruir( lista );
}

void probar_cola(){

  lista_t* lista = lista_crear();
  int num[5] = {1,2,3,4,5};

  for( int i = 0; i<5; i++ ) lista_encolar( lista, &num[i] );
  pa2m_afirmar(
    lista->cantidad == 5 &&
    *(int*)lista->nodo_inicio->elemento==1 &&
    *(int*)lista->nodo_inicio->siguiente->elemento==2 &&
    *(int*)lista->nodo_inicio->siguiente->siguiente->elemento==3 &&
    *(int*)lista->nodo_inicio->siguiente->siguiente->siguiente->elemento==4 &&
    *(int*)lista->nodo_inicio->siguiente->siguiente->siguiente->siguiente->elemento==5 &&
    *(int*)lista->nodo_fin->elemento==5 ,
    "lista_encolar"
  );

  for( int i = 0; i<2; i++ ) lista_desencolar( lista );
  pa2m_afirmar(
    lista->cantidad == 3 &&
    *(int*)lista->nodo_inicio->elemento==3 &&
    *(int*)lista->nodo_inicio->siguiente->elemento==4 &&
    *(int*)lista->nodo_inicio->siguiente->siguiente->elemento==5 &&
    *(int*)lista->nodo_fin->elemento==5 ,
    "lista_desapilar"
  );

  pa2m_afirmar(
    *(int*)lista_primero( lista ) == 3,
    "lista_primero"
  );

  lista_destruir( lista );
}

bool mayor_a( void* numero, void* referencia ){
  return (*(int*)numero) > (*(int*)referencia) ;
}

void pruebas_de_iterador(){
  lista_t* lista = lista_crear();

  int num[5] = {5,4,3,2,1}, ref = 2;
  for( int i = 0; i<5; i++ ) lista_insertar( lista, &num[i] );

  size_t mayores = lista_con_cada_elemento( lista, mayor_a, &ref);

  pa2m_afirmar(
    mayores == 3,
    "iterador interno "
  );

  int comparador = 5, correcto = 1;
  lista_iterador_t* it = NULL;
  for( it = lista_iterador_crear(lista); lista_iterador_tiene_siguiente(it); lista_iterador_avanzar(it) )
    correcto = correcto && *(int*)lista_iterador_elemento_actual(it) == (comparador--);

  pa2m_afirmar(
    correcto,
    "iterador externo "
  );

  lista_iterador_destruir(it);

  lista_destruir( lista );
}

void pruebas_de_lista_vacia(){
  lista_t* lista = lista_crear();

  pa2m_afirmar(
    lista_borrar(lista) == -1 &&
    lista_borrar_de_posicion(lista,0) == -1 &&
    lista_borrar_de_posicion(lista,1) == -1 &&
    !lista_elemento_en_posicion(lista,0) &&
    !lista_elemento_en_posicion(lista,1) &&
    !lista_ultimo(lista) &&
    !lista_elementos(lista),
    "lista vacia"
  );

  pa2m_afirmar(
    lista_desapilar(lista) == -1 &&
    !lista_tope(lista),
    "pila vacia"
  );

  pa2m_afirmar(
    lista_desencolar(lista) == -1 &&
    !lista_primero(lista),
    "cola vacia"
  );

  lista_iterador_t* it = lista_iterador_crear(lista);

  pa2m_afirmar(
    it && !lista_iterador_tiene_siguiente( it ) &&
    !lista_con_cada_elemento(lista, NULL, NULL),
    "iterador de lista vacia"
  );

  lista_iterador_destruir( it );

  lista_destruir( lista );
}

void pruebas_de_NULL(){

  pa2m_afirmar(
    lista_insertar(NULL,NULL) == -1 &&
    lista_insertar_en_posicion(NULL,NULL,0) == -1 &&
    lista_insertar_en_posicion(NULL,NULL,1) == -1 &&
    lista_borrar(NULL) == -1 &&
    lista_borrar_de_posicion(NULL,0) == -1 &&
    lista_borrar_de_posicion(NULL,1) == -1 &&
    !lista_elemento_en_posicion(NULL,0) &&
    !lista_elemento_en_posicion(NULL,1) &&
    !lista_ultimo(NULL) &&
    !lista_elementos(NULL),
    "lista NULL"
  );

  pa2m_afirmar(
    lista_apilar(NULL,NULL) == -1 &&
    lista_desapilar(NULL) == -1 &&
    !lista_tope(NULL),
    "pila NULL"
  );

  pa2m_afirmar(
    lista_encolar(NULL,NULL) == -1 &&
    lista_desencolar(NULL) == -1 &&
    !lista_primero(NULL),
    "cola NULL"
  );

  pa2m_afirmar(
    !lista_iterador_crear(NULL) &&
    !lista_con_cada_elemento(NULL, NULL, NULL),
    "iterador de lista NULL"
  );

  pa2m_afirmar(
    !lista_iterador_tiene_siguiente(NULL) &&
    !lista_iterador_avanzar(NULL) &&
    !lista_iterador_elemento_actual(NULL),
    "iterador NULL"
  );
}

void pruebas_de_funcionamiento(){

  lista_t* lista = lista_crear();

  int num[5] = {1,2,3,4,5};
  size_t i;
  for( i = 0; i<5; i++ ) lista_insertar( lista, &num[i] );

  while ( !lista_vacia(lista) )lista_borrar_de_posicion(lista,0);
  pa2m_afirmar(
    !lista->cantidad &&
    !lista->nodo_inicio &&
    !lista->nodo_fin ,
    "borrar varios"
  );

  int correcto = 1;
  char esperado [50];

  char abecedario[] = "abcdefghijklmopqrstuvwxyz";
  size_t letras = strlen(abecedario);
  for( i = 0; i<5; i++ ) lista_insertar( lista, &abecedario[i] ); //abcde
  for( i = 0; i<5; i++ ) lista_insertar_en_posicion( lista, &abecedario[i+5],3 ); //abcjihgfde
  for( i = 0; i<5; i++ ) lista_insertar_en_posicion( lista, &abecedario[i+20],100 ); //abcjihgfdevwxyz
  for( i = 0; i<2; i++ ) lista_borrar( lista ); //abcjihgfdevwx
  for( i = 0; i<2; i++ ) lista_borrar_de_posicion( lista, i*2 ); //bcihgfdevwx
  strcpy( esperado, "bcihgfdevwx" );
  letras = strlen(esperado);
  correcto = ( letras == lista->cantidad );
  for( i=0; i<letras; i++ ){
    correcto = correcto && ( esperado[i] == *(char*)lista_elemento_en_posicion(lista,i) );
  }
  pa2m_afirmar( correcto, "funcionamiento de lista" );
  while ( !lista_vacia(lista) )lista_borrar_de_posicion(lista,0);

  letras = strlen(abecedario);

  for( i = 0; i<letras; i++ ) lista_apilar( lista, &abecedario[i] );
  correcto = ( letras == lista->cantidad );
  for( i = 0; i<letras; i++ ){
    correcto = correcto && *(char*)lista_tope(lista) == abecedario[letras-1-i];// LIFO
    lista_desapilar(lista);
  }
  correcto = correcto && lista_vacia( lista );
  pa2m_afirmar( correcto, "funcionamiento de pila" );

  for( i = 0; i<letras; i++ ) lista_encolar( lista, &abecedario[i] );
  correcto = ( letras == lista->cantidad );
  for( i = 0; i<letras; i++ ){
    correcto = correcto && *(char*)lista_tope(lista) == abecedario[i];// FIFO
    lista_desencolar(lista);
  }
  correcto = correcto && lista_vacia( lista );
  pa2m_afirmar( correcto, "funcionamiento de cola" );


  mostrar_lista_char(lista);



  lista_destruir( lista );
}

int main(int argc, char const *argv[]) {

    if( argc == 2 && !strcmp( argv[1], "minipruebas" ) ){
      mini_pruebas_originales();
    } else {

      pa2m_nuevo_grupo("PRUEBAS DE INSERTAR");
      probar_insertar();

      pa2m_nuevo_grupo("PRUEBAS DE ELIMINAR");
      probar_eliminar();

      pa2m_nuevo_grupo("PRUEBAS DE VER DATOS");
      probar_ver_datos();

      pa2m_nuevo_grupo("PRUEBAS DE PILA");
      probar_pila();

      pa2m_nuevo_grupo("PRUEBAS DE COLA");
      probar_cola();

      pa2m_nuevo_grupo("PRUEBAS DE ITERADOR");
      pruebas_de_iterador();

      pa2m_nuevo_grupo("PRUEBAS DE LISTA VACIA");
      pruebas_de_lista_vacia();

      pa2m_nuevo_grupo("PRUEBAS DE ARGUMENTO NULO");
      pruebas_de_NULL();

      pa2m_nuevo_grupo("PRUEBAS DE FUNCIONAMIENTO");
      pruebas_de_funcionamiento();

    }

    printf("\n");

    return 0;
}
