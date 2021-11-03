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
// p3.c
void ABC(void) {
	printf("ABC ...\n");
}

void DEF(void) {
	printf("DEF ...\n");
}

void GHI(void) {
	printf("GHI ...\n");
}

int main(void) {
	atexit(ABC);
	atexit(DEF);
	atexit(GHI);

	exit(15);
}
