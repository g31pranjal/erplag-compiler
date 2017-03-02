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
	ruleSeg * rs, *beta;
	unsigned long long dollar = 144115188075855872l, empty = 8589934592l, nt_flw, seg_flw;

	gr->start->follow = dollar;
	leftFollows--;

	while(leftFollows) {

		// printf("\n\n LEFT : %d \n", leftFollows);

		for(i=0;i<26;i++) {
			nt = gr->ntrm[i];
			while(nt != NULL) {
				if(nt->follow == 0) {

					// printf("inspecting : %s ", nt->val);

					nt_flw = 0;
					notPossible = 0;

					for(j=0;j<nt->occ_rhs_num;j++) {
						rl = fetchRuleFromGrammar(gr, nt->occ_rhs[j]);
						rs = rl->rhstop;

						while(rs != NULL) {

							while(rs != NULL && rs->data != nt)
								rs = rs->next;

							if(rs != NULL) {
								if(rs->next == NULL) {
									if(rl->lhs.data != nt) {
										if(rl->lhs.data->follow == 0) {
											notPossible = 1;
												// printf(" depends on %s\n", rl->lhs.data->val);

											break;
										}
										nt_flw = nt_flw | rl->lhs.data->follow;
									}
								}
								else {
									
									beta = rs->next;
									
									seg_flw = 0;

									while(beta != NULL) {
										// printf("beta ka data\n");
										// printSetValues(beta->data->first & (~empty));
										
										if((beta->data->first & (~empty)) == beta->data->first) {
											seg_flw = seg_flw | beta->data->first;
											break;
										}
										else {
											seg_flw = seg_flw | (beta->data->first & (~empty));
										}
										beta = beta->next;
									}
										
									nt_flw = nt_flw | seg_flw;

									// printSetValues(nt_flw);
									// printf("beta %x\n", beta);

									if(beta == NULL) {
										if(rl->lhs.data != nt ) {
											if(rl->lhs.data->follow == 0) {
												notPossible = 1;
												// printf(" depends on %s\n", rl->lhs.data->val);
												break;
											}
											nt_flw = nt_flw | rl->lhs.data->follow;
										}
									}
								}
								rs = rs->next;
							}
							
						}
						if(notPossible)
							break;

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
	
	// printf("\n\n FIRST \n\n");
	calculateFirstSets(gr);
	// printf("\n\n FOLLOW \n\n");
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


treeNode * createTreeNode(int id, /*token * tk,*/ treeNode * parent) {
	
	treeNode * nw;
	nw = (treeNode *)malloc(sizeof(treeNode));

	nw->parent = parent;
	nw->childL = NULL;
	nw->childR = NULL;

	nw->next = NULL;
	nw->prev = NULL;

	nw->id = id;

	// nw->tptr = tk;
	nw->tptr = NULL;

	return nw;

}

int addChildToNode(treeNode * child, treeNode * parent) {

	if(parent->childL == NULL && parent->childR == NULL) {
		parent->childL = child;
		parent->childR = child;
	}	
	else {
		parent->childR->next = child;
		child->prev = parent->childR;
		parent->childR = child;
	}

	return 0;
}

rule * SearchRuleInParseTable(parseList * pl, int ntId, int tId) {

	parseToken * pt; 

	while(pl != NULL) {
		if(pl->id == ntId) {
			pt = pl->top;
			while(pt != NULL) {
				if(pt->terminalId == tId) {
					return pt->rl;
				}
				pt = pt->next;
			}
		}
		pl = pl->next;
	}

	return NULL;

}



treeNode * parseInputSourceCode(grammar * gr, char *filename, parseList * pl) {

	setUpStream(filename);

	treeNode * root, * eof, *nw, * rightend, *popped;
	rule * rl;
	int topId;
	stackWrapper * stackTop, * tmp;
	ruleSeg * rs;

	// eof, to be placed at the end of stack

	eof = (treeNode *)malloc(sizeof(treeNode));
	eof->parent = eof->childR = eof->childL = eof->next = eof->prev = NULL;
	eof->id = 57;
	eof->tptr = NULL;

	tmp = (stackWrapper *)malloc(sizeof(stackWrapper));
	tmp->ptr = eof;
	tmp->next = NULL;

	stackTop = tmp;

	// create root node, add root to stack

	root = createTreeNode(gr->start->id, NULL);

	tmp = (stackWrapper *)malloc(sizeof(stackWrapper));
	tmp->ptr = root;
	tmp->next = NULL;

	tmp->next = stackTop;
	stackTop = tmp;

	token * nxtT;
	nxtT = getToken();

	while(stackTop != NULL) {

		// printf("\n\n\n");

		// printStackWrapperSeq(stackTop);
		// printf("\n\n");
		
		topId = stackTop->ptr->id;

		// printf("top id %d\n", topId);

		// pop out empty from the stack
		if(topId == 33) {
			stackTop = stackTop->next;
		} 
		// terminal
		else if(topId >= 0 && topId < 100) {

			// printf("%s\n", ref[topId]);

			if(topId == nxtT->id) {
				stackTop->ptr->tptr = nxtT;
				// free the stack wrapper here
				stackTop = stackTop->next;
				nxtT = getToken();
			}
			else {
				// error : top stack terminal do not match token (from lexer)
			}

		}
		else {

			// printf("got a non terminal\n");

			// printf("%s\n", nxtT->lxm);

			rl = SearchRuleInParseTable(pl, topId, nxtT->id);

			// printf("%x\n", rl);
			
			if(rl == NULL) {
				// error : no corresponding rule exists
			}
			else {
				popped = stackTop->ptr;
				stackTop = stackTop->next;

				rs = rl->rhstop;

				while(rs != NULL) {

					// printf("creating tree node ... \n" );

					nw = createTreeNode(rs->data->id, popped);
					addChildToNode(nw, popped);

					rs = rs->next;
				}

				rightend = popped->childR;

				while(rightend != NULL) {

					// printf("pushing in stack ... \n" );

					tmp = (stackWrapper *)malloc(sizeof(stackWrapper));
					tmp->ptr = rightend;			
					tmp->next = stackTop;
					stackTop = tmp;

					rightend = rightend->prev;

				}


			}

		}

		// break;

	}

	return 0;

}





int main() {

	grammar * gr = readGrammarFromFile("../modified-grammar/grammar final.txt");
	
	firstAndFollowSets * ff = computeFirstAndFollowSets(gr);

	parseList * tableHead = initParseTable(gr, ff);

	// printParseTable(tableHead);

	// printGrammar(gr);
	// dismantleGrammar(gr);

	// // printFFSets(ff);

	// // calculateFirstSets(gr);


	parseInputSourceCode(gr, "../testcases/test.case6", tableHead);

	
	return 0;

}



