#include "parserDef.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int printGrammar(grammar * gr) {

	printf("\n\n ****** RULES *********\n");
	printf("num of rules : %d\n", gr->rule_num);

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

	printf("\n\n ****** TERMINALS *******\n");
	printf("num of terminals : %d\n", gr->trm_num);
	element * node;

	for(int i=0;i<26;i++) {
		printf("%d\n", i);
		node = gr->trm[i];
		while(node != NULL) {
			printf("%x, %s [ ", node, node->val);
			int i;
			for(i=0;i<node->occ_lhs_num;i++) {
				printf("%d, ", node->occ_lhs[i]);
			}
			printf(" | ");
			for(i=0;i<node->occ_rhs_num;i++) {
				printf("%d, ", node->occ_rhs[i]);
			}
			printf(" ] \n");

			node = node->next;
		}
		printf("\n");
	}

	printf("\n\n ****** non TERMINALS *******\n");
	printf("num of non terminals : %d\n", gr->ntrm_num);

	for(int i=0;i<26;i++) {
		printf("%d\n", i);
		node = gr->ntrm[i];
		while(node != NULL) {
			printf("%x, %s [", node, node->val);
			int i;
			for(i=0;i<node->occ_lhs_num;i++) {
				printf("%d, ", node->occ_lhs[i]);
			}
			printf(" | ");
			for(i=0;i<node->occ_rhs_num;i++) {
				printf("%d, ", node->occ_rhs[i]);
			}
			printf(" ] \n");

			node = node->next;
		}
		printf("\n");
	}

}


// int main() {




// 	grammar * gr = createGrammar();

// 	rule * rl;
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<program>");
// 	fillRuleRHS(gr, rl, "<moduleDeclarations>");
// 	fillRuleRHS(gr, rl, "<otherModules>");
// 	fillRuleRHS(gr, rl, "<driverModule>");
// 	fillRuleRHS(gr, rl, "<otherModules>");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<moduleDeclarations>");
// 	fillRuleRHS(gr, rl, "<moduleDeclaration>");
// 	fillRuleRHS(gr, rl, "<moduleDeclarations>");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<moduleDeclarations>");
// 	fillRuleRHS(gr, rl, "EMPTY");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<moduleDeclaration>");
// 	fillRuleRHS(gr, rl, "DECLARE");
// 	fillRuleRHS(gr, rl, "MODULE");
// 	fillRuleRHS(gr, rl, "ID");
// 	fillRuleRHS(gr, rl, "SEMICOL");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<otherModules>");
// 	fillRuleRHS(gr, rl, "<module>");
// 	fillRuleRHS(gr, rl, "<otherModules>");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<otherModules>");
// 	fillRuleRHS(gr, rl, "EMPTY");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<driverModule>");
// 	fillRuleRHS(gr, rl, "DEF");
// 	fillRuleRHS(gr, rl, "DRIVER");
// 	fillRuleRHS(gr, rl, "PROGRAM");
// 	fillRuleRHS(gr, rl, "ENDDEF");
// 	fillRuleRHS(gr, rl, "<moduleDef>");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<module>");
// 	fillRuleRHS(gr, rl, "DEF");
// 	fillRuleRHS(gr, rl, "MODULE");
// 	fillRuleRHS(gr, rl, "ID");
// 	fillRuleRHS(gr, rl, "ENDDEF");
// 	fillRuleRHS(gr, rl, "<moduleDef>");
// 	fillRuleRHS(gr, rl, "TAKES");
// 	fillRuleRHS(gr, rl, "INPUT");
// 	fillRuleRHS(gr, rl, "SQBO");
// 	fillRuleRHS(gr, rl, "<input_plist>");
// 	fillRuleRHS(gr, rl, "SQBC");
// 	fillRuleRHS(gr, rl, "SEMICOL");
// 	fillRuleRHS(gr, rl, "<ret>");
// 	fillRuleRHS(gr, rl, "<moduleDef>");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<ret>");
// 	fillRuleRHS(gr, rl, "RETURNS");
// 	fillRuleRHS(gr, rl, "SQBO");
// 	fillRuleRHS(gr, rl, "<output_plist>");
// 	fillRuleRHS(gr, rl, "SQBC");
// 	fillRuleRHS(gr, rl, "SEMICOL");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<ret>");
// 	fillRuleRHS(gr, rl, "EMPTY");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<input_plist>");
// 	fillRuleRHS(gr, rl, "ID");
// 	fillRuleRHS(gr, rl, "COLON");
// 	fillRuleRHS(gr, rl, "<dataType>");
// 	fillRuleRHS(gr, rl, "<input_plistRec>");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<input_plistRec>");
// 	fillRuleRHS(gr, rl, "COMMA");
// 	fillRuleRHS(gr, rl, "ID");
// 	fillRuleRHS(gr, rl, "COLON");
// 	fillRuleRHS(gr, rl, "<dataType>");
// 	fillRuleRHS(gr, rl, "<input_plistRec>");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<input_plistRec>");
// 	fillRuleRHS(gr, rl, "EMPTY");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<output_plist>");
// 	fillRuleRHS(gr, rl, "ID");
// 	fillRuleRHS(gr, rl, "COLON");
// 	fillRuleRHS(gr, rl, "<type>");
// 	fillRuleRHS(gr, rl, "<output_plistRec>");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<output_plistRec>");
// 	fillRuleRHS(gr, rl, "COMMA");
// 	fillRuleRHS(gr, rl, "ID");
// 	fillRuleRHS(gr, rl, "COLON");
// 	fillRuleRHS(gr, rl, "<type>");
// 	fillRuleRHS(gr, rl, "<output_plistRec>");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<output_plistRec>");
// 	fillRuleRHS(gr, rl, "EMPTY");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<type>");
// 	fillRuleRHS(gr, rl, "INTEGER");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<type>");
// 	fillRuleRHS(gr, rl, "REAL");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<type>");
// 	fillRuleRHS(gr, rl, "BOOLEAN");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<dataType>");
// 	fillRuleRHS(gr, rl, "<type>");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<dataType>");
// 	fillRuleRHS(gr, rl, "ARRAY");
// 	fillRuleRHS(gr, rl, "SQBO");
// 	fillRuleRHS(gr, rl, "<range>");
// 	fillRuleRHS(gr, rl, "SQBC");
// 	fillRuleRHS(gr, rl, "OF");
// 	fillRuleRHS(gr, rl, "<type>");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<moduleDef>");
// 	fillRuleRHS(gr, rl, "START");
// 	fillRuleRHS(gr, rl, "<statements>");
// 	fillRuleRHS(gr, rl, "END");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<statements>");
// 	fillRuleRHS(gr, rl, "<statement>");
// 	fillRuleRHS(gr, rl, "<statements>");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<statements>");
// 	fillRuleRHS(gr, rl, "EMPTY");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<statement>");
// 	fillRuleRHS(gr, rl, "<ioStmt>");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<statement>");
// 	fillRuleRHS(gr, rl, "<simpleStmt>");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<statement>");
// 	fillRuleRHS(gr, rl, "<declareStmt>");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<statement>");
// 	fillRuleRHS(gr, rl, "<condionalStmt>");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<statement>");
// 	fillRuleRHS(gr, rl, "<iterativeStmt>");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<statement>");
// 	fillRuleRHS(gr, rl, "SEMICOL");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<ioStmt>");
// 	fillRuleRHS(gr, rl, "GET_VALUE");
// 	fillRuleRHS(gr, rl, "ID");
// 	fillRuleRHS(gr, rl, "BO");
// 	fillRuleRHS(gr, rl, "<whichId>");
// 	fillRuleRHS(gr, rl, "BC");
// 	fillRuleRHS(gr, rl, "SEMICOL");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<ioStmt>");
// 	fillRuleRHS(gr, rl, "PRINT");
// 	fillRuleRHS(gr, rl, "BO");
// 	fillRuleRHS(gr, rl, "<print_val>");
// 	fillRuleRHS(gr, rl, "BC");
// 	fillRuleRHS(gr, rl, "SEMICOL");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<print_val>");
// 	fillRuleRHS(gr, rl, "ID");
// 	fillRuleRHS(gr, rl, "<whichId>");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<print_val>");
// 	fillRuleRHS(gr, rl, "NUM");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<print_val>");
// 	fillRuleRHS(gr, rl, "RNUM");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<print_val>");
// 	fillRuleRHS(gr, rl, "TRUE");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<print_val>");
// 	fillRuleRHS(gr, rl, "FALSE");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<whichId>");
// 	fillRuleRHS(gr, rl, "SQBO");
// 	fillRuleRHS(gr, rl, "<index>");
// 	fillRuleRHS(gr, rl, "SQBC");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<whichId>");
// 	fillRuleRHS(gr, rl, "EMPTY");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<index>");
// 	fillRuleRHS(gr, rl, "NUM");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<index>");
// 	fillRuleRHS(gr, rl, "ID");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<simpleStmt>");
// 	fillRuleRHS(gr, rl, "<assignmentStmt>");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<simpleStmt>");
// 	fillRuleRHS(gr, rl, "<moduleReuseStmt>");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<assignmentStmt>");
// 	fillRuleRHS(gr, rl, "ID");
// 	fillRuleRHS(gr, rl, "<whichId>");
// 	fillRuleRHS(gr, rl, "ASSIGNOP");
// 	fillRuleRHS(gr, rl, "<expression>");
// 	fillRuleRHS(gr, rl, "SEMICOL");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<moduleReuseStmt>");
// 	fillRuleRHS(gr, rl, "<optional>");
// 	fillRuleRHS(gr, rl, "USE");
// 	fillRuleRHS(gr, rl, "MODULE");
// 	fillRuleRHS(gr, rl, "ID");
// 	fillRuleRHS(gr, rl, "WITH");
// 	fillRuleRHS(gr, rl, "PARAMETERS");
// 	fillRuleRHS(gr, rl, "<idList>");
// 	fillRuleRHS(gr, rl, "SEMICOL");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<optional>");
// 	fillRuleRHS(gr, rl, "SQBO");
// 	fillRuleRHS(gr, rl, "<idList>");
// 	fillRuleRHS(gr, rl, "SQBC");
// 	fillRuleRHS(gr, rl, "ASSIGNOP");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<optional>");
// 	fillRuleRHS(gr, rl, "EMPTY");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<idList>");
// 	fillRuleRHS(gr, rl, "ID");
// 	fillRuleRHS(gr, rl, "<idListRec>");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<idListRec>");
// 	fillRuleRHS(gr, rl, "COMMA");
// 	fillRuleRHS(gr, rl, "ID");
// 	fillRuleRHS(gr, rl, "<idListRec>");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<idListRec>");
// 	fillRuleRHS(gr, rl, "EMPTY");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<expression>");
// 	fillRuleRHS(gr, rl, "<arithmeticExpr>");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<expression>");
// 	fillRuleRHS(gr, rl, "<booleanExpr>");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<arithmeticExpr>");
// 	fillRuleRHS(gr, rl, "<term>");
// 	fillRuleRHS(gr, rl, "<arithmeticExprRec>");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<arithmeticExprRec>");
// 	fillRuleRHS(gr, rl, "<pm>");
// 	fillRuleRHS(gr, rl, "<term>");
// 	fillRuleRHS(gr, rl, "<arithmeticExprRec>");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<arithmeticExprRec>");
// 	fillRuleRHS(gr, rl, "EMPTY");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<term>");
// 	fillRuleRHS(gr, rl, "<factor>");
// 	fillRuleRHS(gr, rl, "<termRec>");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<termRec>");
// 	fillRuleRHS(gr, rl, "<md>");
// 	fillRuleRHS(gr, rl, "<factor>");
// 	fillRuleRHS(gr, rl, "<termRec>");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<termRec>");
// 	fillRuleRHS(gr, rl, "EMPTY");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<factor>");
// 	fillRuleRHS(gr, rl, "BO");
// 	fillRuleRHS(gr, rl, "<arithmeticExpr>");
// 	fillRuleRHS(gr, rl, "BC");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<factor>");
// 	fillRuleRHS(gr, rl, "<var>");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<var>");
// 	fillRuleRHS(gr, rl, "ID");
// 	fillRuleRHS(gr, rl, "<whichId>");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<var>");
// 	fillRuleRHS(gr, rl, "NUM");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<var>");
// 	fillRuleRHS(gr, rl, "RNUM");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<pm>");
// 	fillRuleRHS(gr, rl, "PLUS");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<pm>");
// 	fillRuleRHS(gr, rl, "MINUS");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<md>");
// 	fillRuleRHS(gr, rl, "MUL");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<md>");
// 	fillRuleRHS(gr, rl, "DIV");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<booleanExpr>");
// 	fillRuleRHS(gr, rl, "<booleanSegment>");
// 	fillRuleRHS(gr, rl, "<booleanExprRec>");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<booleanExprRec>");
// 	fillRuleRHS(gr, rl, "<logicalOp>");
// 	fillRuleRHS(gr, rl, "<booleanSegment>");
// 	fillRuleRHS(gr, rl, "<booleanExprRec>");

// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<booleanExprRec>");
// 	fillRuleRHS(gr, rl, "EMPTY");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<logicalOp>");
// 	fillRuleRHS(gr, rl, "AND");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<logicalOp>");
// 	fillRuleRHS(gr, rl, "OR");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<booleanSegment>");
// 	fillRuleRHS(gr, rl, "<arithmeticExpr>");
// 	fillRuleRHS(gr, rl, "<relationalOp>");
// 	fillRuleRHS(gr, rl, "<arithmeticExpr>");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<booleanSegment>");
// 	fillRuleRHS(gr, rl, "BO");
// 	fillRuleRHS(gr, rl, "<booleanExpr>");
// 	fillRuleRHS(gr, rl, "BC");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<relationalOp>");
// 	fillRuleRHS(gr, rl, "LT");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<relationalOp>");
// 	fillRuleRHS(gr, rl, "LE");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<relationalOp>");
// 	fillRuleRHS(gr, rl, "GT");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<relationalOp>");
// 	fillRuleRHS(gr, rl, "GE");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<relationalOp>");
// 	fillRuleRHS(gr, rl, "NE");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<relationalOp>");
// 	fillRuleRHS(gr, rl, "EQ");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<declareStmt>");
// 	fillRuleRHS(gr, rl, "DECLARE");
// 	fillRuleRHS(gr, rl, "<idList>");
// 	fillRuleRHS(gr, rl, "COLON");
// 	fillRuleRHS(gr, rl, "<dataType>");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<condionalStmt>");
// 	fillRuleRHS(gr, rl, "SWITCH");
// 	fillRuleRHS(gr, rl, "BO");
// 	fillRuleRHS(gr, rl, "<expression>");
// 	fillRuleRHS(gr, rl, "BC");
// 	fillRuleRHS(gr, rl, "START");
// 	fillRuleRHS(gr, rl, "<caseStmt>");
// 	fillRuleRHS(gr, rl, "<default>");
// 	fillRuleRHS(gr, rl, "END");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<caseStmt>");
// 	fillRuleRHS(gr, rl, "CASE");
// 	fillRuleRHS(gr, rl, "<value>");
// 	fillRuleRHS(gr, rl, "COLON");
// 	fillRuleRHS(gr, rl, "<statements>");
// 	fillRuleRHS(gr, rl, "BREAK");
// 	fillRuleRHS(gr, rl, "SEMICOL");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<value>");
// 	fillRuleRHS(gr, rl, "NUM");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<value>");
// 	fillRuleRHS(gr, rl, "TRUE");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<value>");
// 	fillRuleRHS(gr, rl, "FALSE");

// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<default>");
// 	fillRuleRHS(gr, rl, "DEFAULT");
// 	fillRuleRHS(gr, rl, "COLON");
// 	fillRuleRHS(gr, rl, "<statements>");
// 	fillRuleRHS(gr, rl, "BREAK");
// 	fillRuleRHS(gr, rl, "SEMICOL");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<default>");
// 	fillRuleRHS(gr, rl, "EMPTY");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<iterativeStmt>");
// 	fillRuleRHS(gr, rl, "FOR");
// 	fillRuleRHS(gr, rl, "BO");
// 	fillRuleRHS(gr, rl, "ID");
// 	fillRuleRHS(gr, rl, "IN");
// 	fillRuleRHS(gr, rl, "<range>");
// 	fillRuleRHS(gr, rl, "BC");
// 	fillRuleRHS(gr, rl, "START");
// 	fillRuleRHS(gr, rl, "<statements>");
// 	fillRuleRHS(gr, rl, "END");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<iterativeStmt>");
// 	fillRuleRHS(gr, rl, "WHILE");
// 	fillRuleRHS(gr, rl, "BO");
// 	fillRuleRHS(gr, rl, "<booleanExpr>");
// 	fillRuleRHS(gr, rl, "BC");
// 	fillRuleRHS(gr, rl, "START");
// 	fillRuleRHS(gr, rl, "<statements>");
// 	fillRuleRHS(gr, rl, "END");
	
// 	rl = addRuleToGrammar(gr);
// 	fillRuleLHS(gr, rl, "<range>");
// 	fillRuleRHS(gr, rl, "NUM");
// 	fillRuleRHS(gr, rl, "RANGEOP");
// 	fillRuleRHS(gr, rl, "NUM");
	
// 	printGrammar(gr);

// 	return 0;
// }
