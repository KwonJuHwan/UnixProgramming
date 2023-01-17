#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define SIZE (1000000-1)

int main(void) {
	int fdin, fdout, n;
	char buf[SIZE];
	
	fdin= open("dummy", O_RDONLY); //읽기전용 파일로 오픈
	if(fdin == -1){
		perror("Open dummy");
		exit(1);
	}				//read 할 파일 오픈

	fdout=open("copy", O_CREAT | O_WRONLY | O_TRUNC, 0644); //CREAT로 생성 + 쓰기전용 파일로 만듬
	if(fdout == -1){
		perror("Open copy");
		exit(1);
	}				//write 할 파일 오픈	
	while((n=read(fdin, buf, SIZE)) > 0) {  //read를 통해 파일 읽기
		if( write(fdout, buf,n) !=n) perror("Write");
	}
				//write를 통해 copy파일에 쓰기 
	if (n== -1 ) perror("Read");
	close(fdin);
	close(fdout);
	
	return 0;
}	
