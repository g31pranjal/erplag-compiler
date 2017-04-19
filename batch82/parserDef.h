/*
Batch no. 82

AUTHORS : 
Pranjal Gupta (2013B4A7470P)
Tanaya Jha (2013B3A7304P)
*/


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


#include "lexerDef.h"
#include "scopeDef.h"
#include "codegenDef.h"

#ifndef _grammar

#define _grammar

typedef struct el element;

struct el{

	int id;
	char val[25];
	int type;

	int occ_lhs[20];
	int occ_rhs[20];	
	int occ_lhs_num;
	int occ_rhs_num;

	element * next;

	unsigned long long first;
	unsigned long long follow;

};


typedef struct rs ruleSeg;

struct rs {

	element * data;

	ruleSeg * next;
	ruleSeg * prev;

};


typedef struct rl rule;

struct rl {

	ruleSeg lhs;
	ruleSeg * rhstop;
	ruleSeg * rhsbot;
	
	rule * next;
	rule * prev;

};


typedef struct {

	rule * top;
	rule * bot;	
	int rule_num;

	element ** trm; 
	int trm_num;
	element ** ntrm;
	int ntrm_num; 

	element * start;

} grammar;


typedef struct {

	element ** trm; 
	int trm_num;
	element ** ntrm;
	int ntrm_num; 

	element * start;

} firstAndFollowSets;


typedef struct pt parseToken;

struct pt {
	int terminalId;
	element * trmData;
	int ruleNo;
	rule * rl;

	parseToken * next;
};


typedef struct pl parseList;

struct pl {
	parseToken * top;
	int id;
	element * nTrmData;
	
	parseList * next;
};


typedef struct tn treeNode;

struct tn {

	// linkage 
	treeNode * parent;
	treeNode * childL;
	treeNode * childR;

	treeNode * next;
	treeNode * prev;

	element * id;

	symbolScope * scope;
	symbolEntry * se;

	char type[25];

	token * tptr;

	codeBlock * blk;

	char label[10];
	char temporary[5];

};


typedef struct sw stackWrapper;

struct sw {
	treeNode * ptr;
	
	stackWrapper * next;
};




#endif





#ifndef _tokenToNumMapping

#define _tokenToNumMapping

static char * ref[] = {/*0*/"DECLARE", "MODULE", "PRINT", "USE", "DRIVER", "PROGRAM", "WITH", "TAKES", "INPUT", "PARAMETERS",/*10*/ "AND", "RETURNS", "OR", "FOR", "INTEGER", "REAL", "BOOLEAN", "ARRAY", "START", "END",/*20*/ "GET_VALUE", "IN", "SWITCH", "TRUE", "FALSE", "CASE", "BREAK", "DEFAULT", "WHILE", "OF",/*30*/ "ID", "NUM", "RNUM", "EMPTY", "PLUS", "MINUS", "MUL", "DIV", "LT", "LE",/*40*/ "GT", "GE", "NE", "EQ", "DEF", "ENDDEF", "COLON", "RANGEOP", "SEMICOL", "COMMA",/*50*/ "ASSIGNOP", "SQBC", "SQBO", "BO", "BC", "COMMENTMARK", "ERROR", "EOF", "DRIVERDEF", "DRIVERENDDEF", "", "", "", ""};


#endif