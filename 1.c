#include <stdio.h>
#include <unistd.h>
#include <sys/ucontext.h>
#include <signal.h>
#include <stdlib.h>
int i=1;
void handler(int signo) {
	printf("^CHandler is called %d time(s)\n", i);
	i++;
}					//signal을 받으면, handler 호출 
int main(void)
{
struct sigaction act;
	
	sigemptyset(&act.sa_mask);
	act.sa_flags= 0;
	act.sa_handler= handler;
	if (sigaction(SIGINT, &act, (struct sigaction *)NULL) <0) {
		perror("sigaction");
		exit(1);
	}
			//signal을 받기위해 설정
	while(1) {
		printf("I'm in infinite loop\n");
		sleep(5);
	}
	return 0;
}

