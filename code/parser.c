#include "parserDef.h"
#include "lexerDef.h"
#include "lexer.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "aux.c"


grammar * createGrammar() {
	grammar * nw;
	nw = (grammar *)malloc(sizeof(grammar));

	int i;

	nw->trm  = (element **)malloc(26*sizeof(element *));
	nw->ntrm = (element **)malloc(26*sizeof(element *));

	for(i=0;i<26;i++) {
		nw->trm[i] = NULL;
		nw->ntrm[i] = NULL;
	}

	nw->top = NULL;
	nw->bot = NULL;
	nw->start = NULL;

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


element * searchForTerminal(grammar * gr, char * trm_name, int addImp) {
// if addImp is TRUE, record ruleNo for which rule the terminal is accessed

	int key = ((int)trm_name[0])-65, i;

	element * node = gr->trm[key];

	while(node != NULL) {
		if(strcmp(node->val, trm_name) == 0) {
			if(addImp)
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
	
	strcpy(nw->val, trm_name);
	if(addImp)
		nw->occ_rhs[nw->occ_rhs_num++] = gr->rule_num;

	nw->next = gr->trm[key];
	gr->trm[key] = nw;
	gr->trm_num++;


	return nw;
}

element * searchForNonTerminal(grammar * gr, char * trm_name, int orig, int addImp) {
// if addImp is TRUE, record ruleNo for which rule the terminal is accessed
	
	int key = ((int)trm_name[1])-97, i;

	element * node = gr->ntrm[key];

	while(node != NULL) {
		if(strcmp(node->val, trm_name) == 0) {
			if(addImp) {
				if(orig)
					node->occ_lhs[node->occ_lhs_num++] = gr->rule_num;
				else
					node->occ_rhs[node->occ_rhs_num++] = gr->rule_num;
			}
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
	if(addImp) {
		if(orig)
			nw->occ_lhs[nw->occ_lhs_num++] = gr->rule_num;
		else
			nw->occ_rhs[nw->occ_rhs_num++] = gr->rule_num;
	}

	nw->next = gr->ntrm[key];
	gr->ntrm[key] = nw;
	gr->ntrm_num++;

	return nw;
}


int fillRuleLHS(grammar * gr, rule * rl, char * ntrm) {
	rl->lhs.data = searchForNonTerminal(gr, ntrm, 1, 1);
	if(gr->start == NULL) {
		gr->start = rl->lhs.data;
	}
	return 0;
}


int fillRuleRHS(grammar * gr, rule * rl, char * str) {

	element * ref;

	if(str[0] == '<') 
		ref = searchForNonTerminal(gr, str, 0, 1);
	else
		ref = searchForTerminal(gr, str, 1);

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
	gr = createGrammar();

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

	// this will free the structures used in firstAndFollowSets

	// for(i=0;i<26;i++) {
	// 	node = gr->trm[i];
	// 	while(node != NULL) {
	// 		toFree = node;
	// 		node = node->next;
	// 		free(toFree);
	// 	}
	// }

	// free(gr->trm);

	// for(i=0;i<26;i++) {
	// 	node = gr->ntrm[i];
	// 	while(node != NULL) {
	// 		toFree = node;
	// 		node = node->next;
	// 		free(toFree);
	// 	}
	// }

	// free(gr->ntrm);

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

	// free(gr);

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


int calculateFirstSets(grammar * gr) {

	int leftFollows = gr->ntrm_num, i, j, notPossible;
	element * nt, * rhs_ele;
	rule * rl;
	ruleSeg * rs;

	unsigned long long nt_fst, seg_fst, empty = 8589934592l; 

	while(leftFollows) {
		for(i=0;i<26;i++) {
			nt = gr->ntrm[i];
			while(nt != NULL) {
				if(nt->first == 0) {
					nt_fst = 0;
					notPossible = 0;
					for(j=0;j<nt->occ_lhs_num;j++) {
						rl = fetchRuleFromGrammar(gr, nt->occ_lhs[j]);
						rs = rl->rhstop;
						while(rs != NULL) {
							if(rs->data != nt) {
								rhs_ele = rs->data;
								seg_fst = rhs_ele->first;

								if(seg_fst == empty && rs == rl->rhstop) {
									nt_fst = nt_fst | seg_fst;
								}
								else if(rhs_ele->first == 0) {
									notPossible = 1;
									break;
								}
								else {
									if( (seg_fst & (~empty)) == seg_fst ) {
										nt_fst = nt_fst | seg_fst;
										break;
									} 
									else {
										seg_fst = seg_fst & (~empty);
										nt_fst = nt_fst | seg_fst;
									}
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
						// printf("%s\n", nt->val);
						// printSetValues(nt_fst);
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


int calculateFollowSets(grammar * gr) {

	int leftFollows = gr->ntrm_num, i, j, notPossible;
	element * nt;
	rule * rl;
	ruleSeg * rs;
	unsigned long long dollar = 144115188075855872l, empty = 8589934592l, nt_flw, seg_flw;

	gr->start->follow = dollar;
	leftFollows--;

	while(leftFollows) {
		for(i=0;i<26;i++) {
			nt = gr->ntrm[i];
			while(nt != NULL) {
				if(nt->follow == 0) {
					nt_flw = 0;
					notPossible = 0;

					for(j=0;j<nt->occ_rhs_num;j++) {
						rl = fetchRuleFromGrammar(gr, nt->occ_rhs[j]);
						rs = rl->rhstop;

						while(rs->data != nt)
							rs = rs->next;

						if(rs->next == NULL) {
							if(rl->lhs.data != nt) {
								if(rl->lhs.data->follow == 0) {
									notPossible = 1;
									break;
								}
								nt_flw = nt_flw | rl->lhs.data->follow;
							}
						}
						else {
							seg_flw = rs->next->data->first;
							nt_flw = nt_flw | (seg_flw & ~empty);
							if(rl->lhs.data != nt && ( (seg_flw | empty) == seg_flw ) ) {
								if(rl->lhs.data->follow == 0) {
									notPossible = 1;
									break;
								}
								nt_flw = nt_flw | rl->lhs.data->follow;
							}
						}
					}

					if(j == nt->occ_rhs_num) {
						// printf("%s\n", nt->val);
						// printSetValues(nt_flw);
						nt->follow = nt_flw;
						leftFollows--;
					}
				}
				nt = nt->next;
			}
		}
	}
	return 0;
}



firstAndFollowSets * computeFirstAndFollowSets(grammar * gr) {


	int i, j = 100;
	element * nw;
	
	// set id of non terminals

	for(i=0;i<26;i++) {
		nw = gr->ntrm[i];
		while(nw != NULL) {
			nw->id = j++;
			nw = nw->next;
		}
	}

	// set first, follow and id of terminals

	for(i=0;i<26;i++) {
		nw = gr->trm[i];
		while(nw != NULL) {
			nw->follow = 0;
			unsigned long long i = 1;
			int j = 0;
			while(strcmp(ref[j], nw->val) != 0) {
				i = i<<1;
				j++;
			}
			nw->first = i;
			nw->id = j;
			nw = nw->next;
		}
	}
	
	printf("\n\n FIRST \n\n");
	calculateFirstSets(gr);
	printf("\n\n FOLLOWS \n\n");
	calculateFollowSets(gr);
	
	firstAndFollowSets * ff;
	ff = (firstAndFollowSets *)malloc(sizeof(firstAndFollowSets));
	ff->trm = gr->trm;
	ff->ntrm = gr->ntrm;
	ff->trm_num = gr->trm_num;
	ff->ntrm_num = gr->ntrm_num;

	return ff;
}


parseList * initParseTable(grammar * gr, firstAndFollowSets * ff) {

	parseList * head, * nw;
	parseToken * pt;
	head = NULL;
	rule * rl;
	ruleSeg * rs;
	unsigned long long nt_fst, seg_fst, empty = 8589934592l;

	int i, j, k;
	element * nt, * rhs_ele;

	for(i=0;i<26;i++) {
		nt = gr->ntrm[i];
		while(nt != NULL) {
			
			// printf("%s\n", nt->val);
			nw = (parseList *)malloc(sizeof(parseList));
			nw->next = head;
			nw->top = NULL;
			nw->nTrmData = nt;
			head = nw;
			nw->id = nt->id;

			for(j=0;j<nt->occ_lhs_num;j++) {

				rl = fetchRuleFromGrammar(gr, nt->occ_lhs[j]);
				nt_fst = 0;
				rs = rl->rhstop;

				while(rs != NULL) {
					rhs_ele = rs->data;
					seg_fst = rhs_ele->first;

					if(seg_fst == empty && rs == rl->rhstop) {
						nt_fst = nt_fst | seg_fst;
					}
					else {
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
				if(rs == NULL) {
					nt_fst = nt_fst | empty;
				}

				// printf("rule no : %d\n", nt->occ_lhs[j]);
				// printSetValues(nt_fst);

				if( (nt_fst & empty) == empty) {
					// printSetValues(nt_fst);
					nt_fst = (nt_fst & ~empty) | rl->lhs.data->follow;
					// printSetValues(nt_fst);
				}

				k = 0;
				while(nt_fst != 0) {
					if(nt_fst % 2 == 1) {
						pt = (parseToken *)malloc(sizeof(parseToken));
						pt->next = nw->top;
						pt->terminalId = k;
						// printf("gr %x, refk %s\n", gr, ref[k]);
						pt->trmData = searchForTerminal(gr, ref[k], 0);
						pt->ruleNo = nt->occ_lhs[j];
						pt->rl = rl;
						nw->top = pt;
						// printf("%s, rule : %d\n", ref[k], pt->ruleNo);
					}
					nt_fst = nt_fst>>1;
					k++;
				}

			}
			nt = nt->next;
		}
	}
	return head;
}


treeNode * createTreeNode(int id, token * tk, treeNode * parent) {
	
	treeNode * nw;
	nw = (treeNode *)malloc(sizeof(treeNode));

	nw->parent = parent;
	nw->childL = NULL;
	nw->childR = NULL;

	nw->next = NULL;
	nw->prev = NULL;

	nw->id = id;

	memset(nw->tname, 0, sizeof(nw->tname));
	memset(nw->val, 0, sizeof(nw->val));
	nw->lno = -1;

	if(tk != NULL) {
		strcpy(nw->tname, tk->lxm);
		strcpy(nw->val, tk->val);
		nw->lno = tk->lno;
	}

	return nw;

}


treeNode * parseInputSourceCode(char *filename, parseList * pl) {

	setUpStream(filename);

	treeNode * root, * eof;

	// eof, to be placed at the end of stack

	eof = (treeNode *)malloc(sizeof(treeNode));
	eof->parent = eof->childR = eof->childL = eof->next = eof->prev = NULL;
	eof->id = 57;
	eof->lno = -1;
	memset(eof->tname, 0, sizeof(eof->tname));
	memset(eof->val, 0, sizeof(eof->val));

	stackWrapper * top, * tmp;

	tmp = (stackWrapper *)malloc(sizeof(stackWrapper));
	tmp->ptr = eof;
	tmp->next = NULL;

	top = tmp;

	// create root node

	root = createTreeNode(5, NULL, NULL);








	// token * got;

	// got = getToken();
	// for(int i=0;!(got->id == 56 ||got->id == 57) ;i++) {
	// 	printf("------------- %s, %s, %d\n", got->lxm, got->val, got->lno);
	// 	got = getToken();
	// }
	// printf("------------- %s, %s, %d\n", got->lxm, got->val, got->lno);


	
}





int main() {

	// grammar * gr = readGrammarFromFile("../modified-grammar/grammar final.txt");
	
	// firstAndFollowSets * ff = computeFirstAndFollowSets(gr);

	// parseList * tableHead = initParseTable(gr, ff);

	// // printParseTable(tableHead);


	// printGrammar(gr);
	// dismantleGrammar(gr);

	// // printFFSets(ff);

	// // calculateFirstSets(gr);


	parseInputSourceCode("../testcases/test.case2", NULL);

	
	return 0;

}



