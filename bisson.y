%{
    #include <stdio.h>
    #include <string.h>
    #include "ASTdef.h"

    #include "ASTdef.c"

    int yylex(void);
    void yyerror(const char *s);

    Ts* tablaSimbolos;
    Nodo* raiz;
%}

%union {
    int valor;
    char* nombre;
    node arbolAst;
    Tipo tipo;
}

%token SUMA MULTIPLICACION ASIGNACION RETURN INT BOOLEAN VOID MAIN TRUE FALSE PARENTESIS_IZQ PARENTESIS_DER LLAVE_IZQ LLAVE_DER PUNTO_COMA
%token<valor> NUMERO
%token<nombre> IDENTIFICADOR

%type<arbolAst> Declaraciones Decl Sentencias Asignacion Return Expresion Sent
%type<tipo> TipoRetorno Tipo

%start Programa

%%
Programa:TipoRetorno MAIN PARENTESIS_IZQ PARENTESIS_DER LLAVE_IZQ Declaraciones Sentencias LLAVE_DER 
    {   Simbolo* simbolo = (Simbolo*) malloc(sizeof(Simbolo));
        simbolo->nombre = "main";
        simbolo->tipo = $1.tipo;
        simbolo->tipoSimbolo = MAIN_SIM;
        agregarSimbolo(simbolo);
        raiz = nuevoNodo(PROGRAMA, $6, $7);}
    ;

TipoRetorno:Tipo {$$ = $1.tipo;}
            | VOID {$$ = TIPO_VOID;} 
            ;
Tipo:INT {$$ = TIPO_INT;}
    |BOOLEAN {$$ = TIPO_BOOLEAN;}
    ;

Declaraciones:Decl Declaraciones {$$ = nuevoNodo(NODO_DECLS, $1, $2);}
            | 
            ;

Decl:Tipo IDENTIFICADOR PUNTO_COMA 
        {Simbolo* simbolo = (Simbolo*) malloc(sizeof(Simbolo));
        strcpy(simbolo->nombre, $2);
        simbolo->tipo = $1.tipo;
        simbolo->tipoSimbolo = IDENTIFICADOR_SIM;
        if(!agregarSimbolo(simbolo)){
            fprintf(stderr, "Error: variable '%s' ya declarada/\n", simbolo->nombre);
            exit(1);
        }

        Nodo* nodo = nuevaHoja(NODO_IDENTIFICADOR, simbolo);
        $$ = nuevoNodo(NODO_DECL, nodo, NULL);
        }
        ;

Sentencias:Sent Sentencias {$$ = nuevoNodo(NODO_SENTENCIAS, $1, $2);}
            | 
            ;

Sent:Return {$$ = $1;}
    |Asignacion {$$ = $1;}
    ;

Return:RETURN Expresion PUNTO_COMA {
    Simbolo* simbolo = (Simbolo*) malloc(sizeof(Simbolo));
    simbolo->tipo = $2.tipo;
    simbolo->tipoSimbolo = RETURN_SIM;
    agregarSimbolo(simbolo);

    Simbolo* main = buscarSimbolo("main", tablaSimbolos);
    if (simbolo->tipo != main->tipo){
        fprintf(stderr, "Error: tipo de retorno invalido.\n");
        exit(1);
    }

    $$ = nuevoNodo(NODO_RETURN, $2, NULL);}
    |RETURN PUNTO_COMA {
        Simbolo* main = buscarSimbolo("main", tablaSimbolos);
        if(main->tipo != TIPO_VOID){
            fprintf(stderr, "Error: tipo de retorno invalido.\n");
            exit(1);
        }
        $$ = nuevaHoja(NODO_RETURN, NULL);} 
    ;

Asignacion:IDENTIFICADOR ASIGNACION Expresion PUNTO_COMA 
        {Simbolo* simbolo = (Simbolo*) malloc(sizeof(Simbolo));
        strcpy(simbolo->nombre, $1);
        simbolo->tipoSimbolo = IDENTIFICADOR_SIM;
        agregarSimbolo(simbolo);

        Simbolo* idEncontrado = buscarSimbolo(simbolo->nombre, tablaSimbolos);
        if(idEncontrado == NULL) { // TODO poner linea de error
            fprintf(stderr, "Error: variable '%s' no declarada.\n", simbolo->nombre);
            exit(1);
        } else if(idEncontrado->tipo != $3.nodo.simbolo->tipo) {
            printf(stderr, "Error: tipo de dato incompatible en la asignación a '%s'.\n", simbolo->nombre);
            exit(1);
        }
        simbolo->tipo = idEncontrado->tipo;
        idEncontrado->valor = $3.nodo.simbolo->valor;

        Nodo* hojaId = nuevaHoja(NODO_IDENTIFICADOR, idEncontrado);

        $$ = nuevoNodo(NODO_ASIGNACION, hojaId, $3);}
        ;

Expresion:Expresion SUMA Expresion {
        Simbolo* simbolo = (Simbolo*) malloc(sizeof(Simbolo));
        simbolo->tipo = $1.tipo;

        if ($1.tipo != $3.tipo) {
            fprintf(stderr, "Error: tipos de datos incompatibles en la suma.\n");
            exit(1);
        }
        
        simbolo->tipoSimbolo = SUMA_SIM;

        simbolo->valor = $1.nodo.simbolo->valor + $3.nodo.simbolo->valor;

        agregarSimbolo(simbolo);
        
        $$ = nuevoNodo(NODO_SUMA, $1,$3);
    }
    |Expresion MULTIPLICACION Expresion {
        Simbolo* simbolo = (Simbolo*) malloc(sizeof(Simbolo));
        simbolo->tipo = $1.tipo;

        if ($1.tipo != $3.tipo) {
            fprintf(stderr, "Error: tipos de datos incompatibles en el producto.\n");
            exit(1);
        }
        
        simbolo->tipoSimbolo = MULTIPLICACION_SIM;

        simbolo->valor = $1.nodo.simbolo->valor * $3.nodo.simbolo->valor;

        agregarSimbolo(simbolo);
        
        $$ = nuevoNodo(NODO_MULTIPLICACION, $1,$3);
        }
    |PARENTESIS_IZQ Expresion PARENTESIS_DER {$$ = $2;}
    |IDENTIFICADOR {$$ = $1;}
    |NUMERO {
        Simbolo* simbolo = (Simbolo*) malloc(sizeof(Simbolo));
        simbolo->tipo = TIPO_INT;
        simbolo->tipoSimbolo = NUMERO_SIM;
        simbolo->valor = $1.valor;
        agregarSimbolo(simbolo);
        $$ = nuevaHoja(NODO_NUMERO, simbolo);
        }
    |TRUE   {
        Simbolo* simbolo = (Simbolo*) malloc(sizeof(Simbolo));
        simbolo->tipo = TIPO_BOOLEAN;
        simbolo->tipoSimbolo = BOOLEAN_SIM;
        simbolo->valor = $1.valor;
        agregarSimbolo(simbolo);

        $$ = nuevaHoja(NODO_TIPO, simbolo);}
    |FALSE  {
        Simbolo* simbolo = (Simbolo*) malloc(sizeof(Simbolo));
        simbolo->tipo = TIPO_BOOLEAN;
        simbolo->tipoSimbolo = BOOLEAN_SIM;
        simbolo->valor = $1.valor;
        agregarSimbolo(simbolo);
        
        $$ = nuevaHoja(NODO_TIPO, simbolo);}
;
%%

void yyerror(const char *s)
{
    fprintf(stderr, "Error sintáctico: %s\n", s);
}