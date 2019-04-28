/*
ARTHUR BÖCKMANN GROSSI - 00275607
IAN FISCHER SCHILLING - 00275603
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define HASHSIZE 997

typedef struct hashnode{
	int type;	
	char *lit;
	struct hashnode *next;
}hashNode;


hashNode *HashTable[HASHSIZE];

extern char *yytext;

void initMe(void);
int hashAddress(char *lit);
hashNode* hashInsert(int type, char *lit);
void hashPrint(void);
hashNode* hashFind(char *lit, int address);
