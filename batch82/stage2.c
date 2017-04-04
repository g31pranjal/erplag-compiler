#include <stdio.h>
#include "lexerDef.h"
#include "parserDef.h"
#include "parser.c"
#include "lexer.c"


int removeTreeNode(treeNode * head, treeNode * child) {
	if(head->childL == child && head->childR == child) {
		head->childL = NULL;
		head->childR = NULL;
	}
	else if(head->childL == child) {
		head->childL = child->next;
		child->next->prev = NULL;
	}
	else if(head->childR == child) {
		head->childR = child->prev;
		child->prev->next = NULL;
	}
	else {
		child->prev->next = child->next;
		child->next->prev = child->prev;
	}
	free(child->tptr);
	free(child);
}

int constructAST(treeNode * head) {

	treeNode * child;

	int keep[] = {2/*PRINT*/, 10/*AND*/, 12/*OR*/, 13/*FOR*/, 14/*INTEGER*/, 15/*REAL*/, 16/*BOOLEAN*/, 17/*ARRAY*/, 20/*GET_VALUE*/, 23/*TRUE*/, 28/*WHILE*/, 30/*ID*/, 31/*NUM*/, 32/*RNUM*/, 34/*PLUS*/, 35/*MINUS*/, 36/*MUL*/, 37/*DIV*/, 38/*LT*/, 39/*LE*/, 40/*GT*/, 41/*GE*/, 42/*NE*/, 43/*EQ*/, 50/*ASSIGNOP*/};

	int i, toRemove, arrL = sizeof(keep)/sizeof(int);

	if(head->childL != NULL) {
		child = head->childL;
		while(child != NULL) {
			printf("%s . \n", child->id->val);

			if(child->id->id >= 0 && child->id->id < 100) {
				// terminal
				toRemove = 1;
				for(i=0;i<arrL;i++) {
					if(keep[i] == child->id->id) {
						toRemove = 0;
						break;
					}
				}
				if(toRemove) {
					printf(" -- removed\n");
					removeTreeNode(head, child);	
				}
			}
			else {
				constructAST(child);
				if(child->childL == NULL && child->childR == NULL)
					removeTreeNode(head, child);	
			}

			
			child = child->next;
		}
	}



}


int main() {

	char * filename = "testcases/testcase3.txt";
	char * writefn  = "out.put";

	grammar * gr = NULL;
	firstAndFollowSets * ff = NULL;
	parseList * tableHead = NULL;
	treeNode * head = NULL;

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

	constructAST(head);

	FILE * fp = fopen(writefn, "w+");
	printParseTree(gr, head, fp);
										
	fclose(fp);



}