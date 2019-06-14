#include "tac.h"

TAC* tacCreate(int code, hashNode* res, hashNode* op1, hashNode* op2){
    TAC *newTAC;
    newTAC = (TAC* )calloc(1, sizeof(TAC));
    newTAC->code = code;
    newTAC->res = res;
    newTAC->op1 = op1;
    newTAC->op2 = op2;

    return newTAC;
}

TAC* tacGenerate(AST* node){
    int i;
    TAC* generated[MAX_SONS]; 

    
    if(!node){
        return;
    }
    
    for(i=0; i<MAX_SONS; i++){
        generated[i] = tacGenerate(node->son[i]);
    }

    switch(node->type){
        case AST_LIT_CHAR:
        case AST_LIT_INTEGER:
        case AST_LIT_FLOAT:
            return tacCreate(TAC_SYMBOL_LIT, node->symbol, 0, 0);
        
        case AST_LIT_STRING:
            return tacCreate(TAC_SYMBOL_LIT_STRING, node->symbol, 0, 0);
            break;
        
        case AST_TK_IDENTIFIER:
            return tacCreate(TAC_SYMBOL, node->symbol, 0, 0);
            break;

        case AST_VECTOR:
            break;
        case AST_FUNCTION:
            break;
        case AST_OP_ADD:
            break;
        case AST_OP_SUB:
            break;
        case AST_OP_MUL:
            break;
        case AST_OP_DIV:
            break;
        case AST_OP_DIF:
            break;
        case AST_OP_EQ:
            break;
        case AST_OP_GE:
            break;
        case AST_OP_LE:
            break;
        case AST_OP_GT:
            break;
        case AST_OP_LT:
            break;
        case AST_OP_AND:
            break;
        case AST_OP_OR:
            break;
        case AST_OP_NOT:
            break;
        
        case AST_DATATYPE_INT:
            break;
        
        case AST_DATATYPE_FLOAT:
            break;

        case AST_DATATYPE_BYTE:
            break;
                
        case AST_VAR_DECLARATION:
            break;
        case AST_ATRIB:
            break;
        case AST_VEC_DECLARATION:
            break;
        case AST_VEC_DECLARATION_INI:
            break;
        case AST_FUNC_DECLARATION:
            break; 
        case AST_CMD_PRINT:
            break;
        case AST_BLOCK:
            break;
        case AST_CMDLIST:
            break;
        case AST_CMDRESTO:
            break;
        case AST_CMD_RETURN:
            break;
        case AST_CMD_IF:
            break;
        case AST_CMD_LOOP:
            break;
        case AST_CMD_IF_ELSE:
            break;
        case AST_VEC_POS_ATRIB:
            break;
        case AST_INILIST:
            break;
        case AST_ARGRESTO:
            break;
        case AST_ARGLIST:
            break;
        case AST_DECLIST:
            break;
        case AST_FUNC_PARAM:
            break;
        case AST_PARAMRESTO:
            break;
        case AST_FUNC_PARAMLIST:
            break;
        case AST_CMD_READ:
            break;
        case AST_CMD_LEAP:
            break;
        default:
            break;
	}

}

TAC* tacJoin(TAC* t1, TAC* t2){
    TAC* aux = t2;

    if(!t1) return t2;
    if(!t2) return t1;

    while(aux->prev){
        aux = aux->prev;
    }
    aux->prev = t1;
    return t2;
}