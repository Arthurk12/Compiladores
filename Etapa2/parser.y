%{
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

void yyerror(char *msg);
int yylex();

%}

%token KW_BYTE
%token KW_INT
%token KW_FLOAT
%token KW_IF
%token KW_THEN
%token KW_ELSE
%token KW_LOOP
%token KW_LEAP
%token KW_READ
%token KW_RETURN
%token KW_PRINT
%token OPERATOR_LE
%token OPERATOR_GE
%token OPERATOR_EQ
%token OPERATOR_DIF
%token OPERATOR_OR
%token OPERATOR_AND
%token OPERATOR_NOT
%token TK_IDENTIFIER
%token LIT_INTEGER
%token LIT_FLOAT
%token LIT_CHAR
%token LIT_STRING
%token TOKEN_ERROR

%%

programa    : declist
            ;

declist     : dec declist
            |
            ;

dec         : KW_BYTE TK_IDENTIFIER '=' expr                            ';'
            | KW_BYTE TK_IDENTIFIER '[' LIT_INTEGER ']'                 ';'
            | KW_BYTE TK_IDENTIFIER '[' LIT_INTEGER ']' ':' inilist     ';'
            | KW_BYTE TK_IDENTIFIER '(' paramlist ')' '{' cmdlist '}'   ';'
            | KW_INT TK_IDENTIFIER '=' LIT_INTEGER                      ';'
            | KW_INT TK_IDENTIFIER '[' LIT_INTEGER ']'                  ';'
            | KW_INT TK_IDENTIFIER '[' LIT_INTEGER ']' ':' inilist      ';'
            | KW_INT TK_IDENTIFIER '(' paramlist ')' '{' cmdlist '}'    ';'
            | KW_FLOAT TK_IDENTIFIER '=' LIT_FLOAT                      ';'
            | KW_FLOAT TK_IDENTIFIER '[' LIT_INTEGER ']'                ';'
            | KW_FLOAT TK_IDENTIFIER '[' LIT_INTEGER ']' ':' inilist    ';'
            | KW_FLOAT TK_IDENTIFIER '(' paramlist ')' '{' cmdlist '}'  ';'
            ;

inilist     : val inilist
            |
            ;

val         : LIT_INTEGER
            | LIT_FLOAT
            | LIT_CHAR
            ;

expr        : LIT_INTEGER
            | LIT_FLOAT
            | LIT_CHAR
            | TK_IDENTIFIER
            | TK_IDENTIFIER '[' expr ']'
            | TK_IDENTIFIER '(' arglist ')'
            | '(' expr ')'
            | expr '+' expr
            | expr '-' expr
            | expr '*' expr
            | expr '/' expr
            | expr OPERATOR_AND expr
            | expr OPERATOR_OR expr
            | expr OPERATOR_DIF expr
            | expr OPERATOR_EQ expr
            | expr OPERATOR_GE expr
            | expr OPERATOR_LE expr
            | expr '>' expr
            | expr '<' expr
            | OPERATOR_NOT expr
            ;

paramlist   : param resto
            |
            ;

param       : KW_BYTE TK_IDENTIFIER 
            | KW_FLOAT TK_IDENTIFIER
            | KW_INT TK_IDENTIFIER
            |
            ;
            
resto       : ',' param resto
            |
            ;

cmdlist     : cmd cmdresto
            |
            ;

cmd         : KW_READ LIT_CHAR
            | KW_READ LIT_FLOAT
            | KW_READ LIT_INTEGER
            | KW_READ LIT_STRING
            | KW_READ TK_IDENTIFIER
            | KW_PRINT elemlist
            | KW_RETURN expr
            | KW_IF '(' expr ')' KW_THEN cmdlist
            | KW_IF '(' expr ')' KW_THEN cmdlist KW_ELSE cmdlist 
            | KW_LEAP
            | KW_LOOP '(' expr ')' '{' cmdlist '}'
            | atrib
            |
            ;

cmdresto    : ';' cmd cmdresto
            |
            ;

atrib       : TK_IDENTIFIER '=' expr
            | TK_IDENTIFIER '[' expr ']' '=' expr
            ;

elemlist    : elem elemresto
            ;

elemresto   : ',' elem elemresto
            |
            ;

elem        : expr
            | LIT_STRING
            ;

arglist     : arg argresto
            |
            ;

argresto    : ',' arg argresto
            |
            ;

arg         : LIT_INTEGER
            | LIT_CHAR
            | LIT_FLOAT
            | LIT_STRING
            | TK_IDENTIFIER
            ;


%%

void yyerror(char *msg){
    fprintf(stderr, "%s on line: %d\n",msg, getLineNumber());
    exit(3);
}