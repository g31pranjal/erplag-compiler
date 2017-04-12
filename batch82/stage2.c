#include <stdio.h>
#include "lexerDef.h"
#include "parserDef.h"
#include "scopeDef.h"
#include "parser.c"
#include "lexer.c"
#include "ast.c"
#include "scope.c"










int main() {

	char * filename = "testcases/testcase5.txt";
	char * writefn  = "out.put";

	grammar * gr = NULL;
	firstAndFollowSets * ff = NULL;
	parseList * tableHead = NULL;
	treeNode * head = NULL;
	symbolScope * sHead = NULL;

	if(gr == NULL) {
		gr = readGrammarFromFile("grammar.txt");
	}
	if(ff == NULL) {
		ff = computeFirstAndFollowSets(gr);
	}
	if(tableHead == NULL) {
		tableHead = createParseTable(gr, ff);
	}
	if(head == NULL) {
		head = parseInputSourceCode(gr, filename, tableHead);
	}

	// FILE * fp = fopen(writefn, "w+");
	// printParseTree(head, fp);

	constructAST(head);

	// printAST(head);

	sHead = initScopeStructure(head);

	printScopeStructure(sHead);
										
	fclose(fp);



}