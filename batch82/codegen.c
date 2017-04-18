#include <stdio.h>

#include "codegenDef.h"

int LABEL = 1;

int getNextLabelCount() {
	return LABEL++;
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
	if( exp->childL == exp->childR ) {
		codeGenExprRec(exp->childL);
		// additional code
	}
	else {
		codeGenExprRec(exp->childR);
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

	printf("%s\n", ptr->id->val);
}



int codeGenInit(treeNode * head) {

	treeNode * stmts;

	// checking the validity
	if( head->childL != head->childR ) {
		// error. we are considering only the case with driver function
	}
	else {

		// the entire logic code is available here. 
		// this code has to be merged with the code for variable allotment and _start. 


		stmts = head->childL->childL->childL;
		codeGenRec(stmts);
	}
}


