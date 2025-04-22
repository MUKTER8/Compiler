#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Flex part */
%{
#include "y.tab.h"
%}

%%
[0-9]+ {
    yylval.dval = atof(yytext);  // Changed to atof and using dval for double
    return DIGIT;
}
.       return yytext[0];
%%

/* Bison part */
%{
#include <stdio.h>
int yylex(void);
void yyerror(const char *s);
%}

%union {
    double dval;
}

%token <dval> DIGIT
%type <dval> expr
%type <dval> term
%type <dval> factor

%%

line:   expr '\n'        { printf("Result: %g\n", $1); }
      ;

expr:   expr '+' term    { $$ = $1 + $3; }
      | expr '-' term    { $$ = $1 - $3; }
      | term             { $$ = $1; }
      ;

term:   term '*' factor  { $$ = $1 * $3; }
      | term '/' factor  { $$ = $1 / $3; }
      | factor           { $$ = $1; }
      ;

factor: '(' expr ')'     { $$ = $2; }
      | DIGIT           { $$ = $1; }
      ;

%%

int main() {
    printf("Enter arithmetic expression: ");
    yyparse();
    return 0;
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}