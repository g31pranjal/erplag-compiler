

typedef struct se symbolEntry;
typedef struct sy symbolScope;


#ifndef _scopeStruct

#define _scopeStruct

struct se {
	char identifier[25];

	// 1 : variable , 2 : function def , 3 : input parameter , 4 : output , 5 : function dec
	int usage;

	char type[25];

	int isArray;
	int startInd;
	int endInd;

	int lineInit;

	int linesUsed[25];
	int linesUsedNum;

	symbolScope * scope;

	symbolEntry * next;

};


struct sy {

	char stamp[25];

	symbolScope * parent;
	symbolScope * childL;
	symbolScope * childR;
	symbolScope * next;
	symbolScope * prev;

	symbolEntry * seHead;

};


#endif
