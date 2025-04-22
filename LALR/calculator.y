%{
#include <stdio.h>
#include <math.h>

int yylex(void);
void yyerror(const char *s);
%}

%union {
    double dval;
}

%token <dval> DIGIT
%type <dval> expr term factor

%%

input:    /* empty */
        | input line
        ;

line:     expr '\n'   { printf("= %g\n", $1); }
        ;

expr:     expr '+' term   { $$ = $1 + $3; }
        | expr '-' term   { $$ = $1 - $3; }
        | term            { $$ = $1; }
        ;

term:     term '*' factor { $$ = $1 * $3; }
        | term '/' factor { $$ = $1 / $3; }
        | factor          { $$ = $1; }
        ;

factor:   '(' expr ')'    { $$ = $2; }
        | DIGIT           { $$ = $1; }
        ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main() {
    printf("Calculator (enter expressions, Ctrl-Z to exit)\n> ");
    yyparse();
    return 0;
}