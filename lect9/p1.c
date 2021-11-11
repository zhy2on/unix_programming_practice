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
	char ch[512];
	int pid, p[2];

	if (pipe(p) == -1) {
		perror("pipe call");
		exit(1);
	}

	pid = fork();
	if (pid == 0) {
		close(p[1]);
		read(p[0], ch, 512);
		printf("child: %s\n", ch);
		exit(0);
	}

	close(p[0]);
	scanf("%s", ch);
	write(p[1], ch, 512);

	wait(0);
	exit(0);
}
