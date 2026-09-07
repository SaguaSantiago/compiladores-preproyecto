%{
    #include <stdio.h>
    #include "ASTdef.c"

    int yylex(void);
    void yyerror(const char *s);
    Nodo* raiz;
%}

%union {
    int value;
    char* text;
    node AstTree;
}

%token<value> INT BOOLEAN VOID MAIN TRUE FALSE NUMERO PARENTESIS_IZQ PARENTESIS_DER LLAVE_IZQ LLAVE_DER PUNTO_COMA
%token<text> IDENTIFICADOR
%token<AstTree> SUMA MULTIPLICACION ASIGNACION RETURN

%type<AstTree> Declaraciones Decl Sentencias Asignacion Return Expresion

%start Programa

%%
Programa:TipoRetorno MAIN PARENTESIS_IZQ PARENTESIS_DER LLAVE_IZQ Declaraciones Sentencias LLAVE_DER 
    {raiz = nuevoNodo(PROGRAMA, $6, $7);}
    ;

TipoRetorno:Tipo
            | VOID 
            ;
Tipo:INT {$$ = TIPO;}
    |BOOLEAN {$$ = TIPO;}
    ;

Declaraciones:Decl Declaraciones {$$ = nuevoNodo(DECLS, $1, $2);}
            | 
            ;

Decl:Tipo IDENTIFICADOR PUNTO_COMA 
        {Nodo* nodo = nuevaHoja(IDENTIFICADOR, $1, $2.nombre);
        $$ = nuevoNodo(DECL, nodo, NULL);
        }
        ;

Sentencias:Sent Sentencias {$$ = nuevoNodo(SENTENCIAS, $1, $2);}
            | 
            ;

Sent:Return {$$ = $1;}
    |Asignacion {$$ = $1;}
    ;

Return:RETURN Expresion PUNTO_COMA {$$ = nuevoNodo(RETURN, $2, NULL);}
    |RETURN PUNTO_COMA {$$ = nuevaHoja(RETURN, -1, NULL);}
    ;

Asignacion:IDENTIFICADOR ASIGNACION Expresion PUNTO_COMA 
        {Nodo* hojaId = nuevaHoja(IDENTIFICADOR, -1,$1);
         $$ = nuevoNodo(ASIGNACION, hojaId, $3);}
        ;

Expresion:Expresion SUMA Expresion {$$ = nuevoNodo(OPERADOR, $1,$3);}
        |Expresion MULTIPLICACION Expresion {$$ = nuevoNodo(OPERADOR, $1,$3);}
        |PARENTESIS_IZQ Expresion PARENTESIS_DER {$$ = $2;}
        |IDENTIFICADOR {$$ = nuevaHoja(IDENTIFICADOR, -1, $1.nombre);}
        |NUMERO {$$ = nuevaHoja(NUMERO, $1, NULL);}
        |TRUE   {$$ = nuevaHoja(TIPO, $1, NULL);}
        |FALSE  {$$ = nuevaHoja(TIPO, $1, NULL);}
        ;
%%

void yyerror(const char *s)
{
    fprintf(stderr, "Error sintáctico: %s\n", s);
}