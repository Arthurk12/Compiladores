/*
ARTHUR BOCKMANN GROSSI - 00275607
IAN FISCHER SCHILLING - 00275603
*/

#ifndef SYMBOLS_HEADER
#define SYMBOLS_HEADER

//AST SYMBOLS
//OP ARITMETICAS
#define AST_OP_ADD              1
#define AST_OP_SUB              2
#define AST_OP_MUL              3
#define AST_OP_DIV              4
//OP RELACIONAIS
#define AST_OP_DIF              5
#define AST_OP_EQ               6
#define AST_OP_GE               7
#define AST_OP_LE               8
#define AST_OP_GT               9    //greater than ">"
#define AST_OP_LT               10    //less than "<"
//OP LOGICAS
#define AST_OP_AND              11
#define AST_OP_OR               12
#define AST_OP_NOT              13
//LITERAIS
#define AST_LIT_INTEGER         14
#define AST_LIT_FLOAT           15
#define AST_LIT_CHAR            16
#define AST_LIT_STRING          17
//IDENTIFICADORES
#define AST_TK_IDENTIFIER       18
#define AST_VECTOR              19
#define AST_FUNCTION            20
//DECLARACOES
#define AST_VAR_DECLARATION     21
#define AST_VEC_DECLARATION     22
#define AST_FUNC_DECLARATION    23
//TIPOS DE DADOS
#define AST_DATATYPE_BYTE       24
#define AST_DATATYPE_FLOAT      25
#define AST_DATATYPE_INT        26

#define AST_FUNC_PARAM          27
#define AST_DECLIST             28
#define AST_INILIST             29
#define AST_FUNC_PARAMLIST      30
#define AST_BLOCK               31
#define AST_CMDLIST             32
#define AST_CMD_READ            33
#define AST_CMD_PRINT           34
#define AST_CMD_RETURN          35
#define AST_CMD_IF              36
#define AST_CMD_IF_ELSE         37
#define AST_CMD_LEAP            38
#define AST_CMD_LOOP            39
#define AST_CMDRESTO            40
#define AST_ATRIB               41
#define AST_VEC_POS_ATRIB       42
#define AST_ARGRESTO            43
#define AST_ARGLIST             44
#define AST_PARAMRESTO          45
#define AST_VEC_DECLARATION_INI 46



//DATATYPES
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
#define DATATYPE_BOOL           10
#define DATATYPE_STRING         11



//TACS

#define TAC_SYMBOL              1
#define TAC_SYMBOL_LIT          2
#define TAC_SYMBOL_LIT_STRING   3
#define TAC_VECTOR              4
#define TAC_ADD                 5
#define TAC_SUB                 6
#define TAC_MUL                 7
#define TAC_DIV                 8
#define TAC_GE                  9
#define TAC_LE                  10
#define TAC_GT                  11
#define TAC_LT                  12
#define TAC_AND                 13
#define TAC_OR                  14
#define TAC_NOT                 15
#define TAC_DIF                 16
#define TAC_EQ                  17
#define TAC_SYMBOL_VEC          18
#define TAC_PRINT               19
#define TAC_RETURN              20
#define TAC_READ                21
#define TAC_IF_THEN             22
#define TAC_IF_ELSE             23
#define TAC_JUMP                24
#define TAC_LEAP                25
#define TAC_LOOP                26
#define TAC_LABEL               27
#define TAC_FUNC_BEGIN          28
#define TAC_FUNC_END            29
#define TAC_ATRIB               30
#define TAC_ATRIB_VEC_POS       31
#define TAC_FUNC_CALL_BEGIN     32
#define TAC_FUNC_CALL_END       33
#define TAC_VEC_DECLARATION     34
#define TAC_VEC_DECLARATION_INI 35
#define TAC_VEC_DECLARATION_END 36
#define TAC_ARG                 37
#define TAC_PRINT_END           38

//temphash
#define SYMBOL_VAR              100


#endif