#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main() {
        int pd[2];
        char str[] = "parent sneds Pipee Test";
        char buf[BUFSIZ];
        int len, status;
	pid_t pid;

        if(pipe(pd) == -1) {
                perror("pipe");
                exit(1);
                }
	switch (pid =fork()){
		case -1 : 
			perror("fork");
			exit(1);
			break;
		case 0 :
			len= read(pd[0], buf, BUFSIZ);
			printf("pipe: %s", buf);
		default:
       			 write(pd[1], str, strlen(str));
      	}	
	close(pd[0]);
        close(pd[1]);

        return 0;
}

