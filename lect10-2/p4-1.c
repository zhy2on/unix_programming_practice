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
	int semid, i;
	key_t key;
	union semun arg;
	ushort buf[3];
	struct sembuf p_buf[2] = {{0, -1, 0}, {1, -1, 0}}; //num, op, flag

	key = ftok("key", 1);
	semid = semget(key, 3, 0600|IPC_CREAT|IPC_EXCL);

	for (i=0; i<3; i++)
		buf[i] = i + 1;
	arg.array = buf;
	printf("SETALL ... %d\n", semctl(semid, 0, SETALL, arg));

	printf("GETALL ... %d\n", semctl(semid, 0, GETALL, arg));
	for (i=0; i<3; i++) //set 잘 됐나 확인
		printf("%d\n", arg.array[i]);
	
	semop(semid, p_buf, 2); //semaphore 연산 : 2개 동시에

	printf("GETALL ... %d\n", semctl(semid, 0, GETALL, arg));
	for (i=0; i<3; i++)
		printf("%d\n", arg.array[i]);
	sleep(10);

	semctl(semid, 0, IPC_RMID, 0);
	return 0;
}
