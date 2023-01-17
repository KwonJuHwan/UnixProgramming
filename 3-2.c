#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){
	int fd;
	int n;

	char str[] = "UNIX SYSTEM PROGRAMMING";

	fd = open("3-1.txt", O_WRONLY);
	if(fd==-1){
		perror("Open");
		exit(1);
	}
			//3-1.txt 파일 오픈
	n = write(fd, str, strlen(str));
	if(n != strlen(str)){
		perror("Write");
		exit(2);
	}
	close(fd);
	return 0;
}

//3-1.txt파일에 str[] write 하기 

