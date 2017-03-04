/*
Batch no. 82

AUTHORS : 
Pranjal Gupta (2013B4A7470P)
Tanaya Jha (2013B3A7304P)
*/

#include <stdio.h> 
#include <string.h>
#include <unistd.h> 
#include <stdlib.h> 
#include "lexerDef.h"

#define BUFF_SIZE 40
#define HASH_KEYWORD_SIZE 13

typedef struct nd keyword;

struct nd {
	int num;
	char value[25];
	keyword * next;
};

void removeComments(char * filename1) {
	FILE * fp1;
	char c1,c2;
	fp1=fopen(filename1,"r");
	int flag=0;
	if(fp1==NULL)
		return NULL;
	
	do {
		c1 = getc(fp1);
		if(c1 == EOF)
			break;
		if(c1 != '*') {
			printf("%c", c1);
		}
		else {
			c2 = getc(fp1);
			if(c2 == EOF)
				break;
			if(c2 == '*') {
				while(1) {
					char c3=getc(fp1);
					if(c3==EOF) {
						flag=1;
						break;
					}

					if(c3=='*') {
						char c4=getc(fp1);
						if(c4==EOF) {
							flag=1;
							break;
						}
						if(c4=='*')
							break;
					}
				}
				if(flag==1)
					break;
			}
			else {
				printf("%c", c2);
			}
		}
	} while(1);

	fclose(fp1);

}


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

int initLexerHash() {

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

	return 0;
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

static int forward, flag, lastChanged;
static FILE *fp = NULL ;
static char buff1[BUFF_SIZE];
static char buff2[BUFF_SIZE];
static int lno = 1;


int setUpStream(char *filename) {

	initLexerHash();
	
	fp = fopen(filename, "r");
	
	memset(buff1, 0, BUFF_SIZE);
	memset(buff2, 0, BUFF_SIZE);
	fread(buff1, 1, BUFF_SIZE, fp);
	lastChanged = 0;
	forward = 0;
	lno = 1;
	flag = 0;
	return 0;
}



char getChar() {
	int readC;

	if(flag==0) {
		char ch=buff1[forward];
		forward++;
		if(forward==BUFF_SIZE) {
			flag=1;
			forward=0;
			
			if(lastChanged==0) {
				memset(buff2, 0, BUFF_SIZE);
				fread(buff2, 1, BUFF_SIZE, fp);
				lastChanged=1;
			}
		}
		return ch;
	}
	else {
		char ch = buff2[forward];
		forward++;
		if(forward==BUFF_SIZE) {
			flag=0;
			forward=0;
			
			if(lastChanged==1) {
				memset(buff1, 0, BUFF_SIZE);
				fread(buff1, 1, BUFF_SIZE, fp);
				lastChanged=0;
			}
		}
		return ch;
	}
}



void modifyForward() {

	if(forward==0 && flag==1) {
		flag=0;
		forward=BUFF_SIZE-1;
	}
	else if(forward==0 && flag==0) {
		flag=1;
		forward=BUFF_SIZE-1;
	}
	else
		forward--;
}

token * retrace(int state, char attr[30], char lexeme[30]) {

	// printf("got to retracing \n");

	modifyForward();

	if(state == 3) {
		return createToken(36, "*", lno);
	}
	else if(state == 6) {
		return createToken(44, "<<", lno);
	}
	else if(state == 9) {
		return createToken(45, ">>", lno);
	}
	else if(state == 5) {
		return createToken(38, "<", lno);
	}
	else if(state == 8) {
		return createToken(40, ">", lno);
	}
	else if(state == 11) {
		return createToken(46, ":", lno);
	}
	else if(state == 28) {
		return createToken(31, attr, lno);
	}
	else if(state == 30 || state == 33) {
		return createToken(32, attr, lno);
	}
	else if(state == 34) {
		modifyForward();
		char numb[30];
		memset(numb, '\0', 30);
		strncpy(numb, attr, strlen(attr) - 1);
		return createToken(31, numb ,lno);
	}
	else if(state == 27 || state == 26) {
		int val = search(attr);
		if(val>=0)
			return createToken(val, attr, lno);
		else{
			if(strlen(attr) > 8) {
				printf("ERROR_1 : Identifier at line %d is longer the prescribed length\n", lno);
				return createToken(56, attr, lno);	
			}
			return createToken(30, attr, lno);
		}
	}
	else {
		printf("ERROR_3 : Unknown pattern %s \n", lexeme);
		return createToken(56, attr, lno);
	}
   
}


token * getToken() {

	// printf("initiang getToken\n");

	int state = 0;

	char attr[30], spot, lexeme[30];
	memset(attr, '\0', 30);
	memset(lexeme, '\0', 30);
	int atptr = 0;
	int lexemeptr = 0;
	int commented = 0, cmark = 0;

	while(1) {

		spot = getChar();

		// printf("state : %d\n", state);
		// printf("spot : %d\n", spot);

		if(spot == 0) {
			if(state == 0) {
				state = 37;
				return createToken(57, "", lno);
			}
			else {
				return retrace(state, attr, lexeme);
			}
		}
		else if(commented) {
			if(spot == 10)
				lno++;
			else if(spot == '*') {
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
			lexeme[lexemeptr++] = spot;
			if(spot == 10 || spot == 9 || spot == 32 || spot == '\r') {
				if(state == 0){
					if(spot == 10){
						lno++;
					}
					continue;
				}
				else {
					return retrace(state, attr, lexeme);
				}
			}
			else if(spot == '+') {
				if(state == 0){
					state = 1;
					return createToken(34, "+", lno);
				}
				else if(state == 31) {
					attr[atptr++] = spot;
					state = 32;
				}
				else {
					return retrace(state, attr, lexeme);
				}
			}
			else if(spot == '-') {
				if(state == 0) {
					state = 2;
					return createToken(35, "-", lno);
				}
				else if(state == 31) {
					attr[atptr++] = spot;
					state = 32;
				}
				else {
					return retrace(state, attr, lexeme);
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
					return retrace(state, attr, lexeme);
				}
			}
			else if(spot == '<') {
				if(state == 0) {
					state = 5;
				}
				else if(state == 5) {
					state = 6;
				}
				else if(state == 6) {
					state = 35;
					return createToken(58, "<<<", lno);
				}
				else 
					return retrace(state, attr, lexeme);
			}
			else if(spot == '>') {
				if(state == 0) {
					state = 8;
				}
				else if(state == 8) {
					state = 9;
				}
				else if(state == 9) {
					state = 36;
					return createToken(59, ">>>", lno);
				}
				else {
					return retrace(state, attr, lexeme);
				}
			}
			else if(spot == ':') {
				if(state == 0) {
					state = 11;
				}
				else {
					return retrace(state, attr, lexeme);
				}
			}
			else if(spot == '/') {
				if(state == 0) {
					state = 13;
					return createToken(37, "/", lno);
				}
				else {
					return retrace(state, attr, lexeme);
				}
			}
			else if(spot == '!') {
				if(state == 0) {
					state = 24;
				}
				else {
					return retrace(state, attr, lexeme);
				}
			}
			else if(spot == '.') {
				if(state == 0) {
					state = 25;
				}	
				else if(state == 25) {
					state = 15;
					return createToken(47, "..", lno);
				}
				else if(state == 28) {
					attr[atptr++] = spot;
					state = 29;
				}
				else if(state == 29) {
					state = 34;
					return retrace(state, attr, lexeme);
				}
				else {
				}
			}
			else if(spot == '[') {
				if(state == 0) {
					state = 17;
					return createToken(52, "[", lno);
				}
				else {
					return retrace(state, attr, lexeme);
				}
			}
			else if(spot == ']') {
				if(state == 0) {
					state = 16;
					return createToken(51, "]", lno);
				}
				else {
					return retrace(state, attr, lexeme);
				}
			}
			else if(spot == '(') {
				if(state == 0) {
					state = 19;
					return createToken(53, "(", lno);
				}
				else {
					return retrace(state, attr, lexeme);
				}
			}
			else if(spot == ')') {
				if(state == 0) {
					state = 18;
					return createToken(54, ")", lno);
				}
				else {
					return retrace(state, attr, lexeme);
				}
			}
			else if(spot == '=') {
				if(state == 0) {
					state = 23;
				}
				else if(state == 23) {
					state = 20;
					return createToken(43, "==", lno);
				}
				else if(state == 5) {
					state = 6;
					return createToken(39, "<=", lno);
				}
				else if(state == 8) {
					state = 10;
					return createToken(41, ">=", lno);
				}
				else if(state == 24) {
					state = 14;
					return createToken(42, "!=", lno);
				}
				else if(state == 11) {
					state = 12;
					return createToken(50, ":=", lno);
				}
				else {
					return retrace(state, attr, lexeme);
				}
			}
			else if(spot == ',') {
				if(state == 0) {
					state = 22;
					return createToken(49, ",", lno);
				}
				else {
					return retrace(state, attr, lexeme);
				}
			}
			else if(spot == ';') {
				if(state == 0) {
					state = 21;
					return createToken(48, ";", lno);
				}
				else {
					return retrace(state, attr, lexeme);
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
					return retrace(state, attr, lexeme);
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
					return retrace(state, attr, lexeme);
				}
			}
			else if(spot == '_') {
				attr[atptr++] = spot;
				if(state == 26 || state == 27) {
					state = 27;
				}
				else {
					return retrace(state, attr, lexeme);
				}
			}
			else {
				printf("ERROR_2 : Unknown Symbol %c at line %d\n", spot, lno);
				return createToken(56, "", lno);
			}
		}
	}
}













// int main(int argc, char  * argv[]) {

// 	initLexerHash();
// 	setUpStream("../testcases/test.case2");



// 	token * got;

// 	got = getToken();
// 	for(int i=0;!(got->id == 56 ||got->id == 57) ;i++) {
// 		printf("------------- %s, %s, %d\n", got->lxm, got->val, got->lno);
// 		got = getToken();
// 	}
// 	printf("------------- %s, %s, %d\n", got->lxm, got->val, got->lno);


// }



