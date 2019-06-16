#include "tac.h"

TAC* tacCreate(int code, hashNode* res, hashNode* op1, hashNode* op2){
    TAC *newTAC;
    newTAC = (TAC* )calloc(1, sizeof(TAC));
    newTAC->code = code;
    newTAC->res = res;
    newTAC->op1 = op1;
    newTAC->op2 = op2;
    newTAC->next = NULL;
    return newTAC;
}

TAC* tacJoin(TAC* t1, TAC* t2){
    if(!t1) return t2;
    if(!t2) return t1;

    TAC* aux = t1;

    while(aux->next){
        aux = aux->next;
    }
    aux->next = t2;
    return t1;
}

TAC* tacGenerate(AST* node, hashNode* jumpLoopIteration){
    if(!node){
        return 0;
    }

    int i;
    TAC* generated[MAX_SONS];

    if(node->type == AST_CMD_LOOP){
        jumpLoopIteration = makeLabel();
    }
    
    for(i=0; i<MAX_SONS; i++){
        generated[i] = tacGenerate(node->son[i], jumpLoopIteration);
    }

    switch(node->type){
        case AST_LIT_CHAR:
        case AST_LIT_INTEGER:
        case AST_LIT_FLOAT:
            return tacCreate(TAC_SYMBOL_LIT, node->symbol, 0, 0);
            break;
        case AST_LIT_STRING:
            return tacCreate(TAC_SYMBOL_LIT_STRING, node->symbol, 0, 0);
            break;
        case AST_TK_IDENTIFIER:
            return tacCreate(TAC_SYMBOL, node->symbol, 0, 0);
            break;
        case AST_VECTOR:
            return tacJoin(tacCreate(TAC_VECTOR, node->symbol, generated[0]?generated[0]->res:0, 0), generated[0]);
            break;
        case AST_OP_ADD:
            return makeOP(TAC_ADD, generated[0], generated[1]);
            break;
        case AST_OP_SUB:
            return makeOP(TAC_SUB, generated[0], generated[1]);
            break;
        case AST_OP_MUL:
            return makeOP(TAC_MUL, generated[0], generated[1]);
            break;
        case AST_OP_DIV:
            return makeOP(TAC_DIV, generated[0], generated[1]);
            break;
        case AST_OP_DIF:
            return makeOP(TAC_DIF, generated[0], generated[1]);
            break;
        case AST_OP_EQ:
            return makeOP(TAC_EQ, generated[0], generated[1]);
            break;
        case AST_OP_GE:
            return makeOP(TAC_GE, generated[0], generated[1]);
            break;
        case AST_OP_LE:
            return makeOP(TAC_LE, generated[0], generated[1]);
            break;
        case AST_OP_GT:
            return makeOP(TAC_GT, generated[0], generated[1]);
            break;
        case AST_OP_LT:
            return makeOP(TAC_LT, generated[0], generated[1]);
            break;
        case AST_OP_AND:
            return makeOP(TAC_AND, generated[0], generated[1]);
            break;
        case AST_OP_OR:
            return makeOP(TAC_OR, generated[0], generated[1]);
            break;
        case AST_OP_NOT:
            return makeOP(TAC_NOT, generated[0], generated[1]);
            break;
        case AST_DATATYPE_INT:
        case AST_DATATYPE_FLOAT:
        case AST_DATATYPE_BYTE:
            // NOP
            break;  
        case AST_VAR_DECLARATION:
            return tacJoin(tacCreate(TAC_SYMBOL, node->symbol, 0, 0), generated[1]);
            break;
        case AST_VEC_DECLARATION:
        case AST_VEC_DECLARATION_INI:
            return tacCreate(TAC_SYMBOL_VEC, node->symbol, generated[1]?generated[1]->res : 0 , 0);
            break;
        case AST_CMD_PRINT:
            return tacJoin(tacCreate(TAC_PRINT,0, 0, 0), generated[0]);
            break;
        case AST_BLOCK:
            return generated[0];
            break;
        case AST_CMDLIST:
        case AST_DECLIST:
        case AST_FUNC_PARAMLIST:
        case AST_FUNC_PARAM:
        case AST_CMDRESTO:
            return tacJoin(generated[0], generated[1]);
            break;
        case AST_CMD_RETURN:
            return tacJoin(tacCreate(TAC_RETURN, generated[0]?generated[0]->res:0, 0, 0), generated[0]);
            break;
        case AST_CMD_READ:
            return tacCreate(TAC_READ, node->symbol, 0, 0);
            break;
        case AST_CMD_IF:
            return makeIfThen(generated[0], generated[1]);
            break;
        case AST_CMD_IF_ELSE:
            return makeIfThenElse(generated[0], generated[1], generated[2]);
            break;
        case AST_CMD_LOOP:
            return makeLoop(generated[0], generated[1], jumpLoopIteration);
            break;
        case AST_CMD_LEAP:
            return makeLeap(jumpLoopIteration);
            break;
        case AST_FUNCTION:
            
            break;


        case AST_ATRIB:
            break;
        case AST_FUNC_DECLARATION:
            break; 



        case AST_VEC_POS_ATRIB:
            break;
        case AST_INILIST:
            break;
        case AST_ARGRESTO:
            break;
        case AST_ARGLIST:
            break;
        case AST_PARAMRESTO:
            break;
        default:
            break;
	}

}

TAC* makeOP(int code, TAC* res1, TAC* res2){
    TAC* opTAC = tacCreate(code, makeTemp(), res1?res1->res:0, res2?res2->res:0);
    return tacJoin(tacJoin(res2, res1),opTAC);
}

TAC* makeIfThen(TAC* expr, TAC* cIf){
    hashNode* newLabelCont = makeLabel();

    TAC* ifThen = tacCreate(TAC_IF_THEN, expr?expr->res:0, newLabelCont, 0);
    TAC* labelCont = tacCreate(TAC_LABEL, newLabelCont, 0, 0);
    return tacJoin(tacJoin(tacJoin(expr, ifThen),cIf), labelCont);
}
//expr->ifThen->cIf->labelCont;

TAC* makeIfThenElse(TAC* expr, TAC* cIf, TAC* cElse){
    hashNode* newLabelElse = makeLabel();
    hashNode* newLabelCont = makeLabel();

    TAC* ifThenElse = tacCreate(TAC_IF_ELSE, expr?expr->res:0, newLabelElse, 0);
    TAC* labelElse = tacCreate(TAC_LABEL, newLabelElse, 0, 0);
    TAC* labelCont = tacCreate(TAC_LABEL, newLabelCont, 0, 0);
    TAC* jump = tacCreate(TAC_JUMP, newLabelCont, 0, 0);
    return tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(expr, ifThenElse),cIf),jump),labelElse),cElse),labelCont);
}
//expr->ifThenElse->cIf->jump->labelElse->cElse->labelCont;
//                        |                       ^
//                        -------------------------

TAC* makeLeap(hashNode* jumpLoop){
    TAC* leap = tacCreate(TAC_LEAP, jumpLoop, 0, 0);
    TAC* jump = tacCreate(TAC_JUMP, jumpLoop, 0, 0);
    return tacJoin(leap, jump);
}
//leap->jump

TAC* makeLoop(TAC* expr, TAC* cLoop, hashNode* jumpLoop){
    hashNode* newLabelCont = makeLabel();
    hashNode* newLabelLoop = jumpLoop;

    TAC* labelCont = tacCreate(TAC_LABEL, newLabelCont, 0, 0);
    TAC* labelLoop = tacCreate(TAC_LABEL, newLabelLoop, 0, 0);
    TAC* loop = tacCreate(TAC_LOOP, expr?expr->res:0, newLabelCont, newLabelLoop);
    TAC* jump = tacCreate(TAC_JUMP, newLabelLoop, 0, 0);
    return tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(labelLoop, expr), loop), cLoop), jump), labelCont);
}
//labelLoop->expr->loop->cLoop->jmp->labelCont;