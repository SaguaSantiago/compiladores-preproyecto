%{
    #include "preproyecto.h"
%}

Letra       [a-zA-Z]
Digito      [0-9]
Id          {Letra}({Letra}|{Digito})*
Num         {Digito}+

%%
"int"       { printf("%d\n", INT); }
"bool"      { printf("%d\n", BOOL); }
"void"      { printf("%d\n", VOID); }
"main"      { printf("%d\n", MAIN); }
"return"    { printf("%d\n", RETURN); }

"true"      { printf("%d\n", TRUE); }
"false"     { printf("%d\n", FALSE); }

{Id}        { printf("%d\n", ID); }
{Num}       { printf("%d\n", NUM); }

"+"         { printf("%d\n", SUMA); }
"*"         { printf("%d\n", MULTIPLICACION); }
"="         { printf("%d\n", ASIGNACION); }

"("         { printf("%d\n", PARENTESIS_IZQ); }
")"         { printf("%d\n", PARENTESIS_DER); }
"{"         { printf("%d\n", LLAVE_IZQ); }
"}"         { printf("%d\n", LLAVE_DER); }
";"         { printf("%d\n", PUNTO_COMA); }
.           {}
%%

int yywrap(void)
{
    return 1;
}

int main(void){
	yylex();
	return 0;
}