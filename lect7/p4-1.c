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

void catchsig(int);

void do_child() {
	int i;
	static struct sigaction act;

	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGINT);
	sigaddset(&act.sa_mask, SIGUSR1);
	sigaddset(&act.sa_mask, SIGUSR2);

	act.sa_handler = catchsig;

	sigaction(SIGINT, &act, NULL);
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);

	for (i=0; i<5; i++) {
		printf("child is running ... \n", i);
		sleep(1);
	}

	exit(0);
}
//SIGUSR2를 SIGUSR1보다 먼저 보내면 어떻게 될까?
int main(void) {	
	int i, k, status;
	pid_t pid;

	pid = fork();
	if (pid == 0)
		do_child();
	sleep(2);
	kill(pid, SIGINT);
	sleep(1);
	kill(pid, SIGUSR2);
	sleep(1);
	kill(pid, SIGUSR1);
	sleep(1);

	wait(&status);
	printf("exit status=%d\n", WEXITSTATUS(status));

	exit(0);
}

void catchsig(int signo) {
	int i, pid;

	for (i = 0; i < 5; i++) {
		printf("handling sig=%d ... \n", signo);
		sleep(1);
	}
}
