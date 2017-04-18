#include "scopeDef.h"


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
				if( strcmp(ind->childL->se->type,"INTEGER") != 0 ) {
					printf("%sERROR : %s(semantics)%s Index of the ARRAY type identifier '%s' at line %d should be of type INTEGER.\n", BOLDRED, BOLDBLUE, RESET, idref->tptr->val, idref->tptr->lno);
					*errors = 1;
				}
				else if(ind->childL->se->isArray == 1)
					checkArrayCases(ind->childL, errors);
			}
		}
		else {
			printf("%sERROR : %s(semantics)%s Identifier '%s' at line %d of type ARRAY should be addressed by an INTEGER index.\n", BOLDRED, BOLDYELLOW, RESET, idref->tptr->val, idref->tptr->lno);
			*errors = 1;
		}
	}
	else {
		printf("error in AST.\n");
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

int checkInputParameters(symbolEntry * invokedModule, symbolScope * scopeRoot, treeNode * idl, int * errors) {

	char *mName;
	symbolScope *childScope, *mScope;
	symbolEntry *se, * prmtrS;

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

	while(idl != NULL) {

		prmtrS = idl->se;

		printf("getting here\n");
		printf("%s %s\n", se->identifier, prmtrS->identifier);

		if(prmtrS != NULL) {
			printf("and here\n");

			if(se->usage == 3) {

				if( ! ( strcmp(prmtrS->type, se->type) == 0 && prmtrS->isArray == se->isArray && prmtrS->startInd == se->startInd && prmtrS->endInd == se->endInd ) ) {
					printf("%sERROR : %s(semantics)%s actual and formal parameters are not matching");
					*errors = 1;
					break;
				}
				else {
					printf("consumed one\n");
					se = se->next;
					idl = idl->prev;
				}
			}
			else {
				se = se->next;
				continue;
			}
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
		else if(invokedModule->usage == 2) {
			if(idref->tptr->lno < invokedModule->lineInit) {
				printf("%sERROR : %s(semantics)%s The module '%s' refernced at line %d must be declared before referencing.\n", BOLDRED, BOLDBLUE, RESET, idref->tptr->val, idref->tptr->lno);
				*errors = 1;			
			}
		}
		else {

			checkInputParameters(idref->se, sHead, idl, errors);
	
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
			printf("error in AST.\n");	
		}
	}
	else {
		printf("error in AST.\n");
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
			printf("error in AST.\n");	
		}
	}
	else {
		printf("error in AST.\n");
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

		}
		child = child->next;		
	} 
}