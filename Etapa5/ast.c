#include <stdio.h>
#include <string.h>
#include <time.h>

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
    new_node->lineNumber = getLineNumber();
    new_node->datatype = NO_DATATYPE;
    return new_node;
}

void astPrint(AST *node, int level){
    fprintf(stderr, "\n========================================AST PRINT========================================\n");
    astPrintRec(node, level);
    fprintf(stderr, "=========================================================================================\n");
}

void astPrintRec(AST *node, int level){

    int i;
    if(node == 0)return;

    for(i=0; i<=level; i++){
        fprintf(stderr, "  ");
    }

    fprintf(stderr, "AST(");
    switch(node->type){
        case AST_OP_ADD:    fprintf(stderr, "AST_ADD, %d) \n", node->lineNumber);
                        break;
        case AST_OP_SUB:    fprintf(stderr, "AST_SUB, %d) \n", node->lineNumber);
                        break;
        case AST_OP_MUL:    fprintf(stderr, "AST_MUL, %d) \n", node->lineNumber);
                        break;
        case AST_OP_DIV:    fprintf(stderr, "AST_DIV, %d) \n", node->lineNumber);
                        break;
        case AST_OP_AND:    fprintf(stderr, "AST_AND, %d) \n", node->lineNumber);
                        break;
        case AST_OP_OR:     fprintf(stderr, "AST_OR, %d) \n", node->lineNumber);
                        break;
        case AST_OP_DIF:    fprintf(stderr, "AST_DIF, %d) \n", node->lineNumber);
                        break;
        case AST_OP_EQ:     fprintf(stderr, "AST_EQ, %d) \n", node->lineNumber);
                        break;
        case AST_OP_GE:     fprintf(stderr, "AST_GE, %d) \n", node->lineNumber);
                        break;
        case AST_OP_LE:     fprintf(stderr, "AST_LE, %d) \n", node->lineNumber);
                        break;
        case AST_OP_GT:     fprintf(stderr, "AST_GT, %d) \n", node->lineNumber);
                        break;
        case AST_OP_LT:     fprintf(stderr, "AST_LT, %d) \n", node->lineNumber);
                        break;
        case AST_OP_NOT:    fprintf(stderr, "AST_NOT, %d) \n", node->lineNumber);
                        break;
        case AST_LIT_INTEGER:   fprintf(stderr, "AST_INTEGER, %d) \n", node->lineNumber);
                        break;
        case AST_LIT_FLOAT:     fprintf(stderr, "AST_FLOAT, %d) \n", node->lineNumber);
                        break;
        case AST_LIT_CHAR:      fprintf(stderr, "AST_CHAR, %d) \n", node->lineNumber);
                        break;
        case AST_LIT_STRING:    fprintf(stderr, "AST_STRING, %d) \n", node->lineNumber);
                        break;
        case AST_TK_IDENTIFIER: fprintf(stderr, "AST_IDENTIFIER, %d) \n", node->lineNumber);
                        break;
        case AST_VECTOR:        fprintf(stderr, "AST_VECTOR, %d) \n", node->lineNumber);
                        break;
        case AST_FUNCTION:      fprintf(stderr, "AST_FUNCTION, %d) \n", node->lineNumber);
                        break;        
        case AST_VAR_DECLARATION:       fprintf(stderr, "AST_VAR_DECLARATION) \n");
                        break;        
        case AST_VEC_DECLARATION:       fprintf(stderr, "AST_VEC_DECLARATION) \n");
                        break;        
        case AST_FUNC_DECLARATION:      fprintf(stderr, "AST_FUNC_DECLARATION) \n");
                        break;
        case AST_DATATYPE_BYTE:         fprintf(stderr, "AST_DATATYPE_BYTE) \n");
                        break;
        case AST_DATATYPE_FLOAT:        fprintf(stderr, "AST_DATATYPE_FLOAT) \n");
                        break;
        case AST_DATATYPE_INT:          fprintf(stderr, "AST_DATATYPE_INT) \n");
                        break;
        case AST_FUNC_PARAM:            fprintf(stderr, "AST_FUNC_PARAM) \n");
                        break;
        case AST_DECLIST:               fprintf(stderr, "AST_DECLIST) \n");
                        break;
        case AST_INILIST:               fprintf(stderr, "AST_INILIST) \n");
                        break;
        case AST_FUNC_PARAMLIST:        fprintf(stderr, "AST_FUNC_PARAMLIST) \n");
                        break;
        case AST_BLOCK:                 fprintf(stderr, "AST_BLOCK) \n");
                        break;
        case AST_CMDLIST:               fprintf(stderr, "AST_CMDLIST) \n");
                        break;
        case AST_CMD_READ:              fprintf(stderr, "AST_CMD_READ) \n");
                        break;
        case AST_CMD_PRINT:             fprintf(stderr, "AST_CMD_PRINT) \n");
                        break;
        case AST_CMD_RETURN:            fprintf(stderr, "AST_CMD_RETURN) \n");
                        break;
        case AST_CMD_IF:                fprintf(stderr, "AST_CMD_IF) \n");
                        break;
        case AST_CMD_IF_ELSE:           fprintf(stderr, "AST_CMD_IF_ELSE) \n");
                        break;
        case AST_CMD_LEAP:              fprintf(stderr, "AST_CMD_LEAP) \n");
                        break;
        case AST_CMD_LOOP:              fprintf(stderr, "AST_CMD_LOOP) \n");
                        break;
        case AST_CMDRESTO:              fprintf(stderr, "AST_CMDRESTO) \n");
                        break;
        case AST_ATRIB:                 fprintf(stderr, "AST_ATRIB) \n");
                        break;
        case AST_VEC_POS_ATRIB:         fprintf(stderr, "AST_VEC_POS_ATRIB) \n");
                        break;
        case AST_ARGRESTO:              fprintf(stderr, "AST_ARGRESTO) \n");
                        break;
        case AST_ARGLIST:               fprintf(stderr, "AST_ARGLIST) \n");
                        break;
        case AST_PARAMRESTO:            fprintf(stderr, "AST_PARAMRESTO) \n");
                        break;
        case AST_VEC_DECLARATION_INI:   fprintf(stderr, "AST_VEC_DECLARATION_INI) \n");
                        break;
        default:                        fprintf(stderr, "AST_UNKNOWN) %d \n", node->type);
                        break;
    }

    level++;

    for(i=0; i<MAX_SONS; i++)
        astPrintRec(node->son[i], level);
    
}

void generateSource(AST *node, FILE *out) {

	AST *temp = node;
	if (temp == 0) return;

	switch(temp->type) {
		case AST_DECLIST:
			                generateSource(temp->son[0], out);
			                generateSource(temp->son[1], out);
			            break;
		
		case AST_VAR_DECLARATION: 
			                generateSource(temp->son[0], out);
			                fprintf(out,"%s = ", temp->symbol->lit);
			                generateSource(temp->son[1], out);
			                fprintf(out, ";\n");
			            break;
		case AST_VEC_DECLARATION: 
			                generateSource(temp->son[0], out);
			                fprintf(out,"%s ", temp->symbol->lit);
			                fprintf(out, "[");
			                generateSource(temp->son[1], out);
			                fprintf(out, "];\n");
			            break;
		case AST_VEC_DECLARATION_INI: 
			                generateSource(temp->son[0], out);
			                fprintf(out,"%s ", temp->symbol->lit);
			                fprintf(out, "[");
			                generateSource(temp->son[1], out);
			                fprintf(out, "]: ");
			                generateSource(temp->son[2], out);
			                fprintf(out, ";\n");
			            break;
		case AST_DATATYPE_BYTE: 
			                fprintf(out,"byte ");
			            break;
        case AST_DATATYPE_INT: 
			                fprintf(out,"int ");
			            break;
		case AST_DATATYPE_FLOAT: 
			                fprintf(out,"float ");
			            break;		
		case AST_INILIST: 
			                generateSource(temp->son[0], out);
			                fprintf(out," ");
			                generateSource(temp->son[1], out);
			            break;
		case AST_LIT_INTEGER: 
			                fprintf(out,"%s", temp->symbol->lit);
			            break;
		case AST_LIT_FLOAT: 
			                fprintf(out,"%s", temp->symbol->lit);
			            break;
		case AST_LIT_CHAR: 
			                fprintf(out,"'%s'", temp->symbol->lit);
			            break;
        case AST_LIT_STRING:
                            fprintf(out ,"\"%s\"", temp->symbol->lit);
                        break;
        case AST_TK_IDENTIFIER:
                            fprintf(out, "%s", temp->symbol->lit);
                        break;
		case AST_FUNC_DECLARATION: 
			                generateSource(temp->son[0], out);
			                fprintf(out,"%s ", temp->symbol->lit);
			                fprintf(out, "(");
			                generateSource(temp->son[1], out);
			                fprintf(out, ")");
			                generateSource(temp->son[2], out);
			            break;
		case AST_FUNC_PARAMLIST: 
			                generateSource(temp->son[0], out);
			                generateSource(temp->son[1], out);
			            break;
        case AST_PARAMRESTO: 
                            fprintf(out, ", ");
                            generateSource(temp->son[0], out);
                            generateSource(temp->son[1], out);
                        break;
		case AST_FUNC_PARAM:
		 	                generateSource(temp->son[0], out);
			                fprintf(out,"%s ", temp->symbol->lit);
			            break;
        case AST_BLOCK: 
			                fprintf(out, "{\n");
			                generateSource(temp->son[0], out);
			                fprintf(out, "\n};");
			            break;
		case AST_CMDLIST: 
                            if(temp->son[0] != 0){
                                generateSource(temp->son[0], out);
                            }
                            generateSource(temp->son[1], out);
			            break;
		case AST_CMDRESTO: 
			                if( temp->son[0] != 0){
				                fprintf(out, ";\n");
                                generateSource(temp->son[0], out);
			                }
                            generateSource(temp->son[1], out);
			            break;
        case AST_CMD_READ: 
			                fprintf(out, "read ");
			                fprintf(out,"%s", node->symbol->lit);		
			            break;
        case AST_CMD_PRINT: 
			                fprintf(out, "print ");
                            generateSource(temp->son[0], out);	
			            break;
		case AST_CMD_RETURN:
			                fprintf(out,"return ");
                            generateSource(temp->son[0], out);
			            break;
		case AST_CMD_IF: 
			                fprintf(out, "if( ");
			                generateSource(temp->son[0], out);
                            fprintf(out, " ) then \n");
                            generateSource(temp->son[1], out);
                        break;
		case AST_CMD_IF_ELSE: 
			                fprintf(out, "if( ");
			                generateSource(temp->son[0], out);
                            fprintf(out, " ) then \n");
                            generateSource(temp->son[1], out);
                            fprintf(out, " else \n");
                            generateSource(temp->son[2], out);
			            break;
        case AST_CMD_LEAP:
                            fprintf(out, "leap \n");
                        break;
        case AST_CMD_LOOP:
                            fprintf(out, "loop( ");
                            generateSource(temp->son[0], out);
                            fprintf(out, ") \n");
                            generateSource(temp->son[1], out);
                        break;
        case AST_ATRIB:
                            fprintf(out, "%s = ", temp->symbol->lit);
                            generateSource(temp->son[0], out);
                        break;
        case AST_VEC_POS_ATRIB:
                            fprintf(out, "%s [", temp->symbol->lit);
                            generateSource(temp->son[0], out);
                            fprintf(out, "] = ");
                            generateSource(temp->son[1], out);
                        break;
        case AST_ARGLIST:
                            generateSource(temp->son[0], out);
                            generateSource(temp->son[1], out);
                        break;
        case AST_ARGRESTO:
                            fprintf(out, ", ");
                            generateSource(temp->son[0], out);
                            generateSource(temp->son[1], out);
                        break;
        case AST_VECTOR:
                            fprintf(out, "%s [", temp->symbol->lit);
                            generateSource(temp->son[0], out);
                            fprintf(out, "]");
                        break;
        case AST_FUNCTION:
                            fprintf(out, "%s (", temp->symbol->lit);
                            generateSource(temp->son[0], out);
                            fprintf(out, ")");
                        break;
		case AST_OP_ADD: 
			                generateSource(temp->son[0], out);
			                fprintf(out, " + ");
			                generateSource(temp->son[1], out);
			            break;
        case AST_OP_SUB: 
			                generateSource(temp->son[0], out);
			                fprintf(out, " - ");
			                generateSource(temp->son[1], out);
			            break;
        case AST_OP_MUL: 
			                generateSource(temp->son[0], out);
			                fprintf(out, " * ");
			                generateSource(temp->son[1], out);
		                break;
		case AST_OP_DIV: 
			                generateSource(temp->son[0], out);
			                fprintf(out, " / ");
			                generateSource(temp->son[1], out);
			            break;
		case AST_OP_AND: 
			                generateSource(temp->son[0], out);
			                fprintf(out, " and ");
			                generateSource(temp->son[1], out);
			            break;
		case AST_OP_OR: 
			                generateSource(temp->son[0], out);
			                fprintf(out, " or ");
			                generateSource(temp->son[1], out);
			            break;
		case AST_OP_DIF: 
			                generateSource(temp->son[0], out);
			                fprintf(out, " != ");
			                generateSource(temp->son[1], out);
			            break;
		case AST_OP_EQ: 
			                generateSource(temp->son[0], out);
			                fprintf(out, " == ");
			                generateSource(temp->son[1], out);
			            break;
		case AST_OP_GE: 
                            fprintf(out, ">= ");
                            generateSource(temp->son[0], out);
			            break;
		case AST_OP_LE: 
			                generateSource(temp->son[0], out);
			                fprintf(out, " <= ");
			                generateSource(temp->son[1], out);			
			            break;
		case AST_OP_GT: 
			                generateSource(temp->son[0], out);
			                fprintf(out, " > ");
			                generateSource(temp->son[1], out);
			            break;
		case AST_OP_LT: 
			                generateSource(temp->son[0], out);
			                fprintf(out, " < ");
			                generateSource(temp->son[1], out);
                        break;
		case AST_OP_NOT: 
			                fprintf(out, "not ");
			                generateSource(temp->son[0], out);
			            break;
		default: 
            fprintf(stderr, "AST_UNKNOWN(%s)\n", temp->symbol->lit); 
            break;
	}
}

void closeFile(FILE *code){
    fclose(code);
}
