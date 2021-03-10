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
	int msqid;
	int len;
	int toend;
	key_t key;
	system("touch msgq.txt");

	if ((key = ftok("msgq.txt", 'B')) == -1) {
		perror("ftok");
		exit(1);
	}

	if ((msqid = msgget(key, PERMS | IPC_CREAT)) == -1) {
		perror("msgget");
		exit(1);
	}
	printf("Chat:\n");
	buf.mtype = 1; /* we don't really care in this case */

	switch (fork()) {
	case -1:
		perror("fork");
		exit(EXIT_FAILURE);
	case 0:
		for (;;) {
			if (msgrcv(msqid, &buf2, sizeof(buf2.mtext), 2, 0) == -1) {
				perror("msgrcv");
				exit(1);
			}
			printf("ACK: %s\n", buf2.mtext);
			toend = strcmp(buf2.mtext, "end");
			if (toend == 0)
				break;
		}
		printf("message queue: done receiving messages.\n");
		break;
	default:
		while (fgets(buf.mtext, sizeof buf.mtext, stdin) != NULL) {
			len = strlen(buf.mtext);
			/* remove newline at end, if it exists */
			if (buf.mtext[len - 1] == '\n')
				buf.mtext[len - 1] = '\0';
			if (msgsnd(msqid, &buf, len + 1, 0) == -1) /* +1 for '\0' */
				perror("msgsnd");
			if(!strcmp(buf.mtext, "end")) break;
		}

		wait(NULL);
		if (msgctl(msqid, IPC_RMID, NULL) == -1) {
			perror("msgctl");
			exit(1);
		}
		printf("message queue: done sending messages.\n");
	}


	return 0;
}
