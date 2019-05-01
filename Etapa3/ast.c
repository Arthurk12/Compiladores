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
    return new_node;
}

void astPrint(AST *node, int level){

    int i;
    if(node == 0)return;

    for(i=0; i<=level; i++){
        fprintf(stderr, "  ");
    }

    fprintf(stderr, "AST(");
    switch(node->type){
        case AST_OP_EQUAL:  fprintf(stderr, "AST_OP_EQUAL) \n");
                        break;
        case AST_OP_ADD:    fprintf(stderr, "AST_ADD) \n");
                        break;
        case AST_OP_SUB:    fprintf(stderr, "AST_SUB) \n");
                        break;
        case AST_OP_MUL:    fprintf(stderr, "AST_MUL) \n");
                        break;
        case AST_OP_DIV:    fprintf(stderr, "AST_DIV) \n");
                        break;
        case AST_OP_AND:    fprintf(stderr, "AST_AND) \n");
                        break;
        case AST_OP_OR:     fprintf(stderr, "AST_OR) \n");
                        break;
        case AST_OP_DIF:    fprintf(stderr, "AST_DIF) \n");
                        break;
        case AST_OP_EQ:     fprintf(stderr, "AST_EQ) \n");
                        break;
        case AST_OP_GE:     fprintf(stderr, "AST_GE) \n");
                        break;
        case AST_OP_LE:     fprintf(stderr, "AST_LE) \n");
                        break;
        case AST_OP_GT:     fprintf(stderr, "AST_GT) \n");
                        break;
        case AST_OP_LT:     fprintf(stderr, "AST_LT) \n");
                        break;
        case AST_OP_NOT:    fprintf(stderr, "AST_NOT) \n");
                        break;
        case AST_LIT_INTEGER:   fprintf(stderr, "AST_INTEGER) \n");
                        break;
        case AST_LIT_FLOAT:     fprintf(stderr, "AST_FLOAT) \n");
                        break;
        case AST_LIT_CHAR:      fprintf(stderr, "AST_CHAR) \n");
                        break;
        case AST_LIT_STRING:    fprintf(stderr, "AST_STRING) \n");
                        break;
        case AST_TK_IDENTIFIER: fprintf(stderr, "AST_IDENTIFIER) \n");
                        break;
        case AST_VECTOR:        fprintf(stderr, "AST_VECTOR) \n");
                        break;
        case AST_FUNCTION:      fprintf(stderr, "AST_FUNCTION) \n");
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
        default:                        fprintf(stderr, "AST_UNKNOWN) %d \n", node->type);
                        break;
    }

    level++;

    for(i=0; i<MAX_SONS; i++)
        astPrint(node->son[i], level);
    
}

void compile(AST *node, FILE *out) {

	AST *temp = node;
	if (temp == 0) return;

	switch(temp->type) {
		case AST_DECLIST:
			                compile(temp->son[0], out);
			                compile(temp->son[1], out);
			            break;
		
		case AST_VAR_DECLARATION: 
			                compile(temp->son[0], out);
			                fprintf(out,"%s = ", temp->symbol->lit);
			                compile(temp->son[1], out);
			                fprintf(out, ";\n");
			            break;
		case AST_VEC_DECLARATION: 
			                compile(temp->son[0], out);
			                fprintf(out,"%s ", temp->symbol->lit);
			                fprintf(out, "[");
			                compile(temp->son[1], out);
			                fprintf(out, "];\n");
			            break;
		case AST_VEC_DECLARATION_INI: 
			                compile(temp->son[0], out);
			                fprintf(out,"%s ", temp->symbol->lit);
			                fprintf(out, "[");
			                compile(temp->son[1], out);
			                fprintf(out, "]: ");
			                compile(temp->son[2], out);
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
			                compile(temp->son[0], out);
			                fprintf(out," ");
			                compile(temp->son[1], out);
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
			                compile(temp->son[0], out);
			                fprintf(out,"%s ", temp->symbol->lit);
			                fprintf(out, "(");
			                compile(temp->son[1], out);
			                fprintf(out, ")");
			                compile(temp->son[2], out);
			            break;
		case AST_FUNC_PARAMLIST: 
			                compile(temp->son[0], out);
			                compile(temp->son[1], out);
			            break;
        case AST_PARAMRESTO: 
                            fprintf(out, ", ");
                            compile(temp->son[0], out);
                            compile(temp->son[1], out);
                        break;
		case AST_FUNC_PARAM:
		 	                compile(temp->son[0], out);
			                fprintf(out,"%s ", temp->symbol->lit);
			            break;
        case AST_BLOCK: 
			                fprintf(out, "{\n");
			                compile(temp->son[0], out);
			                fprintf(out, "\n};");
			            break;
		case AST_CMDLIST: 
                            if(temp->son[0] != 0){
                                compile(temp->son[0], out);
                            }
                            compile(temp->son[1], out);
			            break;
		case AST_CMDRESTO: 
			                if( temp->son[0] != 0){
				                fprintf(out, ";\n");
                                compile(temp->son[0], out);
			                }
                            compile(temp->son[1], out);
			            break;
        case AST_CMD_READ: 
			                fprintf(out, "read ");
			                fprintf(out,"%s", node->symbol->lit);		
			            break;
        case AST_CMD_PRINT: 
			                fprintf(out, "print ");
                            compile(temp->son[0], out);	
			            break;
		case AST_CMD_RETURN:
			                fprintf(out,"return ");
                            compile(temp->son[0], out);
			            break;
		case AST_CMD_IF: 
			                fprintf(out, "if( ");
			                compile(temp->son[0], out);
                            fprintf(out, " ) then \n");
                            compile(temp->son[1], out);
                        break;
		case AST_CMD_IF_ELSE: 
			                fprintf(out, "if( ");
			                compile(temp->son[0], out);
                            fprintf(out, " ) then \n");
                            compile(temp->son[1], out);
                            fprintf(out, " else \n");
                            compile(temp->son[2], out);
			            break;
        case AST_CMD_LEAP:
                            fprintf(out, "leap \n");
                        break;
        case AST_CMD_LOOP:
                            fprintf(out, "loop( ");
                            compile(temp->son[0], out);
                            fprintf(out, ") \n");
                            compile(temp->son[1], out);
                        break;
        case AST_ATRIB:
                            fprintf(out, "%s = ", temp->symbol->lit);
                            compile(temp->son[0], out);
                        break;
        case AST_VEC_POS_ATRIB:
                            fprintf(out, "%s [", temp->symbol->lit);
                            compile(temp->son[0], out);
                            fprintf(out, "] = ");
                            compile(temp->son[1], out);
                        break;
        case AST_ARGLIST:
                            compile(temp->son[0], out);
                            compile(temp->son[1], out);
                        break;
        case AST_ARGRESTO:
                            fprintf(out, ", ");
                            compile(temp->son[0], out);
                            compile(temp->son[1], out);
                        break;
        case AST_VECTOR:
                            fprintf(out, "%s [", temp->symbol->lit);
                            compile(temp->son[0], out);
                            fprintf(out, "]");
                        break;
        case AST_FUNCTION:
                            fprintf(out, "%s (", temp->symbol->lit);
                            compile(temp->son[0], out);
                            fprintf(out, ")");
                        break;
		case AST_OP_ADD: 
			                compile(temp->son[0], out);
			                fprintf(out, " + ");
			                compile(temp->son[1], out);
			            break;
        case AST_OP_SUB: 
			                compile(temp->son[0], out);
			                fprintf(out, " - ");
			                compile(temp->son[1], out);
			            break;
        case AST_OP_MUL: 
			                compile(temp->son[0], out);
			                fprintf(out, " * ");
			                compile(temp->son[1], out);
		                break;
		case AST_OP_DIV: 
			                compile(temp->son[0], out);
			                fprintf(out, " / ");
			                compile(temp->son[1], out);
			            break;
		case AST_OP_AND: 
			                compile(temp->son[0], out);
			                fprintf(out, " and ");
			                compile(temp->son[1], out);
			            break;
		case AST_OP_OR: 
			                compile(temp->son[0], out);
			                fprintf(out, " or ");
			                compile(temp->son[1], out);
			            break;
		case AST_OP_DIF: 
			                compile(temp->son[0], out);
			                fprintf(out, " != ");
			                compile(temp->son[1], out);
			            break;
		case AST_OP_EQ: 
			                compile(temp->son[0], out);
			                fprintf(out, " == ");
			                compile(temp->son[1], out);
			            break;
		case AST_OP_GE: 
                            fprintf(out, ">= ");
                            compile(temp->son[0], out);
			            break;
		case AST_OP_LE: 
			                compile(temp->son[0], out);
			                fprintf(out, " <= ");
			                compile(temp->son[1], out);			
			            break;
		case AST_OP_GT: 
			                compile(temp->son[0], out);
			                fprintf(out, " > ");
			                compile(temp->son[1], out);
			            break;
		case AST_OP_LT: 
			                compile(temp->son[0], out);
			                fprintf(out, " < ");
			                compile(temp->son[1], out);
                        break;
		case AST_OP_NOT: 
			                compile(temp->son[0], out);
			                fprintf(out, "not ");
			                compile(temp->son[1], out);
			            break;
		default: 
            fprintf(stderr, "AST_UNKNOWN(%s)\n", temp->symbol->lit); 
            break;
	}
}

void initFile(AST *node){
    FILE *code;
    time_t raw;
    char title[40] = "Code";
    char sec[3];
    struct tm * timeinfo;

    time (&raw);
    timeinfo = localtime (&raw);

    strncpy(sec, &asctime(timeinfo)[17],2*sizeof(char));

    strcat(title, sec);
    strcat(title, ".txt");

    code = fopen(title, "w+");
    compile(node, code);
    closeFile(code);
}

void closeFile(FILE *code){
    fclose(code);
}
