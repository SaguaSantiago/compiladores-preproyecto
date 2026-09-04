%{
    #include <stdio.h>

    int yylex(void);
    void yyerror(const char *s);
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
Programa:TipoRetorno MAIN PARENTESIS_IZQ PARENTESIS_DER LLAVE_IZQ Declaraciones Sentencias LLAVE_DER;

TipoRetorno:Tipo
            | VOID
            ;
Tipo:INT
    |BOOLEAN
    ;

Declaraciones:Decl Declaraciones
            | 
            ;

Decl:Tipo IDENTIFICADOR PUNTO_COMA;

Sentencias:Sent Sentencias
            | 
            ;

Sent:Return 
    |Asignacion
    ;

Return:RETURN Expresion PUNTO_COMA
    |RETURN PUNTO_COMA
    ;

Asignacion:IDENTIFICADOR ASIGNACION Expresion PUNTO_COMA;

Expresion:Expresion SUMA Expresion
        |Expresion MULTIPLICACION Expresion
        |PARENTESIS_IZQ Expresion PARENTESIS_DER
        |IDENTIFICADOR
        |NUMERO
        |TRUE
        |FALSE
        ;
%%

void yyerror(const char *s)
{
    fprintf(stderr, "Error sintáctico: %s\n", s);
}