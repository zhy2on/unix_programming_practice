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

void set_p_buf(struct sembuf *p_buf, int snum , int sop) {
	p_buf->sem_num = snum;
	p_buf->sem_op = sop;
	p_buf->sem_flg = 0;
}

int main(void) {
	int semid, n;
	key_t key;
	union semun arg;
	struct sembuf p_buf; //단일 오퍼레이션 지정 예제

	key = ftok("key", 3);
	semid = semget(key, 1, 0600|IPC_CREAT|IPC_EXCL);
	if (semid == -1)
		semid = semget(key, 1, 0);
	else  { //처음 만들어진 경우 초기화
		arg.val = 1; 
		semctl(semid, 0, SETVAL, arg);
	}

	set_p_buf(&p_buf, 0, -1);
	semop(semid, &p_buf, 1);

	printf("process %d in critical section\n", getpid());
	sleep(10);
	printf("process %d leaving critical section\n", getpid());

	set_p_buf(&p_buf, 0, 1);
	semop(semid, &p_buf, 1);

	return 0;
}
