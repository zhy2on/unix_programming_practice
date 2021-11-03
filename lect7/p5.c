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

void catchsig(int signo, siginfo_t *sf, ucontext_t *uc);

int main(void) {
	int status, i;
	pid_t pid;
	static struct sigaction act;

	act.sa_flags = SA_SIGINFO;
	act.sa_handler = catchsig;
	sigaction(SIGUSR1, &act, NULL);

	pid = fork();
	if (pid == 0) {
		pid = getpid();
		for (i = 0; i < 15; i++) {
			printf("... child ... %d\n", pid);
			sleep(1);
		}
		exit(0);
	}
	else {
		sleep(5);
		kill(pid, SIGUSR1);
	}
	wait(&status);
	if (WIFEXITED(status))
		printf("exits ... %d\n", WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		printf("terminated ... %d\n", WTERMSIG(status));

	exit(0);
}

void catchsig(int signo, siginfo_t *sf, ucontext_t *uc) {
	printf("\n CATCHINT: signo=%d\n", signo);
	psiginfo(sf, "...");
	printf("\nsi_code: %d\n", sf->si_code);
}
