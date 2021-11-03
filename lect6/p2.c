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
// p2.c
int main(int argc, char **argv) {
	int i, N;
	pid_t pid;

	N = atoi(argv[1]);

	printf("pid=%ld ... ppid=%ld\n", getpid(), getppid());

	for (i = 0; i < N; i++) {
		pid = fork();
		if (pid == 0) {
			printf("pid=%ld ... ppid=%ld\n", getpid(), getppid());
		}
	}

	for (i = 0; i < N; i++) {
		if (pid > 0)
			wait(0);
	}

	return 0;
}
