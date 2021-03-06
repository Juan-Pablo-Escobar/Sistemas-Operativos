/*
 ============================================================================
 Name        : Ejercicio-8.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

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
	if(id==1){
		char *args[]={"./prom","4","5","6","7","8",NULL};
		execv(args[0],args);
	}else if(id==2){

		char *args[]={"./max","4","5","6","7","8",NULL};
		execv(args[0],args);
	}else if(id==3){

		char *args[]={"./min","4","5","6","7","8",NULL};
		execv(args[0],args);
	}


	return EXIT_SUCCESS;
}
