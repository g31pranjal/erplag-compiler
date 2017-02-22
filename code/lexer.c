#include <stdio.h> 
#include <string.h>
#include <unistd.h> 
#include <stdlib.h> 

#define BUFF_SIZE 100


typedef struct {
	int id;
	char val[30];
	int lno;
} token;


token * createToken(int id, char * val, int lno) {
	token * nw;
	nw = malloc(sizeof(token)); 

	memset(nw->val, 0, sizeof(nw->val));

	nw->id = id;
	nw->lno = lno;
	strcpy(nw->val, val);

	return nw;
}


static char buff[2][BUFF_SIZE];
static int line = 0;
static FILE * fp = NULL;


int getStream() {

	if(fp == NULL) {
		// opening the file for read 
		char * filename = "../testcases/test.case1";	
		fp = fopen(filename, "r");
	}

	int readChars = fread(buff[(line+1)%2], 1, BUFF_SIZE, fp);
	buff[(line+1)%2][BUFF_SIZE] = '\0';
	
	return NULL;	
	
}


int globalPtr = 0;

char getChar() {
	char stream[] = {60, 60, 100, 114, 105, 118, 101, 114, 32, 112, 114, 111, 103, 114, 97, 109, 62, 62, 10, 115, 116, 97, 114, 116, 10, 9, 100, 101, 99, 108, 97, 114, 101, 32, 97, 44, 98, 58, 105, 110, 116, 101, 103, 101, 114, 59, 10, 9, 100, 101, 99, 108, 97, 114, 101, 32, 99, 58, 98, 111, 111, 108, 101, 97, 110, 59, 10, 9, 97, 58, 61, 50, 49, 59, 10, 9, 98, 58, 61, 50, 51, 58, 10, 9, 99, 58, 61, 40, 98, 45, 97, 62, 51, 41, 59, 10, 9, 115, 119, 105, 116, 99, 104, 40, 99, 41, 10, 9, 115, 116, 97, 114, 116, 10, 9, 9, 99, 97, 115, 101, 32, 84, 82, 85, 69, 58, 32, 10, 9, 9, 9, 98, 58, 61, 49, 48, 48, 59, 10, 9, 9, 9, 98, 114, 101, 97, 107, 59, 10, 9, 9, 99, 97, 115, 101, 32, 70, 65, 76, 83, 69, 58, 32, 10, 9, 9, 9, 98, 58, 61, 32, 45, 49, 48, 48, 59, 10, 9, 9, 9, 98, 114, 101, 97, 107, 59, 10, 9, 101, 110, 100, 10, 101, 110, 100, 0};

	return stream[globalPtr++];
}


static int lno = 1;

token * retrace(int state, char attr[30]) {

	// get the pointer back by 1
	globalPtr--;
	// printf("entered retracing \n");
	// printf("state %d\n", state);

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
		return createToken(30, attr, lno);
	}
	else {
		return createToken(64, attr, lno);
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

		printf("spot %d\n", spot);

		if(spot == 0) {
			if(state == 0) {
				state = 27;
				return createToken(70, "", lno);
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
				// printf("got whitespace\n");

				if(state == 0){
					if(spot == 10){
						lno++;
						printf("line increment\n");
					}
					continue;
				}
				else {
					// printf("retracing\n");
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

	token * got;

	got = getToken();
	for(int i=0;!(got->id == 64 ||got->id == 70) ;i++) {
		printf("------------- %d, %s, %d\n", got->id, got->val, got->lno);
		got = getToken();
	}

	// buff[1][BUFF_SIZE] = 0;


	// buffer initialization

	// int readChars, line = 0;

	// iteration on the number of times 
	// while(1) {
		
	// 	printf("reading line %d : \n", line );
	// 	readChars = fread(buff[line%2], 1, BUFF_SIZE, fp);

	// 	if(readChars == -1) {
	// 		printf("reading error.. quitting !\n");
	// 		break;

	// 	}

	// }

	
	// printf("%d\n", readChars);

	// printf("reading buff 2\n");
	
	// printf("%d\n", readChars);

	// printf("printing ... \n");

	// for(int i=0;i<=BUFF_SIZE;i++) {
	// 	printf("%d,%c ",buff[0][i], buff[0][i]);
	// }

	// printf("\n");

	// for(int i=0;i<=BUFF_SIZE;i++) {
	// 	printf("%d,%c ",buff[1][i], buff[1][i]);
	// }

	// printf("\n");

	// int i=0,j=0;

	// for(i=0;i<2;i++) {
	// 	for(j=0;j<1025;j++) {
	// 		printf("%c,", buff[i][j]);
	// 	}
	// 	printf("\n\n");
	// }

}



