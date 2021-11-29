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
	int semid, n, i;
	key_t key;
	union semun arg;
	ushort buf[3];

	key = ftok("key", 1);
	semid = semget(key, 3, 0600|IPC_CREAT|IPC_EXCL);
	if (semid > 0) {
		for (i=0; i<3; i++)
			buf[i] = i+1;
		arg.array = buf;
	}
	printf("SETALL ... %d\n", semctl(semid, 0, SETALL, arg));

	printf("GETALL ... %d\n", semctl(semid, 0, GETALL, arg));
	for (i=0; i<3; i++)
		printf("%d\n", arg.array[i]);

	semctl(semid, 0, IPC_RMID, 0);
	return 0;
}
