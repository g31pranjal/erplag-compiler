

char * expressionCheckerRec(treeNode * nd) {

	char * l, r;

	printf("rec : %s\n", nd->id->val);

	if( strcmp(nd->id->val, "AND") == 0 || strcmp(nd->id->val, "OR") == 0 ) {
		// BOOLEAN <op> BOOLEAN = BOOLEAN
		l = expressionCheckerRec(nd->childL);
		r = expressionCheckerRec(nd->childR);
		if( strcmp(nd->childL->type, "BOOLEAN") == 0 && strcmp(nd->childR->type, "BOOLEAN") == 0 ) {
			strcpy(nd->type, "BOOLEAN");
		}
		else {
			printf("ERROR : lhs of type '%s' does not match rhs of type '%s' for operator %s\n", nd->childL->type, nd->childR->type, nd->tptr->val);
			return NULL;
		}
	}
	else if( strcmp(nd->id->val, "LE") == 0 || strcmp(nd->id->val, "LT") == 0 ||  strcmp(nd->id->val, "GE") == 0 || strcmp(nd->id->val, "GT") == 0 ||  strcmp(nd->id->val, "NE") == 0 || strcmp(nd->id->val, "EQ") == 0  ) {
		// INTEGER <op> INTEGER = BOOLEAN
		// REAL <op> REAL = BOOLEAN
		l = expressionCheckerRec(nd->childL);
		r = expressionCheckerRec(nd->childR);
		if( strcmp(nd->childL->type, "INTEGER") == 0 && strcmp(nd->childR->type, "INTEGER") == 0 ) {
			strcpy(nd->type, "BOOLEAN");
		}
		else if( strcmp(nd->childL->type, "REAL") == 0 && strcmp(nd->childR->type, "REAL") == 0 ) {
			strcpy(nd->type, "BOOLEAN");
		}
		else {
			printf("ERROR : lhs of type '%s' does not match rhs of type '%s' for operator %s\n", nd->childL->type, nd->childR->type, nd->tptr->val);
			return NULL;
		}
	}
	else if( strcmp(nd->id->val, "PLUS") == 0 || strcmp(nd->id->val, "MINUS") == 0 ||  strcmp(nd->id->val, "MUL") == 0 || strcmp(nd->id->val, "DIV") == 0  ) {
		// INTEGER <op> INTEGER = INTEGER
		// REAL <op> REAL = REAL
		l = expressionCheckerRec(nd->childL);
		r = expressionCheckerRec(nd->childR);
		if( strcmp(nd->childL->type, "INTEGER") == 0 && strcmp(nd->childR->type, "INTEGER") == 0 ) {
			strcpy(nd->type, "INTEGER");
		}
		else if( strcmp(nd->childL->type, "REAL") == 0 && strcmp(nd->childR->type, "REAL") == 0 ) {
			strcpy(nd->type, "REAL");
		}
		else {
			printf("ERROR : lhs of type '%s' does not match rhs of type '%s' for operator %s\n", nd->childL->type, nd->childR->type, nd->tptr->val);
			return NULL;
		}
	}
	else if( strcmp(nd->id->val, "<var>") == 0 ) {
		if( strcmp(nd->childL->id->val,"NUM") == 0 )
			strcpy(nd->type, "INTEGER");
		else if( strcmp(nd->childL->id->val,"RNUM") == 0 )
			strcpy(nd->type, "REAL");
		else if( strcmp(nd->childL->id->val,"ID") == 0 ){
			printf("var is ID of type : %s\n", nd->childL->se->type);
			strcpy(nd->type, nd->childL->se->type);		
		}

	}

}


int expressionCheckerInit(treeNode * exp) {
	
	char * yup;
	if( exp->childL == exp->childR ) {
		printf("only one child to recurse on\n");
		
		yup = expressionCheckerRec(exp->childL);
	}
	else {
		// first child is MINUS , recurse on other to determine
	}


	// char * writefn  = "out.put";
	// FILE * fp = fopen(writefn, "w+");
	// printParseTree(exp, fp);
}


int checkSemantics(treeNode * head) {

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
				printf("expression detected.\n");
				expressionCheckerInit(child);
			}
			else {
				checkSemantics(child);
			}



		}



		child = child->next;
		
	} 

}