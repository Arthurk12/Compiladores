/*
ARTHUR BÖCKMANN GROSSI - 00275607
IAN FISCHER SCHILLING - 00275603
*/

#ifndef SEMANTIC_HEADER
#define SEMANTIC_HEADER

#include <stdio.h>
#include "ast.h"


void setDeclaration(AST *node);
void checkUndeclared(void);
void checkOperands(AST* node);

#endif