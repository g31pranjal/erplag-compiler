#include <stdio.h>
#include <stdlib.h>
#include <string.h>
FILE * removeComments(char * filename1,char * filename2) {
	FILE * fp1, * fp2;
	char c1,c2;
	fp1=fopen(filename1,"r");
	fp2=fopen(filename2,"w");
    int flag=0;
	if(fp1==NULL)
		return NULL;
	if(fp2==NULL)
		return NULL;

	do {
		c1 = getc(fp1);
		if(c1 == EOF)
			break;
		if(c1 != '*')
			putc(c1,fp2);
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
				putc(c2,fp2);
			}
		}
	} while(1);

	fclose(fp1);
	fclose(fp2);
	return fp2;
}


int main() {
	FILE * fp1=rmv("../testcases/test.case2","../testcases/myFile.txt");
	return 0;
}