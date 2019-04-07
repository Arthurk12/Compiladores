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

dec         : KW_BYTE TK_IDENTIFIER '=' val ';'
            | KW_INT TK_IDENTIFIER '=' LIT_INTEGER ';'
            | KW_INT TK_IDENTIFIER '[' LIT_INTEGER ']' ';'
            | KW_INT TK_IDENTIFIER '[' LIT_INTEGER ']' ':' inilist ';'
            | KW_FLOAT TK_IDENTIFIER '=' LIT_FLOAT ';'
            ;

inilist     : val inilist
            |
            ;

val         : LIT_CHAR
            | LIT_FLOAT
            | LIT_INTEGER
            | LIT_STRING
            ;
            
%%

void yyerror(char *msg){
    fprintf(stderr, "Syntax error! on line: %d\n", getLineNumber());
    exit(3);
}