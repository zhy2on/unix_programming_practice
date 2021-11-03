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
// p6.c
// 동기화 잘 된 프로그램

void do_child(void) {
	int i;

	for (i = 0; i < 5; i++) {
		printf("child %ld running ...\n", getpid());
		sleep(1);
	}
	exit(0);
}

int main(void) {	
	int i, status, N=3;
	pid_t pid;

	for (i = 0; i < N; i++) {
		pid = fork();
		if (pid == 0) {
			do_child();
		}
	}

	for (i = 0; i < N; i++) { //child 개수만큼 wait 필요
		pid = wait(&status); //어떤 child가 종료했는지 확인
		if (WIFEXITED(status)) {
			printf("%ld ... %d\n", pid, WEXITSTATUS(status));
		}
	}
	exit(0);
}

