/*
ARTHUR BÖCKMANN GROSSI - 00275607
IAN FISCHER SCHILLING - 00275603
*/

#include <stdio.h>
#include "hash.h"
#include "symbols.h"

#define MAX_SONS 4


typedef struct astnode{
    int type;
    hashNode *symbol;
    struct astnode* son[MAX_SONS];
} AST;

AST *astCreate(int type, hashNode *symbol_node, AST *s0, AST *s1, AST *s2, AST *s3);
void astPrint(AST *node, int level);

