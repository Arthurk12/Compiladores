#include "hash.h"
#include "y.tab.h"

void initMe(void) {
	int i=0;
	for(i=0; i<HASHSIZE; i++){
		HashTable[i] = 0;
	}
}

int hashAddress(char *lit) {
	int address = 1;
	int i;
	
	for (i=0; i<strlen(lit); i++){
		address = (address * lit[i]) % HASHSIZE +1;
	}

	return address-1;
}

hashNode* hashFind(char *lit, int address){
	hashNode *node;
	for(node=HashTable[address]; node; node=node->next)
		if(strcmp(node->lit, lit) == 0)
			return node;

	return 0;
}

hashNode* hashInsert(int type, char *lit){
	hashNode *newNode;
	int address = hashAddress(lit);

	lit = trimQuotation(type, lit);

	if((newNode = hashFind(lit, address))!=0)
		return newNode;	

	newNode = (hashNode *) calloc(1, sizeof(hashNode));
	newNode->type = type;
	newNode->lit = calloc(strlen(yytext)+1, sizeof(char));
	newNode->datatype = NO_DATATYPE;

	strcpy(newNode->lit, lit);

	newNode->dec = false;

	newNode->next = HashTable[address];
	HashTable[address] = newNode;

	return newNode;
}

void hashPrint(){
	int i=0;
	hashNode *node;
	printf("\n========================================HASH PRINT========================================\n");
	for(i=0; i<HASHSIZE; i++)
		for(node = HashTable[i]; node!=0; node=node->next)
			printf("Hash_Table_Node[%d]: %s  -> %i |%i|\n", i, node->lit, node->type, node->datatype);
	printf("=========================================================================================\n");
}

bool hashCheckUndeclared(){
	hashNode *node;
	bool error = false;

	int i;
	for (i = 0; i < HASHSIZE; i++){
			for( node = HashTable[i]; node; node = node->next){
				if (node->dec == false && node->type == TK_IDENTIFIER){
					fprintf(stderr, "[SEMANTIC ERROR] - '%s' wasn't declared.\n", node->lit);
					error = true;
				}
			}
	}
	return error;
}

hashNode* makeTemp(){
	static int serial=0;
	static char buffer[100] = "";

	sprintf(buffer, "T3mph4shnod3f0rt4c-%d", serial++);
	return hashInsert(SYMBOL_VAR, buffer);
}

hashNode* makeLabel(){
	static int serial=0;
	static char buffer[100] = "";

	sprintf(buffer, "L4belh4shnod3f0rt4c-%d", serial++);
	return hashInsert(SYMBOL_VAR, buffer);
}

char* trimQuotation(int type, char* lit){
	char *trimmedLit;

	trimmedLit = calloc(strlen(lit-1), sizeof(char));

	if(type == LIT_CHAR){
		
		strncpy(trimmedLit, &lit[1], 1);
	}else if(type == LIT_STRING){

		trimmedLit = strtok(lit, "\"");
	}else{
		return lit;
	}
	return trimmedLit;
}