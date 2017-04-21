/*
Batch no. 82

AUTHORS : 
Pranjal Gupta (2013B4A7470P)
Tanaya Jha (2013B3A7304P)
*/

#ifndef RESET
#define RESET   "\033[0m"
#endif

#ifndef BOLDBLACK
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#endif

#ifndef BOLDRED
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#endif

#ifndef BOLDGREEN
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#endif

#ifndef BOLDYELLOW
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#endif

#ifndef BOLDBLUE
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#endif

#ifndef BOLDMAGENTA
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#endif

#ifndef BOLDCYAN
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#endif

#ifndef BOLDWHITE
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */
#endif



#ifndef _scopeStruct

#define _scopeStruct

typedef struct se symbolEntry;
typedef struct sy symbolScope;

struct se {
	char identifier[25];

	// 1 : variable , 2 : function only def , 3 : input parameter , 4 : output , 5 : function only dec, 6 : function def & dec
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

	char temporary[5];

	int offset;
	int width;

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
