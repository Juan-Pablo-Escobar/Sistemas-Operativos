/*
 ============================================================================
 Name        : Ejercicio-6.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int factorial(int a){
	int result=a;
	for(int i =a;i>1;i--){
		result = result*(i-1);
	}
	return result;
}

int main(void) {
	int mypid = getpid();
	int pid[3];
	int id=0;
	for(int i = 0;i<3;i++){
		pid[i] = fork();
		if(getpid() != mypid){
			id = i+1;
			break;
		}
	}
	if(id == 0){
		printf("Process %d terminated\n",wait(NULL));
		printf("Process %d terminated\n",wait(NULL));
		printf("Process %d terminated\n",wait(NULL));
	}
	if(id!=0){
		for(int i = 1;i<11;i++){
			printf("[%d]Factorial(%d): %d\n",id,i,factorial(i));
		}
	}


	return EXIT_SUCCESS;
}
