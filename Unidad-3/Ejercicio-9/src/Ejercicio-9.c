/*
 ============================================================================
 Name        : Ejercicio-9.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUF_SIZE 10

int Read_From_Pipe(int *pfd, char buf[]) {

	ssize_t numRead;

	if (close(pfd[1]) == -1) { /* Write end is unused */
		perror("close - child");
		exit(EXIT_FAILURE);
	}
	for (;;) { /* Read data from pipe, echo on stdout */
		numRead = read(pfd[0], buf, BUF_SIZE);
		if (numRead == -1) {
			perror("read");
			exit(EXIT_FAILURE);
		}

		if (numRead == 0)
			break; /* End-of-file */
		if (write(STDOUT_FILENO, buf, numRead) != numRead) {
			perror("child - partial/failed write");
			exit(EXIT_FAILURE);
		}
	}
	write(STDOUT_FILENO, "\n", 1);
	if (close(pfd[0]) == -1) {
		perror("close");
		exit(EXIT_FAILURE);
	}
	return 1;
}

int Write_To_Pipe(int *pfd, char buf[]) {

	if (close(pfd[0]) == -1) { /* Read end is unused */
		perror("close - parent");
		exit(EXIT_FAILURE);
	}

	if (write(pfd[1], buf, strlen(buf)) != strlen(buf)) {
		perror("parent - partial/failed write");
		exit(EXIT_FAILURE);
	}
	if (close(pfd[1]) == -1) { /* Child will see EOF */
		perror("close");
		exit(EXIT_FAILURE);
	}
	return 1;
}

int main(int argc, char *argv[]) {
	int pfd1[2];
	int pfd2[2];
	char buf[BUF_SIZE];

	if (argc != 3 || strcmp(argv[1], "--help") == 0) {
		printf("usage error: %s string\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if (pipe(pfd1) == -1) {
		perror("pipe for flow 1");
		exit(EXIT_FAILURE);
	}
	if (pipe(pfd2) == -1) {
		perror("pipe for flow 2");
		exit(EXIT_FAILURE);
	}

	switch (fork()) {
	case -1:
		perror("fork");
		exit(EXIT_FAILURE);
	case 0:
		Write_To_Pipe(pfd1,argv[1]);
		Read_From_Pipe(pfd2,buf);
		exit(EXIT_SUCCESS);
	default:
		Write_To_Pipe(pfd2,argv[2]);
		Read_From_Pipe(pfd1,buf);
		wait(NULL);
		exit(EXIT_SUCCESS);
	}
}

