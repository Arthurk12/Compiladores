/*
ARTHUR BÖCKMANN GROSSI - 00275607
IAN FISCHER SCHILLING - 00275603
*/

#ifndef AST_HEADER
#define AST_HEADER

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "hash.h"
#include "symbols.h"
#include "y.tab.h"


#define MAX_SONS 4

extern int LineNumber;
extern int Running;

typedef struct astnode{
    int type;
    int datatype;
    hashNode *symbol;
    struct astnode* son[MAX_SONS];
    int lineNumber;
} AST;



AST *astCreate(int type, hashNode *symbol_node, AST *s0, AST *s1, AST *s2, AST *s3);
void astPrint(AST *node, int level);
void astPrintRec(AST *node, int level);
void generateSource(AST *node, FILE *out);
void closeFile(FILE *code);
int getLineNumber();
int isRunning();


#endif