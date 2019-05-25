#include <stdio.h>
#include "semantic.h"

void setDeclaration(AST *node){
    if(node == 0) return;

    int i;
    for(i=0; i<MAX_SONS; i++){
        setDeclaration(node->son[i]);
    }

    switch(node->type){
        case AST_VAR_DECLARATION:
        case AST_VEC_DECLARATION:
        case AST_VEC_DECLARATION_INI:
                                    if(node->symbol == 0) return;

                                    if(node->son[0]->type == AST_DATATYPE_BYTE)
                                        node->symbol->datatype = DATATYPE_BYTE;
                                    else if(node->son[0]->type == AST_DATATYPE_INT)
                                        node->symbol->datatype = DATATYPE_INT;
                                    else if(node->son[0]->type == AST_DATATYPE_FLOAT)
                                        node->symbol->datatype = DATATYPE_FLOAT;

                                break;
        default:
                                break;
    }

}