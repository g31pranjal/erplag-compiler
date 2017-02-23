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

int fillRuleLHS(grammar * gr, char * ntrm, rule * rl) {
	rl->lhs.data = searchForNonTerminal(gr, ntrm);
}

int fillRuleRHS(grammar * gr, char * str, rule * rl) {

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

	char tr[20] = "<program>";
	printf("%x\n", searchForNonTerminal(gr, tr));
	strcpy(tr, "<moduleDeclarations>");
	printf("%x\n", searchForNonTerminal(gr, tr));
	strcpy(tr, "PARAMETERS");
	printf("%x\n", searchForTerminal(gr, tr));
	printf("%x\n", searchForTerminal(gr, tr));
	
	printGrammar(gr);

	return 0;
}