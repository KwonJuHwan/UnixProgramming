#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	if (access("Linux.txt" , F_OK)==-1){  //list.txt 파일존재 여부 확인
		perror("Linux.txt");	//오류메시지 출력
		exit(1);		//오류로 인해 프로그램 종료
	}
	return 0;
}
