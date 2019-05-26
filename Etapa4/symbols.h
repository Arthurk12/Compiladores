/*
ARTHUR BOCKMANN GROSSI - 00275607
IAN FISCHER SCHILLING - 00275603
*/

#ifndef SYMBOLS_HEADER
#define SYMBOLS_HEADER

//AST SYMBOLS
#define AST_OP_EQUAL            1
#define AST_OP_ADD              2
#define AST_OP_SUB              3
#define AST_OP_MUL              4
#define AST_OP_DIV              5
#define AST_OP_AND              6
#define AST_OP_OR               7
#define AST_OP_DIF              8
#define AST_OP_EQ               9
#define AST_OP_GE               10
#define AST_OP_LE               11
#define AST_OP_GT               12    //greater than ">"
#define AST_OP_LT               13    //less than "<"
#define AST_OP_NOT              14
#define AST_LIT_INTEGER         15
#define AST_LIT_FLOAT           16
#define AST_LIT_CHAR            17
#define AST_LIT_STRING          18
#define AST_TK_IDENTIFIER       19
#define AST_VECTOR              20
#define AST_FUNCTION            21
#define AST_VAR_DECLARATION     22
#define AST_VEC_DECLARATION     23
#define AST_FUNC_DECLARATION    24
#define AST_DATATYPE_BYTE       25
#define AST_DATATYPE_FLOAT      26
#define AST_DATATYPE_INT        27
#define AST_FUNC_PARAM          28
#define AST_DECLIST             29
#define AST_INILIST             30
#define AST_FUNC_PARAMLIST      31
#define AST_BLOCK               32
#define AST_CMDLIST             33
#define AST_CMD_READ            34
#define AST_CMD_PRINT           35
#define AST_CMD_RETURN          36
#define AST_CMD_IF              37
#define AST_CMD_IF_ELSE         38
#define AST_CMD_LEAP            39
#define AST_CMD_LOOP            40
#define AST_CMDRESTO            41
#define AST_ATRIB               42
#define AST_VEC_POS_ATRIB       43
#define AST_ARGRESTO            44
#define AST_ARGLIST             45
#define AST_PARAMRESTO          46
#define AST_VEC_DECLARATION_INI 47



//HASH DATATYPES
#define NO_DATATYPE             0
#define DATATYPE_BYTE           1
#define DATATYPE_INT            2
#define DATATYPE_FLOAT          3
#define DATATYPE_BYTE_VEC       4
#define DATATYPE_INT_VEC        5
#define DATATYPE_FLOAT_VEC      6
#define DATATYPE_BYTE_FUN       7
#define DATATYPE_INT_FUN        8
#define DATATYPE_FLOAT_FUN      9

#endif