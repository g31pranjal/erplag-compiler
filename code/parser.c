#include "parserDef.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "aux.c"

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
	
	nw->trm_num = 0;
	nw->ntrm_num = 0;
	nw->rule_num = 0;

	return nw;
}

rule * addRuleToGrammar(grammar * gr) {

	rule * nw;
	nw = (rule *)malloc(sizeof(rule));
	
	(nw->lhs).next = (nw->lhs).prev = NULL;
	(nw->lhs).data = NULL;	
	nw->rhstop = nw->rhsbot = NULL;
	nw->next = nw->prev = NULL;

	if(gr->top == NULL && gr->bot == NULL) {
		gr->top = gr->bot = nw;
	}
	else {
		rule * lst;
		lst = gr->bot;
		lst->next = nw;
		nw->prev = lst;
		gr->bot = nw;
	}

	gr->rule_num++;

	return nw;
}


element * searchForTerminal(grammar * gr, char * trm_name) {
	
	int key = ((int)trm_name[0])-65, i;

	element * node = gr->trm[key];

	while(node != NULL) {
		if(strcmp(node->val, trm_name) == 0) {
			node->occurances[node->occ_num++] = gr->rule_num;
			return node;
		}
		node = node->next;
	}

	element * nw;
	nw = (element *)malloc(sizeof(element));
	nw->type = 0;
	for(i=0;i<20;i++) {
		nw->occurances[i] = 0;
	}
	nw->occ_num = 0;
	
	strcpy(nw->val, trm_name);
	nw->occurances[nw->occ_num++] = gr->rule_num;

	nw->next = gr->trm[key];
	gr->trm[key] = nw;
	gr->trm_num++;


	return nw;
}

element * searchForNonTerminal(grammar * gr, char * trm_name) {
	
	int key = ((int)trm_name[1])-97, i;

	element * node = gr->ntrm[key];

	while(node != NULL) {
		if(strcmp(node->val, trm_name) == 0) {
			node->occurances[node->occ_num++] = gr->rule_num;
			return node;
		}
		node = node->next;
	}

	element * nw;
	nw = (element *)malloc(sizeof(element));
	nw->type = 1;
	for(i=0;i<20;i++) {
		nw->occurances[i] = 0;
	}
	nw->occ_num = 0;
	
	strcpy(nw->val, trm_name);
	nw->occurances[nw->occ_num++] = gr->rule_num;
	
	nw->next = gr->ntrm[key];
	gr->ntrm[key] = nw;
	gr->ntrm_num++;

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
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<program>");
	fillRuleRHS(gr, rl, "<moduleDeclarations>");
	fillRuleRHS(gr, rl, "<otherModules>");
	fillRuleRHS(gr, rl, "<driverModule>");
	fillRuleRHS(gr, rl, "<otherModules>");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<moduleDeclarations>");
	fillRuleRHS(gr, rl, "<moduleDeclaration>");
	fillRuleRHS(gr, rl, "<moduleDeclarations>");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<moduleDeclarations>");
	fillRuleRHS(gr, rl, "EMPTY");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<moduleDeclaration>");
	fillRuleRHS(gr, rl, "DECLARE");
	fillRuleRHS(gr, rl, "MODULE");
	fillRuleRHS(gr, rl, "ID");
	fillRuleRHS(gr, rl, "SEMICOL");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<otherModules>");
	fillRuleRHS(gr, rl, "<module>");
	fillRuleRHS(gr, rl, "<otherModules>");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<otherModules>");
	fillRuleRHS(gr, rl, "EMPTY");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<driverModule>");
	fillRuleRHS(gr, rl, "DEF");
	fillRuleRHS(gr, rl, "DRIVER");
	fillRuleRHS(gr, rl, "PROGRAM");
	fillRuleRHS(gr, rl, "ENDDEF");
	fillRuleRHS(gr, rl, "<moduleDef>");
	
	rl = addRuleToGrammar(gr);
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
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<ret>");
	fillRuleRHS(gr, rl, "RETURNS");
	fillRuleRHS(gr, rl, "SQBO");
	fillRuleRHS(gr, rl, "<output_plist>");
	fillRuleRHS(gr, rl, "SQBC");
	fillRuleRHS(gr, rl, "SEMICOL");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<ret>");
	fillRuleRHS(gr, rl, "EMPTY");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<input_plist>");
	fillRuleRHS(gr, rl, "ID");
	fillRuleRHS(gr, rl, "COLON");
	fillRuleRHS(gr, rl, "<dataType>");
	fillRuleRHS(gr, rl, "<input_plistRec>");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<input_plistRec>");
	fillRuleRHS(gr, rl, "COMMA");
	fillRuleRHS(gr, rl, "ID");
	fillRuleRHS(gr, rl, "COLON");
	fillRuleRHS(gr, rl, "<dataType>");
	fillRuleRHS(gr, rl, "<input_plistRec>");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<input_plistRec>");
	fillRuleRHS(gr, rl, "EMPTY");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<output_plist>");
	fillRuleRHS(gr, rl, "ID");
	fillRuleRHS(gr, rl, "COLON");
	fillRuleRHS(gr, rl, "<type>");
	fillRuleRHS(gr, rl, "<output_plistRec>");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<output_plistRec>");
	fillRuleRHS(gr, rl, "COMMA");
	fillRuleRHS(gr, rl, "ID");
	fillRuleRHS(gr, rl, "COLON");
	fillRuleRHS(gr, rl, "<type>");
	fillRuleRHS(gr, rl, "<output_plistRec>");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<output_plistRec>");
	fillRuleRHS(gr, rl, "EMPTY");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<type>");
	fillRuleRHS(gr, rl, "INTEGER");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<type>");
	fillRuleRHS(gr, rl, "REAL");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<type>");
	fillRuleRHS(gr, rl, "BOOLEAN");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<dataType>");
	fillRuleRHS(gr, rl, "<type>");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<dataType>");
	fillRuleRHS(gr, rl, "ARRAY");
	fillRuleRHS(gr, rl, "SQBO");
	fillRuleRHS(gr, rl, "<range>");
	fillRuleRHS(gr, rl, "SQBC");
	fillRuleRHS(gr, rl, "OF");
	fillRuleRHS(gr, rl, "<type>");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<moduleDef>");
	fillRuleRHS(gr, rl, "START");
	fillRuleRHS(gr, rl, "<statements>");
	fillRuleRHS(gr, rl, "END");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<statements>");
	fillRuleRHS(gr, rl, "<statement>");
	fillRuleRHS(gr, rl, "<statements>");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<statements>");
	fillRuleRHS(gr, rl, "EMPTY");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<statement>");
	fillRuleRHS(gr, rl, "<ioStmt>");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<statement>");
	fillRuleRHS(gr, rl, "<simpleStmt>");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<statement>");
	fillRuleRHS(gr, rl, "<declareStmt>");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<statement>");
	fillRuleRHS(gr, rl, "<condionalStmt>");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<statement>");
	fillRuleRHS(gr, rl, "<iterativeStmt>");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<statement>");
	fillRuleRHS(gr, rl, "SEMICOL");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<ioStmt>");
	fillRuleRHS(gr, rl, "GET_VALUE");
	fillRuleRHS(gr, rl, "ID");
	fillRuleRHS(gr, rl, "BO");
	fillRuleRHS(gr, rl, "<whichId>");
	fillRuleRHS(gr, rl, "BC");
	fillRuleRHS(gr, rl, "SEMICOL");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<ioStmt>");
	fillRuleRHS(gr, rl, "PRINT");
	fillRuleRHS(gr, rl, "BO");
	fillRuleRHS(gr, rl, "<print_val>");
	fillRuleRHS(gr, rl, "BC");
	fillRuleRHS(gr, rl, "SEMICOL");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<print_val>");
	fillRuleRHS(gr, rl, "ID");
	fillRuleRHS(gr, rl, "<whichId>");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<print_val>");
	fillRuleRHS(gr, rl, "NUM");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<print_val>");
	fillRuleRHS(gr, rl, "RNUM");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<print_val>");
	fillRuleRHS(gr, rl, "TRUE");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<print_val>");
	fillRuleRHS(gr, rl, "FALSE");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<whichId>");
	fillRuleRHS(gr, rl, "SQBO");
	fillRuleRHS(gr, rl, "<index>");
	fillRuleRHS(gr, rl, "SQBC");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<whichId>");
	fillRuleRHS(gr, rl, "EMPTY");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<index>");
	fillRuleRHS(gr, rl, "NUM");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<index>");
	fillRuleRHS(gr, rl, "ID");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<simpleStmt>");
	fillRuleRHS(gr, rl, "<assignmentStmt>");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<simpleStmt>");
	fillRuleRHS(gr, rl, "<moduleReuseStmt>");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<assignmentStmt>");
	fillRuleRHS(gr, rl, "ID");
	fillRuleRHS(gr, rl, "<whichId>");
	fillRuleRHS(gr, rl, "ASSIGNOP");
	fillRuleRHS(gr, rl, "<expression>");
	fillRuleRHS(gr, rl, "SEMICOL");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<moduleReuseStmt>");
	fillRuleRHS(gr, rl, "<optional>");
	fillRuleRHS(gr, rl, "USE");
	fillRuleRHS(gr, rl, "MODULE");
	fillRuleRHS(gr, rl, "ID");
	fillRuleRHS(gr, rl, "WITH");
	fillRuleRHS(gr, rl, "PARAMETERS");
	fillRuleRHS(gr, rl, "<idList>");
	fillRuleRHS(gr, rl, "SEMICOL");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<optional>");
	fillRuleRHS(gr, rl, "SQBO");
	fillRuleRHS(gr, rl, "<idList>");
	fillRuleRHS(gr, rl, "SQBC");
	fillRuleRHS(gr, rl, "ASSIGNOP");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<optional>");
	fillRuleRHS(gr, rl, "EMPTY");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<idList>");
	fillRuleRHS(gr, rl, "ID");
	fillRuleRHS(gr, rl, "<idListRec>");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<idListRec>");
	fillRuleRHS(gr, rl, "COMMA");
	fillRuleRHS(gr, rl, "ID");
	fillRuleRHS(gr, rl, "<idListRec>");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<idListRec>");
	fillRuleRHS(gr, rl, "EMPTY");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<expression>");
	fillRuleRHS(gr, rl, "<arithmeticExpr>");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<expression>");
	fillRuleRHS(gr, rl, "<booleanExpr>");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<arithmeticExpr>");
	fillRuleRHS(gr, rl, "<term>");
	fillRuleRHS(gr, rl, "<arithmeticExprRec>");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<arithmeticExprRec>");
	fillRuleRHS(gr, rl, "<pm>");
	fillRuleRHS(gr, rl, "<term>");
	fillRuleRHS(gr, rl, "<arithmeticExprRec>");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<arithmeticExprRec>");
	fillRuleRHS(gr, rl, "EMPTY");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<term>");
	fillRuleRHS(gr, rl, "<factor>");
	fillRuleRHS(gr, rl, "<termRec>");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<termRec>");
	fillRuleRHS(gr, rl, "<md>");
	fillRuleRHS(gr, rl, "<factor>");
	fillRuleRHS(gr, rl, "<termRec>");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<termRec>");
	fillRuleRHS(gr, rl, "EMPTY");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<factor>");
	fillRuleRHS(gr, rl, "BO");
	fillRuleRHS(gr, rl, "<arithmeticExpr>");
	fillRuleRHS(gr, rl, "BC");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<factor>");
	fillRuleRHS(gr, rl, "<var>");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<var>");
	fillRuleRHS(gr, rl, "ID");
	fillRuleRHS(gr, rl, "<whichId>");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<var>");
	fillRuleRHS(gr, rl, "NUM");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<var>");
	fillRuleRHS(gr, rl, "RNUM");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<pm>");
	fillRuleRHS(gr, rl, "PLUS");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<pm>");
	fillRuleRHS(gr, rl, "MINUS");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<md>");
	fillRuleRHS(gr, rl, "MUL");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<md>");
	fillRuleRHS(gr, rl, "DIV");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<booleanExpr>");
	fillRuleRHS(gr, rl, "<booleanSegment>");
	fillRuleRHS(gr, rl, "<booleanExprRec>");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<booleanExprRec>");
	fillRuleRHS(gr, rl, "<logicalOp>");
	fillRuleRHS(gr, rl, "<booleanSegment>");
	fillRuleRHS(gr, rl, "<booleanExprRec>");

	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<booleanExprRec>");
	fillRuleRHS(gr, rl, "EMPTY");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<logicalOp>");
	fillRuleRHS(gr, rl, "AND");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<logicalOp>");
	fillRuleRHS(gr, rl, "OR");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<booleanSegment>");
	fillRuleRHS(gr, rl, "<arithmeticExpr>");
	fillRuleRHS(gr, rl, "<relationalOp>");
	fillRuleRHS(gr, rl, "<arithmeticExpr>");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<booleanSegment>");
	fillRuleRHS(gr, rl, "BO");
	fillRuleRHS(gr, rl, "<booleanExpr>");
	fillRuleRHS(gr, rl, "BC");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<relationalOp>");
	fillRuleRHS(gr, rl, "LT");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<relationalOp>");
	fillRuleRHS(gr, rl, "LE");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<relationalOp>");
	fillRuleRHS(gr, rl, "GT");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<relationalOp>");
	fillRuleRHS(gr, rl, "GE");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<relationalOp>");
	fillRuleRHS(gr, rl, "NE");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<relationalOp>");
	fillRuleRHS(gr, rl, "EQ");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<declareStmt>");
	fillRuleRHS(gr, rl, "DECLARE");
	fillRuleRHS(gr, rl, "<idList>");
	fillRuleRHS(gr, rl, "COLON");
	fillRuleRHS(gr, rl, "<dataType>");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<condionalStmt>");
	fillRuleRHS(gr, rl, "SWITCH");
	fillRuleRHS(gr, rl, "BO");
	fillRuleRHS(gr, rl, "<expression>");
	fillRuleRHS(gr, rl, "BC");
	fillRuleRHS(gr, rl, "START");
	fillRuleRHS(gr, rl, "<caseStmt>");
	fillRuleRHS(gr, rl, "<default>");
	fillRuleRHS(gr, rl, "END");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<caseStmt>");
	fillRuleRHS(gr, rl, "CASE");
	fillRuleRHS(gr, rl, "<value>");
	fillRuleRHS(gr, rl, "COLON");
	fillRuleRHS(gr, rl, "<statements>");
	fillRuleRHS(gr, rl, "BREAK");
	fillRuleRHS(gr, rl, "SEMICOL");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<value>");
	fillRuleRHS(gr, rl, "NUM");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<value>");
	fillRuleRHS(gr, rl, "TRUE");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<value>");
	fillRuleRHS(gr, rl, "FALSE");

	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<default>");
	fillRuleRHS(gr, rl, "DEFAULT");
	fillRuleRHS(gr, rl, "COLON");
	fillRuleRHS(gr, rl, "<statements>");
	fillRuleRHS(gr, rl, "BREAK");
	fillRuleRHS(gr, rl, "SEMICOL");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<default>");
	fillRuleRHS(gr, rl, "EMPTY");
	
	rl = addRuleToGrammar(gr);
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
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<iterativeStmt>");
	fillRuleRHS(gr, rl, "WHILE");
	fillRuleRHS(gr, rl, "BO");
	fillRuleRHS(gr, rl, "<booleanExpr>");
	fillRuleRHS(gr, rl, "BC");
	fillRuleRHS(gr, rl, "START");
	fillRuleRHS(gr, rl, "<statements>");
	fillRuleRHS(gr, rl, "END");
	
	rl = addRuleToGrammar(gr);
	fillRuleLHS(gr, rl, "<range>");
	fillRuleRHS(gr, rl, "NUM");
	fillRuleRHS(gr, rl, "RANGEOP");
	fillRuleRHS(gr, rl, "NUM");
	
	printGrammar(gr);

	return 0;
}