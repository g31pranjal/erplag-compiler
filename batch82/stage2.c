#include <stdio.h>
#include "lexerDef.h"
#include "parserDef.h"
#include "parser.c"
#include "lexer.c"

#include "stage2Def.h"


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


symbolScope * stackScope(symbolScope * parent, char * st) {
	symbolScope * newScope;
	newScope = (symbolScope *)malloc(sizeof(symbolScope));
	
	newScope->parent = newScope->childL = newScope->childR = newScope->next = newScope->prev = NULL;
	newScope->seHead = NULL;

	memset(newScope->stamp, 0, sizeof(newScope->stamp));
	strcpy(newScope->stamp, st);

	if(parent != NULL) {
		if(parent->childL == NULL) {
			// no childs
			parent->childL = parent->childR = newScope;
		}
		else {
			parent->childR->next = newScope;
			newScope->prev = parent->childR;
			parent->childR = newScope;
		}
		newScope->parent = parent;
	}

	return newScope;

}

symbolEntry * lookupSymbolEntry(char * identifier, symbolScope * scope, int line ) {

	symbolEntry * se;

	while(scope != NULL) {
		se = scope->seHead;
		while(se != NULL) {
			if(strcmp(se->identifier, identifier) == 0) {
				se->linesUsed[se->linesUsedNum++] = line;
				return se;
			}
			se = se->next;
		}
		scope = scope->parent;
	}

	printf("ERROR : An identifier must be declared before its use. %s\n", identifier);
	return NULL;
}

int addSymbolEntry(char * identifier, int usage, char * type, int isArray, int s, int e, int line, symbolScope * scope) {

	symbolEntry * sStack, * newEntry;
	sStack = scope->seHead;

	int enter = 1;

	while(sStack != NULL) {
		if(strcmp(sStack->identifier, identifier) == 0) {
			if(sStack->usage == 5 && usage == 2) {
				sStack->usage = 2;
				return sStack;
			}
			else {
				printf("ERROR : An identifier cannot be declared multiple times in the same scope.\n");
				return NULL;
			}
		}
		sStack = sStack->next;
	}
	
	if(enter) {
		newEntry = (symbolEntry *)malloc(sizeof(symbolEntry));
		memset(newEntry->identifier, 0, sizeof(newEntry->identifier));
		strcpy(newEntry->identifier, identifier);
		newEntry->usage = usage;
		memset(newEntry->type, 0, sizeof(newEntry->type));
		strcpy(newEntry->type, type);
		newEntry->isArray = isArray;
		newEntry->startInd = s;
		newEntry->endInd = e;
		newEntry->lineInit = line;

		memset(newEntry->linesUsed, 0, sizeof(newEntry->linesUsed));
		newEntry->linesUsedNum = 0;

		newEntry->next = scope->seHead;
		scope->seHead = newEntry;

	}

	return newEntry;
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


int printScopeStructure(symbolScope * head) {
	
	symbolScope * child;
	symbolEntry * seHead;

	printf("stmp : %s ", head->stamp);
	if(head->parent != NULL) 
		printf(" prt stmp : %s", head->parent->stamp);
	printf("\n");

	seHead = head->seHead;

	while(seHead != NULL) {
		printf("ID : %s, US : %d, BASE : %s, AR : %d, SI : %d, EI : %d, LINE : %d\n", seHead->identifier, seHead->usage, seHead->type, seHead->isArray, seHead->startInd, seHead->endInd, seHead->lineInit );
		seHead = seHead->next;
	}	

	child = head->childL;
	while(child != NULL) {
		printScopeStructure(child);
		child = child->next;
	}

}


symbolScope * initScopeStructure(treeNode * head) {

	symbolScope * sHead;
	sHead = stackScope(NULL, "<program>");

	iterOverScope(head, sHead);

	return sHead;
}


int iterOverScope(treeNode * head, symbolScope * scope) {

	symbolScope * newScope;
	symbolEntry * se;
	treeNode * child, * dT;

	head->scope = scope;

	if(head->childL != NULL) {
		child = head->childL;
		while(child != NULL) {

			if(child->id->id >=0 && child->id->id <= 100) {
				
				// terminal 
				
				// kinds of ids to be recorded  

				// 1. declare statement variables (entry).
				// 2. input_plist vairables (entry).
				// 3. output_plist variables (entry).
				// 4. module definition names (entry).
				// 5. module declaration (entry)

				if(child->id->id == 30) {

					// case 1 
					if( strcmp(child->parent->id->val, "<idList>") == 0 && strcmp(child->parent->parent->id->val, "<declareStmt>") == 0 ) {
						// printf("c1 entry into scope for %s\n", child->tptr->val);
						dT = child->parent->next;
						if(dT->childL == dT->childR) {
							// simple type
							printf("identifier %s, type %s, isArray : %d, s : %d, e : %d, l : %d\n", child->tptr->val, dT->childL->id->val, 0, -1, -1, child->tptr->lno); 
							
							se = addSymbolEntry(child->tptr->val, 1, dT->childL->id->val, 0, -1, -1, child->tptr->lno, scope); 
						
						}
						else {
							// array type
							printf("identifier %s, type %s, isArray : %d, s : %d, e : %d, l : %d\n", child->tptr->val, dT->childL->id->val, 1, atoi(dT->childL->next->childL->tptr->val), atoi(dT->childL->next->childR->tptr->val), child->tptr->lno); 

							se = addSymbolEntry(child->tptr->val, 1, dT->childR->id->val, 1, atoi(dT->childL->next->childL->tptr->val), atoi(dT->childL->next->childR->tptr->val), child->tptr->lno, scope); 
						
						}
					}

					// case 2 
					else if( strcmp(child->parent->id->val, "<input_plist>") == 0) {
						// printf("c2 entry into scope for %s\n", child->tptr->val);
						dT = child->next;
						if(dT->childL == dT->childR) {
							// simple type
							printf("identifier %s, type %s, isArray : %d, s : %d, e : %d, l : %d\n", child->tptr->val, dT->childL->id->val, 0, -1, -1, child->tptr->lno); 
							
							se = addSymbolEntry(child->tptr->val, 3, dT->childL->id->val, 0, -1, -1, child->tptr->lno, scope); 
						
						}
						else {
							// array type
							printf("identifier %s, type %s, isArray : %d, s : %d, e : %d, l : %d\n", child->tptr->val, dT->childL->id->val, 1, atoi(dT->childL->next->childL->tptr->val), atoi(dT->childL->next->childR->tptr->val), child->tptr->lno); 

							se = addSymbolEntry(child->tptr->val, 3, dT->childR->id->val, 1, atoi(dT->childL->next->childL->tptr->val), atoi(dT->childL->next->childR->tptr->val), child->tptr->lno, scope); 
						}
					}

					// case 3 
					else if( strcmp(child->parent->id->val, "<output_plist>") == 0 ) {
						// printf("c3 entry into scope for %s\n", child->tptr->val);
						
						printf("identifier %s, type %s, isArray : %d, s : %d, e : %d, l : %d\n", child->tptr->val, child->next->id->val, 0, -1, -1, child->tptr->lno); 
						
						se = addSymbolEntry(child->tptr->val, 4, child->next->id->val, 0, -1, -1, child->tptr->lno, scope); 
						
					}
					
					// case 4 
					else if( strcmp(child->parent->id->val, "<module>") == 0 ) {
						// printf("c4 entry into scope for %s\n", child->tptr->val);

						printf("identifier %s, type %s, isArray : %d, s : %d, e : %d, l : %d\n", child->tptr->val, "", 0, -1, -1, child->tptr->lno); 
						
						se = addSymbolEntry(child->tptr->val, 2, "", 0, -1, -1, child->tptr->lno, scope->parent); 
					}

					// case 5
					else if( strcmp(child->parent->id->val, "<moduleDeclarations>") == 0 ) {
						// printf("c5 entry into scope for %s\n", child->tptr->val);
					
						printf("identifier %s, type %s, isArray : %d, s : %d, e : %d, l : %d\n", child->tptr->val, "", 0, -1, -1, child->tptr->lno); 
						
						se = addSymbolEntry(child->tptr->val, 5, "", 0, -1, -1, child->tptr->lno, scope); 
					}
					else {
						// case of lookup in the symbol table
						se = lookupSymbolEntry(child->tptr->val, scope, child->tptr->lno);

					}
					
					if(se == NULL) {
						// ERRORS EXIST RELATED TO THE SYMBOL TABLE
					}

					child->se = se;

				}

			}
			else {
				// non terminal

				if (( strcmp(child->id->val, "<statements>") == 0 && strcmp(child->parent->id->val, "<caseStmts>") == 0 ) || (strcmp(child->id->val, "<module>") == 0 ) || (strcmp(child->id->val, "<driverModule>") == 0 )  || (strcmp(child->id->val, "<iterativeStmt>") == 0 )  ) {

					newScope = stackScope(scope, child->id->val);	
	 				
	 				// printf("adding new scope for %s, parent : %s\n", child->id->val, child->parent->id->val);
	 				iterOverScope(child, newScope);
	 				// printf("exiting scope for %s, parent : %s\n", child->id->val, child->parent->id->val);

				}
				else {
					iterOverScope(child, scope);
				}

			}


			child = child->next;
			



		}
	}
	



}






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