/*
ARTHUR BÖCKMANN GROSSI - 00275607
IAN FISCHER SCHILLING - 00275603
*/

#ifndef TAC_HEADER
#define TAC_HEADER

#include <stdio.h>
#include "hash.h"
#include "ast.h"

typedef struct tac{
    int code;
    hashNode* res;
    hashNode* op1;
    hashNode* op2;
    struct TAC* prev;
    struct TAC* next;
} TAC;

TAC* tacCreate(int code, hashNode* res, hashNode* op1, hashNode* op2);
TAC* tacJoin(TAC* t1, TAC* t2);
TAC* tacGenerate(AST* node);
void tacPrint();
#endif