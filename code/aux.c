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
		printf("%d\t", i);
		node = gr->trm[i];
		while(node != NULL) {
			printf("%x, %s [ ", node, node->val);
			int i;
			for(i=0;i<node->occ_num;i++) {
				printf("%d, ", node->occurances[i]);
			}
			printf(" ] -> ");
			node = node->next;
		}
		printf("\n");
	}

	printf("\n\n ****** non TERMINALS *******\n");
	printf("num of non terminals : %d\n", gr->ntrm_num);

	for(int i=0;i<26;i++) {
		printf("%d\t", i);
		node = gr->ntrm[i];
		while(node != NULL) {
			printf("%x, %s [", node, node->val);
			int i;
			for(i=0;i<node->occ_num;i++) {
				printf("%d, ", node->occurances[i]);
			}
			printf(" ] -> ");
			node = node->next;
		}
		printf("\n");
	}

}

