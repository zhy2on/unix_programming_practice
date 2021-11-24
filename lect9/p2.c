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
	int i, in , pid, p[2][2];

	for (i=0; i<2; i++) //순서 중요 - pipe를 만들고 fork를 해야 child에도 복사
		pipe(p[i]);

	pid = fork();
	if (pid==0) {
		close(p[0][1]);
		close(p[1][0]);
		read(p[0][0], &in, sizeof(int));
		in++;
		write(p[1][1], &in, sizeof(int));
		exit(0);
	}

	close(p[0][0]);
	close(p[1][1]);
	scanf("%d", &in);
	write(p[0][1], &in, sizeof(int));
	read(p[1][0], &in, sizeof(int));
	printf("parent: %d\n", in);

	wait(0);
	exit(0);
}
