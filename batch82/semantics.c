#include "scopeDef.h"


checkArrayCases(treeNode * idref, int * errors) {

	printf("checking the array subscript\n");

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
					printf("%sERROR : %s(scope resolution)%s Array index for identifier '%s' at line %d is out of bounds.\n", BOLDRED, BOLDYELLOW, RESET, idref->tptr->val, idref->tptr->lno);
					*errors = 1;
				}
			}
			else {
				if( strcmp(ind->childL->se->type,"INTEGER") != 0 ) {
					printf("%sERROR : %s(scope resolution)%s Index of the ARRAY type identifier '%s' at line %d should be of type INTEGER.\n", BOLDRED, BOLDYELLOW, RESET, idref->tptr->val, idref->tptr->lno);
					*errors = 1;
				}
				else if(ind->childL->se->isArray == 1)
					checkArrayCases(ind->childL, errors);
			}
		}
		else {
			printf("%sERROR : %s(scope resolution)%s Identifier '%s' at line %d of type ARRAY should be addressed by an INTEGER index.\n", BOLDRED, BOLDYELLOW, RESET, idref->tptr->val, idref->tptr->lno);
			*errors = 1;
		}
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
			if( nd->childL->se->isArray == 1 )
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


int checkSemantics(treeNode * head, int * errors) {

	treeNode * child;
	child = head->childL;

	while(child != NULL) {

		if(child->childL == NULL) {
			// terminal

		}
		else {
			
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