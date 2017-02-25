#include <stdio.h> 
#include <string.h>
#include <unistd.h> 
#include <stdlib.h> 
#include "lexerDef.h"

#define BUFF_SIZE 1000
#define SIZE 13

struct Node {
	int num;
	char * value;
	struct Node * next;
};

struct Node1 {
	int key;
	struct Node * next;
};


struct Node1 * hashTable[SIZE];


struct Node * newNode(char * value,int num) {
	struct Node * nd=(struct Node *) malloc(sizeof(struct Node));
	if(nd==NULL) {
		return NULL;
	}

	nd->value=value;
	nd->num=num;
	nd->next=NULL;

	return nd;
}

struct Node1 * newNode1(int key) {

	struct Node1 * nd=(struct Node1 *) malloc(sizeof(struct Node1));
	if(nd==NULL) {
		return NULL;
	}

	nd->key=key;
	nd->next=NULL;

	return nd;
}

int computeHashFunction(char * value) {
	int key=0;
	int i=0;
	int len=strlen(value);

	for(i=0;i<len;i++) {
		key=key*31+ value[i];
		key=key%SIZE;
	}

	key=key%SIZE;
	return key;
}



void insert(char * value, int num) {

	int key=computeHashFunction(value);

	if(hashTable[key]==NULL) {
		struct Node1 * nd=newNode1(key);
		hashTable[key]=nd;
		struct Node * el=newNode(value,num);
		nd->next=el;
		return;
	}
	else {
		struct Node * o=hashTable[key]->next;
		struct Node * el=newNode(value,num);
		hashTable[key]->next=el;
		el->next=o;
		return;
	}
 }


int search(char * value) {
	int key=computeHashFunction(value);
	if(hashTable[key]==NULL)
		return -1;
	else {
		struct Node * nd=hashTable[key]->next;
		while(nd!=NULL) {
			if(strcmp(nd->value, value)==0)
				return nd->num;
			nd=nd->next;
		}
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



// static char buff[2][BUFF_SIZE];
// static int line = 0;
// static FILE * fp = NULL;


// int getStream() {

// 	if(fp == NULL) {
// 		// opening the file for read 
// 		char * filename = "../testcases/test.case1";	
// 		fp = fopen(filename, "r");
// 	}

// 	int readChars = fread(buff[(line+1)%2], 1, BUFF_SIZE, fp);
// 	buff[(line+1)%2][BUFF_SIZE] = '\0';
	
// 	return NULL;	
	
// }


static int globalPtr = 0;
static char * filename = "../testcases/test.case2";
static FILE *fp = NULL ;
static char buff[BUFF_SIZE];

int init() {

	fp = fopen(filename, "r");
	
	memset(buff, 0, BUFF_SIZE);
	fread(buff, 1, BUFF_SIZE, fp);
	
	return 0;

}

char getChar() {
	return buff[globalPtr++];
}


static int lno = 1;

token * retrace(int state, char attr[30]) {

	// get the pointer back by 1
	globalPtr--;

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
		int val=search(attr);
		if(val>=0)
			return createToken(val, "", lno);
		else
			return createToken(30, attr, lno);
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
				return retrace(state, attr);
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



