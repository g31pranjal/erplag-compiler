#include <stdio.h> 
#include <string.h>
#include <unistd.h> 
#include <stdlib.h> 
#include "lexerDef.h"

#define BUFF_SIZE 65
#define HASH_KEYWORD_SIZE 13

typedef struct nd keyword;

struct nd {
	int num;
	char value[25];
	keyword * next;
};

keyword * hashedKeywords[HASH_KEYWORD_SIZE];

keyword * newNode(char * value, int num) {
	keyword * nd;
	nd = (keyword *) malloc(sizeof(keyword));
	
	if(nd==NULL) {
		return NULL;
	}

	strcpy(nd->value, value);
	nd->num=num;
	nd->next=NULL;

	return nd;
}

int computeHashFunction(char * value) {
	int key=0, i;
	for(i=0;i<strlen(value);i++) {
		key=key*31 + value[i];
		key=key%HASH_KEYWORD_SIZE;
	}
	return key;
}

void insert(char * value, int num) {
	int key=computeHashFunction(value);
	keyword * ele, nxt;
	ele = newNode(value, num);
	if(hashedKeywords[key] == NULL) {
		hashedKeywords[key] = ele;
	}
	else {
		ele->next = hashedKeywords[key];
		hashedKeywords[key] = ele;
	}
}

int search(char * value) {
	int key=computeHashFunction(value);
	keyword * nd = hashedKeywords[key];
	while(nd!=NULL) {
		if(strcmp(nd->value, value) == 0)
			return nd->num;
		nd=nd->next;
	}
	return -1;
}

token * createToken(int id, char * val, int lno) {
	token * nw;
	nw = malloc(sizeof(token)); 

	memset(nw->val, 0, sizeof(nw->val));
	memset(nw->lxm, 0, sizeof(nw->lxm));

	nw->id = id;
	nw->lno = lno;
	strcpy(nw->val, val);
	strcpy(nw->lxm, ref[id]);

	return nw;
}

static int forward=0;
static char * filename = "../testcases/test.case2";
static FILE *fp = NULL ;
static char buff1[BUFF_SIZE];
static char buff2[BUFF_SIZE];
static int flag = 0;
static int lastChanged = 0;


int init() {

	fp = fopen(filename, "r");
	
	memset(buff1, 0, BUFF_SIZE);
	memset(buff2, 0, BUFF_SIZE);
	fread(buff1, 1, BUFF_SIZE, fp);
	lastChanged=0;
	return 0;
}


void printBuffer() {

	printf("contents of 1 : \n");
	int i;
	for(i=0;i<50;i++) {
		printf("%d ", buff1[i], buff1[i]);
	}
	printf("\n");
	
	printf("contents of 2 : \n");
	// int i;
	for(i=0;i<50;i++) {
		printf("%d ", buff2[i], buff2[i]);
	}
	printf("\n");


}



char getChar() {
	int readC;

	// printf("flag : %d, forward : %d\n", flag, forward);

	if(flag==0) {
		char ch=buff1[forward];
		forward++;
		if(forward==BUFF_SIZE) {
			printf("switching to buff2\n");
			flag=1;
			forward=0;
			
			if(lastChanged==0)
			{
			memset(buff2, 0, BUFF_SIZE);
			fread(buff2, 1, BUFF_SIZE, fp);
			lastChanged=1;
			}
			// printBuffer();
		}
		return ch;
	}
	else {

		// int i;
		// for(i=0;i<100;i++) {
		// 	printf("%c ", buff2[i]);
		// }
		// printf("\n");
		char ch = buff2[forward];
		forward++;
		if(forward==BUFF_SIZE)
		{
			printf("switching to buff1\n");
			flag=0;
			forward=0;
			
			if(lastChanged==1)
			{
			memset(buff1, 0, BUFF_SIZE);
			fread(buff1, 1, BUFF_SIZE, fp);
			lastChanged=0;
		}
			// printBuffer();
		}
		return ch;
	}
}


static int lno = 1;

void modifyForward() {

	// printf("entering modify\n");
	// printf("forward in modify : %d\n", forward);

	if(forward==0 && flag==1)
	{
		printf("switching back to buff1\n");

		flag=0;
		forward=BUFF_SIZE-1;
	}
	else if(forward==0 && flag==0)
	{
		printf("switching back to buff2\n");

     flag=1;
     forward=BUFF_SIZE-1;
	}
	else
    forward--;
}

token * retrace(int state, char attr[30]) {

	// get the pointer back by 1
	modifyForward();

    lexemeBegin=forward+1;

	if(state == 3) {
		return createToken(36, "", lno);
	}
	else if(state == 5) {
		return createToken(38, "", lno);
	}
	else if(state == 8) {
		return createToken(40, "", lno);
	}
	else if(state == 11) {
		return createToken(46, "", lno);
	}
	else if(state == 28) {
		return createToken(31, attr, lno);
	}
	else if(state == 30 || state == 33) {
		return createToken(32, attr, lno);
	}
	else if(state == 27 || state == 26) {
		int val = search(attr);
		if(val>=0)
			return createToken(val, "", lno);
		else{
			if(strlen(attr) > 8) {
				printf("ERROR_1 : Identifier at line %d is longer the prescribed length\n", lno);
				return createToken(56, attr, lno);	
			}
			return createToken(30, attr, lno);
		}
	}
	else {
		return createToken(56, attr, lno);
	}
   
}


token * getToken() {

	int state = 0;

	char attr[30], spot;
	memset(attr, '\0', 30);
	int atptr = 0;
	int commented = 0, cmark = 0;

	while(1) {

		spot = getChar();


		// printf("spot %d\n", spot);

		if(spot == 0) {
			if(state == 0) {
				state = 27;
				return createToken(57, "", lno);
			}
			else {
				return retrace(state, attr);
			}
		}
		else if(commented) {
			if(spot == '*') {
				if(cmark == 0)
					cmark = 1;
				else if(cmark == 1) {
					cmark = 0;
					commented = 0;
				}
			}
			else {
				if(cmark == 1)
					cmark = 0;
			}
		}
		else if(!commented) {
			if(spot == 10 || spot == 9 || spot == 32) {
				if(state == 0){
					if(spot == 10){
						lno++;
					}
					continue;
				}
				else {
					return retrace(state, attr);
				}
			}
			else if(spot == '+') {
				if(state == 0){
					state = 1;
					return createToken(34, "", lno);
				}
				else if(state == 31) {
					state = 32;
				}
				else {
					return retrace(state, attr);
				}
			}
			else if(spot == '-') {
				if(state == 0) {
					state = 2;
					return createToken(35, "", lno);
				}
				else if(state == 31) {
					state = 32;
				}
				else {
					return retrace(state, attr);
				}
			}
			else if(spot == '*') {
				if(state == 0) {
					state = 3;
				}
				else if(state == 3) {
					state = 0;
					commented = 1;
				}
				else {
					return retrace(state, attr);
				}
			}
			else if(spot == '<') {
				if(state == 0) {
					state = 5;
				}
				else if(state == 5) {
					state = 6;
					return createToken(44, "", lno);
				}
				else {
					return retrace(state, attr);
				}
			}
			else if(spot == '>') {
				if(state == 0) {
					state = 8;
				}
				else if(state == 8) {
					state = 9;
					return createToken(45, "", lno);
				}
				else {
					return retrace(state, attr);
				}
			}
			else if(spot == ':') {
				if(state == 0) {
					state = 11;
				}
				else {
					return retrace(state, attr);
				}
			}
			else if(spot == '/') {
				if(state == 0) {
					state = 13;
					return createToken(37, "", lno);
				}
				else {
					return retrace(state, attr);
				}
			}
			else if(spot == '!') {
				if(state == 0) {
					state = 24;
				}
				else {
					return retrace(state, attr);
				}
			}
			else if(spot == '.') {
				if(state == 0) {
					state = 25;
				}	
				else if(state == 25) {
					state = 15;
					return createToken(47, "", lno);
				}
				else if(state == 28) {
					attr[atptr++] = spot;
					state = 29;
				}
				else {
					return retrace(state, attr);
				}
			}
			else if(spot == '[') {
				if(state == 0) {
					state = 17;
					return createToken(52, "", lno);
				}
				else {
					return retrace(state, attr);
				}
			}
			else if(spot == ']') {
				if(state == 0) {
					state = 16;
					return createToken(51, "", lno);
				}
				else {
					return retrace(state, attr);
				}
			}
			else if(spot == '(') {
				if(state == 0) {
					state = 19;
					return createToken(53, "", lno);
				}
				else {
					return retrace(state, attr);
				}
			}
			else if(spot == ')') {
				if(state == 0) {
					state = 18;
					return createToken(54, "", lno);
				}
				else {
					return retrace(state, attr);
				}
			}
			else if(spot == '=') {
				if(state == 0) {
					state = 23;
				}
				else if(state == 23) {
					state = 20;
					return createToken(43, "", lno);
				}
				else if(state == 5) {
					state = 6;
					return createToken(39, "", lno);
				}
				else if(state == 8) {
					state = 10;
					return createToken(41, "", lno);
				}
				else if(state == 24) {
					state = 14;
					return createToken(42, "", lno);
				}
				else if(state == 11) {
					state = 12;
					return createToken(50, "", lno);
				}
				else {
					return retrace(state, attr);
				}
			}
			else if(spot == ',') {
				if(state == 0) {
					state = 22;
					return createToken(49, "", lno);
				}
				else {
					return retrace(state, attr);
				}
			}
			else if(spot == ';') {
				if(state == 0) {
					state = 21;
					return createToken(48, "", lno);
				}
				else {
					return retrace(state, attr);
				}
			}
			else if( (spot >= 65 && spot <= 90) || (spot >= 97 && spot <= 122) ) {
				attr[atptr++] = spot;
				if(state == 0) {
					state = 26;
				}
				else if(state == 26) {
					state = 27;
				}
				else if(state == 27) {
					state = 27;
				}
				else if(state == 30 && (spot == 'e' || spot == 'E')) {
					state = 31;
				}
				else {
					return retrace(state, attr);
				}
			}	
			else if( (spot >= 48 && spot <= 57) ) {
				attr[atptr++] = spot;
				if(state == 0 || state == 28) {
					state = 28;
				}
				else if(state == 26 || state == 27) {
					state = 27;
				}
				else if(state == 29 || state == 30) {
					state = 30;
				}
				else if(state == 31 || state == 32 || state == 33) {
					state = 33;
				}
				else {
					return retrace(state, attr);
				}
			}
			else if(spot == '_') {
				attr[atptr++] = spot;
				if(state == 26 || state == 27) {
					state = 27;
				}
				else {
					return retrace(state, attr);
				}
			}
			else {
				printf("ERROR_2 : Unknown Symbol %c at line %d\n", spot, lno);
				return createToken(56, "", lno);
			}
		}
	}
}













int main(int argc, char  * argv[]) {

	insert("integer",14); 
	insert("real",15);
	insert("boolean",16);
	insert("of",29);
	insert("array",17);
	insert("start",18);
	insert("end",19);
	insert("declare",0);
	insert("module",1);
	insert("driver",4);
	insert("program",5);
	insert("get_value",20);
	insert("print",2);
	insert("use",3);
	insert("with",6);
	insert("parameters",9);
	insert("true",23);
	insert("false",24);
	insert("takes",7);
	insert("input",8);
	insert("returns",11);
	insert("AND",10);
	insert("OR",12);
	insert("for",13);
	insert("in",21);
	insert("switch",22);
	insert("case",25);
	insert("break",26);
	insert("default",27);
	insert("while",28);

	init();

	token * got;

	got = getToken();
	for(int i=0;!(got->id == 56 ||got->id == 57) ;i++) {
		printf("------------- %s, %s, %d\n", got->lxm, got->val, got->lno);
		got = getToken();
	}
	printf("------------- %s, %s, %d\n", got->lxm, got->val, got->lno);


}



