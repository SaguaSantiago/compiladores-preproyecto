%{
    #include <stdio.h>
    #include "bisson.tab.h"
    int yylex(void);
    extern int yywrap(void);
%}

%option yylineno

Letra       [a-zA-Z]
Digito      [0-9]
Id          {Letra}({Letra}|{Digito})*
Num         {Digito}+

%%
"int"       { return INT; }
"boolean"      { return BOOLEAN; }
"void"      { return VOID; }
"main"      { return MAIN; }
"return"    { return RETURN; }

"true"      { 
    yylval.valor = 1;
    return TRUE; 
}
"false"     { 
    yylval.valor = 0;
    return FALSE; 
}

{Id} { 
    yylval.nombre = strdup(yytext);
    return IDENTIFICADOR; 
}
{Num} { 
    yylval.valor = atoi(yytext);
    return NUMERO; 
}

"+"         { return SUMA; }
"*"         { return MULTIPLICACION; }
"="         { return ASIGNACION; }

"("         { return PARENTESIS_IZQ; }
")"         { return PARENTESIS_DER; }
"{"         { return LLAVE_IZQ; }
"}"         { return LLAVE_DER; }
";"         { return PUNTO_COMA; }

[ \t]+     {}
\n         {}
.           {
                fprintf(stderr,
                        "Error léxico en línea %d: carácter inesperado '%s'\n",
                        yylineno,
                        yytext);
            }
%%
