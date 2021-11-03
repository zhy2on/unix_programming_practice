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

int list(const char *name, const struct stat *status, int type) {
	if (type == FTW_NS)
		return 0;
	if (type == FTW_F)
		printf("%-30s\t0%3o\n", name, status->st_mode&0777);
	else
		printf("%-30s*\t0%3o\n", name, status->st_mode&0777);
	return 0;
}

int main() {
	ftw(".", list, 1);

	return 0;
}
