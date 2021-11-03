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
	pid_t pid;
	printf(“Calling fork …\n”);
	pid=fork();
	if (pid==0) {
		printf(“I am the child\n”);
	}
	else if (pid > 0){
		printf(“ I am the parent, child has pid %d\n”, pid);
	}
	else
		printf(“Fork returned error code\n”);
	return 0;

}
