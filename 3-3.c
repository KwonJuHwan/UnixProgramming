#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){
	int fd, n;
	char buf[50];
	
	fd=open("3-1.txt", O_RDONLY);
	if (fd==-1){
		perror("Open");
		exit(1);
	}
	n=read(fd, buf, 30);
	if(n== -1) {
		perror("Read");
		exit(1);
	}


	close(fd);
	fd = open("3-3.txt", O_WRONLY);
	if(fd==-1){
		perror("Write");
		exit(1);
	}
	n=write(fd, buf, strlen(buf));
	if(n != strlen(buf)){
		perror("Write");
		exit(2);
	}
	close(fd);
	return 0;
}









