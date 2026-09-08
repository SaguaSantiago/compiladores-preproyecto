#include <stdlib.h>
#include <string.h> 
#include "TSdef.h"

Ts* inicializarTs(void){
    Ts* ts = (Ts*) malloc(sizeof(Ts));

    ts->niveles = (NodoSimbolo*) malloc(sizeof(NodoSimbolo) * DEFAULT_MAX_NIVELES);
    for(int i = 0; i < DEFAULT_MAX_NIVELES; i++){
        ts->niveles[i].simbolo = NULL;
        ts->niveles[i].sig = NULL;
    }

    ts->nivelActual = 0;
    ts->cant = 1;

    return ts;
}

int agregarSimbolo(Simbolo* simbolo, Ts* tabla){
    int actual = tabla->nivelActual;
    NodoSimbolo* nuevoNodoSimbolo = (NodoSimbolo*) malloc(sizeof(NodoSimbolo));
    
    nuevoNodoSimbolo->simbolo = simbolo;
    
    NodoSimbolo* nodoActual = tabla->niveles[actual].sig;
    if(nodoActual == NULL){
        tabla->niveles[actual].sig = nuevoNodoSimbolo;
        return 1;
    }

    while(nodoActual->sig != NULL){
        Simbolo* simboloActual = nodoActual->simbolo;
        if(strcmp(simboloActual->nombre, simbolo->nombre) == 0){
            // lanzar una excepcion
            return 0;
        }
        nodoActual = nodoActual->sig;
    }
    nodoActual->sig = nuevoNodoSimbolo;
    
    return 1;
}

Simbolo* buscarSimbolo(char* nombreBuscado, Ts* tabla){
    int nivel = tabla->nivelActual;
    NodoSimbolo* nodoActual = tabla->niveles[nivel].sig;

    while(nodoActual != NULL){
        char* nombreActual = (nodoActual->simbolo)->nombre;

        if (strcmp(nombreActual, nombreBuscado)==0) return nodoActual->simbolo;

        nodoActual = nodoActual->sig;
    }   

    free(nodoActual);
    return NULL;
}
