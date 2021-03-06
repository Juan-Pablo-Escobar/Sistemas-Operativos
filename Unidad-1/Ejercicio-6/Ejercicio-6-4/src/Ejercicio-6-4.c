/*
 ============================================================================
 Name        : Ejercicio-6-4.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct point {
	int x;
	int y;
};

struct rectangle {
	struct point pt1;
	struct point pt2;
};

int main(void) {
	struct rectangle rect;
	printf("Ingrese el valor de X del punto 1\n");
	scanf("%d", &rect.pt1.x);
	printf("Ingrese el valor de Y del punto 1\n");
	scanf("%d", &rect.pt1.y);
	printf("Ingrese el valor de X del punto 2\n");
	scanf("%d", &rect.pt2.x);
	printf("Ingrese el valor de Y del punto 2\n");
	scanf("%d", &rect.pt2.y);
	printf("%d",abs(rect.pt1.x-rect.pt2.x)*abs(rect.pt1.y-rect.pt2.y));
}
