/*
ARTHUR BÖCKMANN GROSSI - 00275607
IAN FISCHER SCHILLING - 00275603
*/

#ifndef FUNCTIONS_HEADER
#define FUNCTIONS_HEADER

#include <stdio.h>

extern int Running;
extern int LineNumber;

int getLineNumber();
int isRunning();
void printLineNumber();
char* trimQuotation(int type, char* lit);

#endif