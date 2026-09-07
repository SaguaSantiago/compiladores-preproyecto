#include <stdlib.h>
#include <string.h>

typedef enum TipoNodo{
    DECL,
    DECLS,
    SENTENCIAS,
    ASIGNACION,
    RETORNO,
    OPERADOR,
    IDENTIFICADOR,
    NUMERO,
    PROGRAMA, 
    TIPO
}TipoNodo;

typedef struct Nodo {
    char* nombre;
    TipoNodo tipo;
    int valor_int;

    struct Nodo *izq;
    struct Nodo *der;
} Nodo;

Nodo* nuevaHoja(TipoNodo tipo, int val, const char* nombre) {
    Nodo* nodo = (Nodo*) malloc(sizeof(Nodo));
    
    nodo->tipo = tipo;
    nodo->valor_int = val;
    if(nombre != NULL){
        nodo->nombre = strdup(nombre);
    }
    else{
        nodo->nombre = NULL;
    }

    nodo->izq = NULL;
    nodo->der = NULL;
    return nodo;
}

Nodo* nuevoNodo(TipoNodo tipo, Nodo* izq, Nodo* der){
    Nodo* nodo = (Nodo*) malloc(sizeof(Nodo));

    nodo->tipo = tipo; 
    nodo->valor_int = 0; 
    nodo->nombre = NULL;

    nodo->izq = izq;
    nodo->der = der;

}

