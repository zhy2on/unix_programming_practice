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

void do_child(void) {
	int i;

	for (i = 0; i < 5; i++) {
		printf("child %ld running ...\n", getpid());
		sleep(1);
	}
	exit(0);
}

int main(void) {
	int i, n, status;
	pid_t pid;

	pid = fork();
	if (pid == 0) {
		do_child();
	}
	while (1) {
		n = waitpid(pid, &status, WNOHANG);
		if (n > 0) {
			if (WIFEXITED(status))
				printf("%ld ... %d\n", n, WEXITSTATUS(status));
			exit(0);
		}
		printf("waiting....\n");
		sleep(1);
	}
}

