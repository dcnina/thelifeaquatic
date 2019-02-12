#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readPpmFile(FILE *file){
	int nbLines = 0;
	int r, g, b;
	char c;
	
	while(nbLines != 4){
		c = fgetc(file);
		if(c == '\n')
			nbLines ++;
	}
	
	while(!feof(file)){
		fscanf(file, "%d\n%d\n%d\n", &r, &g, &b);
		if(r != 255 || g != 255 || b != 255)
			printf("color : %d %d %d\n", r, g, b);
	}
}

int main(){

	/*Read ppm file*/
	FILE *fileIn;
	fileIn = fopen("img/test5_ppm.ppm", "r");
	readPpmFile(fileIn);
	fclose(fileIn);
	
return 0;
}
