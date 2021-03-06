/*
 ============================================================================
 Name        : Ejercicio-3.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <pthread.h>

int x = 0;

void ft(){
	int i;
	printf("Identificador de hilo %d. \n tiene el valor de %d \n antes de ser interpretado 1000 veces por este hilo \n",(int)getpid(),x);
	for(i = 0;i<1000;i++)x++;
}

int main()
{
	pthread_t hilos_ids[4];
	int i;
	for(i = 0; i<4;++i) pthread_create(&hilos_ids[i],NULL,(void*)ft,NULL);
	for(i = 0; i<4;++i) pthread_join(hilos_ids[i],NULL);
	printf("Hilo principal: x= %d\n",x);

	return 0;
}
