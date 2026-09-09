#include <stdio.h>
#include <stdlib.h>
#include "ASTdef.h"
int yyparse(void);

int yywrap(void)
{
    return 1;
}
//raiz del árbol declarado en bison
extern Nodo* raiz;

void generadorAssembly(Nodo* nodo){
	if(nodo == NULL){
		return;
	}

	if((nodo->tipo == NODO_PROGRAMA) || (nodo->tipo == NODO_SENTENCIAS)){
		generadorAssembly(nodo->izq);
		generadorAssembly(nodo->der);
	}
	if((nodo->tipo == NODO_NUMERO)){
		printf(nodo->simbolo->valor);
	}
	if(nodo->tipo == NODO_SUMA){
		generadorAssembly(nodo->izq);
		generadorAssembly(nodo->der);
	}
	if(nodo->tipo == NODO_MULTIPLICACION){
		generadorAssembly(nodo->izq);
		generadorAssembly(nodo->der);
	}
	if(nodo->tipo == NODO_ASIGNACION){
		generadorAssembly(nodo->der);
		printf(nodo->izq->simbolo->nombre);
	}
	if(nodo->tipo == NODO_RETORNO){
		if(nodo->izq  != NULL){
			generadorAssembly(nodo->izq);
		}
	}
}

int main(void){
	yyparse();
	return 0;
}