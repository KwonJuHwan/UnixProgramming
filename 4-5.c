#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
int main(void){
	pid_t pid;
	int status;	
	if((pid = fork())<0){
		perror("fork");
		exit(1);
	}
	if(pid > 0){
		wait(&status);
		sleep(10);
	}
	else {
		sleep(10);
	}
	return 0;
}
	
