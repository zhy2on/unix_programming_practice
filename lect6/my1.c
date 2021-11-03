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

void do_child(int i) {
	printf("%ld\n", getpid());
	exit(i);
}

int main(void) {	
	int n[3], i;
	pid_t pid[3];
	int status;

	for (i = 0; i < 3; i++) {
		pid[i] = fork();
		if (pid[i] == 0)
			do_child(i);
	}
	while (1) {
		for (i = 0; i < 3; i++) {
			n[i] = waitpid(pid[i], &status, 0);


	while (1)


