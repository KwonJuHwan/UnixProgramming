#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
    int fd[2];
    pid_t pid;

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }

    switch (pid = fork()) {
        case -1 :
            perror("fork");
            exit(1);
            break;
        case 0 : /* child */
            close(fd[0]);	//child가 ls -l 명령의 결과를 전송
            if (fd[1] != 1) {
                dup2(fd[1], 1);
                close(fd[1]);
            }			//표준 입력을 사용하기위해 close(fd[1])이용
            execlp("ls", "ls", "-l", (char *)NULL);
            wait(NULL);
            break;
				
        default :
					//parent
	close(fd[1]);		//parent는 ls -l 명령의 결과를 받아, grep c 명령 실행
            if (fd[0] != 0) {
                dup2(fd[0], 0);
                close(fd[0]);
            }
				//표준 출력을 사용하기 위해 받음
            execlp("grep", "grep","c",  (char *)NULL);

            exit(1);
            break;

    }
}
