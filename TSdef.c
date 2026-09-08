#include <stdlib.h>
#include <string.h> 
#include "TSdef.h"

Ts* inicializarTs(void){
    Ts* ts = (Ts*) malloc(sizeof(Ts));

    ts->niveles = (NodoSimbolo*) malloc(sizeof(NodoSimbolo) * DEFAULT_MAX_NIVELES);
    ts->nivelActual = 1;
    ts->cant = 1;

    ts->niveles[0].sig = NULL;
    ts->niveles[0].ant = NULL;

    return ts;
}

int agregarSimbolo(Simbolo* simbolo, Ts* tabla){
    int actual = tabla->nivelActual;
    NodoSimbolo* nuevoNodoSimbolo = (NodoSimbolo*) malloc(sizeof(NodoSimbolo));
    
    nuevoNodoSimbolo->simbolo = simbolo;
    
    NodoSimbolo nodoActual = tabla->niveles[actual];
    while(nodoActual->sig != NULL){
        Simbolo* simboloActual = nodoActual->simbolo;
        if(simboloActual->clase == simbolo->clase){
            // lanzar una excepcion
            return 0;
        }
        nodoActual = nodoActual->sig;
        free(simboloActual);
    }
    nodoActual->sig = nuevoNodoSimbolo;
    
    free(nuevoNodoSimbolo);
    return 1;
}

Simbolo* buscarSimbolo(char* nombreBuscado, Ts* tabla){
    int nivel = tabla->nivelActual;
    NodoSimbolo* nodoActual = tabla->niveles[nivel];

    while(nodoActual->sig != NULL){
        char* nombreActual = (nodoActual->simbolo)->nombre;

        if (strcmp(nombreActual, nombreBuscado)==0) return nodoActual->simbolo;

        nodoActual = nodoActual->sig; 
    }   
    
    free(nodoActual);
    return NULL;
}
