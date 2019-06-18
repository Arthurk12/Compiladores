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
        case AST_VAR_DECLARATION:
            return tacJoin(tacCreate(TAC_SYMBOL, node->symbol, 0, 0), generated[1]);
            break;
        case AST_VEC_DECLARATION:
            return tacJoin(tacCreate(TAC_VEC_DECLARATION, node->symbol, 0, 0), generated[1]);
        case AST_VEC_DECLARATION_INI:
            return tacJoin(tacJoin(tacJoin(tacCreate(TAC_VEC_DECLARATION_INI, node->symbol, 0, 0), generated[1]), generated[2]), tacCreate(TAC_VEC_DECLARATION_END, 0, 0, 0));
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
        case AST_ATRIB:
            return tacJoin(tacCreate(TAC_ATRIB, node->symbol, generated[0]?generated[0]->res:0, 0), generated[0]);
            break;
        case AST_VEC_POS_ATRIB:
            return tacJoin(tacCreate(TAC_ATRIB_VEC_POS, node->symbol, generated[0]?generated[0]->res:0, generated[1]?generated[1]->res:0), tacJoin(generated[0], generated[1]));
            break;
        case AST_FUNC_DECLARATION:
            return makeFunc(node, generated[1], generated[2]);
            break; 
        case AST_INILIST:
            return tacJoin(generated[0], generated[1]);
            break;
        case AST_ARGRESTO:
            return tacJoin(generated[0], generated[1]);
            break;
        case AST_ARGLIST:
            return tacJoin(generated[0], generated[1]);
            break;
        case AST_PARAMRESTO:
            return tacJoin(generated[0], generated[1]);
            break;

        case AST_FUNCTION:
            return makeFuncCall(node, generated[0]);
            break;
        case AST_DATATYPE_INT:
        case AST_DATATYPE_FLOAT:
        case AST_DATATYPE_BYTE:
        default:
            return NULL;
            break;
	}

    return NULL;
}

void tacPrintSingle(TAC *tac){
  if(!tac)
  {
    return;
  }
  switch (tac->code)
  {
    case TAC_SYMBOL:
		fprintf(stderr, "\nTAC_SYMBOL ");
        break;
    case TAC_SYMBOL_LIT:
        fprintf(stderr, "\nTAC_SYMBOL_LIT ");
	    break;
    case TAC_SYMBOL_LIT_STRING:
        fprintf(stderr, "\nTAC_SYMBOL_LIT_STRING ");
	    break;
    case TAC_ADD: 
        fprintf(stderr, "\nTAC_ADD ");
        break;
    case TAC_SUB:
        fprintf(stderr, "\nTAC_SUB ");
        break;
    case TAC_MUL:
        fprintf(stderr, "\nTAC_MUL ");
        break;
    case TAC_DIV:
        fprintf(stderr, "\nTAC_DIV ");
        break;
    case TAC_LT:
        fprintf(stderr, "\nTAC_LESS ");
        break;
    case TAC_GT:
        fprintf(stderr, "\nTAC_GREATER ");
        break;
    case TAC_AND:
        fprintf(stderr, "\nTAC_AND ");
        break;
    case TAC_OR:    
        fprintf(stderr, "\nTAC_OR ");
        break;
    case TAC_NOT:
        fprintf(stderr, "\nTAC_NOT ");
        break;
    case TAC_LE:
        fprintf(stderr, "\nTAC_LE ");
        break;
    case TAC_GE:
        fprintf(stderr, "\nTAC_GE ");
        break;
    case TAC_EQ:
        fprintf(stderr, "\nTAC_EQ ");
        break;
    case TAC_VECTOR:
        fprintf(stderr, "\nTAC_VECTOR ");
        break;
    case TAC_SYMBOL_VEC :
		return;
    case TAC_IF_THEN:
        fprintf(stderr, "\nTAC_IFZ ");
        break;
    case TAC_IF_ELSE:
        fprintf(stderr, "\nTAC_IFZ_ELSE ");
        break;
    case TAC_LEAP:
        fprintf(stderr, "\nTAC_LEAP ");
        break;
	  case TAC_LOOP:
        fprintf(stderr, "\nTAC_LOOP ");
        break;
    case TAC_READ :
        fprintf(stderr, "\nTAC_READ ");
        break;
    case TAC_PRINT :
        fprintf(stderr, "\nTAC_PRINT ");
        break;
    case TAC_FUNC_BEGIN:
        fprintf(stderr, "\nTAC_FUNC_BEGIN ");
        break;
    case TAC_FUNC_END:
        fprintf(stderr, "\nTAC_FUNC_END ");
        break;
    case TAC_LABEL :
        fprintf(stderr, "\nTAC_LABEL ");
        break;
    case TAC_JUMP:
        fprintf(stderr, "\nTAC_JUMP " );
        break;
    case TAC_FUNC_CALL_BEGIN:
        fprintf(stderr, "\nTAC_FUNC_CALL_BEGIN ");
        break;
    case TAC_FUNC_CALL_END:
        fprintf(stderr, "\nTAC_FUNC_CALL_END ");
        break;
    case TAC_ATRIB:
        fprintf(stderr, "\nTAC_ATRIB ");
        break;
    case TAC_ATRIB_VEC_POS:
        fprintf(stderr, "\nTAC_ATRIB_VEC_POS ");
        break;
    case TAC_RETURN:
        fprintf(stderr, "\nTAC_RETURN ");
        break;
    case TAC_VEC_DECLARATION:
        fprintf(stderr, "\nTAC_VEC_DECLARATION ");
        break;
    case TAC_VEC_DECLARATION_INI:
        fprintf(stderr, "\nTAC_VEC_DECLARATION_INI ");
        break;
    case TAC_VEC_DECLARATION_END:
        fprintf(stderr, "\nTAC_VEC_DECLARATION_END ");
        break;
    default:
        fprintf(stderr, "\nTAC_UNKNOWN (%d) ", tac->code);
        break;
  }
  if (tac->res)
  {
    fprintf(stderr, "%s ", tac->res->lit);
  }
  if (tac->op1)
  {
    fprintf(stderr, "%s ", tac->op1->lit);
  }
  if (tac->op2)
  {
    fprintf(stderr, "%s ", tac->op2->lit);
  }
}

void tacPrintForward(TAC *tac){
  if (!tac)
  {
    return;
  }
  tacPrintSingle(tac);
  tacPrintForward(tac->next);
}

TAC* makeOP(int code, TAC* res1, TAC* res2){
    TAC* opTAC = tacCreate(code, makeTemp(), res1?res1->res:0, res2?res2->res:0);
    return tacJoin(opTAC, tacJoin(res1, res2));
}
//opTAC->res1->res2;

TAC* makeIfThen(TAC* expr, TAC* cIf){
    hashNode* newLabelCont = makeLabel();

    TAC* ifThen = tacCreate(TAC_IF_THEN, expr?expr->res:0, newLabelCont, 0);
    TAC* labelCont = tacCreate(TAC_LABEL, newLabelCont, 0, 0);
    return tacJoin(expr, tacJoin(ifThen, tacJoin(cIf, labelCont)));
}
//expr->ifThen->cIf->labelCont;

TAC* makeIfThenElse(TAC* expr, TAC* cIf, TAC* cElse){
    hashNode* newLabelElse = makeLabel();
    hashNode* newLabelCont = makeLabel();

    TAC* ifThenElse = tacCreate(TAC_IF_ELSE, expr?expr->res:0, newLabelElse, 0);
    TAC* labelElse = tacCreate(TAC_LABEL, newLabelElse, 0, 0);
    TAC* labelCont = tacCreate(TAC_LABEL, newLabelCont, 0, 0);
    TAC* jump = tacCreate(TAC_JUMP, newLabelCont, 0, 0);
    return tacJoin(expr, tacJoin(ifThenElse, tacJoin(cIf, tacJoin(jump, tacJoin(labelElse, tacJoin(cElse, labelCont))))));
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
    return tacJoin(labelLoop, tacJoin(expr, tacJoin(loop, tacJoin(cLoop, tacJoin(jump, labelCont)))));
}
//labelLoop->expr->loop->cLoop->jump->labelCont;

TAC* makeFunc(AST* node, TAC* param, TAC* cFunc){
    hashNode* labelFuncBegin = makeLabel();
    hashNode* labelFuncEnd = makeLabel();

    TAC* funcBeg = tacCreate(TAC_FUNC_BEGIN, node->symbol, labelFuncBegin, 0);
    TAC* funcEnd = tacCreate(TAC_FUNC_END, node->symbol, labelFuncEnd, 0);
    return tacJoin(tacJoin(tacJoin(funcBeg, param), cFunc), funcEnd);
}
//func->param->labelFuncBegin->cFunc->return

TAC* makeFuncCall(AST* node, TAC* listParam){
    hashNode* labelFuncCallBegin = makeLabel();
    hashNode* labelFuncCallEnd = makeLabel();

    TAC* funcCallBeg = tacCreate(TAC_FUNC_CALL_BEGIN, node->symbol, labelFuncCallBegin, 0);
    TAC* funcCallEnd = tacCreate(TAC_FUNC_CALL_END, node->symbol, labelFuncCallEnd, 0);
    return tacJoin(tacJoin(funcCallBeg, listParam), funcCallEnd);
}