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

struct databuf {
	int d_nread;
	char d_buf[512];
};

int main(void) {	
	char *buf1;
	int i, shmid1, shmid2, shmid3, *buf2;
	struct databuf *buf3;

	shmid1 = shmget(01111, 512, 0600|IPC_CREAT);
	shmid2 = shmget(01112, 10*sizeof(int), 0600|IPC_CREAT);
	shmid3 = shmget(01113, 5*sizeof(struct databuf), 0600|IPC_CREAT);

	buf1 = (char*)shmat(shmid1, 0, 0);
	buf2 = (int*)shmat(shmid2, 0, 0);
	buf3 = (struct databuf*)shmat(shmid3, 0, 0);

	write(1, buf1, 512);
	for (i=0; i<10; i++)
		printf("%d\n", *(buf2+i));
	for (i=0; i<5; i++)
		printf("%s\n", (buf3+i)->d_buf);
	exit(0);
}
