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
        case AST_FUNC_DECLARATION:
        case AST_FUNC_PARAM:
                                    if(node->symbol == 0) return;
                                    if(node->symbol->dec == true){
                                        fprintf(stderr, "Semantic Error: '%s' redeclared on line %i\n", node->symbol->lit, node->lineNumber);
                                    }

                                    if(node->son[0]->type == AST_DATATYPE_BYTE)
                                        node->symbol->datatype = DATATYPE_BYTE;
                                    else if(node->son[0]->type == AST_DATATYPE_INT)
                                        node->symbol->datatype = DATATYPE_INT;
                                    else if(node->son[0]->type == AST_DATATYPE_FLOAT)
                                        node->symbol->datatype = DATATYPE_FLOAT;

                                    node->symbol->dec = true;

                                break;
        default:
                                break;
    }

}

void checkUndeclared(){
    hashCheckUndeclared();
}

void checkOperands(AST* node){
    // TO-DO
}