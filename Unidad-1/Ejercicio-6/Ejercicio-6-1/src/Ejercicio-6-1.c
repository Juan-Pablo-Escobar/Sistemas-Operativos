/*
 ============================================================================
 Name        : Ejercicio-6-1.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

float * randomGenArr();
float mean(float *A);
float float_rand( float min, float max );

int main(void) {
	float *A;
	A = randomGenArr();
	printf(" %f ",mean(A));

}

float * randomGenArr(){

	static float A[100];

	for(int i=0; i<100;i++){
		A[i]=float_rand(0.0,100.0);
	}
	return A;

}

float mean(float *A){
	float mean = 0;
	for(int i=0; i<100;i++){
		mean = (mean+(*A++));
	}
	mean = mean/100;
	return mean;
}

float float_rand( float min, float max )
{
	srand ( time(NULL) );
    float scale = rand() / (float) RAND_MAX;
    return min + scale * ( max - min );
}
