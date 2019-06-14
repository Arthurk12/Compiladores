/*
ARTHUR BÖCKMANN GROSSI - 00275607
IAN FISCHER SCHILLING - 00275603
*/

#ifndef AST_HEADER
#define AST_HEADER

#include <stdio.h>
#include "hash.h"

typedef struct tac{
    char code;
    hashNode* symbol[3];
} TAC;

TAC tacCreate();
void tacPrint();
TAC tacJoin(TAC t1, TAC t2);


#endif