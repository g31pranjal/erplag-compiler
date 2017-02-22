#include <stdio.h> 
#include <string.h>
#include <unistd.h> 
#include <stdlib.h> 

#define BUFF_SIZE 100


typedef struct {
	int id;
	char val[30];
} token;


token * createToken(int id, char * val) {
	token * nw;
	nw = malloc(sizeof(token)); 

	memset(nw->typ, 0, sizeof(nw->typ));
	memset(nw->val, 0, sizeof(nw->val));

	strcpy(nw->id, id);
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


token * getToken() {


	int state = 0;

	while(true) {

		spot = getChar();

		if(spot == '+') {
			if(state == 0){
				state = 1;
				return createToken(34, "");
			}
			else if(state == 31) {
				state = 32;
			}
		}
		else if(spot == '-') {
			if(state == 0) {
				state = 2;
				return createToken(35, "");
			}
			else if(state == 31) {
				state = 32;
			}
		}
		else if(spot == '*') {
			if(state == 0) {
				// this returns a value after look-ahead is false (3)
				state = 3;
			}
			else if(state == 3) {
				state = 4;
				return createToken(55, "");
			}
		}
		else if(spot == '<') {
			if(state == 0) {
				// this returns a value after look-ahead is false (38)
				state = 5;
			}
			if(state == 5) {
				state = 6;
				return createToken(44, "");
			}
		}
		else if(spot == '>') {
			if(state == 0) {
				// this returns a value after look-ahead is false (40)
				state = 8;
			}
			if(state == 8) {
				state = 9;
				return createToken(45, "");
			}
		}
		else if(spot == ':') {
			if(state == 0) {
				// this returns a value after look-ahead is false (46)
				state = 11;
			}
		}
		else if(spot == '/') {
			if(state == 0) {
				state = 13;
				return createToken(37, "");
			}
		}
		else if(spot == '!') {
			if(state == 0) {
				state = 24;
			}
		}
		else if(spot == '.') {
			if(state == 0) {
				state = 25;
			}	
			else if(state == 25) {
				state = 15;
				return createToken(47, "");
			}
			else if(state == 28) {
				state = 29;
			}
		}
		else if(spot == '[') {
			if(state == 0) {
				state = 17;
				return createToken(52, "");
			}
		}
		else if(spot == ']') {
			if(state == 0) {
				state = 16;
				return createToken(53, "");
			}
		}
		else if(spot == '(') {
			if(state == 0) {
				state = 19;
				return createToken(55, "");
			}
		}
		else if(spot == ')') {
			if(state == 0) {
				state = 18;
				return createToken(54, "");
			}
		}
		else if(spot == '=') {
			if(state == 0) {
				// this returns a value after look-ahead is false (43)
				state = 23;
			}
			else if(state == 23) {
				state = 20;
				return createToken(43, "");
			}
			else if(state == 5) {
				state = 6;
				return createToken(39, "");
			}
			else if(state == 8) {
				state = 10;
				return createToken(41, "");
			}
			else if(state == 24) {
				state = 14;
				return createToken(14, "");
			}
			else if(state == 11) {
				state = 12;
				return createToken(12, "");
			}
		}
		else if(spot == ',') {
			if(state == 0) {
				state = 22;
				return createToken(44, "");
			}
		}
		else if(spot == ';') {
			if(state == 0) {
				state = 21;
				return createToken(45, "");
			}
		}
		else if( (spot >= 65 && spot <= 90) || (spot >= 97 && spot <= 122) ) {
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
		}	
		else if( (spot >= 97 && spot <= 122) ) {
			if(state == 0 || state == 28) {
				// this returns a value after look-ahead is false (NUM)
				state = 28;
			}
			else if(state == 29 || state == 30) {
				// this returns a value after look-ahead is false (RNUM)
				state = 30
			}
			else if(state == 31 || state == 32 || state == 33) {
				// this returns a value after look-ahead is false (RNUM)
				state = 33;
			}
		}
		else if(spot == '_') {
			if(state == 26) {
				// this returns a value after look-ahead is false (ID with lookup check)
				state = 27;
			}
			else if(state == 27) {
				// this returns a value after look-ahead is false (ID with lookup check)
				state = 27;
			}
		}




	}


}













int main(int argc, char  * argv[]) {

	buff[1][BUFF_SIZE] = 0;
	createToken("hello", "");


	// buffer initialization

	int readChars, line = 0;

	// iteration on the number of times 
	// while(1) {
		
	// 	printf("reading line %d : \n", line );
	// 	readChars = fread(buff[line%2], 1, BUFF_SIZE, fp);

	// 	if(readChars == -1) {
	// 		printf("reading error.. quitting !\n");
	// 		break;

	// 	}

	// }

	
	printf("%d\n", readChars);

	printf("reading buff 2\n");
	
	printf("%d\n", readChars);

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



