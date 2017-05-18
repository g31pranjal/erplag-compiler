/*
Batch no. 82

AUTHORS : 
Pranjal Gupta (2013B4A7470P)
Tanaya Jha (2013B3A7304P)
*/


#ifndef _codegenStruct

#define _codegenStruct


typedef struct c_ln codeLine;

struct c_ln {
	char line[100];
	codeLine * next;
};

typedef struct c_bl codeBlock;

struct c_bl {
	codeLine * top;
	codeLine * bot;
};


#endif