#include <stdio.h>
#include "semantic.h"

bool semanticError = false;
AST* rootNode = 0;

void setDeclaration(AST *node){
    if(node == 0) return;
    if(rootNode == 0)
                rootNode = node;
    int i;
    for(i=0; i<MAX_SONS; i++){
        setDeclaration(node->son[i]);
    }

    if(node->symbol == 0) return;

    switch(node->type){
        case AST_VAR_DECLARATION:
        case AST_FUNC_PARAM:
            if(node->symbol->dec == true){
                fprintf(stderr, "Semantic Error: '%s' redeclared on line %i\n", node->symbol->lit, node->lineNumber);
                semanticError = true;
                break;
            }
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
            if(node->symbol->dec == true){
                fprintf(stderr, "Semantic Error: '%s' redeclared on line %i\n", node->symbol->lit, node->lineNumber);
                semanticError = true;
                break;
            }
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
            if(node->symbol->dec == true){
                fprintf(stderr, "Semantic Error: '%s' redeclared on line %i\n", node->symbol->lit, node->lineNumber);
                semanticError = true;
                break;
            }
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
	if (node == 0 ){
        return;
    }
    
    int i;
	for ( i = 0; i < MAX_SONS; i++){
        checkOperands(node->son[i]);
    }

	switch(node->type){
        case AST_TK_IDENTIFIER:
            if(node->symbol == 0){
                fprintf(stderr, "[SEMANTIC ERROR] - Line %i: No symbol.\n", node->lineNumber);
                semanticError = 1;
                break;
            }
            if((node->symbol->type != TK_IDENTIFIER) || !isVariable(node->symbol->datatype)){
                fprintf(stderr, "[SEMANTIC ERROR] - Line %i: %s doesn't match it's type.\n", node->lineNumber, node->symbol->lit);
                semanticError = 1;
            }
            node->datatype = node->symbol->datatype;
            break;
        case AST_VECTOR:
            if(node->symbol == 0){
                fprintf(stderr, "[SEMANTIC ERROR] - Line %i: No symbol.\n", node->lineNumber);
                semanticError = 1;
                break;
            }
            if((node->symbol->type != TK_IDENTIFIER) || !isVector(node->symbol->datatype)){
                fprintf(stderr, "[SEMANTIC ERROR] - Line %i: %s doesn't match it's type.\n", node->lineNumber, node->symbol->lit);
                semanticError = 1;
            }
            if(!isInt(node->son[0]->datatype)){
                fprintf(stderr, "[SEMANTIC ERROR] - Line %i: index must be an integer.\n", node->son[0]->lineNumber);
                semanticError = 1;
            }
            node->datatype = node->symbol->datatype;
            break;
        case AST_FUNCTION:
            if(node->symbol == 0){
                fprintf(stderr, "[SEMANTIC ERROR] - Line %i: No symbol.\n", node->lineNumber);
                semanticError = 1;
                break;
            }
            if((node->symbol->type != TK_IDENTIFIER) || !isFunction(node->symbol->datatype)){
                fprintf(stderr, "[SEMANTIC ERROR] - Line %i: %s doesn't match it's type.\n", node->lineNumber, node->symbol->lit);
                semanticError = 1;
            }
            AST* aux = getFunction(rootNode, node->symbol->lit);
            if(!checkFunctionParameters(aux->son[1], node->son[0])){
                fprintf(stderr, "[SEMANTIC ERROR] - Line %i: function parameters wrong.\n", node->lineNumber);
                semanticError = 1;
            }
            node->datatype = node->symbol->datatype;
            break;
        case AST_OP_ADD:
        case AST_OP_SUB:
        case AST_OP_MUL:
        case AST_OP_DIV:
            node->datatype = getDatatype(node->son[0]->datatype, node->son[1]->datatype);
            if(node->datatype == NO_DATATYPE){
                fprintf(stderr, "[SEMANTIC ERROR] - Line %i: operands not compatible.\n", node->lineNumber);
                semanticError = 1;
            }
            break;
        case AST_OP_DIF:
        case AST_OP_EQ:
        case AST_OP_GE:
        case AST_OP_LE:
        case AST_OP_GT:
        case AST_OP_LT:
            if(isBool(node->son[0]->datatype)&&isBool(node->son[1]->datatype)){
                node->datatype = DATATYPE_BOOL;
                break;
            }
            else if(getDatatype(node->son[0]->datatype, node->son[1]->datatype) == NO_DATATYPE){
                fprintf(stderr, "[SEMANTIC ERROR] - Line %i: operands not compatible.\n", node->lineNumber);
                semanticError = 1;
            }
            node->datatype = DATATYPE_BOOL;
            break;
        case AST_OP_AND:
        case AST_OP_OR:
            if(!isSameDatatype(node->son[0]->datatype, node->son[1]->datatype)){
                fprintf(stderr, "[SEMANTIC ERROR] - Line %i: must be compatible.\n", node->lineNumber);
                semanticError = 1;
            }
            node->datatype = DATATYPE_BOOL;
            break;
        case AST_OP_NOT:
            if(node->son[0]->datatype == NO_DATATYPE){
                fprintf(stderr, "[SEMANTIC ERROR] - Line %i: must be compatible.\n", node->lineNumber);
                semanticError = 1;
            }
            node->datatype = DATATYPE_BOOL;
            break;
        case AST_LIT_INTEGER:
        case AST_DATATYPE_INT:
            node->datatype = DATATYPE_INT;
            break;
        case AST_LIT_FLOAT:
        case AST_DATATYPE_FLOAT:
            node->datatype = DATATYPE_FLOAT;
            break;
        case AST_LIT_CHAR:
        case AST_DATATYPE_BYTE:
            node->datatype = DATATYPE_BYTE;
            break;
        case AST_LIT_STRING:
            node->datatype = DATATYPE_STRING;
            break;        
        case AST_VAR_DECLARATION:
        case AST_ATRIB:
            if(node->symbol == 0){
                fprintf(stderr, "[SEMANTIC ERROR] - Line %i: No symbol.\n", node->lineNumber);
                semanticError = 1;
                break;
            }
            if(!isVariable(node->symbol->datatype)){
                fprintf(stderr, "[SEMANTIC ERROR] - Line %i: %s doesn't match it's type.\n", node->lineNumber, node->symbol->lit);
                semanticError = 1;
            }
            if(!isCompatible(node->symbol->datatype, node->son[0]->datatype)){
                fprintf(stderr, "[SEMANTIC ERROR] - Line %i: must be compatible.\n", node->lineNumber);
                semanticError = 1;
            }
            node->datatype = node->symbol->datatype;
            break;
        case AST_VEC_DECLARATION:
            if(!isInt(node->son[1]->datatype)){
                fprintf(stderr, "[SEMANTIC ERROR] - Line %i: index must be an integer.\n", node->son[1]->lineNumber);
                semanticError = 1;
            }
            if(node->symbol == 0){
                fprintf(stderr, "[SEMANTIC ERROR] - Line %i: No symbol.\n", node->lineNumber);
                semanticError = 1;
                break;
            }
            if(!isVector(node->symbol->datatype)){
                fprintf(stderr, "[SEMANTIC ERROR] - Line %i: %s doesn't match it's type.\n", node->lineNumber, node->symbol->lit);
                semanticError = 1;
            }
            node->datatype = node->symbol->datatype;
            break;
        case AST_VEC_DECLARATION_INI:
            if(!isInt(node->son[1]->datatype)){
                fprintf(stderr, "[SEMANTIC ERROR] - Line %i: index must be an integer.\n", node->son[1]->lineNumber);
                semanticError = 1;
            }
            if(node->symbol == 0){
                fprintf(stderr, "[SEMANTIC ERROR] - Line %i: No symbol.\n", node->lineNumber);
                semanticError = 1;
                break;
            }
            if(!isCompatible(node->symbol->datatype, node->son[2]->datatype)){
                fprintf(stderr, "[SEMANTIC ERROR] - Line %i: the elements of a vector must be compatible.\n", node->son[1]->lineNumber);
                semanticError = 1;
            }
            if(!isVector(node->symbol->datatype)){
                fprintf(stderr, "[SEMANTIC ERROR] - Line %i: %s doesn't match it's type.\n", node->lineNumber, node->symbol->lit);
                semanticError = 1;
            }
            node->datatype = node->symbol->datatype;
            break;
        case AST_FUNC_DECLARATION:
            if(node->symbol == 0){
                fprintf(stderr, "[SEMANTIC ERROR] - Line %i: No symbol.\n", node->lineNumber);
                semanticError = 1;
                break;
            }
            if(!isCompatible(node->symbol->datatype, node->son[2]->datatype)){
                fprintf(stderr, "[SEMANTIC ERROR] - Line %i: no function return / wrong type.\n", node->lineNumber);
                semanticError = 1;
            }
            node->datatype = node->symbol->datatype;
            break; 
        case AST_CMD_PRINT:
            if(node->son[0]->datatype == NO_DATATYPE){
                fprintf(stderr, "[SEMANTIC ERROR] - Line %i: can't print this.\n", node->lineNumber);
                semanticError = 1;
            }
            break;
        case AST_BLOCK:
            node->datatype = node->son[0]->datatype;
            break;
        case AST_CMDLIST:
        case AST_CMDRESTO:
            if((node->son[0]==0)&&(node->son[1]==0)){
                node->datatype = NO_DATATYPE;
            }
            else if(node->son[0]==0){
                node->datatype = node->son[1]->datatype;
            }
            else if(node->son[1]==0){
                node->datatype = node->son[0]->datatype;
            }
            else{
                if(node->son[0]->datatype==NO_DATATYPE && node->son[1]->datatype==NO_DATATYPE)
                    node->datatype = NO_DATATYPE;
                else if(node->son[0]->datatype==NO_DATATYPE)
                    node->datatype = node->son[1]->datatype;
                else if(node->son[1]->datatype==NO_DATATYPE)
                    node->datatype = node->son[0]->datatype;
                else
                    node->datatype = getDatatype(node->son[0]->datatype, node->son[1]->datatype);
            }
            break;
        case AST_CMD_RETURN:
            node->datatype = node->son[0]->datatype;
            break;
        case AST_CMD_IF:
        case AST_CMD_IF_ELSE:
        case AST_CMD_LOOP:
            if(!isBool(node->son[0]->datatype)){
                fprintf(stderr, "[SEMANTIC ERROR] - Line %i: expression must be boolean.\n", node->lineNumber);
                semanticError = 1;
            }
            break;
        case AST_VEC_POS_ATRIB:
            if(node->symbol == 0){
                fprintf(stderr, "[SEMANTIC ERROR] - Line %i: No symbol.\n", node->lineNumber);
                semanticError = 1;
                break;
            }
            if((node->symbol->type != TK_IDENTIFIER) || !isVector(node->symbol->datatype)){
                fprintf(stderr, "[SEMANTIC ERROR] - Line %i: %s doesn't match it's type.\n", node->lineNumber, node->symbol->lit);
                semanticError = 1;
            }
            if(node->son[1] == 0 ){
                fprintf(stderr, "[SEMANTIC ERROR] - Line %i: %s doesn't match it's type.\n", node->lineNumber, node->symbol->lit);
                semanticError = 1;
            }
            if(!isCompatible(node->symbol->datatype, node->son[1]->datatype)){
                fprintf(stderr, "[SEMANTIC ERROR] - Line %i: must be compatible.\n", node->lineNumber);
                semanticError = 1;
            }
            if(!isInt(node->son[0]->datatype)){
                fprintf(stderr, "[SEMANTIC ERROR] - Line %i: index must be an integer.\n", node->son[1]->lineNumber);
                semanticError = 1;
            }
            node->datatype = node->symbol->datatype;
            break;
        case AST_INILIST:
            if(node->son[0] == 0){
                node->datatype = NO_DATATYPE;
            }
            else if(node->son[1] == 0){
                node->datatype = node->son[0]->datatype;
            }
            else{
                node->datatype = getDatatype(node->son[0]->datatype, node->son[1]->datatype);
            }
            break;
        case AST_ARGRESTO:
        case AST_ARGLIST:
            if(node->son[0] == 0){
                node->datatype = NO_DATATYPE;
            }
            else if(node->son[1] == 0){
                node->datatype = node->son[0]->datatype;
            }
            else{
                if(node->son[0]==NO_DATATYPE || node->son[1]==NO_DATATYPE)
                    node->datatype = NO_DATATYPE;
                else
                    node->datatype = DATATYPE_STRING;
            }
            break;
        case AST_DECLIST:
        case AST_FUNC_PARAM:
        case AST_PARAMRESTO:
        case AST_FUNC_PARAMLIST:
        case AST_CMD_READ:
        case AST_CMD_LEAP:       
        default:
            break;
	}
}

bool isInt(int datatype){
    switch (datatype){
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
    switch (datatype){
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

bool isCompatible(int var, int atrib){
    if(isFloat(var)){
        if(isFloat(atrib)||isInt(atrib))
            return true;
        else
            return false;
    }
    else if (isInt(var)){
        if(isInt(atrib))
            return true;
        else
            return false;
    }
    else if(isBool(var)){
        if(isBool(atrib))
            return true;
        else 
            return false;
    }
    return false;
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

int getDatatype(int datatype1, int datatype2){
    if((!isInt(datatype1)&&!isFloat(datatype1))||(!isInt(datatype2)&&!isFloat(datatype2))){
        return NO_DATATYPE;
    }
    else if(isFloat(datatype1)||isFloat(datatype2)){
        return DATATYPE_FLOAT;
    }
    return DATATYPE_INT;
}

AST* getFunction(AST* rnode, char* lit){
    if(rnode == 0 || rnode->son[0]==0)
        return 0;
    if( strcmp(rnode->son[0]->symbol->lit, lit) == 0 ){
        return rnode->son[0];
    }
    return getFunction(rnode->son[1], lit);
}

bool checkFunctionParameters(AST* fun, AST* node){
    if(fun == 0){
        if(node == 0)
            return true;
        else
            return false;
    }
    else if(node == 0){
        return false;
    }
    if(!isCompatible(fun->son[0]->datatype, node->son[0]->datatype)){
        return false;
    }
    else{
        return checkFunctionParameters(fun->son[1], node->son[1]);
    }
    
}