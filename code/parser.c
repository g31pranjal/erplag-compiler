#include "parserDef.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

grammar * createGrammar() {
	grammar * nw;
	nw = (grammar *)malloc(sizeof(grammar));
	nw->top = NULL;
	nw->bot = NULL;

	int i;
	for(i=0;i<26;i++) {
		nw->trm[i] = NULL;
		nw->ntrm[i] = NULL;
	}

	return nw;
}

int printGrammar(grammar * gr) {

	printf("****** RULES *********\n");

	rule * rl = gr->top;
	ruleSeg * rs;

	while(rl != NULL) {
		printf("%s -> ", rl->lhs.data->val);
		rs = rl->rhstop;
		while(rs != NULL) {
			printf("%s, ", rs->data->val);
			rs = rs->next;
		}
		printf("\n");
		rl = rl->next;
	}

	printf("****** TERMINALS *******\n");

	element * node;

	for(int i=0;i<26;i++) {
		printf("%d\t", i);
		node = gr->trm[i];
		while(node != NULL) {
			printf("%x, %s -> ", node, node->val);
			node = node->next;
		}
		printf("\n");
	}

	printf("****** non TERMINALS *******\n");

	for(int i=0;i<26;i++) {
		printf("%d\t", i);
		node = gr->ntrm[i];
		while(node != NULL) {
			printf("%x, %s -> ", node, node->val);
			node = node->next;
		}
		printf("\n");
	}

}

int addRuleToGrammar(grammar * gr, rule * rl) {
	if(gr->top == NULL && gr->bot == NULL) {
		gr->top = gr->bot = rl;
	}
	else {
		rule * lst;
		lst = gr->bot;
		lst->next = rl;
		rl->prev = lst;
		gr->bot = rl;
	}
	return 0;
}

rule * createRule() {
	rule * nw;
	nw = (rule *)malloc(sizeof(rule));
	
	(nw->lhs).next = (nw->lhs).prev = NULL;
	(nw->lhs).data = NULL;	
	nw->rhstop = nw->rhsbot = NULL;
	nw->next = nw->prev = NULL;

	return nw;
}

element * searchForTerminal(grammar * gr, char * trm_name) {
	
	int key = ((int)trm_name[0])-65;

	element * node = gr->trm[key];

	while(node != NULL) {
		if(strcmp(node->val, trm_name) == 0)
			return node;
		node = node->next;
	}

	element * nw;
	nw = (element *)malloc(sizeof(element));
	nw->type = 0;
	strcpy(nw->val, trm_name);
	nw->next = gr->trm[key];
	gr->trm[key] = nw;

	return nw;
}

element * searchForNonTerminal(grammar * gr, char * trm_name) {
	
	int key = ((int)trm_name[1])-97;

	element * node = gr->ntrm[key];

	while(node != NULL) {
		if(strcmp(node->val, trm_name) == 0)
			return node;
		node = node->next;
	}

	element * nw;
	nw = (element *)malloc(sizeof(element));
	nw->type = 1;
	strcpy(nw->val, trm_name);
	nw->next = gr->ntrm[key];
	gr->ntrm[key] = nw;

	return nw;
}

int fillRuleLHS(grammar * gr, rule * rl, char * ntrm) {
	rl->lhs.data = searchForNonTerminal(gr, ntrm);
}

int fillRuleRHS(grammar * gr, rule * rl, char * str) {

	element * ref;

	if(str[0] == '<') 
		ref = searchForNonTerminal(gr, str);
	else
		ref = searchForTerminal(gr, str);

	ruleSeg * nw, * lst;
	nw = (ruleSeg *)malloc(sizeof(ruleSeg));
	nw->next = nw->prev = NULL;
	nw->data = ref;

	if(rl->rhstop == NULL && rl->rhsbot == NULL) {
		rl->rhstop = rl->rhsbot = nw;
	}
	else {
		lst = rl->rhsbot;
		lst->next = nw;
		nw->prev = lst;
		rl->rhsbot = nw;
	}

	return 0;

}


int main() {

	grammar * gr = createGrammar();

	rule * rl;
	rl = createRule();
	fillRuleLHS(gr, rl, "<program>");
	fillRuleRHS(gr, rl, "<moduleDeclarations>");
	fillRuleRHS(gr, rl, "<otherModules>");
	fillRuleRHS(gr, rl, "<driverModule>");
	fillRuleRHS(gr, rl, "<otherModules>");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<moduleDeclarations>");
	fillRuleRHS(gr, rl, "<moduleDeclaration>");
	fillRuleRHS(gr, rl, "<moduleDeclarations>");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<moduleDeclarations>");
	fillRuleRHS(gr, rl, "EMPTY");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<moduleDeclaration>");
	fillRuleRHS(gr, rl, "DECLARE");
	fillRuleRHS(gr, rl, "MODULE");
	fillRuleRHS(gr, rl, "ID");
	fillRuleRHS(gr, rl, "SEMICOL");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<otherModules>");
	fillRuleRHS(gr, rl, "<module>");
	fillRuleRHS(gr, rl, "<otherModules>");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<otherModules>");
	fillRuleRHS(gr, rl, "EMPTY");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<driverModule>");
	fillRuleRHS(gr, rl, "DEF");
	fillRuleRHS(gr, rl, "DRIVER");
	fillRuleRHS(gr, rl, "PROGRAM");
	fillRuleRHS(gr, rl, "ENDDEF");
	fillRuleRHS(gr, rl, "<moduleDef>");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<module>");
	fillRuleRHS(gr, rl, "DEF");
	fillRuleRHS(gr, rl, "MODULE");
	fillRuleRHS(gr, rl, "ID");
	fillRuleRHS(gr, rl, "ENDDEF");
	fillRuleRHS(gr, rl, "<moduleDef>");
	fillRuleRHS(gr, rl, "TAKES");
	fillRuleRHS(gr, rl, "INPUT");
	fillRuleRHS(gr, rl, "SQBO");
	fillRuleRHS(gr, rl, "<input_plist>");
	fillRuleRHS(gr, rl, "SQBC");
	fillRuleRHS(gr, rl, "SEMICOL");
	fillRuleRHS(gr, rl, "<ret>");
	fillRuleRHS(gr, rl, "<moduleDef>");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<ret>");
	fillRuleRHS(gr, rl, "RETURNS");
	fillRuleRHS(gr, rl, "SQBO");
	fillRuleRHS(gr, rl, "<output_plist>");
	fillRuleRHS(gr, rl, "SQBC");
	fillRuleRHS(gr, rl, "SEMICOL");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<ret>");
	fillRuleRHS(gr, rl, "EMPTY");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<input_plist>");
	fillRuleRHS(gr, rl, "ID");
	fillRuleRHS(gr, rl, "COLON");
	fillRuleRHS(gr, rl, "<dataType>");
	fillRuleRHS(gr, rl, "<input_plistRec>");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<input_plistRec>");
	fillRuleRHS(gr, rl, "COMMA");
	fillRuleRHS(gr, rl, "ID");
	fillRuleRHS(gr, rl, "COLON");
	fillRuleRHS(gr, rl, "<dataType>");
	fillRuleRHS(gr, rl, "<input_plistRec>");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<input_plistRec>");
	fillRuleRHS(gr, rl, "EMPTY");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<output_plist>");
	fillRuleRHS(gr, rl, "ID");
	fillRuleRHS(gr, rl, "COLON");
	fillRuleRHS(gr, rl, "<type>");
	fillRuleRHS(gr, rl, "<output_plistRec>");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<output_plistRec>");
	fillRuleRHS(gr, rl, "COMMA");
	fillRuleRHS(gr, rl, "ID");
	fillRuleRHS(gr, rl, "COLON");
	fillRuleRHS(gr, rl, "<type>");
	fillRuleRHS(gr, rl, "<output_plistRec>");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<output_plistRec>");
	fillRuleRHS(gr, rl, "EMPTY");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<type>");
	fillRuleRHS(gr, rl, "INTEGER");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<type>");
	fillRuleRHS(gr, rl, "REAL");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<type>");
	fillRuleRHS(gr, rl, "BOOLEAN");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<dataType>");
	fillRuleRHS(gr, rl, "<type>");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<dataType>");
	fillRuleRHS(gr, rl, "ARRAY");
	fillRuleRHS(gr, rl, "SQBO");
	fillRuleRHS(gr, rl, "<range>");
	fillRuleRHS(gr, rl, "SQBC");
	fillRuleRHS(gr, rl, "OF");
	fillRuleRHS(gr, rl, "<type>");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<moduleDef>");
	fillRuleRHS(gr, rl, "START");
	fillRuleRHS(gr, rl, "<statements>");
	fillRuleRHS(gr, rl, "END");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<statements>");
	fillRuleRHS(gr, rl, "<statement>");
	fillRuleRHS(gr, rl, "<statements>");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<statements>");
	fillRuleRHS(gr, rl, "EMPTY");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<statement>");
	fillRuleRHS(gr, rl, "<ioStmt>");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<statement>");
	fillRuleRHS(gr, rl, "<simpleStmt>");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<statement>");
	fillRuleRHS(gr, rl, "<declareStmt>");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<statement>");
	fillRuleRHS(gr, rl, "<condionalStmt>");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<statement>");
	fillRuleRHS(gr, rl, "<iterativeStmt>");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<statement>");
	fillRuleRHS(gr, rl, "SEMICOL");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<ioStmt>");
	fillRuleRHS(gr, rl, "GET_VALUE");
	fillRuleRHS(gr, rl, "ID");
	fillRuleRHS(gr, rl, "BO");
	fillRuleRHS(gr, rl, "<whichId>");
	fillRuleRHS(gr, rl, "BC");
	fillRuleRHS(gr, rl, "SEMICOL");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<ioStmt>");
	fillRuleRHS(gr, rl, "PRINT");
	fillRuleRHS(gr, rl, "BO");
	fillRuleRHS(gr, rl, "<print_val>");
	fillRuleRHS(gr, rl, "BC");
	fillRuleRHS(gr, rl, "SEMICOL");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<print_val>");
	fillRuleRHS(gr, rl, "ID");
	fillRuleRHS(gr, rl, "<whichId>");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<print_val>");
	fillRuleRHS(gr, rl, "NUM");
	addRuleToGrammar(gr, rl);rl = createRule();
	fillRuleLHS(gr, rl, "<print_val>");
	fillRuleRHS(gr, rl, "RNUM");
	addRuleToGrammar(gr, rl);rl = createRule();
	fillRuleLHS(gr, rl, "<print_val>");
	fillRuleRHS(gr, rl, "TRUE");
	addRuleToGrammar(gr, rl);rl = createRule();
	fillRuleLHS(gr, rl, "<print_val>");
	fillRuleRHS(gr, rl, "FALSE");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<whichId>");
	fillRuleRHS(gr, rl, "SQBO");
	fillRuleRHS(gr, rl, "<index>");
	fillRuleRHS(gr, rl, "SQBC");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<whichId>");
	fillRuleRHS(gr, rl, "EMPTY");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<index>");
	fillRuleRHS(gr, rl, "NUM");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<index>");
	fillRuleRHS(gr, rl, "ID");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<simpleStmt>");
	fillRuleRHS(gr, rl, "<assignmentStmt>");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<simpleStmt>");
	fillRuleRHS(gr, rl, "<moduleReuseStmt>");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<assignmentStmt>");
	fillRuleRHS(gr, rl, "ID");
	fillRuleRHS(gr, rl, "<whichId>");
	fillRuleRHS(gr, rl, "ASSIGNOP");
	fillRuleRHS(gr, rl, "<expression>");
	fillRuleRHS(gr, rl, "SEMICOL");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<moduleReuseStmt>");
	fillRuleRHS(gr, rl, "<optional>");
	fillRuleRHS(gr, rl, "USE");
	fillRuleRHS(gr, rl, "MODULE");
	fillRuleRHS(gr, rl, "ID");
	fillRuleRHS(gr, rl, "WITH");
	fillRuleRHS(gr, rl, "PARAMETERS");
	fillRuleRHS(gr, rl, "<idList>");
	fillRuleRHS(gr, rl, "SEMICOL");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<optional>");
	fillRuleRHS(gr, rl, "SQBO");
	fillRuleRHS(gr, rl, "<idList>");
	fillRuleRHS(gr, rl, "SQBC");
	fillRuleRHS(gr, rl, "ASSIGNOP");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<optional>");
	fillRuleRHS(gr, rl, "EMPTY");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<idList>");
	fillRuleRHS(gr, rl, "ID");
	fillRuleRHS(gr, rl, "<idListRec>");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<idListRec>");
	fillRuleRHS(gr, rl, "COMMA");
	fillRuleRHS(gr, rl, "ID");
	fillRuleRHS(gr, rl, "<idListRec>");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<idListRec>");
	fillRuleRHS(gr, rl, "EMPTY");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<expression>");
	fillRuleRHS(gr, rl, "<arithmeticExpr>");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<expression>");
	fillRuleRHS(gr, rl, "<booleanExpr>");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<arithmeticExpr>");
	fillRuleRHS(gr, rl, "<term>");
	fillRuleRHS(gr, rl, "<arithmeticExprRec>");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<arithmeticExprRec>");
	fillRuleRHS(gr, rl, "<pm>");
	fillRuleRHS(gr, rl, "<term>");
	fillRuleRHS(gr, rl, "<arithmeticExprRec>");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<arithmeticExprRec>");
	fillRuleRHS(gr, rl, "EMPTY");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<term>");
	fillRuleRHS(gr, rl, "<factor>");
	fillRuleRHS(gr, rl, "<termRec>");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<termRec>");
	fillRuleRHS(gr, rl, "<md>");
	fillRuleRHS(gr, rl, "<factor>");
	fillRuleRHS(gr, rl, "<termRec>");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<termRec>");
	fillRuleRHS(gr, rl, "EMPTY");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<factor>");
	fillRuleRHS(gr, rl, "BO");
	fillRuleRHS(gr, rl, "<arithmeticExpr>");
	fillRuleRHS(gr, rl, "BC");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<factor>");
	fillRuleRHS(gr, rl, "<var>");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<var>");
	fillRuleRHS(gr, rl, "ID");
	fillRuleRHS(gr, rl, "<whichId>");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<var>");
	fillRuleRHS(gr, rl, "NUM");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<var>");
	fillRuleRHS(gr, rl, "RNUM");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<pm>");
	fillRuleRHS(gr, rl, "PLUS");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<pm>");
	fillRuleRHS(gr, rl, "MINUS");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<md>");
	fillRuleRHS(gr, rl, "MUL");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<md>");
	fillRuleRHS(gr, rl, "DIV");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<booleanExpr>");
	fillRuleRHS(gr, rl, "<booleanSegment>");
	fillRuleRHS(gr, rl, "<booleanExprRec>");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<booleanExprRec>");
	fillRuleRHS(gr, rl, "<logicalOp>");
	fillRuleRHS(gr, rl, "<booleanSegment>");
	fillRuleRHS(gr, rl, "<booleanExprRec>");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<logicalOp>");
	fillRuleRHS(gr, rl, "AND");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<logicalOp>");
	fillRuleRHS(gr, rl, "OR");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<booleanSegment>");
	fillRuleRHS(gr, rl, "<arithmeticExpr>");
	fillRuleRHS(gr, rl, "<relationalOp>");
	fillRuleRHS(gr, rl, "<arithmeticExpr>");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<booleanSegment>");
	fillRuleRHS(gr, rl, "BO");
	fillRuleRHS(gr, rl, "<booleanExpr>");
	fillRuleRHS(gr, rl, "BC");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<relationalOp>");
	fillRuleRHS(gr, rl, "LT");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<relationalOp>");
	fillRuleRHS(gr, rl, "LE");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<relationalOp>");
	fillRuleRHS(gr, rl, "GT");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<relationalOp>");
	fillRuleRHS(gr, rl, "GE");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<relationalOp>");
	fillRuleRHS(gr, rl, "NE");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<relationalOp>");
	fillRuleRHS(gr, rl, "EQ");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<declareStmt>");
	fillRuleRHS(gr, rl, "DECLARE");
	fillRuleRHS(gr, rl, "<idList>");
	fillRuleRHS(gr, rl, "COLON");
	fillRuleRHS(gr, rl, "<dataType>");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<condionalStmt>");
	fillRuleRHS(gr, rl, "SWITCH");
	fillRuleRHS(gr, rl, "BO");
	fillRuleRHS(gr, rl, "<expression>");
	fillRuleRHS(gr, rl, "BC");
	fillRuleRHS(gr, rl, "START");
	fillRuleRHS(gr, rl, "<caseStmt>");
	fillRuleRHS(gr, rl, "<default>");
	fillRuleRHS(gr, rl, "END");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<caseStmt>");
	fillRuleRHS(gr, rl, "CASE");
	fillRuleRHS(gr, rl, "<value>");
	fillRuleRHS(gr, rl, "COLON");
	fillRuleRHS(gr, rl, "<statements>");
	fillRuleRHS(gr, rl, "BREAK");
	fillRuleRHS(gr, rl, "SEMICOL");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<value>");
	fillRuleRHS(gr, rl, "NUM");
	fillRuleRHS(gr, rl, "TRUE");
	fillRuleRHS(gr, rl, "FALSE");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<default>");
	fillRuleRHS(gr, rl, "DEFAULT");
	fillRuleRHS(gr, rl, "COLON");
	fillRuleRHS(gr, rl, "<statements>");
	fillRuleRHS(gr, rl, "BREAK");
	fillRuleRHS(gr, rl, "SEMICOL");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<default>");
	fillRuleRHS(gr, rl, "EMPTY");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<iterativeStmt>");
	fillRuleRHS(gr, rl, "FOR");
	fillRuleRHS(gr, rl, "BO");
	fillRuleRHS(gr, rl, "ID");
	fillRuleRHS(gr, rl, "IN");
	fillRuleRHS(gr, rl, "<range>");
	fillRuleRHS(gr, rl, "BC");
	fillRuleRHS(gr, rl, "START");
	fillRuleRHS(gr, rl, "<statements>");
	fillRuleRHS(gr, rl, "END");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<iterativeStmt>");
	fillRuleRHS(gr, rl, "WHILE");
	fillRuleRHS(gr, rl, "BO");
	fillRuleRHS(gr, rl, "<booleanExpr>");
	fillRuleRHS(gr, rl, "BC");
	fillRuleRHS(gr, rl, "START");
	fillRuleRHS(gr, rl, "<statements>");
	fillRuleRHS(gr, rl, "END");
	addRuleToGrammar(gr, rl);
	rl = createRule();
	fillRuleLHS(gr, rl, "<range>");
	fillRuleRHS(gr, rl, "NUM");
	fillRuleRHS(gr, rl, "RANGEOP");
	fillRuleRHS(gr, rl, "NUM");
	addRuleToGrammar(gr, rl);


	printGrammar(gr);

	return 0;
}