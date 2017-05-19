/*
Batch no. 82

AUTHORS : 
Pranjal Gupta (2013B4A7470P)
Tanaya Jha (2013B3A7304P)
*/

/*
	this module constructs the symbol-table for the corresponding AST. The symbol table has a tree structure that depicts the scoping of the blocks of code. Each node of the tree has a linked list of its locally defined variables. It also reports the errors related to redundant declaration, no declaration of variables and modules.
*/


#include <stdio.h>
#include "parserDef.h"
#include "scopeDef.h"

int OFFSET = 0;

symbolScope * stackScope(symbolScope * parent, char * st) {
	symbolScope * newScope;
	newScope = (symbolScope *)malloc(sizeof(symbolScope));

	if(parent != NULL && parent->parent == NULL) {
		// global scope
		OFFSET = 0;
	}
	
	newScope->parent = newScope->childL = newScope->childR = newScope->next = newScope->prev = NULL;
	newScope->seHead = NULL;

	memset(newScope->stamp, 0, 25);
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

symbolEntry * lookupSymbolEntry(char * identifier, symbolScope * scope, int line, int isFunc, int * errors) {

	symbolEntry * se;

	while(scope != NULL) {
		se = scope->seHead;
		while(se != NULL) {
			if(strcmp(se->identifier, identifier) == 0) {
				if( !isFunc || ( isFunc && ( se->usage == 2 || se->usage == 6 || se->usage == 5 ) ) ) {
					se->linesUsed[se->linesUsedNum++] = line;
					return se;
				}
			}
			se = se->next;
		}
		scope = scope->parent;
	}

	*errors = 1;
	printf("%sERROR : %s(scope resolution)%s The identifier '%s' at line %d must be declared before its use. \n", BOLDRED, BOLDYELLOW, RESET, identifier, line);
	return NULL;
}

int addSymbolEntry(char * identifier, int usage, char * type, int isArray, int s, int e, int line, symbolScope * scope, int * errors) {

	symbolEntry * sStack, * newEntry;
	sStack = scope->seHead;

	int enter = 1;

	while(sStack != NULL) {
		if(strcmp(sStack->identifier, identifier) == 0) {
			if(sStack->usage == 5 && usage == 2) {
				sStack->usage = 6;
				sStack->lineInit = line;
				return sStack;
			}
			else {
				if(scope-> parent != NULL) 
					printf("%sERROR : %s(scope resolution)%s The identifier '%s' at line %d cannot be declared multiple times in the same scope.\n", BOLDRED, BOLDYELLOW, RESET, identifier, line);
				else
					printf("%sERROR : %s(scope resolution)%s Module overloading for module '%s' at line %d is not supported.\n", BOLDRED, BOLDYELLOW, RESET, identifier, line);

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
		memset(newEntry->temporary, 0, 5);
		newEntry->isArray = isArray;
		newEntry->startInd = s;
		newEntry->endInd = e;
		newEntry->lineInit = line;
		newEntry->scope = scope;

		if(scope->parent != NULL) {
			newEntry->offset = OFFSET;
			if( strcmp(type, "INTEGER") == 0 ){
				OFFSET += (e-s+1)*2;
				newEntry->width = (e-s+1)*2;
			}
			else if( strcmp(type, "REAL") == 0 ){
				OFFSET += (e-s+1)*4;
				newEntry->width = (e-s+1)*4;
			}
			else if( strcmp(type, "BOOLEAN") == 0 ) {
				OFFSET += (e-s+1)*1;
				newEntry->width = (e-s+1)*1;
			}
		}
		else {
			newEntry->offset = -1;
			newEntry->width = -1;
		}

		memset(newEntry->linesUsed, 0, sizeof(newEntry->linesUsed));
		newEntry->linesUsedNum = 0;

		newEntry->next = scope->seHead;
		scope->seHead = newEntry;

	}
	return newEntry;
}


symbolScope * resolveCurrentModule(symbolScope * currScope) {

	char * stamp;
	symbolEntry * se;

	while(currScope->parent != NULL) {
		stamp = currScope->stamp;
		currScope = currScope->parent;
	}


	if( strcmp(stamp, "<driverModule>") == 0 )
		return NULL;
	else {
		se = currScope->seHead;

		while(se != NULL) {
			if( strcmp(se->identifier, stamp) == 0 )
				return se;
			se = se->next;
		}
	}

	return NULL;
}





int printScopeStructure(symbolScope * head) {
	
	symbolScope * child, * deep, * curr;
	symbolEntry * seHead;
	int depth;

	// printf("\nSCOPE TABLE");
	// printf("---------------------------------------------------------------------------------------------------------------------------\n");

	// printf("stmp : %s ", head->stamp);
	// if(head->parent != NULL) 
	// 	printf(" prt stmp : %s", head->parent->stamp);
	// printf("\n\n");

	seHead = head->seHead;

	char * usg[] = {"", "   variable", "defined module", "input  parameter", "output parameter", "declared module", "defined module"};
	char mName[25];
	memset(mName, 0, 25);

	// while(seHead != NULL) {
	// 	printf("ID : %s, US : %d, BASE : %s, AR : %d, SI : %d, EI : %d, LINE : %d, OFFSET : %d, TEMP : %s\n", seHead->identifier, seHead->usage, seHead->type, seHead->isArray, seHead->startInd, seHead->endInd, seHead->lineInit, seHead->offset, seHead->temporary );
	// 	seHead = seHead->next;
	// }	

	while(seHead != NULL) {

		deep = seHead->scope;
		depth = 0;

		while(deep->parent != NULL) {
			depth++;
			strcpy(mName, deep->stamp);
			deep = deep->parent;
		}

		// identifier - usage - type - line declared - depth - width - offset
		
		if(seHead->isArray == 1) {
			printf("%s\t\t%s\t\tArray(%d, %s)\t\t%d\t\t%s\t\t%d\t\t%d\t\t%d\n", seHead->identifier, usg[seHead->usage], seHead->endInd - seHead->startInd, seHead->type, seHead->lineInit, mName, depth, seHead->width, seHead->offset );
		}
		else {
			printf("%s\t\t%s\t\t  %s  \t\t%d\t\t%s\t\t%d\t\t%d\t\t%d\n", seHead->identifier, usg[seHead->usage], seHead->type, seHead->lineInit, mName, depth, seHead->width, seHead->offset );
		}

		seHead = seHead->next;
	}

	child = head->childL;
	while(child != NULL) {
		printScopeStructure(child);
		child = child->next;
	}

}


symbolScope * initScopeStructure(treeNode * head, int * errors) {

	symbolScope * sHead;
	sHead = stackScope(NULL, "<program>");

	iterOverScope(head, sHead, errors);

	return sHead;
}


int iterOverScope(treeNode * head, symbolScope * scope, int * errors) {

	symbolScope * newScope;
	symbolEntry * se;
	treeNode * child, * dT, * ind;
	int iVal;

	head->scope = scope;

	if(head->childL != NULL) {
		child = head->childL;
		while(child != NULL) {

			if(child->childL == NULL) {
				// terminal

				if(child->id->id == 30) {
				
					// case 1 : declare statement variables 
					if( strcmp(child->parent->id->val, "<idList>") == 0 && strcmp(child->parent->parent->id->val, "<declareStmt>") == 0 ) {
						dT = child->parent->next;
						if(dT->childL == dT->childR) {
							// simple type
							se = addSymbolEntry(child->tptr->val, 1, dT->childL->id->val, 0, -1, -1, child->tptr->lno, scope, errors);
						}
						else {
							// array type
							se = addSymbolEntry(child->tptr->val, 1, dT->childR->id->val, 1, atoi(dT->childL->next->childL->tptr->val), atoi(dT->childL->next->childR->tptr->val), child->tptr->lno, scope, errors); 
						}
					}

					// case 2 : input list variables
					else if( strcmp(child->parent->id->val, "<input_plist>") == 0) {
						dT = child->next;
						if(dT->childL == dT->childR) {
							// simple type
							se = addSymbolEntry(child->tptr->val, 3, dT->childL->id->val, 0, -1, -1, child->tptr->lno, scope, errors);
						}
						else {
							// array type
							se = addSymbolEntry(child->tptr->val, 3, dT->childR->id->val, 1, atoi(dT->childL->next->childL->tptr->val), atoi(dT->childL->next->childR->tptr->val), child->tptr->lno, scope, errors); 
						}
					}

					// case 3 : output list 
					else if( strcmp(child->parent->id->val, "<output_plist>") == 0 ) {
						se = addSymbolEntry(child->tptr->val, 4, child->next->id->val, 0, -1, -1, child->tptr->lno, scope, errors); 	
					}
					
					// case 4 : id of module definition
					else if( strcmp(child->parent->id->val, "<module>") == 0 ) {
						se = addSymbolEntry(child->tptr->val, 2, "", 0, -1, -1, child->tptr->lno, scope->parent, errors); 
					}

					// case 5 : id of module declaration
					else if( strcmp(child->parent->id->val, "<moduleDeclarations>") == 0 ) {
						se = addSymbolEntry(child->tptr->val, 5, "", 0, -1, -1, child->tptr->lno, scope, errors); 
					}

					else {
						// printf("looking up %s...\n", child->tptr->val);
						
						if( strcmp(child->parent->id->val, "<moduleReuseStmt>") == 0 ) 
							se = lookupSymbolEntry(child->tptr->val, scope, child->tptr->lno, 1, errors);
						else
							se = lookupSymbolEntry(child->tptr->val, scope, child->tptr->lno, 0, errors);
					

					}
					if(se != NULL) {
						child->se = se;
						strcpy(child->type, se->type);
					}
				}
			}

			else {
				// non terminal 

				if (( strcmp(child->id->val, "<statements>") == 0 && strcmp(child->parent->id->val, "<caseStmts>") == 0 ) || (strcmp(child->id->val, "<module>") == 0 ) || (strcmp(child->id->val, "<driverModule>") == 0 )  || (strcmp(child->id->val, "<iterativeStmt>") == 0 )  ) {

					if( strcmp(child->id->val, "<module>") == 0 ){
						newScope = stackScope(scope, child->childL->tptr->val);
					}
					else {
						newScope = stackScope(scope, child->id->val);
					}

	 				iterOverScope(child, newScope, errors);
				}
				else {
					iterOverScope(child, scope, errors);
				}
			}

			child = child->next;
			
		}
	}
}


