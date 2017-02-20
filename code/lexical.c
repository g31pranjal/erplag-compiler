#include <stdio.h> 
#include <string.h>
#include <unistd.h> 
#include <stdlib.h> 

typedef struct {
	char typ[12];
	char val[30];
} token;


token * createToken(char * typ, char * val) {
	token * nw;
	nw = malloc(sizeof(token)); 

	memset(nw->typ, 0, sizeof(nw->typ));
	memset(nw->val, 0, sizeof(nw->val));

	strcpy(nw->typ, typ);
	strcpy(nw->val, val);

	return nw;
}





int main(int argc, char  * argv[]) {

	createToken("hello", "");

	// opening the file for read 
	char * filename = "../testcases/test.case1";
	FILE *fp;
	fp = fopen(filename, "r");

	// buffer initialization
	int BUFF_SIZE = 400;
	char buff[2][BUFF_SIZE + 1];
	buff[0][BUFF_SIZE] = buff[1][BUFF_SIZE] = '\0';

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
	readChars = fread(buff[1], 1, BUFF_SIZE, fp);
	
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

