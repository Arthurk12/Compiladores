/*
ARTHUR BÖCKMANN GROSSI - 00275607
IAN FISCHER SCHILLING - 00275603
*/

#ifndef TAC_HEADER
#define TAC_HEADER

#include <stdio.h>
#include "symbols.h"
#include "hash.h"
#include "ast.h"



typedef struct tac{
    int code;
    hashNode* res;
    hashNode* op1;
    hashNode* op2;
    struct tac *next;
} TAC;

TAC* tacCreate(int code, hashNode* res, hashNode* op1, hashNode* op2);
TAC* tacJoin(TAC* t1, TAC* t2);
TAC* tacGenerate(AST* node, hashNode* jumpLoopIteration);
TAC* makeOP(int code, TAC* res1, TAC* res2);
TAC* makeIfThen(TAC* expr, TAC* cIf);
TAC* makeIfThenElse(TAC* expr, TAC* cIf, TAC* cElse);
TAC* makeLeap(hashNode* jumpLoop);
TAC* makeLoop(TAC* expr, TAC* cLoop, hashNode* jumpLoop);
TAC* makeFunc(AST* node, TAC* param, TAC* cFunc);
TAC* makeFuncCall(AST* node, TAC* listParam);

void tacPrintSingle(TAC *tac);
void tacPrintForward(TAC *tac);

#endif