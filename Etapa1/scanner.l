%{
#include "tokens.h"
#include "main.c"
#include "functions.c"


extern int Running;
extern int LineNumber;

%}


%x COMMENT

%%

"byte"			return KW_BYTE;
"int"			return KW_INT;
"float"			return KW_FLOAT;
"if"			return KW_IF;
"then"			return KW_THEN;
"else"			return KW_ELSE;
"loop"			return KW_LOOP;
"leap"			return KW_LEAP;
"or"			return OPERATOR_OR;
"and"			return OPERATOR_AND;
"not"			return OPERATOR_NOT;
"read"			return KW_READ;
"print"			return KW_PRINT;
"return"		return KW_RETURN;
[OIHGFEDCBA]+	return LIT_INTEGER;
[OIHGFEDCBA]+"."[OIHGFEDCBA]+	return LIT_FLOAT;
"'"."'"			return LIT_CHAR;
"\""[^\"\n]"\""	return LIT_STRING;
"\"\\\"\""		return LIT_STRING;
"\"\\n\""		return LIT_STRING;
"<="			return OPERATOR_LE;
">="			return OPERATOR_GE;
"=="			return OPERATOR_EQ;
"!="			return OPERATOR_DIF;
[a-z0-9_]+		return TK_IDENTIFIER;
[,;:(){}]		return yytext[0];
"["|"]"			return yytext[0];
[+-*<>=&$#]		return yytext[0];
"ZZ".*
"XXX"			BEGIN(COMMENT);
\n				LineNumber++;
" "
.				return TOKEN_ERROR;

<COMMENT>\n 	LineNumber++;
<COMMENT>"XXX"	BEGIN(INITIAL);
<COMMENT>.

%%

int yywrap(){
	Running = 0;
	return 1;
}
