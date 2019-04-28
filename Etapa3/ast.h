/*
ARTHUR BÖCKMANN GROSSI - 00275607
IAN FISCHER SCHILLING - 00275603
*/

#include <stdio.h>
#include "hash.h"

#define MAX_SONS 4
#define AST_SYMBOL 1
#define AST_ADD 2
#define AST_SUB 3


typedef struct astnode{
    int type;
    hashNode *symbol;
    struct astnode* son[MAX_SONS];
} AST;

AST *astCreate(int type, hashNode *node, AST s0, AST s1, AST s2, AST s3);
void astPrint(AST node);

