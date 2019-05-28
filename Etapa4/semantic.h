/*
ARTHUR BÖCKMANN GROSSI - 00275607
IAN FISCHER SCHILLING - 00275603
*/

#ifndef SEMANTIC_HEADER
#define SEMANTIC_HEADER

#include <stdio.h>
#include "ast.h"
#include "y.tab.h"
#include<stdbool.h>


void setDeclaration(AST *node);
void checkUndeclared(void);
void checkOperands(AST* node);

bool isInt(int datatype);
bool isFloat(int datatype);
bool isBool(int datatype);
bool isVariable(int datatype);
bool isVector(int datatype);
bool isFunction(int datatype);
bool isSameDatatype(int datatype1, int datatype2);
bool isCompatible(int var, int atrib);

int basicDatatype(int datatype);
int getDatatype(int datatype1, int datatype2);
AST* getFunction(AST* rnode, char* lit);
bool checkFunctionParameters(AST* fun, AST* node);

#endif