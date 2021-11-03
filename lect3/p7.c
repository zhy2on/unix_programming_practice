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
	DIR *dp;
	struct dirent *d;

	dp = opendir(".");
	d = readdir(dp);
	while (d) {
		printf("%ld : %s\n", d->d_ino, d->d_name);
		d = readdir(dp);
	}
	
	return 0;
}
