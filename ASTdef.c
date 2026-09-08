#include <stdlib.h>
#include <string.h>
#include "ASTdef.h"
#include "TSdef.h"

Nodo* nuevaHoja(TipoNodo tipo, Simbolo* simbolo) {
    Nodo* nodo = (Nodo*) malloc(sizeof(Nodo));
    
    nodo->tipo = tipo;
    nodo->simbolo = &simbolo;

    nodo->izq = NULL;
    nodo->der = NULL;
    return nodo;
}

Nodo* nuevoNodo(TipoNodo tipo, Simbolo simbolo, Nodo* izq, Nodo* der){
    Nodo* nodo = (Nodo*) malloc(sizeof(Nodo));

    nodo->tipo = tipo; 
    nodo->simbolo = &simbolo;
    nodo->izq = izq;
    nodo->der = der;
}

