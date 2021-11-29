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
	int semid, n;
	key_t key;
	union semun arg;

	key = ftok("key", 1);
	semid = semget(key, 3, 0600|IPC_CREAT);

	arg.val = 3; //arg의 val값을 변경하고
	semctl(semid, 0, SETVAL, arg); //arg로 SETVAL을 해줘야 적용됨

	n = semctl(semid, 0, GETVAL, arg);
	printf("%d\n", n);

	n = semctl(semid, 0, GETPID, arg); //마지막으로 access한 process
	printf("%d vs %d\n", n, getpid());

	n = semctl(semid, 0, GETNCNT, arg); //첫 번째 큐에서 대기하고 있는 process 수
	printf("%d\n", n);
	
	n = semctl(semid, 0, GETZCNT, arg); //두 번째 큐에서 대기하고 있는 process 수
	printf("%d\n", n);

	return 0;
}
