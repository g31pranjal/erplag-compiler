#include <stdio.h>
#include "lexerDef.h"
#include "parserDef.h"
#include "scopeDef.h"

#include "parser.c"
#include "lexer.c"
#include "ast.c"
#include "scope.c"
#include "semantics.c"



int main() {

	char * filename = "testcases/testcase3.txt";
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

	int errors;
	if(head == NULL) {
		head = parseInputSourceCode(gr, filename, tableHead, &errors);
		constructAST(head);
	}

	if(!errors) {
		sHead = initScopeStructure(head, &errors);
		// printScopeStructure(sHead);
		
		checkSemantics(head, &errors);
	}


	// printf("error reporting : %d\n", errors);









	// FILE * fp = fopen(writefn, "w+");
	// printParseTree(head, fp);

	// printParseTree(head, fp);

	// errors can arise in here 

	
	// checkSemantics(head);

	fclose(fp);

}