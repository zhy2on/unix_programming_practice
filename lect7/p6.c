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

void catchalarm(int);

int main(void) {	
	int i, n;
	static struct sigaction act;

	act.sa_handler = catchalarm;
	sigaction(SIGALRM, &act, NULL);

	n = alarm(10); //alarm의 리턴 값은 첫 alarm의 잔여시간
	printf("알람설정: %d\n", n);
	for (i = 0; i < 10; i++) {
		printf("... running ...\n");
		if (i==1) {
			n = alarm(3);
			printf("알람재설정: %d\n", n);
		}
		sleep(1);
	}
	exit(0);
}

void catchalarm(int signo) {
	printf("\n CATCHALARM: signo=%d\n", signo);
	alarm(3);
}
