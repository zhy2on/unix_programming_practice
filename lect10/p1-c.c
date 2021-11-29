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
	int qid, i, in;
	key_t key;
	struct q_entry msg;

	key = ftok("key", 190);
	qid = msgget(key, IPC_CREAT|0600);
	for(i=0; i<3; i++) {
		scanf("%d", &in);
		msg.mtype=1;
		msg.mnum=in;
		msgsnd(qid, &msg, sizeof(int), 0);
	}
	exit(0);
}
