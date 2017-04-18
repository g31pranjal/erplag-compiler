#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "parserDef.h"

#include "codegenDef.h"

int LABEL = 1;
int TEMP_COUNT = 1;

char TEMP_BUF[5];
char LABEL_BUF[10];


int getTemporary() {
	memset(TEMP_BUF, 0, 5);
	sprintf(TEMP_BUF, "ri%d", TEMP_COUNT++);
}


int getLabel() {
	memset(LABEL_BUF, 0, 10);
	sprintf(LABEL_BUF, "label%d", LABEL++);
}


codeBlock * createCodeBlock() {

	codeBlock * new;
	new = (codeBlock *)malloc(sizeof(codeBlock));
	new->top = new->bot = NULL;

	return new;
}


int addCodeLine(char * buffer, codeBlock * cb) {

	codeLine * new;
	new = (codeLine *)malloc(sizeof(codeLine));
	new->next = NULL;
	memset(new->line, 0, 100);
	strcpy(new->line, buffer);

	if(cb->top == NULL && cb->bot == NULL) {
		cb->top = new;
		cb->bot = new;
	}
	else {
		cb->bot->next = new;
		cb->bot = new;
	}
}


int mergeCodeBlocks(codeBlock * a, codeBlock * b) {
	
	a->bot->next = b->top;
	a->bot = b->bot;
}


int printCodeBlock(codeBlock * blk) {

	codeLine * ln;
	ln = blk->top;

	while(ln != NULL) {
		printf("%s\n", ln->line);
		ln = ln->next;
	}
}


int codeGenIO(treeNode * ptr) {

	if( strcmp(ptr->childL->id->val, "GET_VALUE") == 0 ) {
		// code addition for GET_VALUE thing
	}
	else if( strcmp(ptr->childL->id->val, "PRINT") == 0 ) {
		// code addition for PRINT thing
	}
	else {
		// error in AST.
	}
}

int codeGenAssg(treeNode * ptr) {

}

int codeGenSwitch(treeNode * ptr) {

}

int codeGenIter(treeNode * ptr) {
	if( strcmp(ptr->childL->id->val, "FOR") == 0 ) {
		// code addition for the FOR construct
	}
	else if( strcmp(ptr->childL->id->val, "PRINT") == 0 ) {
		// code addition for the WHILE construct
	}
	else {
		// error in AST.
	}
}

int codeGenExprRec(treeNode * ptr) {

	if( strcmp(ptr->id->val, "PLUS") == 0 ) {

	}
	else if( strcmp(ptr->id->val, "MINUS") == 0 ) {
		
	}
	else if( strcmp(ptr->id->val, "MUL") == 0 ) {
		
	}
	else if( strcmp(ptr->id->val, "DIV") == 0 ) {
		
	}
	else if( strcmp(ptr->id->val, "LE") == 0 ) {
		
	}
	else if( strcmp(ptr->id->val, "LT") == 0 ) {
		
	}
	else if( strcmp(ptr->id->val, "GE") == 0 ) {
		
	}
	else if( strcmp(ptr->id->val, "GT") == 0 ) {
		
	}
	else if( strcmp(ptr->id->val, "NE") == 0 ) {
		
	}
	else if( strcmp(ptr->id->val, "EQ") == 0 ) {
		
	}
	else if( strcmp(ptr->id->val, "AND") == 0 ) {
		
	}
	else if( strcmp(ptr->id->val, "OR") == 0 ) {
		
	}
	else if( strcmp(ptr->id->val, "LE") == 0 ) {
		
	}
	else if( strcmp(ptr->id->val, "<var>") == 0 ) {
		
	}

}

int codeGenExpr(treeNode * ptr) {
	// outer Expr function that differentiates between the two cases.
	if( ptr->childL == ptr->childR ) {
		codeGenExprRec(ptr->childL);
		// additional code
	}
	else {
		codeGenExprRec(ptr->childR);
		// additional code (add a negative sign)
	}
}

int codeGenRec(treeNode * ptr) {

	treeNode * child;
	child = ptr->childL;

	while(child != NULL) {

		// for bottom-up parsing, call recursion 
		codeGenRec(child);

		if( strcmp(child->id->val, "<ioStmt>") == 0 ) {
			codeGenIO(child);
		}
		else if( strcmp(child->id->val, "<simpleStmt>") == 0 ) {
			// passing its child <assignmentStmt> as the parameter.
			codeGenAssg(child->childL);
		}
		else if( strcmp(child->id->val, "<condionalStmt>") == 0 ) {
			codeGenSwitch(child);
		}
		else if( strcmp(child->id->val, "<iterativeStmt>") == 0 ) {
			codeGenIter(child);
		}
		else if( strcmp(child->id->val, "<expression>") == 0 ) {
			codeGenExpr(child);
		}

		child = child->next;
	}

}


int addTemporaries(symbolScope * head) {

	symbolScope * child;
	symbolEntry * se;
	se = head->seHead;
	child = head->childL;

	while(se != NULL) {
		getTemporary();
		strcpy(se->temporary, TEMP_BUF);
		se = se->next;
	}

	while(child != NULL) {
		addTemporaries(child);
		child = child->next;
	}
}


int codeGenInit(treeNode * head, symbolScope * sHead) {

	treeNode * stmts;

	// checking the validity
	if( head->childL != head->childR ) {
		// error. we are considering only the case with driver function
	}
	else {

		// the entire logic code is available here. 
		// this code has to be merged with the code for variable allotment and _start. 

		addTemporaries(sHead->childL);
		printf("ad\n");
		printScopeStructure(sHead);

		codeBlock * header;

		header = createCodeBlock();

		addCodeLine("global _start", header);
		addCodeLine("\n", header);
		addCodeLine("section .bss", header);
		addCodeLine("\n", header);
		addCodeLine("section .text", header);
		addCodeLine("_start : ", header);

		// printCodeBlock(header);

		// printf("\n\n");

		stmts = head->childL->childL->childL;

		// merge blocks from statements 

		// dump the entire thing to file

		codeGenRec(stmts);
	}
}


