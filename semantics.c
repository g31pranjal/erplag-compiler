/*
Batch no. 82

AUTHORS : 
Pranjal Gupta (2013B4A7470P)
Tanaya Jha (2013B3A7304P)
*/

/*
	this module performs semantic checks on the AST for verifiying semantic correctness of the source code. It also determines the correctness of the expression.

	The following checks are performed :
		1. 	WHILE should have a valid BOOLEAN expression
		2. 	The identifier of the FOR should be an INTEGER
		3.  The identifier of type ARRAY should have an index
		4. 	If the index of the ARRAY identifier is a NUM, then it should be within limits.
		5.	Index of the array should always by INTEGER
		6.  Recursive module calling is not allowed. 
		7.  Function overloading is not allowed.
		8.  The identifier of the SWITCH construct should be INTEGER or BOOLEAN.
		9.  If the SWITCH has INTEGER identifier, all case statements must have NUM and should be followed by DEFAULT statement.
		10. If the SWITCH has BOOLEAN identifier, all case statements must have TRUE and FALSE and should not be followed by DEFAULT 		statement.
		11. The parameter list of the moduleReuseStmt should match the formal parameters of the called module.
		12. The idlist of the moduleReuseStmt should match the output_list of the called module.
		13. A module most be declared (or defined) before its used in other module.
		14. The called module should be definately defined and not only declared.

		15. AND/OR can only have BOOLEAN arguments, returns BOOLEAN.
		16. PLUS/MINUS/MUL/DIV can only have both NUM or RNUM arguments, returns NUM or RNUM respectively.
		17. type of LHS of the assignment statement should match the type of the RHS expression.
		18. LT/LE/GT/GE/NE/EQ can only have both NUM or RNUM arguments, returns BOOLEAN.


*/

#include <stdio.h>
#include "parserDef.h"
#include "scopeDef.h"
#include "scope.h"


int checkArrayCases(treeNode * idref, int * errors) {

	symbolEntry * se = idref->se;
	treeNode * ind;
	int iVal;

	if(se != NULL && se->isArray == 1) {
		if(idref->next != NULL && strcmp(idref->next->id->val, "<index>") == 0 ) {
			ind = idref->next;
			if( strcmp(ind->childL->id->val, "NUM") == 0 ) {
				// check index bounds
				iVal = atoi(ind->childL->tptr->val);
				if( iVal < se->startInd || iVal > se->endInd ) {
					printf("%sERROR : %s(semantics)%s Array index for identifier '%s' at line %d is out of bounds.\n", BOLDRED, BOLDBLUE, RESET, idref->tptr->val, idref->tptr->lno);
					*errors = 1;
				}
			}
			else {
				if( ind->childL->se != NULL && strcmp(ind->childL->se->type,"INTEGER") != 0 ) {
					printf("%sERROR : %s(semantics)%s Index of the ARRAY type identifier '%s' at line %d should be of type INTEGER.\n", BOLDRED, BOLDBLUE, RESET, idref->tptr->val, idref->tptr->lno);
					*errors = 1;
				}
				else {
					// scoping errors are there.
				}
			}
		}
		else {
			printf("%sERROR : %s(semantics)%s Identifier '%s' at line %d of type ARRAY should be addressed by an INTEGER index.\n", BOLDRED, BOLDBLUE, RESET, idref->tptr->val, idref->tptr->lno);
			*errors = 1;
		}
	}
	else {
		// printf("error in AST.\n");
	}
}


int expressionCheckerRec(treeNode * nd, int * errors) {

	char * l, r;

	if( strcmp(nd->id->val, "AND") == 0 || strcmp(nd->id->val, "OR") == 0 ) {
		
		expressionCheckerRec(nd->childL, errors);
		expressionCheckerRec(nd->childR, errors);
		
		// BOOLEAN <op> BOOLEAN = BOOLEAN
		if( strcmp(nd->childL->type, "BOOLEAN") == 0 && strcmp(nd->childR->type, "BOOLEAN") == 0 ) {
			strcpy(nd->type, "BOOLEAN");
		}
		else {
			printf("%sERROR : %s(semantics)%s lhs of type '%s' does not match rhs of type '%s' for operator %s at line %d\n", BOLDRED, BOLDBLUE, RESET, nd->childL->type, nd->childR->type, nd->tptr->val, nd->tptr->lno);
			*errors = 1;
			return NULL;
		}
	}
	else if( strcmp(nd->id->val, "LE") == 0 || strcmp(nd->id->val, "LT") == 0 ||  strcmp(nd->id->val, "GE") == 0 || strcmp(nd->id->val, "GT") == 0 ||  strcmp(nd->id->val, "NE") == 0 || strcmp(nd->id->val, "EQ") == 0  ) {
		
		expressionCheckerRec(nd->childL, errors);
		expressionCheckerRec(nd->childR, errors);
		
		// INTEGER <op> INTEGER = BOOLEAN
		if( strcmp(nd->childL->type, "INTEGER") == 0 && strcmp(nd->childR->type, "INTEGER") == 0 ) {
			strcpy(nd->type, "BOOLEAN");
		}
		// REAL <op> REAL = BOOLEAN
		else if( strcmp(nd->childL->type, "REAL") == 0 && strcmp(nd->childR->type, "REAL") == 0 ) {
			strcpy(nd->type, "BOOLEAN");
		}
		else {
			printf("%sERROR : %s(semantics)%s lhs of type '%s' does not match rhs of type '%s' for operator %s at line %d\n", BOLDRED, BOLDBLUE, RESET, nd->childL->type, nd->childR->type, nd->tptr->val, nd->tptr->lno);
			*errors = 1;
			return NULL;
		}
	}
	else if( strcmp(nd->id->val, "PLUS") == 0 || strcmp(nd->id->val, "MINUS") == 0 ||  strcmp(nd->id->val, "MUL") == 0 || strcmp(nd->id->val, "DIV") == 0  ) {
		expressionCheckerRec(nd->childL, errors);
		expressionCheckerRec(nd->childR, errors);
		
		// INTEGER <op> INTEGER = INTEGER
		if( strcmp(nd->childL->type, "INTEGER") == 0 && strcmp(nd->childR->type, "INTEGER") == 0 ) {
			strcpy(nd->type, "INTEGER");
		}
		// REAL <op> REAL = REAL
		else if( strcmp(nd->childL->type, "REAL") == 0 && strcmp(nd->childR->type, "REAL") == 0 ) {
			strcpy(nd->type, "REAL");
		}
		else {
			printf("%sERROR : %s(semantics)%s lhs of type '%s' does not match rhs of type '%s' for operator %s at line %d\n", BOLDRED, BOLDBLUE, RESET, nd->childL->type, nd->childR->type, nd->tptr->val, nd->tptr->lno);
			*errors = 1;
			return NULL;
		}
	}
	else if( strcmp(nd->id->val, "<var>") == 0 ) {
		if( strcmp(nd->childL->id->val,"NUM") == 0 )
			strcpy(nd->type, "INTEGER");
		else if( strcmp(nd->childL->id->val,"RNUM") == 0 )
			strcpy(nd->type, "REAL");
		else if( strcmp(nd->childL->id->val,"TRUE") == 0 || strcmp(nd->childL->id->val,"FALSE") == 0 )
			strcpy(nd->type, "BOOLEAN");
		else if( strcmp(nd->childL->id->val,"ID") == 0 ) {
			if( nd->childL->se != NULL && nd->childL->se->isArray == 1 )
				checkArrayCases(nd->childL, errors);
			strcpy(nd->type, nd->childL->type);
		}
	}
}


int expressionCheckerInit(treeNode * exp, int * errors) {
	
	char * yup;
	if( exp->childL == exp->childR ) {
		expressionCheckerRec(exp->childL, errors);
		strcpy(exp->type, exp->childL->type);
	}
	else {
		expressionCheckerRec(exp->childR, errors);
		strcpy(exp->type, exp->childR->type);
	}
	// printf("exp type : %s\n", exp->type);
}


int switchSemantics(treeNode * swt, int * errors) {
	
	treeNode * id, * cr, *df;
	id = swt->childL;
	cr = swt->childL->next->childL;
	df = swt->childL->next->next;

	if( strcmp(id->se->type, "INTEGER") != 0 && strcmp(id->se->type, "BOOLEAN") != 0 ) {
		printf("%sERROR : %s(semantics)%s The identifier '%s' in switch statement at line %d should be of type INTEGER or BOOLEAN.\n", BOLDRED, BOLDBLUE, RESET, id->id->val, id->tptr->lno);
		*errors = 1;
	}
	else {
		if( strcmp(id->se->type, "INTEGER") == 0 && df == NULL) {
			printf("%sERROR : %s(semantics)%s The INTEGER identifier '%s' in switch statement at line %d must be followed by the DEFAULT statement.\n", BOLDRED, BOLDBLUE, RESET, id->id->val, id->tptr->lno);
			*errors = 1;
		}
		else if( strcmp(id->se->type, "BOOLEAN") == 0 && df != NULL) {
			printf("%sERROR : %s(semantics)%s The BOOLEAN identifier '%s' in switch statement at line %d must not be followed by the DEFAULT statement.\n", BOLDRED, BOLDBLUE, RESET, id->id->val, id->tptr->lno);
			*errors = 1;
		}

		while(cr != NULL) {
			if( strcmp(cr->id->val,"<value>") == 0 ) {
				if( strcmp(id->se->type, "INTEGER") == 0 && strcmp(cr->childL->id->val, "NUM") != 0 ) {
					printf("%sERROR : %s(semantics)%s Switch statement with INTEGER typed identifier can have only INTEGER values in case statements. Found otherwise at line %d\n", BOLDRED, BOLDBLUE, RESET, cr->childL->tptr->lno);
					*errors = 1;
				}
				else if( strcmp(id->se->type, "BOOLEAN") == 0 &&  strcmp(cr->childL->id->val, "TRUE") != 0 && strcmp(cr->childL->id->val, "FALSE") != 0  ) {
					printf("%sERROR : %s(semantics)%s Switch statement with BOOLEAN typed identifier can have only TRUE / FALSE values in case statements. Found otherwise at line %d\n", BOLDRED, BOLDBLUE, RESET, cr->childL->tptr->lno);
					*errors = 1;
				}
			}
			cr = cr->next;
		}
	}
}


int checkInputParameters(symbolEntry * invokedModule, symbolScope * scopeRoot, treeNode * idl, int lno, int * errors) {

	char *mName;
	symbolScope *childScope, *mScope;
	symbolEntry *se, * prmtrS;
	int errorLoc = 0;

	mName = invokedModule->identifier;
	childScope = scopeRoot->childL;

	while(childScope != NULL) {
		if( strcmp(mName, childScope->stamp) == 0 ) {
			mScope = childScope;
		}
		childScope = childScope->next;
	}

	idl = idl->childR;
	se = mScope->seHead;

	while(idl != NULL && se != NULL) {

		prmtrS = idl->se;

		// printf("getting here\n");
		// printf("%s %s\n", se->identifier, prmtrS->identifier);

		if(prmtrS != NULL) {
			if(se->usage == 3) {
				// printf("valid\n");
				// printf("%s\n", prmtrS->type);
			
				if( ! ( strcmp(prmtrS->type, se->type) == 0 && prmtrS->isArray == se->isArray && prmtrS->startInd == se->startInd && prmtrS->endInd == se->endInd ) ) {
					printf("%sERROR : %s(semantics)%s actual and formal parameters are not matching at line %d\n", BOLDRED, BOLDBLUE, RESET, lno);
					errorLoc = 1;
					*errors = 1;
					break;
				}
				else {
					se = se->next;
					idl = idl->prev;
				}


			}
			else {
				se = se->next;
				continue;
			}
		}
		else {
			// printf("error in AST.\n");
			break;
		}
	}

	if( !errorLoc && ( idl != NULL || se != NULL ) ) {
		printf("%sERROR : %s(semantics)%s number of parameters passed to the module differs at line %d\n", BOLDRED, BOLDBLUE, RESET, lno);
		*errors = 1;
	}

}


int checkOutputParameters(symbolEntry * invokedModule, symbolScope * scopeRoot, treeNode * idr, int lno, int * errors) {

	char *mName;	
	symbolScope *childScope, *mScope;
	symbolEntry *se, * prmtrS;
	int errorLoc = 0;

	mName = invokedModule->identifier;
	childScope = scopeRoot->childL;

	while(childScope != NULL) {
		if( strcmp(mName, childScope->stamp) == 0 ) {
			mScope = childScope;
		}
		childScope = childScope->next;
	}

	se = mScope->seHead;

	if(idr == NULL) {
		
		while(se != NULL) {
			if(se->usage == 4) {
				printf("%sERROR : %s(semantics)%s The invoked module has return parameters which needs to be assigned at line %d\n", BOLDRED, BOLDBLUE, RESET, lno);
				*errors = 1;
				errorLoc = 1;
				break;
			}
			se = se->next;
		}

	}
	else {
		// parameters are there
		idr = idr->childR;

		while(idr != NULL && se != NULL) {

			prmtrS = idr->se;

			// printf("getting here\n");
			// printf("%s %s\n", se->identifier, prmtrS->identifier);

			if(prmtrS != NULL) {
				if(se->usage == 4) {
					// printf("valid\n");
					// printf("%s\n", prmtrS->type);
				
					if( ! ( strcmp(prmtrS->type, se->type) == 0 && prmtrS->isArray == se->isArray && prmtrS->startInd == se->startInd && prmtrS->endInd == se->endInd ) ) {
						printf("%sERROR : %s(semantics)%s The parameters returned by the module is not matching the set of parameters used to invoke the function at line %d\n", BOLDRED, BOLDBLUE, RESET, lno);
						*errors = 1;
						errorLoc = 1;
						break;
					}
					else {
						se = se->next;
						idr = idr->prev;
						// printf("consumed one\n");
					}
				}
				else {
					se = se->next;
					continue;
				}
			}
			else {
				// printf("error in AST.\n");
				break;
			}
		}

		if( !errorLoc && (idr != NULL || (se != NULL && se->usage == 4) ) ) {
			printf("%sERROR : %s(semantics)%s number of parameters returned by the module differs at line %d\n", BOLDRED, BOLDBLUE, RESET, lno);
			*errors = 1;
		}
	}

}


int callingModule(treeNode * callMod, symbolScope * sHead, int * errors) {

	// check if the called function is visible.
	// check if the output parameters are correct
	// check if the input parameters are correct

	treeNode * idr, * idref, * idl, * child;
	symbolEntry * invokedModule, * currentModule;

	if( strcmp(callMod->childL->id->val, "ID") == 0 ) {
		idr = NULL;
		idref = callMod->childL;
		idl = callMod->childL->next;
	}
	else {
		idr = callMod->childL;
		idref = callMod->childL->next;
		idl = callMod->childL->next->next;	
	}

	currentModule = resolveCurrentModule(callMod->scope);
	invokedModule = idref->se;

	if(invokedModule != NULL) {
		if(invokedModule == currentModule) {
			printf("%sERROR : %s(semantics)%s Recursive call to module '%s' is not allowed at line %d\n", BOLDRED, BOLDBLUE, RESET, idref->tptr->val, idref->tptr->lno);
			*errors = 1;
		}

		if(invokedModule->usage == 5 ) {
			printf("%sERROR : %s(semantics)%s The module '%s' refernced at line %d is not defined and only declared\n", BOLDRED, BOLDBLUE, RESET, idref->tptr->val, idref->tptr->lno);
			*errors = 1;
		}
		else if(invokedModule->usage == 2 && idref->tptr->lno < invokedModule->lineInit) {
			printf("%sERROR : %s(semantics)%s The module '%s' refernced at line %d must be declared before referencing.\n", BOLDRED, BOLDBLUE, RESET, idref->tptr->val, idref->tptr->lno);
			*errors = 1;			
		}
		else {

			checkInputParameters(idref->se, sHead, idl, idref->tptr->lno, errors);
			checkOutputParameters(idref->se, sHead, idr, idref->tptr->lno, errors);
	
		}
	}
}


int checkIOStmt(treeNode * io, int * errors) {

	treeNode * var;
	
	if(io->childL != NULL) {
		if( strcmp(io->childL->id->val, "PRINT") == 0 ) {
			var = io->childL->next;
			if( strcmp(var->childL->id->val, "ID") == 0 && var->childL->se != NULL && var->childL->se->isArray == 1 )
				checkArrayCases(var->childL, errors);
		}
		else if( strcmp(io->childL->id->val, "GET_VALUE") == 0 ) {
			if( io->childL->next->se != NULL && io->childL->next->se->isArray == 1 )
				checkArrayCases(io->childL->next, errors);
		}
		else {
			// printf("error in AST.\n");	
		}
	}
	else {
		// printf("error in AST.\n");
	}
}


int checkIterativeStmt(treeNode * it, int * errors) {

	treeNode * tmp;

	if(it->childL != NULL) {
		if( strcmp(it->childL->id->val, "FOR") == 0 ) {
			tmp = it->childL->next;
			if(tmp != NULL && tmp->se != NULL && strcmp(tmp->se->type, "INTEGER") != 0 ) {
				printf("%sERROR : %s(semantics)%s The identifier '%s' used as the control variable of the FOR loop at line %d, has to be of INTEGER type\n", BOLDRED, BOLDBLUE, RESET, tmp->tptr->val, tmp->tptr->lno);
				*errors = 1;
			}
		}
		else if( strcmp(it->childL->id->val, "WHILE") == 0 ) {
			tmp = it->childL->next;
			expressionCheckerRec(tmp, errors);
			if( strcmp(tmp->type, "BOOLEAN") != 0 ) {
				printf("%sERROR : %s(semantics)%s The control expression of the WHILE loop at line %d, has to be of BOOLEAN type\n", BOLDRED, BOLDBLUE, RESET, tmp->tptr->val, it->childL->tptr->lno);
				*errors = 1;
			}
		}
		else {
			// printf("error in AST.\n");	
		}
	}
	else {
		// printf("error in AST.\n");
	}
}

int checkAssignmentStmt(treeNode * assg, int * errors) {

	treeNode * idref, * exp ;

	idref = assg->childL;
	exp = assg->childR;

	if(idref->se != NULL ) {
		if(idref->se->isArray == 1){
			checkArrayCases(idref, errors);
		}
		if( strcmp(exp->type, "") != 0 ) {
			if( strcmp(exp->type, idref->se->type) != 0 ) {
				printf("%sERROR : %s(semantics)%s expression on the right side of := does not match the type of variable in LHS at line %d\n", BOLDRED, BOLDBLUE, RESET, idref->tptr->lno);
				*errors = 1;
			}
		}
		else {
			// expression calculation error
		}
	}
	else {
		// scoping errors 
	}

}


int checkSemantics(treeNode * head, symbolScope * sHead, int * errors) {

	treeNode * child;
	child = head->childL;

	while(child != NULL) {

		if(child->childL == NULL) {
			// terminal
		}
		else {
			checkSemantics(child, sHead, errors);
			
			// checks the expression subtree
			if( strcmp(child->id->val, "<expression>") == 0 ) {
				expressionCheckerInit(child, errors);
			}
			else if( strcmp(child->id->val, "<condionalStmt>") == 0 ) {
				switchSemantics(child, errors);
			}
			else if( strcmp(child->id->val, "<moduleReuseStmt>") == 0 ) {
				callingModule(child, sHead, errors);
			}
			else if( strcmp(child->id->val, "<ioStmt>") == 0 ) {
				checkIOStmt(child, errors);
			}
			else if( strcmp(child->id->val, "<iterativeStmt>") == 0 ) {
				checkIterativeStmt(child, errors);
			}
			else if( strcmp(child->id->val, "<assignmentStmt>") == 0 ) {
				checkAssignmentStmt(child, errors);
			}

		}
		child = child->next;		
	} 
}