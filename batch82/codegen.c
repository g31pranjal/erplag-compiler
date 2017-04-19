#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "parserDef.h"

#include "codegenDef.h"

int LABEL = 1;
int TEMP_COUNT = 1;

char TEMP_BUF[5];
char LABEL_BUF[10];

char buffer[100];

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
	if(b->top != NULL && b->bot != NULL) {
		b->bot->next = a->top;
		a->top = b->top;
	}	
}


int printCodeBlock(codeBlock * blk) {

	codeLine * ln;
	ln = blk->top;

	while(ln != NULL) {
		printf("%s", ln->line);
		ln = ln->next;
	}
}

int printToFile(codeBlock * blk, FILE * fp) {

	codeLine * ln;
	ln = blk->top;

	while(ln != NULL) {
		fprintf(fp, "%s", ln->line);
		ln = ln->next;
	}
}


int codeGenIO(treeNode * ptr) {

	codeBlock * blk;
	
	if( strcmp(ptr->childL->id->val, "GET_VALUE") == 0 ) {
		
		blk = createCodeBlock();

		addCodeLine("\t; getting a value into a variable\n", blk);
		// message length, all messages are 4 bytes (word)
		addCodeLine("\tmov\tedx, 4\n", blk); 
		// file descriptor (stdout)
		addCodeLine("\tmov\teax, 3\n", blk);
		// system call number 
		addCodeLine("\tmov\tebx, 2\n", blk); 

		// *********************************** THIS HAS TO BE WORKED OUT ******************************************
		// message to write is copied to register ecx 
		addCodeLine("\tmov\tecx, 1\n", blk); 

		addCodeLine("\tint\t80h\n", blk);

	}
	else if( strcmp(ptr->childL->id->val, "PRINT") == 0 ) {
		
		blk = createCodeBlock();

		addCodeLine("\t; printing a value\n", blk);
		// message length, all messages are 4 bytes (word)
		addCodeLine("\tmov\tedx, 4\n", blk); 
		// file descriptor (stdout)
		addCodeLine("\tmov\teax, 4\n", blk);
		// system call number 
		addCodeLine("\tmov\tebx, 1\n", blk); 

		// *********************************** THIS HAS TO BE WORKED OUT ******************************************
		// message to write is copied to register ecx 
		addCodeLine("\tmov\tecx, 1\n", blk); 

		addCodeLine("\tint\t80h\n", blk);

		ptr->blk = blk;

	}
	else {
		// error in AST.
	}
}

int codeGenAssg(treeNode * ptr) {
	// this function gets only the <assignmentStmt>
	codeBlock * blk;
	blk = createCodeBlock();

	treeNode * child;
	child = ptr->childL;

	if( strcmp(child->next->id->val, "<expression>") == 0 ) {
		addCodeLine("\t;assignment expression\n", blk);
		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov %s, %s\n", ptr->childL->se->temporary, child->next->temporary);
		addCodeLine(buffer, blk);
	}
	else {
		// handle array element 
	}

	mergeCodeBlocks(blk, child->next->blk);
	ptr->blk = blk;

}

int codeGenSwitch(treeNode * ptr) {
	
}

int codeGenExprRec(treeNode * ptr) {

	// printf("reaching exp rec\n");
	// printf("ptr : %s\n", ptr->id->val);

	codeBlock * blk;
	blk = createCodeBlock();
	char tmpl1[10],  tmpl2[10];

	if( strcmp(ptr->id->val, "PLUS") == 0 ) {

		codeGenExprRec(ptr->childL);
		codeGenExprRec(ptr->childR);

		addCodeLine("\t;adding two numbers\n", blk);
		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov eax, %s\n", ptr->childL->temporary);
		addCodeLine(buffer, blk);
		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov ebx, %s\n", ptr->childR->temporary);
		addCodeLine(buffer, blk);
		addCodeLine("\tadd eax, ebx\n", blk);
		getTemporary();
		strcpy(ptr->temporary, TEMP_BUF);
		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov %s, eax\n", ptr->temporary);
		addCodeLine(buffer, blk);
		addCodeLine("\n", blk);

		mergeCodeBlocks(blk, ptr->childL->blk);
		mergeCodeBlocks(blk, ptr->childR->blk);

	}
	else if( strcmp(ptr->id->val, "MINUS") == 0 ) {

		codeGenExprRec(ptr->childL);
		codeGenExprRec(ptr->childR);

		addCodeLine("\t;substracting two numbers\n", blk);
		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov eax, %s\n", ptr->childL->temporary);
		addCodeLine(buffer, blk);
		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov ebx, %s\n", ptr->childR->temporary);
		addCodeLine(buffer, blk);
		addCodeLine("\tsub eax, ebx\n", blk);
		getTemporary();
		strcpy(ptr->temporary, TEMP_BUF);
		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov %s, eax\n", ptr->temporary);
		addCodeLine(buffer, blk);
		addCodeLine("\n", blk);

		mergeCodeBlocks(blk, ptr->childL->blk);
		mergeCodeBlocks(blk, ptr->childR->blk);

	}
	else if( strcmp(ptr->id->val, "MUL") == 0 ) {

		codeGenExprRec(ptr->childL);
		codeGenExprRec(ptr->childR);

		addCodeLine("\t;multiplying two numbers\n", blk);
		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov eax, %s\n", ptr->childL->temporary);
		addCodeLine(buffer, blk);
		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov ebx, %s\n", ptr->childR->temporary);
		addCodeLine(buffer, blk);
		addCodeLine("\timul ebx\n", blk);
		getTemporary();
		strcpy(ptr->temporary, TEMP_BUF);
		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov %s, eax\n", ptr->temporary);
		addCodeLine(buffer, blk);
		addCodeLine("\n", blk);

		mergeCodeBlocks(blk, ptr->childL->blk);
		mergeCodeBlocks(blk, ptr->childR->blk);

	}
	else if( strcmp(ptr->id->val, "DIV") == 0 ) {

		codeGenExprRec(ptr->childL);
		codeGenExprRec(ptr->childR);

		addCodeLine("\t;dividing two numbers\n", blk);
		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov eax, %s\n", ptr->childL->temporary);
		addCodeLine(buffer, blk);
		addCodeLine("\tmov edx, 0\n", blk);
		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov ebx, %s\n", ptr->childR->temporary);
		addCodeLine(buffer, blk);
		addCodeLine("\tidiv ebx\n", blk);
		getTemporary();
		strcpy(ptr->temporary, TEMP_BUF);
		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov %s, eax\n", ptr->temporary);
		addCodeLine(buffer, blk);
		addCodeLine("\n", blk);

		mergeCodeBlocks(blk, ptr->childL->blk);
		mergeCodeBlocks(blk, ptr->childR->blk);

	}
	else if( strcmp(ptr->id->val, "LE") == 0 ) {

		codeGenExprRec(ptr->childL);
		codeGenExprRec(ptr->childR);

		addCodeLine("\t;comparing two numbers\n", blk);
		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov eax %s\n", ptr->childL->temporary);
		addCodeLine(buffer, blk);
		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov ebx %s\n", ptr->childR->temporary);
		addCodeLine(buffer, blk);
		addCodeLine("\tcmp eax, ebx\n", blk);

		getLabel();
		strcpy(tmpl1, LABEL_BUF);

		memset(buffer, 0, 100);
		sprintf(buffer, "\tjle %s\n", tmpl1);
		addCodeLine(buffer, blk);

		getTemporary();
		strcpy(ptr->temporary, TEMP_BUF);
		
		// false
		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov %s, 0\n", ptr->temporary);
		addCodeLine(buffer, blk);
		
		getLabel();
		strcpy(tmpl2, LABEL_BUF);

		memset(buffer, 0, 100);
		sprintf(buffer, "\tjmp %s\n", tmpl2);
		addCodeLine(buffer, blk);

		memset(buffer, 0, 100);
		sprintf(buffer, "%s :\n", tmpl1);
		addCodeLine(buffer, blk);

		// true	
		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov %s, 1\n", ptr->temporary);
		addCodeLine(buffer, blk);

		memset(buffer, 0, 100);
		sprintf(buffer, "%s :\n", tmpl2);
		addCodeLine(buffer, blk);
	}
	else if( strcmp(ptr->id->val, "LT") == 0 ) {

		codeGenExprRec(ptr->childL);
		codeGenExprRec(ptr->childR);

		addCodeLine("\t;comparing two numbers\n", blk);
		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov eax %s\n", ptr->childL->temporary);
		addCodeLine(buffer, blk);
		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov ebx %s\n", ptr->childR->temporary);
		addCodeLine(buffer, blk);
		addCodeLine("\tcmp eax, ebx\n", blk);

		getLabel();
		strcpy(tmpl1, LABEL_BUF);

		memset(buffer, 0, 100);
		sprintf(buffer, "\tjl %s\n", tmpl1);
		addCodeLine(buffer, blk);

		getTemporary();
		strcpy(ptr->temporary, TEMP_BUF);
		
		// false
		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov %s, 0\n", ptr->temporary);
		addCodeLine(buffer, blk);
		
		getLabel();
		strcpy(tmpl2, LABEL_BUF);

		memset(buffer, 0, 100);
		sprintf(buffer, "\tjmp %s\n", tmpl2);
		addCodeLine(buffer, blk);

		memset(buffer, 0, 100);
		sprintf(buffer, "%s :\n", tmpl1);
		addCodeLine(buffer, blk);

		// true	
		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov %s, 1\n", ptr->temporary);
		addCodeLine(buffer, blk);

		memset(buffer, 0, 100);
		sprintf(buffer, "%s :\n", tmpl2);
		addCodeLine(buffer, blk);
	}
	else if( strcmp(ptr->id->val, "GE") == 0 ) {

		codeGenExprRec(ptr->childL);
		codeGenExprRec(ptr->childR);

		addCodeLine("\t;comparing two numbers\n", blk);
		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov eax %s\n", ptr->childL->temporary);
		addCodeLine(buffer, blk);
		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov ebx %s\n", ptr->childR->temporary);
		addCodeLine(buffer, blk);
		addCodeLine("\tcmp eax, ebx\n", blk);

		getLabel();
		strcpy(tmpl1, LABEL_BUF);

		memset(buffer, 0, 100);
		sprintf(buffer, "\tjge %s\n", tmpl1);
		addCodeLine(buffer, blk);

		getTemporary();
		strcpy(ptr->temporary, TEMP_BUF);
		
		// false
		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov %s, 0\n", ptr->temporary);
		addCodeLine(buffer, blk);
		
		getLabel();
		strcpy(tmpl2, LABEL_BUF);

		memset(buffer, 0, 100);
		sprintf(buffer, "\tjmp %s\n", tmpl2);
		addCodeLine(buffer, blk);

		memset(buffer, 0, 100);
		sprintf(buffer, "%s :\n", tmpl1);
		addCodeLine(buffer, blk);

		// true	
		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov %s, 1\n", ptr->temporary);
		addCodeLine(buffer, blk);

		memset(buffer, 0, 100);
		sprintf(buffer, "%s :\n", tmpl2);
		addCodeLine(buffer, blk);
	}
	else if( strcmp(ptr->id->val, "GT") == 0 ) {

		codeGenExprRec(ptr->childL);
		codeGenExprRec(ptr->childR);

		addCodeLine("\t;comparing two numbers\n", blk);
		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov eax %s\n", ptr->childL->temporary);
		addCodeLine(buffer, blk);
		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov ebx %s\n", ptr->childR->temporary);
		addCodeLine(buffer, blk);
		addCodeLine("\tcmp eax, ebx\n", blk);

		getLabel();
		strcpy(tmpl1, LABEL_BUF);

		memset(buffer, 0, 100);
		sprintf(buffer, "\tjg %s\n", tmpl1);
		addCodeLine(buffer, blk);

		getTemporary();
		strcpy(ptr->temporary, TEMP_BUF);
		
		// false
		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov %s, 0\n", ptr->temporary);
		addCodeLine(buffer, blk);
		
		getLabel();
		strcpy(tmpl2, LABEL_BUF);

		memset(buffer, 0, 100);
		sprintf(buffer, "\tjmp %s\n", tmpl2);
		addCodeLine(buffer, blk);

		memset(buffer, 0, 100);
		sprintf(buffer, "%s :\n", tmpl1);
		addCodeLine(buffer, blk);

		// true	
		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov %s, 1\n", ptr->temporary);
		addCodeLine(buffer, blk);

		memset(buffer, 0, 100);
		sprintf(buffer, "%s :\n", tmpl2);
		addCodeLine(buffer, blk);
	}
	else if( strcmp(ptr->id->val, "NE") == 0 ) {

		codeGenExprRec(ptr->childL);
		codeGenExprRec(ptr->childR);

		addCodeLine("\t;comparing two numbers\n", blk);
		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov eax %s\n", ptr->childL->temporary);
		addCodeLine(buffer, blk);
		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov ebx %s\n", ptr->childR->temporary);
		addCodeLine(buffer, blk);
		addCodeLine("\tcmp eax, ebx\n", blk);

		getLabel();
		strcpy(tmpl1, LABEL_BUF);

		memset(buffer, 0, 100);
		sprintf(buffer, "\tjne %s\n", tmpl1);
		addCodeLine(buffer, blk);

		getTemporary();
		strcpy(ptr->temporary, TEMP_BUF);
		
		// false
		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov %s, 0\n", ptr->temporary);
		addCodeLine(buffer, blk);
		
		getLabel();
		strcpy(tmpl2, LABEL_BUF);

		memset(buffer, 0, 100);
		sprintf(buffer, "\tjmp %s\n", tmpl2);
		addCodeLine(buffer, blk);

		memset(buffer, 0, 100);
		sprintf(buffer, "%s :\n", tmpl1);
		addCodeLine(buffer, blk);

		// true	
		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov %s, 1\n", ptr->temporary);
		addCodeLine(buffer, blk);

		memset(buffer, 0, 100);
		sprintf(buffer, "%s :\n", tmpl2);
		addCodeLine(buffer, blk);
	}
	else if( strcmp(ptr->id->val, "EQ") == 0 ) {

		codeGenExprRec(ptr->childL);
		codeGenExprRec(ptr->childR);

		addCodeLine("\t;comparing two numbers", blk);
		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov eax %s\n", ptr->childL->temporary);
		addCodeLine(buffer, blk);
		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov ebx %s\n", ptr->childR->temporary);
		addCodeLine(buffer, blk);
		addCodeLine("\tcmp eax, ebx", blk);

		getLabel();
		strcpy(tmpl1, LABEL_BUF);

		memset(buffer, 0, 100);
		sprintf(buffer, "\tje %s\n", tmpl1);
		addCodeLine(buffer, blk);

		getTemporary();
		strcpy(ptr->temporary, TEMP_BUF);
		
		// false
		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov %s, 0\n", ptr->temporary);
		addCodeLine(buffer, blk);
		
		getLabel();
		strcpy(tmpl2, LABEL_BUF);

		memset(buffer, 0, 100);
		sprintf(buffer, "\tjmp %s\n", tmpl2);
		addCodeLine(buffer, blk);

		memset(buffer, 0, 100);
		sprintf(buffer, "%s :\n", tmpl1);
		addCodeLine(buffer, blk);

		// true	
		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov %s, 1\n", ptr->temporary);
		addCodeLine(buffer, blk);

		memset(buffer, 0, 100);
		sprintf(buffer, "%s :\n", tmpl2);
		addCodeLine(buffer, blk);
	}
	else if( strcmp(ptr->id->val, "AND") == 0 ) {	
		// logic for handling AND

	}
	else if( strcmp(ptr->id->val, "OR") == 0 ) {
		// logic for handling OR
	
	}
	else if( strcmp(ptr->id->val, "<var>") == 0 ) {
		if( strcmp(ptr->childL->id->val, "ID") == 0 ) {
			if(ptr->childL->se->isArray == 0) {
				strcpy(ptr->temporary, ptr->childL->se->temporary);
			}
			else {
				// handle arrays
			}
		}
		else if( strcmp(ptr->childL->id->val, "RNUM") == 0 ) {
			getTemporary();
			strcpy(ptr->temporary, TEMP_BUF);
			memset(buffer, 0, 100);
			sprintf(buffer, "\tmov %s, %s\n", ptr->temporary, ptr->childL->tptr->val);
			addCodeLine(buffer, blk);
			addCodeLine("\n", blk);

		}
		else if( strcmp(ptr->childL->id->val, "NUM") == 0 ) {
			getTemporary();
			strcpy(ptr->temporary, TEMP_BUF);
			memset(buffer, 0, 100);
			sprintf(buffer, "\tmov %s, %s\n", ptr->temporary, ptr->childL->tptr->val);
			addCodeLine(buffer, blk);
			addCodeLine("\n", blk);
		}
	}
	ptr->blk = blk;
}


int codeGenExpr(treeNode * ptr) {
	// outer Expr function that differentiates between the two cases.
	if( ptr->childL == ptr->childR ) {
		codeGenExprRec(ptr->childL);
		strcpy(ptr->temporary, ptr->childL->temporary);
		
		// empty block for expression
		codeBlock * blk;
		blk = createCodeBlock();
		ptr->blk = blk;

	}
	else {
		codeGenExprRec(ptr->childR);
		// additional code (add a negative sign)
	}
}


int codeGenIter(treeNode * ptr) {

	codeBlock * blk, * sBlk, * eBlk;
	blk = createCodeBlock();

	treeNode * child;
	child = ptr->childL;

	char l1[10], l2[10];

	if( strcmp(child->id->val, "FOR") == 0 ) {
		// code addition for the FOR construct
		addCodeLine("\t;iterative for loop\n", blk);
		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov %s, %d\n", child->next->se->temporary, atoi(child->next->next->childR->tptr->val) - atoi(child->next->next->childL->tptr->val) );
		addCodeLine(buffer, blk);
		
		getLabel();
		strcpy(l1, LABEL_BUF);

		memset(buffer, 0, 100);
		sprintf(buffer, "%s:\n", l1 );
		addCodeLine(buffer, blk);
		
		if( strcmp(ptr->childR->id->val, "<statements>") == 0 ) {
			sBlk = ptr->childR->blk;
			blk->bot->next = sBlk->top;
			blk->bot = sBlk->bot;	
		}
		else {
			// empty for loop
		}

		memset(buffer, 0, 100);
		sprintf(buffer, "\tdec %s\n", child->next->se->temporary );
		addCodeLine(buffer, blk);

		memset(buffer, 0, 100);
		sprintf(buffer, "\tjnz %s\n", l1 );
		addCodeLine(buffer, blk);

	}
	else if( strcmp(child->id->val, "WHILE") == 0 ) {
		
		// label 1
		// expr
		// if 0 jmp label2
		// statements
		// jmp label 1
		// label 2

		addCodeLine("\t;iterative while loop\n", blk);

		getLabel();
		strcpy(l1, LABEL_BUF);

		getLabel();
		strcpy(l2, LABEL_BUF);

		memset(buffer, 0, 100);
		sprintf(buffer, "%s :\n", l1 );
		addCodeLine(buffer, blk);

		codeGenExprRec(child->next);
		eBlk = child->next->blk;

		blk->bot->next = eBlk->top;
		blk->bot = eBlk->bot;

		memset(buffer, 0, 100);
		sprintf(buffer, "\tcmp %s, 0\n", child->next->temporary);
		addCodeLine(buffer, blk);

		memset(buffer, 0, 100);
		sprintf(buffer, "\tje %s\n", l2);
		addCodeLine(buffer, blk);
		addCodeLine("\n", blk);

		if( strcmp(ptr->childR->id->val, "<statements>") == 0 ) {
			sBlk = ptr->childR->blk;
			blk->bot->next = sBlk->top;
			blk->bot = sBlk->bot;	
		}
		else {
			// empty for loop
		}

		memset(buffer, 0, 100);
		sprintf(buffer, "\tjmp %s\n", l1);
		addCodeLine(buffer, blk);

		memset(buffer, 0, 100);
		sprintf(buffer, "%s :\n", l2);
		addCodeLine(buffer, blk);

		// printf("%s\n", child->next->id->val);
		printCodeBlock(blk);


	}
	else {
		// error in AST.
	}
}


int codeGenStmts(treeNode * ptr) {

	codeBlock * blk;
	blk = createCodeBlock();

	addCodeLine("\t;statements", blk);
	addCodeLine("\n", blk);
	addCodeLine("\n", blk);

	ptr->blk = blk;
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
		else if( strcmp(child->id->val, "<statements>") == 0 ) {
			codeGenStmts(child);
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


int codeGenInit(treeNode * head, symbolScope * sHead, FILE * fp) {

	treeNode * stmts;
	int i;
	char buffer[100];

	// checking the validity
	if( head->childL != head->childR ) {
		// error. we are considering only the case with driver function
	}
	else {

		
		// map variables to temporaries 
		addTemporaries(sHead->childL);
		
		printScopeStructure(sHead);

		// recurse over the AST to generate code blocks
		stmts = head->childL->childL;
		codeGenRec(stmts);

		// prepare header
		codeBlock * header;
		header = createCodeBlock();
		addCodeLine("\n", header);
		addCodeLine("section .bss\n", header);
		for(int i=1;i<TEMP_COUNT;i++) {
			memset(buffer, 0, 100);
			sprintf(buffer, "\tri%d\tdw\t0\n", i);
			addCodeLine(buffer, header);
		}
		addCodeLine("\n", header);
		addCodeLine("section .text\n", header);
		addCodeLine("\tglobal _start\n", header);
		addCodeLine("_start : \n", header);

		// printCodeBlock(header);
		
		// merge blocks from statements 
		;

		// dump the entire thing to file
		printToFile(header, fp);

	}
}


