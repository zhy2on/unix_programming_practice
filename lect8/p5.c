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

int main(void) {	
	int fd, i;
	int *addr;
	pid_t pid;

	fd = open("data3", O_RDWR|O_CREAT, 0600);
	if (fork() == 0) {
		addr = mmap(NULL, 50, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
		printf("%d\n", *(addr + 4));
	}
	else {
		addr = mmap(NULL, 50, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
		ftruncate(fd, sizeof(int) * 5);
		for (i = 0; i < 5; i++) {
			*(addr + i) = i;
		}
	}

	wait(0);
	exit(0);
}
