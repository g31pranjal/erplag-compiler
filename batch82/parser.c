/*
Batch no. 82

AUTHORS : 
Pranjal Gupta (2013B4A7470P)
Tanaya Jha (2013B3A7304P)
*/


#include "parserDef.h"
#include "lexerDef.h"
#include "lexer.h"

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
			printf("%lld, %x, %s [ ", node->first, node, node->val);
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
			printf("%lld, %x, %s [", node->first, node, node->val);
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


int printFFSets(firstAndFollowSets * gr) {


	printf("\n\n ****** TERMINALS *******\n\n");
	printf("num of terminals : %d\n", gr->trm_num);
	element * node;

	for(int i=0;i<26;i++) {
		printf("%d\n", i);
		node = gr->trm[i];
		while(node != NULL) {
			printf("%d, %lld, %lld, %s [ ", node->id, node->first, node->follow, node->val);
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
			printf("%d, %lld, %lld, %s [",node->id, node->first, node->follow, node->val);
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


int printParseTable(parseList * pl) {

	parseToken * pt;

	printf("%x\n", pl);

	while(pl != NULL) {
		printf("NT : %d, %s\n", pl->id, pl->nTrmData->val);
		pt = pl->top;
		while(pt != NULL) {
			printf("%s, %d -> ", ref[pt->terminalId], pt->ruleNo);
			pt = pt->next;
		}
		printf("\n");
		pl = pl->next;
	}
}

int printStackWrapperSeq(stackWrapper * head) {

	while(head != NULL) {
		printf("%s \n", head->ptr->id->val);
		head = head->next;
	}

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

	nw->follow = 0;
	unsigned long long ii = 1;
	int j = 0;
	while(strcmp(ref[j], nw->val) != 0) {
		ii = ii<<1;
		j++;
	}
	nw->first = ii;
	nw->id = j;
	
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
			if(buf[ptr] == 10 ||  buf[ptr] == 0 || buf[ptr] == 13 ) 
				break;
			else if(buf[ptr] == 9 || buf[ptr] == 32) {
			}
			else if(buf[ptr] == 58) {
				crossed = 1;
			}
			else {
				valptr = 0;
				memset(val, 0, 25);
				while(buf[ptr] != 9 && buf[ptr] != 32 && buf[ptr] != 10 && buf[ptr] != 0 && buf[ptr] != 13) {
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


parseList * createParseTable(grammar * gr, firstAndFollowSets * ff) {

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


treeNode * createTreeNode(element * id, treeNode * parent) {
	
	treeNode * nw;
	nw = (treeNode *)malloc(sizeof(treeNode));

	nw->parent = parent;
	nw->childL = NULL;
	nw->childR = NULL;
	nw->next = NULL;
	nw->prev = NULL;

	nw->scope = NULL;
	nw->se = NULL;

	memset(nw->type, 0, 25);

	nw->id = id;

	// nw->tptr = tk;
	nw->tptr = NULL;

	return nw;

}

int addChildToNode(treeNode * child, treeNode * parent) {

	// printf("adding child : %x to parent %x with left child %x\n", child, parent, parent->childL);

	if(parent->childL == NULL && parent->childR == NULL) {
		// printf("case of first child\n");
		parent->childL = child;
		parent->childR = child;
	}	
	else {
		// printf("case of more than one child\n");
		parent->childR->next = child;
		child->prev = parent->childR;
		parent->childR = child;
	}

	child->parent = parent;

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


treeNode * parseInputSourceCode(grammar * gr, char *filename, parseList * pl, int * errors) {

	setUpStream(filename);

	treeNode * root, * eof, *nw, * rightend, *popped;
	rule * rl;
	*errors = 0;
	unsigned long long sync;
	stackWrapper * stackTop, * tmp;
	ruleSeg * rs;
	element * topEle;

	// eof, to be placed at the end of stack

	eof = (treeNode *)malloc(sizeof(treeNode));
	eof->parent = eof->childR = eof->childL = eof->next = eof->prev = NULL;
	eof->id = searchForTerminal(gr, "EOF", 0);
	eof->tptr = NULL;

	tmp = (stackWrapper *)malloc(sizeof(stackWrapper));
	tmp->ptr = eof;
	tmp->next = NULL;

	stackTop = tmp;

	// create root node, add root to stack

	root = createTreeNode(gr->start, NULL);

	// printf("creating node : %x\n", root);

	tmp = (stackWrapper *)malloc(sizeof(stackWrapper));
	tmp->ptr = root;
	tmp->next = NULL;

	tmp->next = stackTop;
	stackTop = tmp;


	token * nxtT;
	nxtT = getToken();
	while(nxtT->id == 56)
		nxtT = getToken();

	while(stackTop != NULL) {
		// printStackWrapperSeq(stackTop);
		// printf("\n\n");

		topEle = stackTop->ptr->id;

		if(topEle->id == 33) {
			stackTop = stackTop->next;
		} 
		// terminal
		else if(topEle->id >= 0 && topEle->id < 100) {

			if(topEle->id == nxtT->id) {
				stackTop->ptr->tptr = nxtT;
				// free the stack wrapper here
				stackTop = stackTop->next;
				nxtT = getToken();
				while(nxtT->id == 56)
					nxtT = getToken();
			}
			else {
				// error : top stack terminal do not match token (from lexer)
				*errors = 1;
				// printf("%d\n", nxtT->id);
				printf("%sERROR : %s(parser)%s The token %s for the lexeme \'%s\' does not match at line %d\n", BOLDRED, BOLDMAGENTA, RESET, stackTop->ptr->id->val, nxtT->val, nxtT->lno);	
				stackTop = stackTop->next;
				nxtT = getToken();
				while(nxtT->id == 56)
					nxtT = getToken();
			}

		}
		else {

			rl = SearchRuleInParseTable(pl, topEle->id, nxtT->id);

			if(rl == NULL) {

				*errors = 1;
				printf("%sERROR : %s(parser)%s The non terminal %s does not produce lexeme \'%s\' at line %d\n", BOLDRED, BOLDMAGENTA, RESET, topEle->val, nxtT->val, nxtT->lno );

				sync = 0;
				sync = topEle->first | topEle->follow;

				if((searchForTerminal(gr, ref[nxtT->id], 0)->follow | sync) == sync) {
					popped = stackTop->ptr;
					stackTop = stackTop->next;

					nw = createTreeNode(searchForTerminal(gr, "EMPTY", 0), popped);
					addChildToNode(nw, popped);

					tmp = (stackWrapper *)malloc(sizeof(stackWrapper));
					tmp->ptr = nw;
					tmp->next = stackTop;
					stackTop = tmp;
				}
				else {
					nxtT = getToken();
					while(nxtT == 56)
						nxtT = getToken();
				}
			}
			else {
				popped = stackTop->ptr;
				stackTop = stackTop->next;

				rs = rl->rhstop;

				while(rs != NULL) {
					nw = createTreeNode(rs->data, popped);
					addChildToNode(nw, popped);
					rs = rs->next;
				}

				rightend = popped->childR;

				while(rightend != NULL) {

					tmp = (stackWrapper *)malloc(sizeof(stackWrapper));
					tmp->ptr = rightend;			
					tmp->next = stackTop;
					stackTop = tmp;

					rightend = rightend->prev;

				}
			}
		}

	}

	if(*errors) {
		printf("\n%sThere are syntactical errors in the source code.%s\n\n", BOLDRED, RESET);
	}
	else {
		printf("\n%sInput source code has no syntactical errors.%s\n\n", BOLDGREEN, RESET);
	}

	return root;

}




// int printParseTree( treeNode * head, FILE * fp)  {

// 	int first = 0;
// 	treeNode * child;
// 	child = head->childL;

// 	// printf("starting printing on head : %x\n", head->id->id);

// 	if( head->id->id > 100 && child != NULL) {

// 		while(child != NULL) {

// 			printParseTree(child, fp);
// 			if(first == 0) {
// 				// printing a non terminal 
// 				// printf("node : %x\n", head);
				
// 				if(head->parent != NULL) {
// 					printf("---\t\t---\t\t---\t\t---\t\t%s\t\tNO\t\t%s\n", head->parent->id->val, head->id->val);
// 					fprintf(fp, "---\t\t---\t\t---\t\t---\t\t%s\t\tNO\t\t%s\n", head->parent->id->val, head->id->val);	
// 				}
					
// 				else{
// 					printf("---\t\t---\t\t---\t\t---\t\tROOT\t\tNO\t\t%s\n",  head->id->val);
// 					fprintf(fp, "---\t\t---\t\t---\t\t---\t\tROOT\t\tNO\t\t%s\n",  head->id->val);
// 				}

// 				first = 1;
// 			}
// 			child = child->next;
// 		}

// 	}
// 	else if(head->id->id > 100 && child == NULL) {
// 		printf("non terminal with no children. something fishy\n");
// 		if(head->parent != NULL) {
// 			printf("---\t\t---\t\t---\t\t---\t\t%s\t\tNO\t\t%s\n", head->parent->id->val, head->id->val);
// 			fprintf(fp, "---\t\t---\t\t---\t\t---\t\t%s\t\tNO\t\t%s\n", head->parent->id->val, head->id->val);	
// 		}
			
// 		else{
// 			printf("---\t\t---\t\t---\t\t---\t\tROOT\t\tNO\t\t%s\n",  head->id->val);
// 			fprintf(fp, "---\t\t---\t\t---\t\t---\t\tROOT\t\tNO\t\t%s\n",  head->id->val);
// 		}
// 	}
// 	else if() {
// 		if(head->tptr != NULL) {
// 			// with the token 
// 			if(head->tptr->id == 31 || head->tptr->id == 32 ){
// 				printf("%s\t\t%d\t\t%s\t\t%s\t\t%s\t\tYES\t\t---\n", head->tptr->val, head->tptr->lno, head->tptr->lxm, head->tptr->val, head->parent->id->val);
// 				fprintf(fp, "%s\t\t%d\t\t%s\t\t%s\t\t%s\t\tYES\t\t---\n", head->tptr->val, head->tptr->lno, head->tptr->lxm, head->tptr->val, head->parent->id->val);
// 			}
// 			else { 
// 				printf("%s\t\t%d\t\t%s\t\t---\t\t%s\t\tYES\t\t---\n", head->tptr->val, head->tptr->lno, head->tptr->lxm, head->parent->id->val);
// 				fprintf(fp, "%s\t\t%d\t\t%s\t\t---\t\t%s\t\tYES\t\t---\n", head->tptr->val, head->tptr->lno, head->tptr->lxm, head->parent->id->val);
// 			}
// 		}
// 		else {
// 			// printf("terminal node : %d\n", head->id);
// 			printf("---\t\t---\t\t %s\t\t---\t\t%s\t\tYES\t\t---\n", ref[head->id->id], head->parent->id->val );
// 			fprintf(fp, "---\t\t---\t\t%s\t\t---\t\t%s\t\tYES\t\t---\n", ref[head->id->id], head->parent->id->val );

// 		}
// 	}

// }


int printParseTree(treeNode * head, FILE * fp)  {

	int first = 0;
	treeNode * child;
	child = head->childL;


	// printf("starting printing on head : %x\n", head);

	if(child != NULL) {


		while(child != NULL) {

			printParseTree(child, fp);
			if(first == 0) {
				// printing a non terminal 
				// printf("node : %x\n", head);
				
				if(head->parent != NULL) {
					// printf("---\t\t---\t\t---\t\t---\t\t%s\t\tNO\t\t%s\n", head->parent->id->val, head->id->val);
					printf("%s ( %x ) parent of %s ( %x )\n", head->parent->id->val, head->parent, head->id->val, head);
					// fprintf(fp, "---\t\t---\t\t---\t\t---\t\t%s\t\tNO\t\t%s\n", head->parent->id)->val, head->id->val);	
				}
					
				else{
					printf("---\t\t---\t\t---\t\t---\t\tROOT\t\tNO\t\t%s\n",  head->id->val);
					fprintf(fp, "---\t\t---\t\t---\t\t---\t\tROOT\t\tNO\t\t%s\n",  head->id->val);
				}

				first = 1;
			}
			child = child->next;

		}
	}
	else {
		if(head->tptr != NULL) {
			// with the token 
			if(head->tptr->id == 31 || head->tptr->id == 32 ){
				printf("%s\t\t%d\t\t%s\t\t%s\t\t%s (%x)\t\tYES\t\t---\n", head->tptr->val, head->tptr->lno, head->tptr->lxm, head->tptr->val, head->parent->id->val, head->parent);
				fprintf(fp, "%s\t\t%d\t\t%s\t\t%s\t\t%s (%x)\t\tYES\t\t---\n", head->tptr->val, head->tptr->lno, head->tptr->lxm, head->tptr->val, head->parent->id->val, head->parent);
			}
			else { 
				printf("%s\t\t%d\t\t%s\t\t---\t\t%s (%x)\t\tYES\t\t---\n", head->tptr->val, head->tptr->lno, head->tptr->lxm, head->parent->id->val, head->parent);
				fprintf(fp, "%s\t\t%d\t\t%s\t\t---\t\t%s (%x)\t\tYES\t\t---\n", head->tptr->val, head->tptr->lno, head->tptr->lxm, head->parent->id->val, head->parent);
			}
		}
		else {
			// printf("terminal node : %d\n", head->id);
			printf("---\t\t---\t\t %s\t\t---\t\t%s (%x)\t\tYES\t\t---\n", ref[head->id->id], head->parent->id->val, head->parent );
			fprintf(fp, "---\t\t---\t\t%s\t\t---\t\t%s (%x)\t\tYES\t\t---\n", ref[head->id->id], head->parent->id->val, head->parent );

		}
	}




}
