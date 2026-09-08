#ifndef TSDEF_H
#define TSDEF_H

#include "Tipos.h"
#define DEFAULT_MAX_NIVELES 10

typedef enum {
    IDENTIFICADOR_SIM,
    NUMERO_SIM,
    SUMA_SIM,
    MULTIPLICACION_SIM,
    ASIGNACION_SIM,
    RETURN_SIM,
    MAIN_SIM,
    BOOLEAN_SIM
} TSimbolo;

typedef struct simbolo {
    TSimbolo tipoSimbolo;
    char* nombre;
    Tipo tipo;
    int valor;
} Simbolo;


typedef struct NodoSimbolo {
    Simbolo* simbolo;
    struct NodoSimbolo* sig;
} NodoSimbolo;

typedef struct ts {
    NodoSimbolo* niveles;
    int nivelActual;
    int cant;
} Ts;

Ts* inicializarTs(void);
int agregarSimbolo(Simbolo* simbolo, Ts* tabla);
Simbolo* buscarSimbolo(char* nombreBuscado, Ts* tabla);
void agregarNivel(Ts* tabla);
void sacarNivel(Ts* tabla);

#endif