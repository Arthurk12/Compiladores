/*
ARTHUR BÖCKMANN GROSSI - 00275607
IAN FISCHER SCHILLING - 00275603
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define HASHSIZE 997

typedef enum { false, true } bool;

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
void hashCheckUndeclared();