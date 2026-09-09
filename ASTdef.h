#ifndef ASTDEF_H
#define ASTDEF_H
#include "TSdef.h"

typedef enum TipoNodo{
    NODO_DECL,
    NODO_DECLS,
    NODO_SENTENCIAS,
    NODO_ASIGNACION,
    NODO_RETORNO,
    NODO_SUMA,
    NODO_MULTIPLICACION,
    NODO_IDENTIFICADOR,
    NODO_NUMERO,
    NODO_PROGRAMA, 
    NODO_BOOLEAN
}TipoNodo;

typedef struct Nodo {
    Simbolo* simbolo;
    TipoNodo tipo;

    struct Nodo *izq;
    struct Nodo *der;
} Nodo;

#endif