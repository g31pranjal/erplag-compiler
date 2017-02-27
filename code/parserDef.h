

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






#endif





#ifndef _tokenToNumMapping

#define _tokenToNumMapping

static char * ref[] = {"DECLARE", "MODULE", "PRINT", "USE", "DRIVER", "PROGRAM", "WITH", "TAKES", "INPUT", "PARAMETERS", "AND", "RETURNS", "OR", "FOR", "INTEGER", "REAL", "BOOLEAN", "ARRAY", "START", "END", "GET_VALUE", "IN", "SWITCH", "TRUE", "FALSE", "CASE", "BREAK", "DEFAULT", "WHILE", "OF", "ID", "NUM", "RNUM", "EMPTY", "PLUS", "MINUS", "MUL", "DIV", "LT", "LE", "GT", "GE", "NE", "EQ", "DEF", "ENDDEF", "COLON", "RANGEOP", "SEMICOL", "COMMA", "ASSIGNOP", "SQBC", "SQBO", "BO", "BC", "COMMENTMARK", "ERROR", "EOF", "DRIVERDEF", "DRIVERENDDEF", "", "", "", ""};


#endif