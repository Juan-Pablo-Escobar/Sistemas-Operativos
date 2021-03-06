/*
 ============================================================================
 Name        : Ejercicio-1.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

const char FILE_NAME[] = "/home/juan-pablo/Escritorio/input.txt";


int main(void) {
	int count =0;
	FILE *in_file;

	int ch;
	in_file = fopen(FILE_NAME,"r");
	if(in_file == NULL){
		printf("Cannot open %s\n", FILE_NAME);
		exit(0);
	}

	while(1){
		ch=fgetc(in_file);
		if(ch == EOF)
			break;
			++count;
	}
	printf("number of characters in %s is %d\n",FILE_NAME,count);
	char a;
	fclose(in_file);
	FILE *out_file;
	out_file = fopen("/home/juan-pablo/Escritorio/output.txt","w+");
	a = fputc('a', out_file);
	printf("%c",a);
	fclose(out_file);
	return(0);

}

