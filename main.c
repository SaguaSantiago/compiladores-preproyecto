int yyparse(void);

int yywrap(void)
{
    return 1;
}

int main(void){
	yyparse();
	return 0;
}