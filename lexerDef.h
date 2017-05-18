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
// for bold text, black colored
#define BOLDBLACK   "\033[1m\033[30m"      
#endif

#ifndef BOLDRED
// for bold text, red colored
#define BOLDRED     "\033[1m\033[31m" 
#endif

#ifndef BOLDGREEN
// for bold text, green colored
#define BOLDGREEN   "\033[1m\033[32m"   
#endif

#ifndef BOLDYELLOW
// for bold text, yellow colored
#define BOLDYELLOW  "\033[1m\033[33m"    
#endif

#ifndef BOLDBLUE
// for bold text, blue colored
#define BOLDBLUE    "\033[1m\033[34m"  
#endif

#ifndef BOLDMAGENTA
// for bold text, magenta colored
#define BOLDMAGENTA "\033[1m\033[35m"     
#endif

#ifndef BOLDCYAN
// for bold text, cyan colored
#define BOLDCYAN    "\033[1m\033[36m"  
#endif

#ifndef BOLDWHITE
// for bold text, white colored
#define BOLDWHITE   "\033[1m\033[37m"   
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