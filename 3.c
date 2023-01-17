#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main() {
    int shmid, i;
    char *shmaddr, *shmaddr2;
    pid_t pid;

    shmid = shmget(IPC_PRIVATE, 20, IPC_CREAT|0644);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }
				//공유 메모리 식별자 생성
    switch (pid=fork()) {
        case -1:
            perror("fork");
            exit(1);
            break;
        case 0:				//child process에서 addr1에 문자열 쓰기
            shmaddr = (char *)shmat(shmid, (char *)NULL, 0);
            printf("=Child %d begins\n",getpid());
            strcpy(shmaddr,"Message from process#");	//getpid()를 이용해 child process pid 출력), strcpy를 이용해, 공유메모리에 문자열 넣기 
            shmdt((char *)shmaddr);
       	    printf("=Child %d ends\n", getpid());    
	 exit(0);
            break;
        default:			//parent process에서 add2로 문자열 받기
            wait(0);
            shmaddr2 = (char *)shmat(shmid, (char *)NULL, 0);
            printf("=Parent Process %d begins\n", getpid());	//get pid()를 ㅣ이용해 부모 프로세스 pid 출력	
            printf("%d %s  %d\n", getpid(),shmaddr2, pid);//공유메모리에서 문자열 읽어와서 출력 
            shmdt((char *)shmaddr2);	//geppid()로 부모 프로세스, pid로 자식 프로세스 pid 출력
            shmctl(shmid, IPC_RMID, (struct shmid_ds *)NULL);
       	    printf("=Parent %d ends\n", getpid());    
	 break;
    }
}
