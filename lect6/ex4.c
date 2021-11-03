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

//프로세스의 동기화(2)
int main(void) {	
	pid_t pid;
	int status, exit_status;

	if ((pid=fork()) < 0) {
		perror("fork failed");
		exit(1);
	}
	if (pid==0) {
		sleep(4);
		exit(5);
	}
	if ((pid=wait(&status)) == -1) {
		perror("wait failed");
		exit(2);
	}
	if (WIFEXITED(status)) {
		exit_status = WEXITSTATUS(status);
		printf("Exit status from %d was %d\n", pid, exit_status);
	}
	exit(0);
}
