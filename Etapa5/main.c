/*
ARTHUR BÖCKMANN GROSSI - 00275607
IAN FISCHER SCHILLING - 00275603
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include "tac.h"
#include "ast.h"
#include "semantic.h"
#include "y.tab.h"

extern int yylex();
extern int yyparse();
extern char *yytext;
extern FILE *yyin;
extern FILE *out;
extern bool semanticError;

//int isRunning();
//int getLineNumber();

int main(int argc, char** argv){
	initMe();

	if(argc < 2){
		printf("Use o comando: ./etapa4 input.txt\n");
		exit(1);	
	}
	
	if((yyin = fopen(argv[1], "r"))==0){
		printf("Erro ao abrir o arquivo de entrada!");
		exit(2);
	}

	while(isRunning()){
		yyparse();
	}
		
	if(semanticError == false){
		printf("Valid Program! \n");
	}else{
		printf("Program has semantic errors!\n");
		exit(4);
	}
	exit(0);
}

