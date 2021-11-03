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
	pid_t pid;

	switch (pid=fork()) {
		case -1: perror("fork failed");
			 exit(1);
			 break;
		case 0: execl("/bin/ls", "ls", "-l", (char *)0);
			perror("exec failed");
			exit(1);
			break;
		default: wait((int *)0);
			 printf("ls completed\n");
			 exit(0);
	}
}
