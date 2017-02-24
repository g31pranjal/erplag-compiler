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
	for(i=0;i<25;i++) {
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

grammar * readGrammarFromFile(char * filename) {

	FILE * fp;
	fp = fopen(filename, "r");

	// buffer to hold a line_no (rule)
	size_t bSize = 300;
	char * buf = (char *)malloc(sizeof(char)*bSize);

	int line_no = 1, i;
	
	grammar * gr;
	gr = (grammar *)malloc(sizeof(grammar));

	rule * rl;

	// to hold a token
	char val[25];
	int valptr, charline;

	while(charline = getline(&buf, &bSize, fp) != -1)  {

		rl = addRuleToGrammar(gr);

		int ptr = 0;
		int crossed = 0;

		while(1) {
			if(buf[ptr] == 10 ||  buf[ptr] == 0) 
				break;
			else if(buf[ptr] == 9 || buf[ptr] == 32) {
			}
			else if(buf[ptr] == 58) {
				crossed = 1;
			}
			else {
				valptr = 0;
				memset(val, 0, 25);
				while(buf[ptr] != 9 && buf[ptr] != 32 && buf[ptr] != 10 && buf[ptr] != 0) {
					val[valptr++] = buf[ptr];
					ptr++;
				}
				if(crossed)
					fillRuleRHS(gr, rl, val);
				else
					fillRuleLHS(gr, rl, val);
				ptr--;
			}
			ptr++;
		}

		memset(buf, 0, 300);
	}

	return gr;


}


int main() {

	grammar * gr = readGrammarFromFile("../modified-grammar/grammar final.txt");

	printGrammar(gr);

	return 0;
}