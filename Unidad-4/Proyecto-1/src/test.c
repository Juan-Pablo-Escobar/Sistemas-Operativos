#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>


void unix_error(char *msg) /* Unix-style error */
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}

void printDir(char dir[30],int tabs){
	DIR *streamp;
	struct dirent *dep;
	streamp = opendir(dir);

	errno = 0;
	while ((dep = readdir(streamp)) != NULL) {
		for(int i=0;i<tabs;i++){
			printf(" ");
		}
		printf("%s\n", dep->d_name);
		if(dep->d_type == 4){
			if(dep->d_name[0] != '.'){
				char dirT[100];
				strcpy(dirT,dir);
				if(dirT[strlen(dirT)-1]!='/'){
					sprintf(dirT,"%s%s",dirT,"/");
				}
				sprintf(dirT,"%s%s\0",dirT,dep->d_name);
				printDir(dirT,tabs+1);
			}
		}
	}
	if (errno != 0)
		unix_error("readdir error");

	closedir(streamp);
}


int main(int argc, char **argv)
{

	if (argc != 2) {
		printf("usage: %s <pathname>\n", argv[0]);
		exit(1);
	}
	printDir(argv[1],0);

    exit(0);
}

