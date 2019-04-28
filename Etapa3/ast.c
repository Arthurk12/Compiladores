#include <stdio.h>
#include "ast.h"

AST *astCreate(int type, hashNode *symbol_node, AST *s0, AST *s1, AST *s2, AST *s3){
    AST *new_node;
    new_node = (AST*) calloc(1, sizeof(AST));
    new_node->type = type;
    new_node->symbol = symbol_node;
    new_node->son[0] = s0;
    new_node->son[1] = s1;
    new_node->son[2] = s2;
    new_node->son[3] = s3;
    return new_node;
}

void astPrint(AST *node){

    int i;
    if(!node)return;
    fprintf(stderr, "AST(");
    switch(node->type){
        case AST_SYMBOL:fprintf(stderr, "AST_SYMBOL, \n");
                        break;
        case AST_ADD:   fprintf(stderr, "AST_ADD, \n");
                        break;
        case AST_SUB:   fprintf(stderr, "AST_SUB, \n");
                        break;
        default:        fprintf(stderr, "AST_UNKNOWN, \n");
                        break;
    }

    for(i=0; i<MAX_SONS; i++)
        astPrint(node->son[i]);
}