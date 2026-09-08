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

int agregarSimbolo(Simbolo* simbolo, Ts* tabla) {
    int actual = tabla->nivelActual;
    NodoSimbolo* nodoActual = tabla->niveles[actual].sig;

    while (nodoActual != NULL) {
        if (nodoActual->simbolo != NULL &&
            nodoActual->simbolo->tipoSimbolo == IDENTIFICADOR_SIM &&
            simbolo->tipoSimbolo == IDENTIFICADOR_SIM &&
            strcmp(nodoActual->simbolo->nombre, simbolo->nombre) == 0) {
            return 0;
        }

        nodoActual = nodoActual->sig;
    }

    NodoSimbolo* nuevo = malloc(sizeof(NodoSimbolo));
    nuevo->simbolo = simbolo;
    nuevo->sig = tabla->niveles[actual].sig;
    tabla->niveles[actual].sig = nuevo;

    return 1;
}

Simbolo* buscarSimbolo(char* nombreBuscado, Ts* tabla){
    int nivel = tabla->nivelActual;
    NodoSimbolo* nodoActual = tabla->niveles[nivel].sig;

    
    // while(nodoActual != NULL){
    //     char* nombreActual = (nodoActual->simbolo)->nombre;

    //     if(nodoActual->simbolo == NULL){
    //         nodoActual = nodoActual->sig;
    //         continue;
    //     }
    //     if (strcmp(nombreActual, nombreBuscado)==0) return nodoActual->simbolo;

    //     nodoActual = nodoActual->sig;
    // }   
    while (nodoActual != NULL) {
        if (nodoActual->simbolo != NULL &&
            nodoActual->simbolo->nombre != NULL &&
            strcmp(nodoActual->simbolo->nombre, nombreBuscado) == 0) {
            return nodoActual->simbolo;
        }

        nodoActual = nodoActual->sig;
    }

    free(nodoActual);
    return NULL;
}
