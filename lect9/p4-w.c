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
	int fd, i, n;
	char buf[512];
	
	mkfifo("fifo", 0600);

	fd = open("fifo", O_RDWR);

	for(;;) {
		n=read(fd, buf, 512);
		write(1, buf, n);
	}
}
