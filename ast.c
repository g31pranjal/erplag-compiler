/*
Batch no. 82

AUTHORS : 
Pranjal Gupta (2013B4A7470P)
Tanaya Jha (2013B3A7304P)
*/

/*
	this module takes in the parse tree and 1). Delete all the irrelevant tokens, 2). Changes the structure of <expressions> to infix notation (for proper checking and evaluation), 3). removes chaining in tree and 4). removes empty non-terminals. 
*/

#include <stdio.h>
#include "parserDef.h"


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


int liftUpNode(treeNode * child) {

	treeNode * childchild;

	if(child->parent->childL == child) {
		// left child of its parent 
		child->parent->childL = child->childL;
		child->childL->prev = NULL;
	}
	else {
		child->prev->next = child->childL;
		child->childL->prev = child->prev;
	}

	if(child->parent->childR == child) {
		// right child of its parent 
		child->parent->childR = child->childR;
		child->childR->next = NULL;
	}
	else {
		child->next->prev = child->childR;
		child->childR->next = child->next;
	}

	childchild = child->childL;

	while(childchild != NULL) {

		childchild->parent = child->parent;
		childchild = childchild->next;
	}
}


int constructAST(treeNode * head) {

	treeNode * child , * childchild;

	int keep[] = {2/*PRINT*/, 10/*AND*/, 12/*OR*/, 13/*FOR*/, 14/*INTEGER*/, 15/*REAL*/, 16/*BOOLEAN*/, 17/*ARRAY*/, 20/*GET_VALUE*/, 23/*TRUE*/, 24/*FALSE*/, 28/*WHILE*/, 30/*ID*/, 31/*NUM*/, 32/*RNUM*/, 34/*PLUS*/, 35/*MINUS*/, 36/*MUL*/, 37/*DIV*/, 38/*LT*/, 39/*LE*/, 40/*GT*/, 41/*GE*/, 42/*NE*/, 43/*EQ*/};

	int i, toRemove, arrL = sizeof(keep)/sizeof(int);

	
	if(head->childL != NULL) {
		child = head->childL;
		while(child != NULL) {
			// printf("%d, %s, %d . \n", child->id->id, child->id->val, child->id->type);
			
			if(child->childL == NULL) {
				// terminal
				toRemove = 1;
				for(i=0;i<arrL;i++) {
					if(keep[i] == child->id->id) {
						toRemove = 0;
						break;
					}
				}
				if(toRemove) {
					removeTreeNode(head, child);	
				}
			}
			else {
				// non terminal (folding empty terminals and compressing recursion)

				constructAST(child);
				if(child->childL == NULL && child->childR == NULL) {
					// printf("removing %s\n", child->id->val);
					removeTreeNode(head, child);
				}
				else {
					// printf("in for child %s\n", child->id->val);
					// printf("in for child %s\n", child->childL->id->val);

					// moduleDeclarations recursion compressing
					if(strcmp(child->id->val, "<moduleDeclarations>") == 0) {
						liftUpNode(child->childL);
						if(strcmp(child->parent->id->val, "<moduleDeclarations>") == 0)
							liftUpNode(child);
					}

					// input_pListRec compression
					else if(strcmp(child->id->val, "<input_plistRec>") == 0) 
						liftUpNode(child);

					// otherModules recursion compressing
					else if(strcmp(child->id->val, "<otherModules>") == 0 && strcmp(child->parent->id->val, "<otherModules>") == 0)
						liftUpNode(child);

					// output_pListRec compression
					else if(strcmp(child->id->val, "<output_plistRec>") == 0)
						liftUpNode(child);

					// statements recursion compressing
					else if(strcmp(child->id->val, "<statements>") == 0 && strcmp(child->parent->id->val, "<statements>") == 0)
						liftUpNode(child);

					// caseStmtsRec compression
					else if(strcmp(child->id->val, "<caseStmtsRec>") == 0)
						liftUpNode(child);

					// idListRec compression
					else if(strcmp(child->id->val, "<idListRec>") == 0)
						liftUpNode(child);

					// type compression
					else if(strcmp(child->id->val, "<type>") == 0)
						liftUpNode(child);

					// ret compression
					else if(strcmp(child->id->val, "<ret>") == 0)
						liftUpNode(child);

					// optional compression
					else if(strcmp(child->id->val, "<optional>") == 0)
						liftUpNode(child);

					// statement compression
					else if(strcmp(child->id->val, "<statement>") == 0)
						liftUpNode(child);

					// expression symbols lifting up
					else if((strcmp(child->id->val, "<pm>") == 0) || (strcmp(child->id->val, "<md>") == 0) || (strcmp(child->id->val, "<logicalOp>") == 0) || (strcmp(child->id->val, "<relationalOp>") == 0) )
						liftUpNode(child);

					// whichId compression
					else if(strcmp(child->id->val, "<whichId>") == 0 )
						liftUpNode(child);

					// <arithOrBoolExprRec> compression
					else if( child->childL != NULL && (strcmp(child->childL->id->val, "AND") == 0 || strcmp(child->childL->id->val, "OR") == 0 ) && (strcmp(child->parent->id->val, "<arithOrBoolExpr>") == 0 || strcmp(child->parent->id->val, "<arithOrBoolExprRec>") == 0 ) && child->parent->childR == child  )  {
						
						child->parent->id  = child->childL->id;
						child->parent->tptr = child->childL->tptr;
						child->childL->tptr = NULL;
						removeTreeNode(child, child->childL);
						if(child->childL == child->childR)
							liftUpNode(child);
					}

					// <anyTermRec> compression
					else if( child->childL != NULL && (strcmp(child->childL->id->val, "LT") == 0 || strcmp(child->childL->id->val, "LE") == 0 || strcmp(child->childL->id->val, "GE") == 0 || strcmp(child->childL->id->val, "GT") == 0 || strcmp(child->childL->id->val, "NE") == 0 || strcmp(child->childL->id->val, "EQ") == 0 ) && (strcmp(child->parent->id->val, "<anyTerm>") == 0 || strcmp(child->parent->id->val, "<anyTermRec>") == 0 )  && child->parent->childR == child )  {
						
						child->parent->id  = child->childL->id;
						child->parent->tptr = child->childL->tptr;
						child->childL->tptr = NULL;
						removeTreeNode(child, child->childL);
						if(child->childL == child->childR)
							liftUpNode(child);
					}

					// <arithmeticExprRec> compression
					else if( child->childL != NULL && (strcmp(child->childL->id->val, "PLUS") == 0 || strcmp(child->childL->id->val, "MINUS") == 0 ) && (strcmp(child->parent->id->val, "<arithmeticExpr>") == 0 || strcmp(child->parent->id->val, "<arithmeticExprRec>") == 0 )  && child->parent->childR == child )  {
						
						child->parent->id  = child->childL->id;
						child->parent->tptr = child->childL->tptr;
						child->childL->tptr = NULL;
						removeTreeNode(child, child->childL);
						if(child->childL == child->childR)
							liftUpNode(child);
					}

					// <termRec> compression
					else if( child->childL != NULL && (strcmp(child->childL->id->val, "MUL") == 0 || strcmp(child->childL->id->val, "DIV") == 0 ) && (strcmp(child->parent->id->val, "<term>") == 0 || strcmp(child->parent->id->val, "<termRec>") == 0 ) && child->parent->childR == child )  {
						
						child->parent->id  = child->childL->id;
						child->parent->tptr = child->childL->tptr;
						child->childL->tptr = NULL;
						removeTreeNode(child, child->childL);
						if(child->childL == child->childR)
							liftUpNode(child);
					}

					// <arithOrBoolExpr> <anyterm> <arithmeticExpr> <term> <factor> compression
					else if( strcmp(child->id->val, "<arithOrBoolExpr>") == 0 || strcmp(child->id->val, "<anyTerm>") == 0 || strcmp(child->id->val, "<arithmeticExpr>") == 0 || strcmp(child->id->val, "<term>") == 0 || strcmp(child->id->val, "<factor>") == 0 ){
						liftUpNode(child);
					}

				}
			}
			child = child->next;

		}
	}
}




int printAST(treeNode * head)  {

	int first = 0;
	treeNode * child;
	child = head->childL;

	if(child != NULL) {
		while(child != NULL) {

			printAST(child);
			if(first == 0) {
				// printing a non terminal 
				// printf("node : %x\n", head);
				
				if(head->parent != NULL) {
					printf("---\t\t---\t\t---\t\t---\t\t%s\t\tNO\t\t%s\n", head->parent->id->val, head->id->val);
				}
					
				else{
					printf("---\t\t---\t\t---\t\t---\t\tROOT\t\tNO\t\t%s\n", head->id->val);
				}

				first = 1;
			}
			child = child->next;

		}
	}
	
	else {
		if(head->tptr != NULL) {
			// with the token 
			if(head->tptr->id == 31 || head->tptr->id == 32 ){
				printf("%s\t\t%d\t\t%s\t\t%s\t\t%s\t\tYES\t\t---\n", head->tptr->val, head->tptr->lno, head->tptr->lxm, head->tptr->val, head->parent->id->val);
			}
			else { 
				printf("%s\t\t%d\t\t%s\t\t---\t\t%s\t\tYES\t\t---\n", head->tptr->val, head->tptr->lno, head->tptr->lxm, head->parent->id->val);
			}
		}
		else {
			printf("---\t\t---\t\t %s\t\t---\t\t%s\t\tYES\t\t---\n", ref[head->id->id], head->parent->id->val );
		
		}
	}

}
