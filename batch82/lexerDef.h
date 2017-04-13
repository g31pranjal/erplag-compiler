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