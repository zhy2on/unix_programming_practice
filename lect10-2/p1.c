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

union semun {
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};

int main(void) {
	int semid, n;
	key_t key;
	union semun arg;
	struct semid_ds temp;

	key = ftok("key", 1);
	printf("%d\n", semid=semget(key, 3, 0600|IPC_CREAT));

	arg.buf=&temp;
	printf("%d\n", semctl(semid, 0, IPC_STAT, arg));
	printf("%d %d\n", arg.buf->sem_perm.uid, getuid());

	scanf("%d", &n);
	semctl(semid, 0, IPC_RMID, 0);
	return 0;
}
