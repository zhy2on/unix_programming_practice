#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <ftw.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <time.h>

struct q_entry {
	long mtype;
	int mnum;
};

int main(void) {	
	struct q_entry msg;
	int qid;

	qid = msgget(0111, 0600|IPC_CREAT);

	while (msgrcv(qid, &msg, sizeof(int), 1, 0) > 0) { //1번으로 받고
		printf("%d\n", msg.mnum);
		msg.mtype = 2;
		msg.mnum = msg.mnum + 8;
		msgsnd(qid, &msg, sizeof(int), 0); //2번으로 보낸다
	}
}
