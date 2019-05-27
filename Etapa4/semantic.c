#include <stdio.h>
#include "semantic.h"

bool semanticError = false;

void setDeclaration(AST *node){
    if(node == 0) return;

    int i;
    for(i=0; i<MAX_SONS; i++){
        setDeclaration(node->son[i]);
    }

    if(node->symbol == 0) return;
    if(node->symbol->dec == true){
        fprintf(stderr, "Semantic Error: '%s' redeclared on line %i\n", node->symbol->lit, node->lineNumber);
        semanticError = true;
    }

    switch(node->type){
        case AST_VAR_DECLARATION:
        case AST_FUNC_PARAM:
            if(node->son[0]->type == AST_DATATYPE_BYTE)
                node->symbol->datatype = DATATYPE_BYTE;
            else if(node->son[0]->type == AST_DATATYPE_INT)
                node->symbol->datatype = DATATYPE_INT;
            else if(node->son[0]->type == AST_DATATYPE_FLOAT)
                node->symbol->datatype = DATATYPE_FLOAT;

            node->symbol->dec = true;
            node->datatype = node->symbol->datatype;
            break;
        case AST_VEC_DECLARATION:
        case AST_VEC_DECLARATION_INI:
            if(node->son[0]->type == AST_DATATYPE_BYTE)
                node->symbol->datatype = DATATYPE_BYTE_VEC;
            else if(node->son[0]->type == AST_DATATYPE_INT)
                node->symbol->datatype = DATATYPE_INT_VEC;
            else if(node->son[0]->type == AST_DATATYPE_FLOAT)
                node->symbol->datatype = DATATYPE_FLOAT_VEC;

            node->symbol->dec = true;
            node->datatype = node->symbol->datatype;
            break;
        case AST_FUNC_DECLARATION:
            if(node->son[0]->type == AST_DATATYPE_BYTE)
                node->symbol->datatype = DATATYPE_BYTE_FUN;
            else if(node->son[0]->type == AST_DATATYPE_INT)
                node->symbol->datatype = DATATYPE_INT_FUN;
            else if(node->son[0]->type == AST_DATATYPE_FLOAT)
                node->symbol->datatype = DATATYPE_FLOAT_FUN;

            node->symbol->dec = true;
            node->datatype = node->symbol->datatype;
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
        case AST_TK_IDENTIFIER:
            if((node->symbol->type != TK_IDENTIFIER) || !isVariable(node->symbol->datatype)){
                fprintf(stderr, "[SEMANTIC ERROR] - Line %i: %s doesn't match it's type.\n", node->lineNumber, node->symbol->lit);
                semanticError = 1;
            }
            node->datatype = node->symbol->datatype;
            break;
        case AST_VECTOR:
            if((node->symbol->type != TK_IDENTIFIER) || !isVector(node->symbol->datatype)){
                fprintf(stderr, "[SEMANTIC ERROR] - Line %i: %s doesn't match it's type.\n", node->lineNumber, node->symbol->lit);
                semanticError = 1;
            }
            if(!isInt(node->son[0]->datatype)){
                fprintf(stderr, "[SEMANTIC ERROR] - Line %i: %s index must be an integer.\n", node->son[0]->lineNumber, node->son[0]->symbol->lit);
                semanticError = 1;
            }
            node->datatype = node->symbol->datatype;
            break;
        case AST_FUNCTION:
            if((node->symbol->type != TK_IDENTIFIER) || !isFunction(node->symbol->datatype)){
                fprintf(stderr, "[SEMANTIC ERROR] - Line %i: %s doesn't match it's type.\n", node->lineNumber, node->symbol->lit);
                semanticError = 1;
            }
            node->datatype = node->symbol->datatype;
            break;
        case AST_OP_ADD:
        case AST_OP_SUB:
        case AST_OP_MUL:
        case AST_OP_DIV:
            if(!isSameDatatype(node->son[0]->datatype, node->son[1]->datatype)){
                fprintf(stderr, "[SEMANTIC ERROR] - Line %i: %s and %s must have the same datatype.\n", node->lineNumber, node->son[0]->symbol->lit, node->son[1]->symbol->lit);
                semanticError = 1;
            }
            else if(isBool(node->son[0]->datatype)){
                fprintf(stderr, "[SEMANTIC ERROR] - Line %i: can't use boolean.\n", node->lineNumber);
                semanticError = 1;
            }
            node->datatype = basicDatatype(node->son[0]->datatype);
            break;
        case AST_OP_DIF:
        case AST_OP_EQ:
        case AST_OP_GE:
        case AST_OP_LE:
        case AST_OP_GT:
        case AST_OP_LT:
        case AST_OP_AND:
        case AST_OP_OR:
            if(!isSameDatatype(node->son[0]->datatype, node->son[1]->datatype)){
                fprintf(stderr, "[SEMANTIC ERROR] - Line %i: %s and %s must have the same datatype.\n", node->lineNumber, node->son[0]->symbol->lit, node->son[1]->symbol->lit);
                semanticError = 1;
            }
            node->datatype = DATATYPE_BOOL;
            break;
        case AST_OP_NOT:
            if(node->son[0]->datatype == NO_DATATYPE){
                fprintf(stderr, "[SEMANTIC ERROR] - Line %i: %s has no datatype.\n", node->lineNumber, node->son[0]->symbol->lit);
                semanticError = 1;
            }
            node->datatype = DATATYPE_BOOL;
            break;





        case AST_LIT_INTEGER:
        case AST_LIT_FLOAT:
        case AST_LIT_CHAR:
        case AST_LIT_STRING:
        
        
        
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

bool isInt(int datatype){
    switch (type){
        case DATATYPE_BYTE:
        case DATATYPE_BYTE_VEC:
        case DATATYPE_BYTE_FUN:
        case DATATYPE_INT:
        case DATATYPE_INT_VEC: 
        case DATATYPE_INT_FUN:
            return true;
            break;
        
        default:
            return false;
            break;
    }
}

bool isFloat(int datatype){
    switch (type){
        case DATATYPE_FLOAT:
        case DATATYPE_FLOAT_VEC:
        case DATATYPE_FLOAT_FUN:
            return true;
            break;
        
        default:
            return false;
            break;
    }
}

bool isBool(int datatype){
    if(datatype == DATATYPE_BOOL)
        return true;
    else
        return false;
    
}

bool isVariable(int datatype){
    switch(datatype){
        case DATATYPE_BYTE:
        case DATATYPE_INT:
        case DATATYPE_FLOAT:
            return true;
            break;
        default:
            return false;
            break;
    }
}

bool isVector(int datatype){
    switch(datatype){
        case DATATYPE_BYTE_VEC:
        case DATATYPE_INT_VEC:
        case DATATYPE_FLOAT_VEC:
            return true;
            break;
        default:
            return false;
            break;
    }
}

bool isFunction(int datatype){
    switch(datatype){
        case DATATYPE_BYTE_FUN:
        case DATATYPE_INT_FUN:
        case DATATYPE_FLOAT_FUN:
            return true;
            break;
        default:
            return false;
            break;
    }
}

bool isSameDatatype(int datatype1, int datatype2){
    if(
        (isInt(datatype1)&&isInt(datatype2))||
        (isFloat(datatype1)&&isFloat(datatype2))||
        (isBool(datatype1)&&isBool(datatype2))){
            return true;
        }
    else{
        return false;
    }
    
}

int basicDatatype(int datatype){
    if(isInt(datatype))
        return DATATYPE_INT;
    if(isFloat(datatype))
        return DATATYPE_FLOAT;
    if(isBool(datatype))
        return DATATYPE_BOOL;
    return NO_DATATYPE;
}