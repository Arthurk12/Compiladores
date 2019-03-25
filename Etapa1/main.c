#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "tokens.h"

extern int yylex();
extern char *yytext;
extern FILE *yyin;

int isRunning();
int getLineNumber();
int printLineNumber();

int main(int argc, char** argv){
	int tok = 0;
	
	initMe();

	if(argc < 2){
		printf("Use o comando: ./etapa1 input.txt \n");
		exit(1);	
	}
	
	if((yyin = fopen(argv[1], "r"))==0){
		printf("Erro ao abrir o arquivo de entrada!");
		exit(1);
	}
	int line = 0;
	while(isRunning()){
		tok = yylex();
		if(line != getLineNumber()){
			line = getLineNumber();
			printLineNumber();
		}
		switch(tok){
		
			case KW_BYTE: 		printf("KW_BYTE "); break;
			case KW_INT: 		printf("KW_INT "); break;
			case KW_FLOAT: 		printf("KW_FLOAT "); break;
			case KW_IF: 		printf("KW_IF "); break;
			case KW_THEN: 		printf("KW_THEN "); break;
			case KW_ELSE: 		printf("KW_ELSE "); break;
			case KW_LOOP: 		printf("KW_LOOP "); break;
			case KW_LEAP: 		printf("KW_LEAP "); break;
			case OPERATOR_OR: 	printf("OPERATOR_OR "); break;
			case OPERATOR_AND: 	printf("OPERATOR_AND "); break;
			case OPERATOR_NOT: 	printf("OPERATOR_NOT "); break;
			case OPERATOR_LE: 	printf("OPERATOR_LE "); break;
			case OPERATOR_GE: 	printf("OPERATOR_GE "); break;
			case OPERATOR_EQ: 	printf("OPERATOR_EQ "); break;
			case OPERATOR_DIF: 	printf("OPERATOR_DIF "); break;
			case KW_READ:		printf("KW_READ "); break;			
			case KW_PRINT: 		printf("KW_PRINT "); break;
			case KW_RETURN: 	printf("KW_RETURN "); break;
			case TK_IDENTIFIER:	printf("TK_IDENTIFIER "); break;
			case LIT_INTEGER:	printf("LIT_INTEGER "); break;
			case LIT_FLOAT:		printf("LIT_FLOAT "); break;
			case LIT_CHAR:		printf("LIT_CHAR "); break;
			case LIT_STRING:	printf("LIT_CHAR "); break;
			case TOKEN_ERROR:	printf("TOKEN_ERROR "); break;
			default: 			printf("%s ", yytext); break;

		}
		
	}
hashPrint();
}

