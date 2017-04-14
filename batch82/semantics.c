

char * expressionCheckerRec(treeNode * nd, int * errors) {

	char * l, r;

	if( strcmp(nd->id->val, "AND") == 0 || strcmp(nd->id->val, "OR") == 0 ) {
		// BOOLEAN <op> BOOLEAN = BOOLEAN
		l = expressionCheckerRec(nd->childL, errors);
		r = expressionCheckerRec(nd->childR, errors);
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
		// INTEGER <op> INTEGER = BOOLEAN
		// REAL <op> REAL = BOOLEAN
		l = expressionCheckerRec(nd->childL, errors);
		r = expressionCheckerRec(nd->childR, errors);
		if( strcmp(nd->childL->type, "INTEGER") == 0 && strcmp(nd->childR->type, "INTEGER") == 0 ) {
			strcpy(nd->type, "BOOLEAN");
		}
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
		// INTEGER <op> INTEGER = INTEGER
		// REAL <op> REAL = REAL
		l = expressionCheckerRec(nd->childL, errors);
		r = expressionCheckerRec(nd->childR, errors);
		if( strcmp(nd->childL->type, "INTEGER") == 0 && strcmp(nd->childR->type, "INTEGER") == 0 ) {
			strcpy(nd->type, "INTEGER");
		}
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
		else if( strcmp(nd->childL->id->val,"ID") == 0 ){
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


int checkSemantics(treeNode * head, int * errors) {

	treeNode * child;
	child = head->childL;

	while(child != NULL) {

		if(child->childL == NULL) {
			// terminal

		}
		else {
			// non-terminal 
			
			// checks the expression subtree
			if( strcmp(child->id->val, "<expression>") == 0 ) {
				expressionCheckerInit(child, errors);
			}
			else {
				checkSemantics(child, errors);
			}



		}



		child = child->next;
		
	} 

}