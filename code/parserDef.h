

#ifndef _grammar

#define _grammar

typedef struct el element;

struct el{

	char val[25];
	int type;
	int occurances[20];
	int occ_num;

	element * next;

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

	element * trm[26]; 
	int trm_num;
	element * ntrm[26];
	int ntrm_num; 

} grammar;




#endif