%{
/* Program to replace 'abc' with 'ABC' */
#include <stdio.h>
%}

%%
abc    { printf("ABC"); }   /* Replace 'abc' with 'ABC' */
.|\n   { ECHO; }            /* Print other characters as-is */
%%

int main() {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}