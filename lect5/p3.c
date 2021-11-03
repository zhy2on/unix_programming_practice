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

int main(void) {
	printf("pid=%ld\n", getpid());
	printf("parent pid=%ld\n", getppid());
	printf("group id=%ld\n", getpgrp());
	printf("session id=%ld\n", getsid(getpid()));

	return 0;
}
