

#ifndef _token

#define _token

typedef struct {
	int id;
	char val[30];
	char lxm[25];
	int lno;
} token;

#endif



#ifndef _tokenToNumMapping

#define _tokenToNumMapping

static char * ref[] = {/*0*/"DECLARE", "MODULE", "PRINT", "USE", "DRIVER", "PROGRAM", "WITH", "TAKES", "INPUT", "PARAMETERS",/*10*/ "AND", "RETURNS", "OR", "FOR", "INTEGER", "REAL", "BOOLEAN", "ARRAY", "START", "END",/*20*/ "GET_VALUE", "IN", "SWITCH", "TRUE", "FALSE", "CASE", "BREAK", "DEFAULT", "WHILE", "OF",/*30*/ "ID", "NUM", "RNUM", "EMPTY", "PLUS", "MINUS", "MUL", "DIV", "LT", "LE",/*40*/ "GT", "GE", "NE", "EQ", "DEF", "ENDDEF", "COLON", "RANGEOP", "SEMICOL", "COMMA",/*50*/ "ASSIGNOP", "SQBC", "SQBO", "BO", "BC", "COMMENTMARK", "ERROR", "EOF", "DRIVERDEF", "DRIVERENDDEF", "", "", "", ""};


#endif