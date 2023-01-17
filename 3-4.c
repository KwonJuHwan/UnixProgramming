#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main(void){
	struct stat buf;
	stat("password.txt", &buf);

	printf("Inode = %d\n", (int)buf.st_ino); //파일의 inode 번호 출력

	printf("Mode = %o\n", (unsigned int)buf.st_mode); //파일의 종류와 접근 권한 출력
	printf("Nlink = %o\n", (unsigned int)buf.st_nlink); //하드 링크의 개수 출력
	printf("UID = %d\n", (int)buf.st_uid); //파일소유자의 UID 출력
	printf("GID = %d\n", (int)buf.st_gid); //파일소유 그룹의 GID 출력
	printf("SIZE = %d\n", (int)buf.st_size); //파일의 size 출력
	printf("Atime= %d\n", (int)buf.st_atime); //마지막으로 파일을 읽거나 실행한 시각 출력
	printf("Mtime= %d\n", (int)buf.st_mtime); //마지막으로 파일의 내용을 변경한 시각을 출력
	printf("Ctime= %d\n", (int)buf.st_ctime); //마지막으로 inode의 내용을 변경한 시각을 출력
	printf("Blksize = %d\n", (int)buf.st_blksize);
				//파일 내용을 입출력할때 사용하는 버퍼의 크기 출력	
	printf("Blocks = %d\n", (int)buf.st_blocks);
				//파일에 할당된 파일 시스템의 블록 수 출력
	return 0;
}


