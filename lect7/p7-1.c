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

void catchint(int);

int main(void) {	
	int i, j, num[10], sum=0;
	static struct sigaction act;

	act.sa_handler = catchint;
	sigaction(SIGINT, &act, NULL);

	for (i = 0; i < 5; i++) {
		scanf("%d", &num[i]);
		sum += num[i];
		for (j = 0; j <= i; j++) {
			printf("... i=%d num[%d]=%d\n", i, j, num[j]);
			sleep(1);
		}
	}
	exit(0);
}
void catchint(int signo) {
	printf("DO NOT INTERRUPT ...\n");
}
