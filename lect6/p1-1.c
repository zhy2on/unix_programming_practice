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
// p1-1.c
int main(void) {
	pid_t pid;

	printf("pid=%ld ... ppid=%ld\n", getpid(), getppid());

	pid = fork();
	if (pid == 0) {
		printf("pid=%ld ... ppid=%ld\n", getpid(), getppid());
		sleep(5);
		printf("pid=%ld ... ppid=%ld\n", getpid(), getppid());
		return 0;
	}
	
	sleep(1);
	return 0;
}
