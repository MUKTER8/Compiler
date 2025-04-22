%{
#include "calculator.tab.h"
%}

%option noyywrap

%%
[0-9]+(\.[0-9]+)? {
    yylval.dval = atof(yytext);
    return DIGIT;
}
[ \t]   ; /* ignore whitespace */
\n      return '\n';
.       return yytext[0];
%%