#include <stdio.h>
#include "semantic.h"

bool semanticError = false;

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
                                        semanticError = true;
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
    if(hashCheckUndeclared())
        semanticError = true;    
}

void checkOperands(AST* node){
	int i;
	int err;

	if (node == 0 ){
        return;
    }

	for ( i = 0; i < MAX_SONS; i++){
		checkOperands(node->son[i]);
    }
	switch(node->type){
        case AST_OP_EQUAL:
        case AST_OP_ADD:
        case AST_OP_SUB:
        case AST_OP_MUL:
        case AST_OP_DIV:
        case AST_OP_AND:
        case AST_OP_OR:
        case AST_OP_DIF:
        case AST_OP_EQ:
        case AST_OP_GE:
        case AST_OP_LE:
        case AST_OP_GT:
        case AST_OP_LT:
        case AST_OP_NOT:
        case AST_LIT_INTEGER:
        case AST_LIT_FLOAT:
        case AST_LIT_CHAR:
        case AST_LIT_STRING:
        case AST_TK_IDENTIFIER:
        case AST_VECTOR:
        case AST_FUNCTION:
        case AST_VAR_DECLARATION:
        case AST_VEC_DECLARATION:
        case AST_FUNC_DECLARATION:
        case AST_DATATYPE_BYTE:
        case AST_DATATYPE_FLOAT:
        case AST_DATATYPE_INT:
        case AST_FUNC_PARAM:
        case AST_DECLIST:
        case AST_INILIST:
        case AST_FUNC_PARAMLIST:
        case AST_BLOCK:
        case AST_CMDLIST:
        case AST_CMD_READ:
        case AST_CMD_PRINT:
        case AST_CMD_RETURN:
        case AST_CMD_IF:
        case AST_CMD_IF_ELSE:
        case AST_CMD_LEAP:
        case AST_CMD_LOOP:
        case AST_CMDRESTO:
        case AST_ATRIB:
        case AST_VEC_POS_ATRIB:
        case AST_ARGRESTO:
        case AST_ARGLIST:
        case AST_PARAMRESTO:
        case AST_VEC_DECLARATION_INI:
        default:
            break;
	}
}