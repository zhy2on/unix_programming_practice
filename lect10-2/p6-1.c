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

union semun{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};

int main(void) {	
	int semid, n, val;
	key_t key;
	union semun arg;
	struct sembuf p_buf;

	key = ftok("key", 7);
	semid = semget(key, 1, 0600|IPC_CREAT|IPC_EXCL);
	if (semid==-1) {
		semid = semget(key, 1, 0);
	}
	else {
		arg.val = 1;
		semctl(semid, 0, SETVAL, arg);
	}
	val = semctl(semid, 0, GETVAL, 0);
	printf("semid: %d val: %d\n", semid, val);

	printf("process %d : %d -->", getpid(), semctl(semid, 0, GETVAL, 0));
	p_buf.sem_num = 0;
	p_buf.sem_op = -1;
	p_buf.sem_flg = 0;
	semop(semid, &p_buf, 1);

	printf(" %d\n", semctl(semid, 0, GETVAL, 0));

	return 0;
}
