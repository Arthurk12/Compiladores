%{
#include <stdio.h>
#include <stdlib.h>
#include "semantic.h"
#include "functions.h"


void yyerror(char *msg);
int yylex();

FILE *out = NULL;
%}

%union{
    struct hashnode *symbol;
    struct astnode *ast;
}

%type <ast> expr arglist argresto programa declist dec val inilist paramlist param paramresto block cmdlist cmd cmdresto atrib

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


%left OPERATOR_OR
%left OPERATOR_AND
%left OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_DIF OPERATOR_NOT '<' '>'
%left '+' '-'
%left '*' '/'
%left '(' ')'

%%

programa    : declist                                                       {$$ = $1;astPrint($1, 0); generateSource($1, out); setDeclaration($1);}
            ;

declist     : dec declist                                                   {$$ = astCreate(AST_DECLIST, 0, $1, $2, 0, 0);}
            |                                                               {$$ = 0;}
            ;

dec         : KW_BYTE TK_IDENTIFIER '=' val                             ';' {$$ = astCreate(AST_VAR_DECLARATION, $2, astCreate(AST_DATATYPE_BYTE, 0, 0, 0, 0, 0), $4, 0, 0);}
            | KW_BYTE TK_IDENTIFIER '[' LIT_INTEGER ']'                 ';' {$$ = astCreate(AST_VEC_DECLARATION, $2, astCreate(AST_DATATYPE_BYTE, 0, 0, 0, 0, 0), astCreate(AST_LIT_INTEGER, $4, 0, 0, 0, 0), 0, 0);}
            | KW_BYTE TK_IDENTIFIER '[' LIT_INTEGER ']' ':' inilist     ';' {$$ = astCreate(AST_VEC_DECLARATION_INI, $2, astCreate(AST_DATATYPE_BYTE, 0, 0, 0, 0, 0), astCreate(AST_LIT_INTEGER, $4, 0, 0, 0, 0), $7, 0);}
            | KW_BYTE TK_IDENTIFIER '(' paramlist ')' block             ';' {$$ = astCreate(AST_FUNC_DECLARATION, $2, astCreate(AST_DATATYPE_BYTE, 0, 0, 0, 0, 0), $4, $6, 0);}
            | KW_INT TK_IDENTIFIER '=' val                              ';' {$$ = astCreate(AST_VAR_DECLARATION, $2, astCreate(AST_DATATYPE_INT, 0, 0, 0, 0, 0), $4, 0, 0);}
            | KW_INT TK_IDENTIFIER '[' LIT_INTEGER ']'                  ';' {$$ = astCreate(AST_VEC_DECLARATION, $2, astCreate(AST_DATATYPE_INT, 0, 0, 0, 0, 0), astCreate(AST_LIT_INTEGER, $4, 0, 0, 0, 0), 0, 0);}
            | KW_INT TK_IDENTIFIER '[' LIT_INTEGER ']' ':' inilist      ';' {$$ = astCreate(AST_VEC_DECLARATION_INI, $2, astCreate(AST_DATATYPE_INT, 0, 0, 0, 0, 0), astCreate(AST_LIT_INTEGER, $4, 0, 0, 0, 0), $7, 0);}
            | KW_INT TK_IDENTIFIER '(' paramlist ')' block              ';' {$$ = astCreate(AST_FUNC_DECLARATION, $2, astCreate(AST_DATATYPE_INT, 0, 0, 0, 0, 0), $4, $6, 0);}
            | KW_FLOAT TK_IDENTIFIER '=' val                            ';' {$$ = astCreate(AST_VAR_DECLARATION, $2, astCreate(AST_DATATYPE_FLOAT, 0, 0, 0, 0, 0), $4, 0, 0);}
            | KW_FLOAT TK_IDENTIFIER '[' LIT_INTEGER ']'                ';' {$$ = astCreate(AST_VEC_DECLARATION, $2, astCreate(AST_DATATYPE_FLOAT, 0, 0, 0, 0, 0), astCreate(AST_LIT_INTEGER, $4, 0, 0, 0, 0), 0, 0);}
            | KW_FLOAT TK_IDENTIFIER '[' LIT_INTEGER ']' ':' inilist    ';' {$$ = astCreate(AST_VEC_DECLARATION_INI, $2, astCreate(AST_DATATYPE_FLOAT, 0, 0, 0, 0, 0), astCreate(AST_LIT_INTEGER, $4, 0, 0, 0, 0), $7, 0);}
            | KW_FLOAT TK_IDENTIFIER '(' paramlist ')' block            ';' {$$ = astCreate(AST_FUNC_DECLARATION, $2, astCreate(AST_DATATYPE_FLOAT, 0, 0, 0, 0, 0), $4, $6, 0);}
            ;

inilist     : val inilist                   {$$ = astCreate(AST_INILIST, 0, $1, $2, 0, 0);}
            |                               {$$ = 0;}
            ;

val         : LIT_INTEGER                   {$$ = astCreate(AST_LIT_INTEGER, $1, 0, 0, 0, 0);}
            | LIT_FLOAT                     {$$ = astCreate(AST_LIT_FLOAT, $1, 0, 0, 0, 0);}
            | LIT_CHAR                      {$$ = astCreate(AST_LIT_CHAR, $1, 0, 0, 0, 0);}
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

paramlist   : param paramresto              {$$ = astCreate(AST_FUNC_PARAMLIST, 0, $1, $2, 0, 0);}
            ;

param       : KW_BYTE TK_IDENTIFIER         {$$ = astCreate(AST_FUNC_PARAM, $2, astCreate(AST_DATATYPE_BYTE, 0, 0, 0, 0, 0), 0, 0, 0);}
            | KW_FLOAT TK_IDENTIFIER        {$$ = astCreate(AST_FUNC_PARAM, $2, astCreate(AST_DATATYPE_FLOAT, 0, 0, 0, 0, 0), 0, 0, 0);}
            | KW_INT TK_IDENTIFIER          {$$ = astCreate(AST_FUNC_PARAM, $2, astCreate(AST_DATATYPE_INT, 0, 0, 0, 0, 0), 0, 0, 0);}
            |                               {$$ = 0;}
            ;
            
paramresto  : ',' param paramresto          {$$ = astCreate(AST_PARAMRESTO, 0, $2, $3, 0, 0);}
            |                               {$$ = 0;}
            ;


block       : '{' cmdlist '}'               {$$ = astCreate(AST_BLOCK, 0, $2, 0, 0, 0);}
            ;

cmdlist     : cmd cmdresto                  {$$ = astCreate(AST_CMDLIST, 0, $1, $2, 0, 0);}
            ;

cmd         : KW_READ TK_IDENTIFIER                         {$$ = astCreate(AST_CMD_READ, $2, 0, 0, 0, 0);}
            | KW_PRINT arglist                              {$$ = astCreate(AST_CMD_PRINT, 0, $2, 0, 0, 0);}
            | KW_RETURN expr                                {$$ = astCreate(AST_CMD_RETURN, 0, $2, 0, 0, 0);}
            | KW_IF '(' expr ')' KW_THEN cmd                {$$ = astCreate(AST_CMD_IF, 0, $3, $6, 0, 0);}
            | KW_IF '(' expr ')' KW_THEN cmd KW_ELSE cmd    {$$ = astCreate(AST_CMD_IF_ELSE, 0, $3, $6, $8, 0);}
            | KW_LEAP                                       {$$ = astCreate(AST_CMD_LEAP, 0, 0, 0, 0, 0);}
            | KW_LOOP '(' expr ')' cmd                      {$$ = astCreate(AST_CMD_LOOP, 0, $3, $5, 0, 0);}
            | block                                         {$$ = $1;}
            | atrib                                         {$$ = $1;}    
            |                                               {$$ = 0;}
            ;

cmdresto    : ';' cmd cmdresto                              {$$ = astCreate(AST_CMDRESTO, 0, $2, $3, 0, 0);}
            |                                               {$$ = 0;}
            ;

atrib       : TK_IDENTIFIER '=' expr                        {$$ = astCreate(AST_ATRIB, $1, $3, 0, 0, 0);}
            | TK_IDENTIFIER '[' expr ']' '=' expr           {$$ = astCreate(AST_VEC_POS_ATRIB, $1, $3, $6, 0, 0);}
            ;

arglist     : expr argresto                                 {$$ = astCreate(AST_ARGLIST, 0, $1, $2, 0, 0);}
            |                                               {$$ = 0;}
            ;

argresto    : ',' expr argresto                             {$$ = astCreate(AST_ARGRESTO, 0, $2, $3, 0, 0);}
            |                                               {$$ = 0;}
            ;

%%

void yyerror(char *msg){
    fprintf(stderr, "%s on line: %d\n", msg, getLineNumber());
    exit(3);
}
