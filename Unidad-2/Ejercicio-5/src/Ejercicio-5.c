/*
 ============================================================================
 Name        : Ejercicio-5.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int IsDigit(char a[]){
	int i = 0;
	while(1){
		if(a[i]==NULL){
			break;
		}
		if(!isdigit(a[i])){
			return 0;
		}
		i++;
	}
	return 1;
}

int main(int argc, char *argv[]) {

	int *b = malloc(sizeof(int)*argc);
	int realsize = 0;
	for (int i = 0; i < argc; i++) {
		if(IsDigit(argv[i])){
			b[realsize] = atoi(argv[i]);
			realsize++;
		}
	}
	float sum = 0;
	float prom = 0;
	int max = b[0];
	int min = b[0];
	for(int i =0;i<realsize;i++){
		sum += b[i];
		if(b[i]> max){
			max = b[i];
		}
		if(b[i]< min){
			min = b[i];
		}
	}
	prom = sum/((float)realsize);
	printf("Promedio: %.2f Maximo: %d Minimo: %d",prom,max,min);
	exit(EXIT_SUCCESS);
}
