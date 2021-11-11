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
	char *addr;
	pid_t pid;

	fd = open("data2", O_RDWR);
	if (fork() == 0) {
		addr = mmap(NULL, 50, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
		printf("%s\n", addr);
	}
	else {
		addr = mmap(NULL, 50, PROT_READ|PROT_WRITE, MAP_PRIVATE, fd, 0);
		for (i = 0; i < 5; i++) {
			*(addr + i) = *(addr + i) + 1;
		}
		printf("......\n%s\n", addr);
	}
	
	wait(0);
	exit(0);
}
