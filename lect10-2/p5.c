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

int main(int argc, char **argv) {	
	int semid, n, k, val;
	key_t key;
	union semun arg;
	struct sembuf p_buf;

	k = atoi(argv[1]);

	key = ftok("key", 6);
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

	p_buf.sem_num = 0;
	p_buf.sem_op = -k;
	p_buf.sem_flg = 0;
	semop(semid, &p_buf, 1);

	printf("process %d in critical section\n", getpid());
	sleep(10);
	printf("process %d leaving critical section\n", getpid());

	p_buf.sem_num = 0;
	p_buf.sem_op = 2*k;
	p_buf.sem_flg = 0;
	semop(semid, &p_buf, 1);

	return 0;
}
