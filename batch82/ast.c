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
		child->childL->prev = NULL;
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

	int keep[] = {2/*PRINT*/, 10/*AND*/, 12/*OR*/, 13/*FOR*/, 14/*INTEGER*/, 15/*REAL*/, 16/*BOOLEAN*/, 17/*ARRAY*/, 18/*START*/, 19/*END*/, 20/*GET_VALUE*/, 23/*TRUE*/, 28/*WHILE*/, 30/*ID*/, 31/*NUM*/, 32/*RNUM*/, 34/*PLUS*/, 35/*MINUS*/, 36/*MUL*/, 37/*DIV*/, 38/*LT*/, 39/*LE*/, 40/*GT*/, 41/*GE*/, 42/*NE*/, 43/*EQ*/, 50/*ASSIGNOP*/};

	int i, toRemove, arrL = sizeof(keep)/sizeof(int);

	if(head->childL != NULL) {
		child = head->childL;
		while(child != NULL) {
			// printf("%d, %s, %d . \n", child->id->id, child->id->val, child->id->type);

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
					// printf(" -- removed\n");
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

					// statement compression
					else if(strcmp(child->id->val, "<statement>") == 0)
						liftUpNode(child);

					// <arithOrBoolExprRec> compression, lifting logical op
					// else if( ( strcmp(child->id->val, "<arithOrBoolExprRec>") == 0 || strcmp(child->id->val, "AND") == 0 || strcmp(child->id->val, "OR") == 0 )  &&  child->childL != NULL )  {

					// 	child->parent-> id  = child->childL->childL->id;
					// 	child->parent->tptr = child->childL->childL->tptr;
					// 	child->childL->tptr = NULL;
					// 	removeTreeNode(child->, child->childL);
					// 	removeTreeNode(child, child->childL);
					// 	liftUpNode(child);
					// }

				}
			}
			child = child->next;
		}
	}
}



int printAST(treeNode * head) {
	treeNode * child;
	child = head->childL;

	while(child != NULL) {
		printAST(child);
		child = child->next;
	}

	if(head->id->type == 0 ) {
		printf("%s, %s\n", head->tptr->val, head->id->val);
	}
	else {
		// non terminal 
		printf("%s\n", head->id->val);
	}

}