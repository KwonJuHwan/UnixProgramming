#include<sys/types.h>
#include<stdlib.h>
#include<unistd.h>

int main(void){
	pid_t pids[3], pid;
	int state;
	int runProcess=0;	
	while(runProcess <3){
		pids[runProcess]= fork();
		if(pids[runProcess] <0){
			perror("fork");
			exit(1);
		}
		if(pids[runProcess] ==0){
			printf("my pid is %d and ppid is %d\n", (int)getpid(),(int)getppid());
			exit(0);
		}
		runProcess++;
	}
	return 0;
}
