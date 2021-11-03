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

int main(void) {
	pid_t pid;

	printf("parent ... %ld : %ld\n", getpid(), getppid());
	printf("parent ... %ld vs. %ld\n", getpgrp(), getpgid(0));

	pid = fork();
	if (pid == 0) {
		printf("child before ... %ld : %ld\n", getpid(), getppid());
		printf("child before ... %ld vs. %ld\n", getpgrp(), getpgid(0));
		
		setpgid(getpid(), getpid());

		printf("child after ... %ld : %ld\n", getpid(), getppid());
		printf("child after ... %ld vs. %ld\n", getpgrp(), getpgid(0));
	}

	wait(0);
	return 0;
}
