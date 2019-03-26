/*
ARTHUR BÖCKMANN GROSSI - 00275607
IAN FISCHER SCHILLING - 00275603
*/

#include <stdio.h>

extern int Running;
extern int LineNumber;

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
