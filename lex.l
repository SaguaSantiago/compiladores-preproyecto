%{
    #include <stdio.h>
    #include "bisson.tab.h"
    int yylex(void);
    extern int yywrap(void);
%}

Letra       [a-zA-Z]
Digito      [0-9]
Id          {Letra}({Letra}|{Digito})*
Num         {Digito}+
BoolConst   {true | false}

%%
"int"       { return INT; }
"boolean"      { return BOOLEAN; }
"void"      { return VOID; }
"main"      { return MAIN; }
"return"    { return RETURN; }

"true"      { return TRUE; }
"false"     { return FALSE; }

{Id}        { return IDENTIFICADOR; }
{Num}       { return NUMERO; }

"+"         { return SUMA; }
"*"         { return MULTIPLICACION; }
"="         { return ASIGNACION; }

"("         { return PARENTESIS_IZQ; }
")"         { return PARENTESIS_DER; }
"{"         { return LLAVE_IZQ; }
"}"         { return LLAVE_DER; }
";"         { return PUNTO_COMA; }

[ \n\t]+     {}
\nl.           {printf("Token Desconocido: %s\n", yytext);}
%%
