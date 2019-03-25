%{
#include "tokens.h"
#include "functions.c"
//#include "main.c"


int Running=1;
int LineNumber=1;

%}

%x COMMENT_LINE
%x COMMENT

%%

"byte"				return KW_BYTE;
"int"					return KW_INT;
"float"				return KW_FLOAT;
"if"					return KW_IF;
"then"				return KW_THEN;
"else"				return KW_ELSE;
"loop"				return KW_LOOP;
"leap"				return KW_LEAP;
"or"					return OPERATOR_OR;
"and"					return OPERATOR_AND;
"not"					return OPERATOR_NOT;
"read"				return KW_READ;
"print"				return KW_PRINT;
"return"				return KW_RETURN;
[OIHGFEDCBA]+			return LIT_INTEGER;
[OIHGFEDCBA]+"."[OIHGFEDCBA]+	return LIT_FLOAT;
"'"."'"				return LIT_CHAR;
\"(\\\"|[^\"\n])+\"		return LIT_STRING;
"<="					return OPERATOR_LE;
">="					return OPERATOR_GE;
"=="					return OPERATOR_EQ;
"!="					return OPERATOR_DIF;
[a-z0-9_]+				return TK_IDENTIFIER;
[,;:(){}]				return yytext[0];
"["|"]"				return yytext[0];
[+\-*/<>=&$#]			return yytext[0];
"ZZ"					BEGIN(COMMENT_LINE);
"XXX"					BEGIN(COMMENT);
\n					LineNumber++;
" "
.					return TOKEN_ERROR;

<COMMENT_LINE>\n 	{LineNumber++; BEGIN(INITIAL);}
<COMMENT_LINE>.

<COMMENT>\n 	LineNumber++;
<COMMENT>"XXX"	BEGIN(INITIAL);
<COMMENT>.

%%

int yywrap(){
	Running = 0;
	return 1;
}
