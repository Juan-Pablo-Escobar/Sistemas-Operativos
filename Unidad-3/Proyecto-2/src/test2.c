#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <unistd.h>
#include <ctype.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>

#define PERMS 0644
struct my_msgbuf {
	long mtype;
	char mtext[200];
};

int main(void) {
	struct my_msgbuf buf;
	struct my_msgbuf buf2;
	buf.mtype = 1;
	buf2.mtype = 2;
	int len;
	int msqid;
	int toend;
	key_t key;

	if ((key = ftok("msgq.txt", 'B')) == -1) {
		perror("ftok");
		exit(1);
	}

	if ((msqid = msgget(key, PERMS)) == -1) { /* connect to the queue */
		perror("msgget");
		exit(1);
	}
	printf("Chat:\n");

	switch (fork()) {
	case -1:

	case 0:
		for (;;) {
			if (msgrcv(msqid, &buf, sizeof(buf.mtext), 1, 0) == -1) {
				perror("msgrcv");
				exit(1);
			}
			printf("ACK: %s\n", buf.mtext);
			toend = strcmp(buf.mtext, "end");
			if (toend == 0)
				break;
		}
		printf("message queue: done receiving messages.\n");
		break;
	default:
		while (fgets(buf2.mtext, sizeof buf2.mtext, stdin) != NULL) {
			len = strlen(buf2.mtext);
			/* remove newline at end, if it exists */
			if (buf2.mtext[len - 1] == '\n')
				buf2.mtext[len - 1] = '\0';
			if (msgsnd(msqid, &buf2, len + 1, 0) == -1) /* +1 for '\0' */
				perror("msgsnd");
			if(!strcmp(buf2.mtext, "end")) break;
		}
		wait(NULL);
		printf("message queue: done sending messages.\n");
		system("rm msgq.txt");
	}

	return 0;
}
