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

int printLineNumber(){	
	printf("\nLinha %d :", getLineNumber());
}
