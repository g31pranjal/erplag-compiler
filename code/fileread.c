#include <stdio.h> 
#include <string.h>
#include <unistd.h> 
#include <stdlib.h> 


int main(int argc, char  * argv[]) {

	// opening the file for read 
	char * filename = "../testcases/test.case2";
	FILE *fp;
	fp = fopen(filename, "r");

	// buffer initialization
	int BUFF_SIZE = 1000;
	char buff[2][BUFF_SIZE];

	memset(buff[1], 1, 1000);

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

	
	// printf("%d\n", readChars);

	printf("reading buff 2\n");
	readChars = fread(buff[1], 1, BUFF_SIZE, fp);
	
	printf("%d\n", readChars);

	printf("printing ... \n");

	for(int i=0;i<=BUFF_SIZE;i++) {
		printf("%d, ", buff[1][i]);
	}

	printf("\n");

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