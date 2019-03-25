#include <stdio.h>
#include <stdlib.h>


#define HASHSIZE 997


typedef struct{
	int type;	
	char *lit;
	struct hashNode *next;
}hashNode;


hashNode *HashTable[HASHSIZE];

extern char *yytext;

void initMe(void);
int hashAddress(char *lit);
hashNode* insert(int type, char *lit);
void hashPrint(void);
hashNode* hasFind(char *lit, int address);
