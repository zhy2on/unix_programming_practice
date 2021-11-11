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

	fd = open("data1", O_RDWR);
	addr=mmap(NULL, 10, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 15);
	for (i=0; i<5; i++) {
		printf("%c ... ", *(addr + i));
		*(addr + i) = *(addr + i) + 1;
		printf("%c\n", *(addr + i));
	}
	munmap(addr, 10);

	exit(0);
}
