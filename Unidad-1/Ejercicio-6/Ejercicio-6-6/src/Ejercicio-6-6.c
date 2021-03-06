/*
 ============================================================================
 Name        : Ejercicio-6-6.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>


int main(void) {
	int count =0;
	char FILE_NAME[20];
	FILE *in_file;
	FILE *out_file;
	int ch;


	while(1){
		printf("Ingrese la ruta del archivo a leer\n");
		scanf("%s",FILE_NAME);

		in_file = fopen(FILE_NAME,"r");
		if(in_file == NULL){
			printf("Cannot open %s\n", FILE_NAME);

		}
		break;
	}

	while(1){
		printf("Ingrese la ruta del archivo a escribir\n");
		scanf("%s",FILE_NAME);

		out_file = fopen(FILE_NAME,"w+");
		if(out_file == NULL){
			printf("Cannot open %s\n", FILE_NAME);
		}
		break;
	}

	printf("Mensaje a transcribir:\n");
	while(1){
		ch = fgetc(in_file);

		if(ch == EOF)
			break;
			printf("%c",fputc(ch, out_file));
			++count;
	}
	fclose(in_file);
	fclose(out_file);
	exit(0);
}
