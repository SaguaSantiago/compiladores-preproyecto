#ifdef GENERADOR_ASSEMBLY_H
#define GENERADOR_ASSEMBLY_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "ASTdef.h"

int temp_n;

char* newTemp();
char* generadorAssembly(Nodo* nodo, FILE* archivoAssembly);
#endif