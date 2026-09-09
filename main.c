#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "ASTdef.h"
#include "interprete.c"
#include "generadorAssembly.c"

int yyparse(void);
extern void interprete(Nodo* raiz);

int yywrap(void)
{
    return 1;
}
//raiz del árbol declarado en bison
extern Nodo* raiz;


int main(void){
	yyparse();
	FILE* f = fopen("./output.txt", "w");
	generadorAssembly(raiz, f);
	close(f); 
	interprete(raiz);
	return 0;
}