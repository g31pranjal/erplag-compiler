/*
Batch no. 82

AUTHORS : 
Pranjal Gupta (2013B4A7470P)
Tanaya Jha (2013B3A7304P)
*/

/*
	Generates the NASM-assembly code of the source code. 
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "parserDef.h"

#include "codegenDef.h"


int LABEL = 1;
int TEMP_COUNT = 1;
int TEMP_LOCAL = 1;

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
	treeNode * var;
	
	if( strcmp(ptr->childL->id->val, "GET_VALUE") == 0 ) {
		
		blk = createCodeBlock();

		addCodeLine("\t; getting a value into a variable\n", blk);
		// setup stack frame 
		addCodeLine("\tpush rbp\n", blk); 
		// move printing format
		addCodeLine("\tmov rdi, s_fmt\n", blk);
		addCodeLine("\tmov rax, 0\n", blk);
		

		// handle arrays

		
		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov rsi, %s\n", ptr->childL->next->se->temporary);
		addCodeLine(buffer, blk);
		
		addCodeLine("\tcall scanf\n", blk);
		addCodeLine("\tpop rbp\n", blk);

	}
	else if( strcmp(ptr->childL->id->val, "PRINT") == 0 ) {
		
		blk = createCodeBlock();

		addCodeLine("\t; printing a value\n", blk);
		// setup stack frame 
		addCodeLine("\tpush rbp\n", blk); 
		// move printing format
		addCodeLine("\tmov rdi, p_fmt\n", blk);
		addCodeLine("\tmov rax, 0\n", blk);
		
		if( strcmp(ptr->childL->next->id->val, "<var>") == 0 ) {
			var = ptr->childL->next;
			if( strcmp(var->childL->id->val, "ID") == 0 ) {
				if(var->childL->se->isArray == 0) {
					memset(buffer, 0, 100);
					sprintf(buffer, "\tmov rsi, [%s]\n", var->childL->se->temporary);
					addCodeLine(buffer, blk);
				}
				else {

					if( strcmp(var->childL->next->childL->id->val, "NUM") == 0 ) {
						memset(buffer, 0, 100);
						sprintf(buffer, "\tmov ebx, dword %s\n", var->childL->next->childL->tptr->val);
						addCodeLine(buffer, blk);							
					}
					else {
						memset(buffer, 0, 100);
						sprintf(buffer, "\tmov ebx, [%s]\n", var->childL->next->childL->se->temporary);
						addCodeLine(buffer, blk);							
					}

					memset(buffer, 0, 100);
					sprintf(buffer, "\tmov rsi, [%s + 4*ebx]\n", var->childL->se->temporary);
					addCodeLine(buffer, blk);	
				}
			}
			else if( strcmp(var->childL->id->val, "RNUM") == 0 ) {
				memset(buffer, 0, 100);
				sprintf(buffer, "\tmov rsi, dword %s\n", var->childL->tptr->val);
				addCodeLine(buffer, blk);	
			}
			else if( strcmp(var->childL->id->val, "NUM") == 0 ) {
				memset(buffer, 0, 100);
				sprintf(buffer, "\tmov rsi, dword %s\n", var->childL->tptr->val);
				addCodeLine(buffer, blk);
			}
		}

		addCodeLine("\tcall printf\n", blk);
		addCodeLine("\tpop rbp\n", blk);


	}
	else {
		// error in AST.
	}

	ptr->blk = blk;
}


int codeGenAssg(treeNode * ptr) {
	// this function gets only the <assignmentStmt>
	codeBlock * blk;
	blk = createCodeBlock();

	treeNode * child, * exp, *ind;
	child = ptr->childL;

	if( strcmp(child->next->id->val, "<expression>") == 0 ) {
		addCodeLine("\t;assignment expression\n", blk);
	
		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov eax, [%s]\n", child->next->temporary);
		addCodeLine(buffer, blk);

		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov [%s], eax\n", ptr->childL->se->temporary);
		addCodeLine(buffer, blk);
	
		mergeCodeBlocks(blk, child->next->blk);
	}
	else {
		ind = child->next;
		exp = child->next->next;

		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov eax, [%s]\n", exp->temporary);
		addCodeLine(buffer, blk);

		if( strcmp(ind->childL->id->val, "ID") == 0 ) {

			memset(buffer, 0, 100);
			sprintf(buffer, "\tmov ebx, [%s]\n", ind->childL->se->temporary);
			addCodeLine(buffer, blk);
			memset(buffer, 0, 100);
			sprintf(buffer, "\tmov [%s + 4*ebx], eax\n", ptr->childL->se->temporary);
			addCodeLine(buffer, blk);

		}
		else {

			memset(buffer, 0, 100);
			sprintf(buffer, "\tmov ebx, dword %s\n", ind->childL->tptr->val);
			addCodeLine(buffer, blk);

			memset(buffer, 0, 100);
			sprintf(buffer, "\tmov [%s + 4*ebx], eax\n", ptr->childL->se->temporary);
			addCodeLine(buffer, blk);

		}

		mergeCodeBlocks(blk, child->next->next->blk);

	}

	ptr->blk = blk;
	ptr->parent->blk = blk;
}


int codeGenSwitch(treeNode * ptr) {
	// have to complete

	codeBlock * blk, *sBlk, *dBlk;
	blk = createCodeBlock();

	treeNode * id, * cSt, * cStc;
	id = ptr->childL;
	cSt = id->next;

	char l1[10], lf[10];

	if(cSt != NULL) {

		cStc = cSt->childL; 

		getLabel();
		strcpy(lf, LABEL_BUF);

		getLabel();
		strcpy(l1, LABEL_BUF);

		memset(buffer, 0, 100);
		sprintf(buffer, "%s :\n", l1);
		addCodeLine(buffer, blk);

		if( strcmp(cStc->id->val, "<value>") == 0 ) {
			
			while(cStc != NULL) {

				if(strcmp(cStc->childL->id->val, "NUM") == 0) {
					addCodeLine("\t; a case begins\n", blk);
					memset(buffer, 0, 100);
					sprintf(buffer, "\tcmp [%s], dword %s\n", id->se->temporary, cStc->childL->tptr->val);
					addCodeLine(buffer, blk);

					getLabel();
					strcpy(l1, LABEL_BUF);

					memset(buffer, 0, 100);
					sprintf(buffer, "\tjne %s\n", l1);
					addCodeLine(buffer, blk);
				}
				else if(strcmp(cStc->childL->id->val, "TRUE") == 0) {
					memset(buffer, 0, 100);
					sprintf(buffer, "\tcmp [%s], dword 1\n", id->se->temporary);
					addCodeLine(buffer, blk);

					getLabel();
					strcpy(l1, LABEL_BUF);

					memset(buffer, 0, 100);
					sprintf(buffer, "\tjne %s\n", l1);
					addCodeLine(buffer, blk);
				}
				if(strcmp(cStc->childL->id->val, "FALSE") == 0) {
					memset(buffer, 0, 100);
					sprintf(buffer, "\tcmp [%s], dword 0\n", id->se->temporary);
					addCodeLine(buffer, blk);

					getLabel();
					strcpy(l1, LABEL_BUF);

					memset(buffer, 0, 100);
					sprintf(buffer, "\tjne %s\n", l1);
					addCodeLine(buffer, blk);
				}
		
				cStc = cStc->next;

				if( strcmp(cStc->id->val, "<statements>") == 0 ) {
					sBlk = cStc->blk;

					blk->bot->next = sBlk->top;
					blk->bot = sBlk->bot;

					memset(buffer, 0, 100);
					sprintf(buffer, "\tjmp %s\n", lf);
					addCodeLine(buffer, blk);

					addCodeLine("\n", blk);

					memset(buffer, 0, 100);
					sprintf(buffer, "%s :\n", l1);
					addCodeLine(buffer, blk);
				}

				cStc = cStc->next;
			}

			
		} 
	}
	else {
		// no case statements found.
	}

	if(cSt->next != NULL && strcmp(cSt->next->id->val, "<default>") == 0  ) {
		dBlk = cSt->next->childL->blk;

		blk->bot->next = dBlk->top;
		blk->bot = dBlk->bot;
	}

	memset(buffer, 0, 100);
	sprintf(buffer, "%s :\n", lf);
	addCodeLine(buffer, blk);

	ptr->blk = blk;
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
		sprintf(buffer, "\tmov eax, [%s]\n", ptr->childL->temporary);
		addCodeLine(buffer, blk);
		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov ebx, [%s]\n", ptr->childR->temporary);
		addCodeLine(buffer, blk);
		addCodeLine("\tadd eax, ebx\n", blk);
		getTemporary();
		strcpy(ptr->temporary, TEMP_BUF);
		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov [%s], eax\n", ptr->temporary);
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
		sprintf(buffer, "\tmov eax, [%s]\n", ptr->childL->temporary);
		addCodeLine(buffer, blk);
		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov ebx, [%s]\n", ptr->childR->temporary);
		addCodeLine(buffer, blk);
		addCodeLine("\tsub eax, ebx\n", blk);
		getTemporary();
		strcpy(ptr->temporary, TEMP_BUF);
		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov [%s], eax\n", ptr->temporary);
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
		sprintf(buffer, "\tmov eax, [%s]\n", ptr->childL->temporary);
		addCodeLine(buffer, blk);
		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov ebx, [%s]\n", ptr->childR->temporary);
		addCodeLine(buffer, blk);
		addCodeLine("\timul ebx\n", blk);
		getTemporary();
		strcpy(ptr->temporary, TEMP_BUF);
		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov [%s], eax\n", ptr->temporary);
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
		sprintf(buffer, "\tmov eax, [%s]\n", ptr->childL->temporary);
		addCodeLine(buffer, blk);
		addCodeLine("\tmov edx, 0\n", blk);
		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov ebx, [%s]\n", ptr->childR->temporary);
		addCodeLine(buffer, blk);
		addCodeLine("\tidiv ebx\n", blk);
		getTemporary();
		strcpy(ptr->temporary, TEMP_BUF);
		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov [%s], eax\n", ptr->temporary);
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
		sprintf(buffer, "\tmov eax, [%s]\n", ptr->childL->temporary);
		addCodeLine(buffer, blk);
		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov ebx, [%s]\n", ptr->childR->temporary);
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
		sprintf(buffer, "\tmov [%s], dword 0\n", ptr->temporary);
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
		sprintf(buffer, "\tmov [%s], dword 1\n", ptr->temporary);
		addCodeLine(buffer, blk);

		memset(buffer, 0, 100);
		sprintf(buffer, "%s :\n", tmpl2);
		addCodeLine(buffer, blk);

		mergeCodeBlocks(blk, ptr->childL->blk);
		mergeCodeBlocks(blk, ptr->childR->blk);

	}
	else if( strcmp(ptr->id->val, "LT") == 0 ) {

		codeGenExprRec(ptr->childL);
		codeGenExprRec(ptr->childR);

		addCodeLine("\t;comparing two numbers\n", blk);
		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov eax, [%s]\n", ptr->childL->temporary);
		addCodeLine(buffer, blk);
		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov ebx, [%s]\n", ptr->childR->temporary);
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
		sprintf(buffer, "\tmov [%s], dword 0\n", ptr->temporary);
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
		sprintf(buffer, "\tmov [%s], dword 1\n", ptr->temporary);
		addCodeLine(buffer, blk);

		memset(buffer, 0, 100);
		sprintf(buffer, "%s :\n", tmpl2);
		addCodeLine(buffer, blk);

		mergeCodeBlocks(blk, ptr->childL->blk);
		mergeCodeBlocks(blk, ptr->childR->blk);

	}
	else if( strcmp(ptr->id->val, "GE") == 0 ) {

		codeGenExprRec(ptr->childL);
		codeGenExprRec(ptr->childR);

		addCodeLine("\t;comparing two numbers\n", blk);
		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov eax, [%s]\n", ptr->childL->temporary);
		addCodeLine(buffer, blk);
		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov ebx, [%s]\n", ptr->childR->temporary);
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
		sprintf(buffer, "\tmov [%s], dword 0\n", ptr->temporary);
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
		sprintf(buffer, "\tmov [%s], dword 1\n", ptr->temporary);
		addCodeLine(buffer, blk);

		memset(buffer, 0, 100);
		sprintf(buffer, "%s :\n", tmpl2);
		addCodeLine(buffer, blk);

		mergeCodeBlocks(blk, ptr->childL->blk);
		mergeCodeBlocks(blk, ptr->childR->blk);

	}
	else if( strcmp(ptr->id->val, "GT") == 0 ) {

		codeGenExprRec(ptr->childL);
		codeGenExprRec(ptr->childR);

		addCodeLine("\t;comparing two numbers\n", blk);
		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov eax, [%s]\n", ptr->childL->temporary);
		addCodeLine(buffer, blk);
		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov ebx, [%s]\n", ptr->childR->temporary);
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
		sprintf(buffer, "\tmov [%s], dword 0\n", ptr->temporary);
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
		sprintf(buffer, "\tmov [%s], dword 1\n", ptr->temporary);
		addCodeLine(buffer, blk);

		memset(buffer, 0, 100);
		sprintf(buffer, "%s :\n", tmpl2);
		addCodeLine(buffer, blk);

		mergeCodeBlocks(blk, ptr->childL->blk);
		mergeCodeBlocks(blk, ptr->childR->blk);

	}
	else if( strcmp(ptr->id->val, "NE") == 0 ) {

		codeGenExprRec(ptr->childL);
		codeGenExprRec(ptr->childR);

		addCodeLine("\t;comparing two numbers\n", blk);
		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov eax, [%s]\n", ptr->childL->temporary);
		addCodeLine(buffer, blk);
		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov ebx, [%s]\n", ptr->childR->temporary);
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
		sprintf(buffer, "\tmov [%s], dword 0\n", ptr->temporary);
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
		sprintf(buffer, "\tmov [%s], dword 1\n", ptr->temporary);
		addCodeLine(buffer, blk);

		memset(buffer, 0, 100);
		sprintf(buffer, "%s :\n", tmpl2);
		addCodeLine(buffer, blk);

		mergeCodeBlocks(blk, ptr->childL->blk);
		mergeCodeBlocks(blk, ptr->childR->blk);

	}
	else if( strcmp(ptr->id->val, "EQ") == 0 ) {

		codeGenExprRec(ptr->childL);
		codeGenExprRec(ptr->childR);

		addCodeLine("\t;comparing two numbers", blk);
		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov eax, [%s]\n", ptr->childL->temporary);
		addCodeLine(buffer, blk);
		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov ebx, [%s]\n", ptr->childR->temporary);
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
		sprintf(buffer, "\tmov [%s], dword 0\n", ptr->temporary);
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
		sprintf(buffer, "\tmov [%s], dword 1\n", ptr->temporary);
		addCodeLine(buffer, blk);

		memset(buffer, 0, 100);
		sprintf(buffer, "%s :\n", tmpl2);
		addCodeLine(buffer, blk);

		mergeCodeBlocks(blk, ptr->childL->blk);
		mergeCodeBlocks(blk, ptr->childR->blk);

	}
	else if( strcmp(ptr->id->val, "AND") == 0 ) {	
		// logic for handling AND

		//compare op1 with 1 
		//if false jmp to l1
		//compare op2 with 1
		//if false jmp to l1
		//set 1
		//jump to l2
		//l1 : set 0

		codeGenExprRec(ptr->childL);
		codeGenExprRec(ptr->childR);

		getLabel();
		strcpy(tmpl1, LABEL_BUF);

		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov eax, [%s]\n", ptr->childL->temporary);
		addCodeLine(buffer, blk);

		addCodeLine("\tcmp eax, 1\n", blk);

		memset(buffer, 0, 100);
		sprintf(buffer, "\tjne %s\n", tmpl1);
		addCodeLine(buffer, blk);

		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov eax, [%s]\n", ptr->childR->temporary);
		addCodeLine(buffer, blk);

		addCodeLine("\tcmp eax, 1\n", blk);

		memset(buffer, 0, 100);
		sprintf(buffer, "\tjne %s\n", tmpl1);
		addCodeLine(buffer, blk);

		getTemporary();
		strcpy(ptr->temporary, TEMP_BUF);

		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov [%s], dword 1\n", ptr->temporary);
		addCodeLine(buffer, blk);

		getLabel();
		strcpy(tmpl2, LABEL_BUF);

		memset(buffer, 0, 100);
		sprintf(buffer, "\tjmp %s\n", tmpl1);
		addCodeLine(buffer, blk);

		memset(buffer, 0, 100);
		sprintf(buffer, "%s :\n", tmpl1);
		addCodeLine(buffer, blk);

		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov [%s], dword 0\n", ptr->temporary);
		addCodeLine(buffer, blk);

		memset(buffer, 0, 100);
		sprintf(buffer, "%s :\n", tmpl2);
		addCodeLine(buffer, blk);

		mergeCodeBlocks(blk, ptr->childL->blk);
		mergeCodeBlocks(blk, ptr->childR->blk);

	}
	else if( strcmp(ptr->id->val, "OR") == 0 ) {
		// logic for handling OR

		// compare op1 with 1 
		// if true jmp to l1
		// compare op2 with 1
		// if true jmp to l1
		// set 0
		// jump to l2
		// l1 : set 1

		codeGenExprRec(ptr->childL);
		codeGenExprRec(ptr->childR);

		getLabel();
		strcpy(tmpl1, LABEL_BUF);

		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov eax, [%s]\n", ptr->childL->temporary);
		addCodeLine(buffer, blk);

		addCodeLine("\tcmp eax, 1\n", blk);

		memset(buffer, 0, 100);
		sprintf(buffer, "\tje %s\n", tmpl1);
		addCodeLine(buffer, blk);

		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov eax, [%s]\n", ptr->childR->temporary);
		addCodeLine(buffer, blk);

		addCodeLine("\tcmp eax, 1\n", blk);

		memset(buffer, 0, 100);
		sprintf(buffer, "\tje %s\n", tmpl1);
		addCodeLine(buffer, blk);

		getTemporary();
		strcpy(ptr->temporary, TEMP_BUF);

		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov [%s], dword 0\n", ptr->temporary);
		addCodeLine(buffer, blk);

		getLabel();
		strcpy(tmpl2, LABEL_BUF);

		memset(buffer, 0, 100);
		sprintf(buffer, "\tjmp %s\n", tmpl2);
		addCodeLine(buffer, blk);

		memset(buffer, 0, 100);
		sprintf(buffer, "%s :\n", tmpl2);
		addCodeLine(buffer, blk);

		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov [%s], dword 1\n", ptr->temporary);
		addCodeLine(buffer, blk);

		mergeCodeBlocks(blk, ptr->childL->blk);
		mergeCodeBlocks(blk, ptr->childR->blk);
	
	}
	else if( strcmp(ptr->id->val, "<var>") == 0 ) {
		if( strcmp(ptr->childL->id->val, "ID") == 0 ) {
			if(ptr->childL->se->isArray == 0) {
				strcpy(ptr->temporary, ptr->childL->se->temporary);
			}
			else {
				treeNode * ind;
				ind = ptr->childL->next;
				if( strcmp(ind->childL->id->val, "ID") == 0 ) {

					memset(buffer, 0, 100);
					sprintf(buffer, "\tmov ebx, [%s]\n", ind->childL->se->temporary);
					addCodeLine(buffer, blk);

					memset(buffer, 0, 100);
					sprintf(buffer, "\tmov eax, [%s + 4*ebx]\n", ptr->childL->se->temporary);
					addCodeLine(buffer, blk);

					getTemporary();
					strcpy(ptr->temporary, TEMP_BUF);

					memset(buffer, 0, 100);
					sprintf(buffer, "\tmov [%s], eax\n", ptr->temporary);
					addCodeLine(buffer, blk);

				}
				else {

					memset(buffer, 0, 100);
					sprintf(buffer, "\tmov ebx, dword %s\n", ind->childL->tptr->val);
					addCodeLine(buffer, blk);

					memset(buffer, 0, 100);
					sprintf(buffer, "\tmov eax, [%s + 4*ebx]\n", ptr->childL->se->temporary);
					addCodeLine(buffer, blk);

					getTemporary();
					strcpy(ptr->temporary, TEMP_BUF);

					memset(buffer, 0, 100);
					sprintf(buffer, "\tmov [%s], eax\n", ptr->temporary);
					addCodeLine(buffer, blk);

				}
			}
		}
		else if( strcmp(ptr->childL->id->val, "RNUM") == 0 ) {
			getTemporary();
			strcpy(ptr->temporary, TEMP_BUF);
			memset(buffer, 0, 100);
			sprintf(buffer, "\tmov [%s], dword %s\n", ptr->temporary, ptr->childL->tptr->val);
			addCodeLine(buffer, blk);
			addCodeLine("\n", blk);

		}
		else if( strcmp(ptr->childL->id->val, "NUM") == 0 ) {
			getTemporary();
			strcpy(ptr->temporary, TEMP_BUF);
			memset(buffer, 0, 100);
			sprintf(buffer, "\tmov [%s], dword %s\n", ptr->temporary, ptr->childL->tptr->val);
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
		ptr->blk = ptr->childL->blk;

	}
	else {
		codeGenExprRec(ptr->childR);

		codeBlock * blk;
		blk = createCodeBlock();

		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov eax, [%s]\n", ptr->childR->temporary);
		addCodeLine(buffer, blk);
		
		addCodeLine("\tneg eax\n", blk);
		
		memset(buffer, 0, 100);
		sprintf(buffer, "\tmov [%s], eax\n", ptr->childR->temporary);
		addCodeLine(buffer, blk);

		strcpy(ptr->temporary, ptr->childR->temporary);

		mergeCodeBlocks(blk, ptr->childR->blk);

		ptr->blk = blk;
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
		sprintf(buffer, "\tmov [%s], dword %d\n", child->next->se->temporary, atoi(child->next->next->childL->tptr->val) );
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
		sprintf(buffer, "\tinc dword [%s]\n", child->next->se->temporary );
		addCodeLine(buffer, blk);

		memset(buffer, 0, 100);
		sprintf(buffer, "\tcmp [%s], dword %d\n", child->next->se->temporary, atoi(child->next->next->childR->tptr->val) + 1 );
		addCodeLine(buffer, blk);

		memset(buffer, 0, 100);
		sprintf(buffer, "\tjne %s\n", l1 );
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
		sprintf(buffer, "\tcmp [%s], dword 0\n", child->next->temporary);
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

	}
	else {
		// error in AST.
	}

	ptr->blk = blk;
}


int codeGenStmts(treeNode * ptr) {

	codeBlock * blk;
	blk = createCodeBlock();

	treeNode * child;

	addCodeLine("\t;a block of statements\n", blk);
	
	child = ptr->childR;

	while(child != NULL) {
		if( strcmp(child->id->val, "<declareStmt>") != 0 )
			mergeCodeBlocks(blk, child->blk);
		child = child->prev;

	}

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


int addTemporaries(symbolScope * head , codeBlock * bss ) {

	symbolScope * child;
	symbolEntry * se;
	se = head->seHead;
	child = head->childL;

	while(se != NULL) {
		getTemporary();
		strcpy(se->temporary, TEMP_BUF);

		memset(buffer, 0, 100);
		sprintf(buffer, "\t%s :\tresd\t%d\n", se->temporary, se->endInd - se->startInd + 1 );
		addCodeLine(buffer, bss);		

		se = se->next;
	}

	while(child != NULL) {
		addTemporaries(child, bss);
		child = child->next;
	}
}


int codeGenInit(treeNode * head, symbolScope * sHead, FILE * fp) {

	treeNode * modDef;
	int i;

	// checking the validity
	if( head->childL != head->childR ) {
		printf("\nCannot handle such types of source code for generating ASM.\n");
	}
	else {
		
		codeBlock * header, * bssBlk;

		header = createCodeBlock();
		bssBlk = createCodeBlock();
		
		addCodeLine("\n", bssBlk);
		addCodeLine("section .bss\n", bssBlk);
		
		// map variables to temporaries 
		addTemporaries(sHead->childL, bssBlk);
		
		TEMP_LOCAL = TEMP_COUNT;

		// recurse over the AST to generate code blocks
		modDef = head->childL->childL;
		codeGenRec(modDef);

		modDef->blk = modDef->childL->blk;


		for(i=TEMP_LOCAL;i<TEMP_COUNT;i++) {
			memset(buffer, 0, 100);
			sprintf(buffer, "\tri%d :\tresd\t1\n", i);
			addCodeLine(buffer, bssBlk);
		}


		// prepare header

		// extern 
		addCodeLine("\n", header);
		addCodeLine("extern printf, scanf\n", header);
		addCodeLine("global main\n", header);
		
		// bss section
		addCodeLine("\n", header);
		

		header->bot->next = bssBlk->top;
		header->bot = bssBlk->bot;

		// data section
		addCodeLine("\n", header);
		addCodeLine("section .data\n", header);
		addCodeLine("\ts_fmt:    db \"\%d\", 0\n", header);
		addCodeLine("\tp_fmt:    db \"\%d\", 10, 0\n", header);
		addCodeLine("\n", header);

		// text section
		addCodeLine("section .text\n", header);
		addCodeLine("main : \n", header);

		mergeCodeBlocks(modDef->childL->blk, header);

		// exit code
		addCodeLine("\n\n;exit code\n" , modDef->childL->blk);
		addCodeLine("mov eax, 1\n" , modDef->childL->blk);
		addCodeLine("mov ebx, 0\n" , modDef->childL->blk);
		addCodeLine("int 80h\n" , modDef->childL->blk);

		// printCodeBlock(header);
	
		// dump the entire thing to file
		printToFile(modDef->childL->blk, fp);

	}
}


