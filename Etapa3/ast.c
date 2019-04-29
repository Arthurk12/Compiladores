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

void astPrint(AST *node, int level){

    int i;
    if(!node)return;
    for(i=0; i<=level; i++)
        fprintf(stderr, " ");
    fprintf(stderr, "AST(");
    switch(node->type){
        case AST_OP_EQUAL:  fprintf(stderr, "AST_OP_EQUAL, \n");
                        break;
        case AST_OP_ADD:    fprintf(stderr, "AST_ADD, \n");
                        break;
        case AST_OP_SUB:    fprintf(stderr, "AST_SUB, \n");
                        break;
        case AST_OP_MUL:    fprintf(stderr, "AST_MUL, \n");
                        break;
        case AST_OP_DIV:    fprintf(stderr, "AST_DIV, \n");
                        break;
        case AST_OP_AND:    fprintf(stderr, "AST_AND, \n");
                        break;
        case AST_OP_OR:    fprintf(stderr, "AST_OR, \n");
                        break;
        case AST_OP_DIF:    fprintf(stderr, "AST_DIF, \n");
                        break;
        case AST_OP_EQ:    fprintf(stderr, "AST_EQ, \n");
                        break;
        case AST_OP_GE:    fprintf(stderr, "AST_GE, \n");
                        break;
        case AST_OP_LE:    fprintf(stderr, "AST_LE, \n");
                        break;
        case AST_OP_GT:    fprintf(stderr, "AST_GT, \n");
                        break;
        case AST_OP_LT:    fprintf(stderr, "AST_LT, \n");
                        break;
        case AST_OP_NOT:    fprintf(stderr, "AST_NOT, \n");
                        break;
        case AST_LIT_INTEGER: fprintf(stderr, "AST_INTEGER, \n");
                        break;
        case AST_LIT_FLOAT:fprintf(stderr, "AST_FLOAT, \n");
                        break;
        case AST_LIT_CHAR:fprintf(stderr, "AST_CHAR, \n");
                        break;
        case AST_LIT_STRING:fprintf(stderr, "AST_STRING, \n");
                        break;
        case AST_TK_IDENTIFIER:fprintf(stderr, "AST_IDENTIFIER, \n");
                        break;
        case AST_VECTOR:fprintf(stderr, "AST_VECTOR, \n");
                        break;
        case AST_FUNCTION:fprintf(stderr, "AST_FUNCTION, \n");
                        break;
        default:            fprintf(stderr, "AST_UNKNOWN, \n");
                        break;
    }

    level++;

    for(i=0; i<MAX_SONS; i++)
        astPrint(node->son[i], level);
}