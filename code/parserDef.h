

#ifndef _grammar

#define _grammar

typedef struct el element;

struct el{

	char val[20];
	int type;

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

	element * trm[26]; 
	element * ntrm[26]; 

} grammar;




#endif