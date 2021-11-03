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
	char *const av[] = {"p3", (char*)0};
#p는 정확한 경로를 써주지 않으면 cwd에서 찾는 게 아니라 환경변수에 의해 설정된
#path에서 명령을 찾는다.
	execvp("p3", av);
	exit(0);
}
