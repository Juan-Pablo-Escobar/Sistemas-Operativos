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

int main(void) {
	int a;
	int b;
	char o;
	do {
		printf("Ingrese el primer operando\n");
		scanf("%d", &a);
		printf("Ingrese el primer operando\n");
		scanf("%d", &b);
		do {
			printf("Ingrese el operador\n");
			o = getchar();
			o = getchar();
			if (o != '+' & o != '-' & o != '*' & o != '/') {
				printf("Eror en el operador\n");
			}
		} while (o != '+' & o != '-' & o != '*' & o != '/');
		if (o == '+') {
			printf("%d\n", a + b);
		} else if (o == '-') {
			printf("%d\n", a - b);
		} else if (o == '*') {
			printf("%d\n", a * b);
		} else if (o == '/') {
			printf("%d\n", a / b);
		}
		do {
			printf("Desea Continuar s/n\n");
			o = getchar();
			o = getchar();
		} while (o == 's' & o == 'n');
	} while (o != 'n');
	printf("end");
	return (0);
}
