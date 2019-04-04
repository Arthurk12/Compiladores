/*
ARTHUR BÖCKMANN GROSSI - 00275607
IAN FISCHER SCHILLING - 00275603
*/

#include <stdio.h>
#include "functions.h"


int getLineNumber(){
	return LineNumber;
}

int isRunning(){
	if(Running)	
		return 1;
	else
		return 0;
}

void printLineNumber(){	
	printf("\nLinha %d :", getLineNumber());
}

char* trimQuotation(int type, char* lit){
	char *trimmedLit;

	trimmedLit = calloc(strlen(lit-1), sizeof(char));

	if(type == LIT_CHAR){
		
		strncpy(trimmedLit, &lit[1], 1);
	}else if(type == LIT_STRING){

		trimmedLit = strtok(lit, "\"");
	}else{
		return lit;
	}
	return trimmedLit;
}