/*
ARTHUR BÖCKMANN GROSSI - 00275607
IAN FISCHER SCHILLING - 00275603
*/

#ifndef HASH_HEADER
#define HASH_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "symbols.h"
#include "y.tab.h"


#define HASHSIZE 997

typedef struct hashnode{
	int type;
	int datatype;	
	char *lit;
	struct hashnode *next;
	bool dec;
}hashNode;

hashNode *HashTable[HASHSIZE];

extern char *yytext;

void initMe(void);
int hashAddress(char *lit);
hashNode* hashInsert(int type, char *lit);
void hashPrint(void);
hashNode* hashFind(char *lit, int address);
bool hashCheckUndeclared(void);

hashNode* makeTemp();
hashNode* makeLabel();
char* trimQuotation(int type, char* lit);

#endif