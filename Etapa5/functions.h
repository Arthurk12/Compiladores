/*
ARTHUR BÖCKMANN GROSSI - 00275607
IAN FISCHER SCHILLING - 00275603
*/

#ifndef FUNCTIONS_HEADER
#define FUNCTIONS_HEADER

#include <stdio.h>
#include "tac.h"
#include "ast.h"
#include "semantic.h"
#include "y.tab.h"


extern int Running;
extern int LineNumber;
extern bool semanticError;

int getLineNumber();
int isRunning();
void printLineNumber();
char* trimQuotation(int type, char* lit);
void callTacFunction(AST* node);

#endif