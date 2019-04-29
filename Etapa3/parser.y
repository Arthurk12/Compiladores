%{
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "functions.h"


void yyerror(char *msg);
int yylex();

%}

%union{
    struct hashnode *symbol;
    struct astnode *ast;
}

%type <ast> expr arglist argresto programa

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
%token <symbol> TK_IDENTIFIER
%token <symbol> LIT_INTEGER
%token <symbol> LIT_FLOAT  
%token <symbol> LIT_CHAR 
%token <symbol> LIT_STRING 
%token TOKEN_ERROR

%left OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_DIF OPERATOR_NOT '<' '>'
%left OPERATOR_OR
%left OPERATOR_AND
%left '+' '-'
%left '*' '/'

%%

programa    : declist
            ;

declist     : dec declist
            | 
            ;

dec         : KW_BYTE TK_IDENTIFIER '=' val                             ';'
            | KW_BYTE TK_IDENTIFIER '[' LIT_INTEGER ']'                 ';'
            | KW_BYTE TK_IDENTIFIER '[' LIT_INTEGER ']' ':' inilist     ';'
            | KW_BYTE TK_IDENTIFIER '(' paramlist ')' block             ';'
            | KW_INT TK_IDENTIFIER '=' val                              ';'
            | KW_INT TK_IDENTIFIER '[' LIT_INTEGER ']'                  ';'
            | KW_INT TK_IDENTIFIER '[' LIT_INTEGER ']' ':' inilist      ';'
            | KW_INT TK_IDENTIFIER '(' paramlist ')' block              ';'
            | KW_FLOAT TK_IDENTIFIER '=' val                            ';'
            | KW_FLOAT TK_IDENTIFIER '[' LIT_INTEGER ']'                ';'
            | KW_FLOAT TK_IDENTIFIER '[' LIT_INTEGER ']' ':' inilist    ';'
            | KW_FLOAT TK_IDENTIFIER '(' paramlist ')' block            ';'
            ;

inilist     : val inilist
            | 
            ;

val         : LIT_INTEGER
            | LIT_FLOAT
            | LIT_CHAR
            ;

expr        : LIT_INTEGER                   {$$ = astCreate(AST_LIT_INTEGER, $1, 0, 0, 0, 0);}
            | LIT_FLOAT                     {$$ = astCreate(AST_LIT_FLOAT, $1, 0, 0, 0, 0);}
            | LIT_CHAR                      {$$ = astCreate(AST_LIT_CHAR, $1, 0, 0, 0, 0);}
            | LIT_STRING                    {$$ = astCreate(AST_LIT_STRING, $1, 0, 0, 0, 0);}
            | TK_IDENTIFIER                 {$$ = astCreate(AST_TK_IDENTIFIER, $1, 0, 0, 0, 0);}
            | TK_IDENTIFIER '[' expr ']'    {$$ = astCreate(AST_VECTOR, $1, $3, 0, 0, 0);}
            | TK_IDENTIFIER '(' arglist ')' {$$ = astCreate(AST_FUNCTION, $1, $3, 0, 0, 0);}
            | '(' expr ')'                  {$$ = $2;}
            | expr '+' expr                 {$$ = astCreate(AST_OP_ADD, 0, $1, $3, 0, 0);}
            | expr '-' expr                 {$$ = astCreate(AST_OP_SUB, 0, $1, $3, 0, 0);}
            | expr '*' expr                 {$$ = astCreate(AST_OP_MUL, 0, $1, $3, 0, 0);}
            | expr '/' expr                 {$$ = astCreate(AST_OP_DIV, 0, $1, $3, 0, 0);}
            | expr OPERATOR_AND expr        {$$ = astCreate(AST_OP_AND, 0, $1, $3, 0, 0);}
            | expr OPERATOR_OR expr         {$$ = astCreate(AST_OP_OR, 0, $1, $3, 0, 0);}
            | expr OPERATOR_DIF expr        {$$ = astCreate(AST_OP_DIF, 0, $1, $3, 0, 0);}
            | expr OPERATOR_EQ expr         {$$ = astCreate(AST_OP_EQ, 0, $1, $3, 0, 0);}
            | expr OPERATOR_GE expr         {$$ = astCreate(AST_OP_GE, 0, $1, $3, 0, 0);}
            | expr OPERATOR_LE expr         {$$ = astCreate(AST_OP_LE, 0, $1, $3, 0, 0);}
            | expr '>' expr                 {$$ = astCreate(AST_OP_GT, 0, $1, $3, 0, 0);}
            | expr '<' expr                 {$$ = astCreate(AST_OP_LT, 0, $1, $3, 0, 0);}
            | OPERATOR_NOT expr             {$$ = astCreate(AST_OP_NOT, 0, $2, 0, 0, 0);}
            ;

paramlist   : param resto
            ;

param       : KW_BYTE TK_IDENTIFIER 
            | KW_FLOAT TK_IDENTIFIER
            | KW_INT TK_IDENTIFIER
            | 
            ;
            
resto       : ',' param resto
            | 
            ;


block       : '{' cmdlist '}'
            ;

cmdlist     : cmd cmdresto
            ;

cmd         : KW_READ TK_IDENTIFIER
            | KW_PRINT arglist
            | KW_RETURN expr
            | KW_IF '(' expr ')' KW_THEN cmd            {astPrint($3, 0);}
            | KW_IF '(' expr ')' KW_THEN cmd KW_ELSE cmd 
            | KW_LEAP
            | KW_LOOP '(' expr ')' cmd
            | block
            | atrib
            | 
            ;

cmdresto    : ';' cmd cmdresto
            | 
            ;

atrib       : TK_IDENTIFIER '=' expr
            | TK_IDENTIFIER '[' expr ']' '=' expr
            ;

arglist     : expr argresto         {$$ = $1;}
            |                       {$$ = 0;}
            ;

argresto    : ',' expr argresto     {$$ = $2;}
            |                       {$$ = 0;}
            ;

%%

void yyerror(char *msg){
    fprintf(stderr, "%s on line: %d\n",msg, getLineNumber());
    exit(3);
}
