%{
#include "functions.c"
#include "hash.h"
#include "y.tab.h"


int Running=1;
int LineNumber=1;

%}

%x COMMENT_LINE
%x COMMENT

%%

"byte"							return KW_BYTE;
"int"							return KW_INT;
"float"							return KW_FLOAT;
"if"							return KW_IF;
"then"							return KW_THEN;
"else"							return KW_ELSE;
"loop"							return KW_LOOP;
"leap"							return KW_LEAP;
"or"							return OPERATOR_OR;
"and"							return OPERATOR_AND;
"not"							return OPERATOR_NOT;
"read"							return KW_READ;
"print"							return KW_PRINT;
"return"						return KW_RETURN;
[OIHGFEDCBA]+					{hashInsert(LIT_INTEGER, yytext);return LIT_INTEGER;}
[OIHGFEDCBA]+"."[OIHGFEDCBA]+	{hashInsert(LIT_FLOAT, yytext);return LIT_FLOAT;}
"'"."'"							{hashInsert(LIT_CHAR, yytext);return LIT_CHAR;}
\"(\\\"|[^\"\n])*\"				{hashInsert(LIT_STRING, yytext);return LIT_STRING;}
"<="							return OPERATOR_LE;
">="							return OPERATOR_GE;
"=="							return OPERATOR_EQ;
"!="							return OPERATOR_DIF;
[a-z0-9_]+						{hashInsert(TK_IDENTIFIER, yytext);return TK_IDENTIFIER;}
[,;(){}]						return yytext[0];
"["|"]"							return yytext[0];
":"								return yytext[0];
[+\-*/<>=&$#]					return yytext[0];
"ZZ"							BEGIN(COMMENT_LINE);
"XXX"							BEGIN(COMMENT);
\n								LineNumber++;
[ \t]
.								return TOKEN_ERROR;

<COMMENT_LINE>\n 				{LineNumber++; BEGIN(INITIAL);}
<COMMENT_LINE>.

<COMMENT>\n 					LineNumber++;
<COMMENT>"XXX"					BEGIN(INITIAL);
<COMMENT>.

%%

int yywrap(){
	Running = 0;
	return 1;
}
