/*
ARTHUR BÖCKMANN GROSSI - 00275607
IAN FISCHER SCHILLING - 00275603
*/

#ifndef SEMANTIC_HEADER
#define SEMANTIC_HEADER

#include <stdio.h>
#include "ast.h"
#include "y.tab.h"


void setDeclaration(AST *node);
void checkUndeclared(void);
void checkOperands(AST* node);

bool isInt(int type);
bool isFloat(int type);

#endif