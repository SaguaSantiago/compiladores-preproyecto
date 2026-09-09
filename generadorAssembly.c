#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "generadorAssembly.h"

temp_n = 1; 

char* newTemp() {
    char* temp = (char*) malloc(16);
    sprintf(temp, "t%d", temp_n++);
    return temp;
}

char* generadorAssembly(Nodo* nodo, FILE* archivoAssembly){
	if(nodo == NULL){
		return NULL;
	}
	char* temp;
	switch (nodo->tipo)
	{
		case NODO_PROGRAMA:
			fprintf(archivoAssembly, "main:\n");
			generadorAssembly(nodo->izq, archivoAssembly);
			generadorAssembly(nodo->der, archivoAssembly);
			break;
		case NODO_SENTENCIAS:
		case NODO_DECLS:
			generadorAssembly(nodo->izq, archivoAssembly);
			generadorAssembly(nodo->der, archivoAssembly);
			break;

		case NODO_ASIGNACION:
			temp = generadorAssembly(nodo->der, archivoAssembly); 	
			fprintf(archivoAssembly, "Store_Mem %s %s\n", temp, nodo->izq->simbolo->nombre);
			break;
		case NODO_NUMERO:
		case NODO_BOOLEAN:
			temp = newTemp();

			fprintf(archivoAssembly, "Load_Const %d %s\n", nodo->simbolo->valor, temp);
			return temp;

		case NODO_SUMA:
			char* temp1 = generadorAssembly(nodo->izq, archivoAssembly);
			char* temp2 = generadorAssembly(nodo->der, archivoAssembly);
			
			fprintf(archivoAssembly, "Add_Reg %s %s\n", temp1, temp2);

			return temp2;
			
		case NODO_MULTIPLICACION:
			temp1 = generadorAssembly(nodo->izq, archivoAssembly);
			temp2 = generadorAssembly(nodo->der, archivoAssembly);
			
			fprintf(archivoAssembly, "Mul_Reg %s %s\n", temp1, temp2);
			
			return temp2;
			
		case NODO_DECL:
			fprintf(archivoAssembly,"Store_Mem %s %d\n", nodo->izq->simbolo->nombre, 0);
			break;

		case NODO_IDENTIFICADOR:
			temp = newTemp();
			fprintf(archivoAssembly,"Load_Mem %s %s\n", nodo->simbolo->nombre, temp);
			
			return temp;

		case NODO_RETORNO:
			 if (nodo->izq != NULL) {
				temp = generadorAssembly(nodo->izq, archivoAssembly);
				fprintf(archivoAssembly, "Return %s\n", temp);
				free(temp);
			}
			fprintf(archivoAssembly, "HALT\n");
			
			return NULL;
		default:
			return NULL;
			break;
	}

	return NULL;
}