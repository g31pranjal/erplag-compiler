#include "parserDef.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "aux.c"

unsigned long long getUniqueID(char * trm) {
	unsigned long long i = 1;
	int j = 0;
	while(strcmp(ref[j], trm) != 0) {
		i *= 2l;
		j++;
	}

	return i;
}


grammar * createGrammar() {
	grammar * nw;
	nw = (grammar *)malloc(sizeof(grammar));

	int i;
	for(i=0;i<26;i++) {
		nw->trm[i] = NULL;
		nw->ntrm[i] = NULL;
	}

	nw->top = NULL;
	nw->bot = NULL;
	
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
			node->occ_rhs[node->occ_rhs_num++] = gr->rule_num;
			return node;
		}
		node = node->next;
	}

	element * nw;
	nw = (element *)malloc(sizeof(element));
	nw->type = 0;
	for(i=0;i<20;i++) {
		nw->occ_lhs[i] = 0;
		nw->occ_lhs[i] = 0;
	}
	nw->occ_lhs_num = 0;
	nw->occ_rhs_num = 0;
	nw->follow = 0;
	nw->first = getUniqueID(trm_name);
	
	strcpy(nw->val, trm_name);
	nw->occ_rhs[nw->occ_rhs_num++] = gr->rule_num;

	nw->next = gr->trm[key];
	gr->trm[key] = nw;
	gr->trm_num++;


	return nw;
}

element * searchForNonTerminal(grammar * gr, char * trm_name, int orig) {
	
	int key = ((int)trm_name[1])-97, i;

	element * node = gr->ntrm[key];

	while(node != NULL) {
		if(strcmp(node->val, trm_name) == 0) {
			if(orig)
				node->occ_lhs[node->occ_lhs_num++] = gr->rule_num;
			else
				node->occ_rhs[node->occ_rhs_num++] = gr->rule_num;
			return node;
		}
		node = node->next;
	}

	element * nw;
	nw = (element *)malloc(sizeof(element));
	nw->type = 1;
	for(i=0;i<25;i++) {
		nw->occ_lhs[i] = 0;
		nw->occ_rhs[i] = 0;
	}
	nw->occ_lhs_num = 0;
	nw->occ_rhs_num = 0;
	
	strcpy(nw->val, trm_name);
	if(orig)
		nw->occ_lhs[nw->occ_lhs_num++] = gr->rule_num;
	else
		nw->occ_rhs[nw->occ_rhs_num++] = gr->rule_num;

	nw->next = gr->ntrm[key];
	gr->ntrm[key] = nw;
	gr->ntrm_num++;

	return nw;
}


int fillRuleLHS(grammar * gr, rule * rl, char * ntrm) {
	rl->lhs.data = searchForNonTerminal(gr, ntrm, 1);
	return 0;
}


int fillRuleRHS(grammar * gr, rule * rl, char * str) {

	element * ref;

	if(str[0] == '<') 
		ref = searchForNonTerminal(gr, str, 0);
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
	free(buf);
	fclose(fp);

	return gr;
}


int dismantleGrammar(grammar * gr) {

	int i;
	element * node, * toFree;

	int freed = 0;
	size_t sz = 0;

	for(i=0;i<26;i++) {
		node = gr->trm[i];
		while(node != NULL) {
			toFree = node;
			node = node->next;
			free(toFree);
		}
	}

	for(i=0;i<26;i++) {
		node = gr->ntrm[i];
		while(node != NULL) {
			toFree = node;
			node = node->next;
			free(toFree);
		}
	}

	rule * rl = gr->top, * rltf;
	ruleSeg * rs, * rstf;

	while(rl != NULL) {
		rs = rl->rhstop;
		while(rs != NULL) {
			rstf = rs;
			rs = rs->next;
			free(rstf);
		}
		rltf = rl;
		rl = rl->next;
		free(rltf);
	}
	free(gr);

	return 0;
}


rule * fetchRuleFromGrammar(grammar * gr, int ruleno) {

	int i = 1;
	rule * rl = gr->top;

	while(i<=ruleno) {
		if(i == ruleno)
			return rl;
		i++;
		rl = rl->next;
	}
	return NULL;
}

void printSetValues(unsigned long long val) {

	int exp = 0;
	unsigned long long trace = 1;

	while( val != 0 ) {

		// printf("%lld, %lld\n", val, trace);

		if( (val | trace) == val) {
			printf("%s, ", ref[exp]);
			val = val ^ trace;
		}
		trace = trace*2;
		exp++;
	}
	printf("\n");

}


int calculateFirstSets(grammar * gr) {

	int leftFollows = gr->ntrm_num, i, j, notPossible;
	element * nt, * rhs_ele;
	rule * rl;
	ruleSeg * rs;

	unsigned long long nt_fst, seg_fst, empty = 8589934592l; 

	while(leftFollows) {

		// printf("left :: %d\n", leftFollows);

		for(i=0;i<26;i++) {
			nt = gr->ntrm[i];
			while(nt != NULL) {
				
				if(nt->first == 0) {
					
					nt_fst = 0;
					notPossible = 0;

					// iterating over all the rules with nt on lhs
					for(j=0;j<nt->occ_lhs_num;j++) {
						// fetching the rule from the grammar
						rl = fetchRuleFromGrammar(gr, nt->occ_lhs[j]);
						
						rs = rl->rhstop;
						while(rs != NULL) {
							rhs_ele = rs->data;
							seg_fst = rhs_ele->first;
							
							if(seg_fst == empty && rs == rl->rhstop) {
								// first token is an 'EMPTY'
								nt_fst = nt_fst | seg_fst;
							}
							else if(rhs_ele->first == 0) {
								notPossible = 1;
								break;
							}
							else {
								// if EMPTY is not there 
								if( (seg_fst & (~empty)) == seg_fst ) {
									nt_fst = nt_fst | seg_fst;
									break;
								}
								else {
									seg_fst = seg_fst & (~empty);
									nt_fst = nt_fst | seg_fst;
								}
							}

							rs = rs->next;
						}

						if(notPossible)
							break;
						else if(rs == NULL) {
							nt_fst = nt_fst | empty;
						}
						
					}

					if(j == nt->occ_lhs_num) {
						// all rules are done 
						printf("%s\n", nt->val);
						printSetValues(nt_fst);
						nt->first = nt_fst;
						leftFollows--;
					}
					
				}
				nt = nt->next;
			}
		}
	}
	return 0;
}



int main() {

	grammar * gr = readGrammarFromFile("../modified-grammar/grammar final.txt");

	
	calculateFirstSets(gr);



	// printGrammar(gr);
	
	// dismantleGrammar(gr);

	// calculateFirstSets(gr);

	return 0;
}