/*
ARTHUR BÖCKMANN GROSSI - 00275607
IAN FISCHER SCHILLING - 00275603
*/

#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "ast.h"

extern int yylex();
extern int yyparse();
extern char *yytext;
extern FILE *yyin;
extern FILE *out;
extern bool semanticError;

int isRunning();
int getLineNumber();

int main(int argc, char** argv){
	initMe();

	if(argc < 3){
		printf("Use o comando: ./etapa4 input.txt output.txt\n");
		exit(1);	
	}
	
	if((yyin = fopen(argv[1], "r"))==0){
		printf("Erro ao abrir o arquivo de entrada!");
		exit(2);
	}

	if((out = fopen(argv[2], "w+"))==0){
		printf("Erro ao criar o arquivo de saida!");
		exit(1);
	}

	while(isRunning()){
		yyparse();

		if(semanticError == false)
			printf("Valid Program! \n");
		else{
			printf("Program has semantic errors!\n");
			exit(4);
		}
	}
		
	hashPrint();
	exit(0);
}

