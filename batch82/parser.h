/*
Batch no. 82

AUTHORS : 
Pranjal Gupta (2013B4A7470P)
Tanaya Jha (2013B3A7304P)
*/

#include "lexerDef.h"
#include "parserDef.h"
#include "lexer.h"


extern grammar * readGrammarFromFile(char * filename);

extern firstAndFollowSets * computeFirstAndFollowSets(grammar * gr);

extern parseList * createParseTable(grammar * gr, firstAndFollowSets * ff);

extern treeNode * parseInputSourceCode(grammar * gr, char *filename, parseList * pl, int * errors);

extern int printParseTreeOring(treeNode * head);

extern int countNodes(treeNode * head, int * count);
