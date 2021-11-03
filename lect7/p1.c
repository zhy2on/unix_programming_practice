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
	int i, status;
	pid_t pid;

	pid = fork();
	if (pid == 0) {
		for (i = 0; i < 100; i++) {
			printf("... child ... \n");
			sleep(1);
		}
		exit(0);
	}
	else {
		sleep(5);
		kill(pid, SIGINT);
	}
	wait(&status);
	if (WIFEXITED(status))
		printf("exits ... %d\n", WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		printf("terminated ... %d\n", WTERMSIG(status));
	exit(0);
}
