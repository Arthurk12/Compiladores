/*
ARTHUR BÖCKMANN GROSSI - 00275607
IAN FISCHER SCHILLING - 00275603
*/

#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "functions.h"

extern int yylex();
extern int yyparse();
extern char *yytext;
extern FILE *yyin;

int isRunning();
int getLineNumber();

int main(int argc, char** argv){
	initMe();

	if(argc < 2){
		printf("Use o comando: ./etapa1 input.txt \n");
		exit(1);	
	}
	
	if((yyin = fopen(argv[1], "r"))==0){
		printf("Erro ao abrir o arquivo de entrada!");
		exit(1);
	}

	while(isRunning()){
		yyparse();
		printf("Programa Valido! \n");
	}
		
	hashPrint();
	exit(0);
}

