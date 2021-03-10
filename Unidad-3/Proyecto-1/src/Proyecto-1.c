/*
 ============================================================================
 Name        : Proyecto-1.c
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
#include <ctype.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>

#define BUF_SIZE 10

void tolowercase(char *a){
	for(int i = 0;i<strlen(a);i++){
		a[i] = tolower(a[i]);
	}
}

void touppercase(char *a){
	for(int i = 0;i<strlen(a);i++){
		a[i] = toupper(a[i]);
	}
}


int main(int argc, char *argv[])
{

	printf("Para salir del proceso escribir exit\n");

    int pfd[2]; /* Pipe file descriptors */
    int pfd_aux[2]; /* Pipe file descriptors */
    char buf[BUF_SIZE];

    if (argc != 2 || strcmp(argv[1], "--help") == 0){
        printf("usage error: %s string\n", argv[0]);
        exit(EXIT_FAILURE);
    }


    if (pipe(pfd) == -1){ /* Create the pipe */
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    if (pipe(pfd_aux) == -1){ /* Create the pipe */
		perror("pipe");
		exit(EXIT_FAILURE);
	}

    switch (fork())
    {
    case -1:
        perror("fork");
        exit(EXIT_FAILURE);
    case 0: /* Child  - reads from pipe */
        if (close(pfd[1]) == -1)
        { /* Write end is unused */
            perror("close - child");
            exit(EXIT_FAILURE);
        }
        if (close(pfd_aux[0]) == -1)
		{
			perror("close - child");
			exit(EXIT_FAILURE);
		}
        while(1){

			read(pfd[0], buf, BUF_SIZE);
			if(!strcmp(buf,"exit")) break;
			touppercase(buf);
        	if (write(pfd_aux[1], buf, BUF_SIZE) != BUF_SIZE)
			{
				perror("parent - partial/failed write");
				exit(EXIT_FAILURE);
			}

		}

        write(STDOUT_FILENO, "\n", 1);
        if (close(pfd[0]) == -1)
        {
            perror("close");
            exit(EXIT_FAILURE);
        }
        if (close(pfd_aux[1]) == -1)
		{
			perror("close");
			exit(EXIT_FAILURE);
		}

        exit(EXIT_SUCCESS);
    default: /* Parent - writes to pipe */

        if (close(pfd[0]) == -1)
        {
            perror("close - parent");
            exit(EXIT_FAILURE);
        }
        if (close(pfd_aux[1]) == -1)
		{
			perror("close - parent");
			exit(EXIT_FAILURE);
		}
        while(1){
        	scanf("%s",buf);
        	tolowercase(buf);
			if (write(pfd[1], buf, BUF_SIZE) != BUF_SIZE)
			{
				perror("parent - partial/failed write");
				exit(EXIT_FAILURE);
			}
			if(!strcmp(buf,"exit")) break;
			read(pfd_aux[0], buf, BUF_SIZE);
			printf("%s\n",buf);
        }

        if (close(pfd[1]) == -1)
        { /* Child will see EOF */
            perror("close");
            exit(EXIT_FAILURE);
        }
        if (close(pfd_aux[0]) == -1)
		{ /* Child will see EOF */
			perror("close");
			exit(EXIT_FAILURE);
		}
        wait(NULL); /* Wait for child to finish */
        exit(EXIT_SUCCESS);
    }
}
