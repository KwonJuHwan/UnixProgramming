#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char** argv) {
    int sd;
    char buf [256];
    struct sockaddr_in ser;

    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }
			//소켓 생성
    memset((char *)&ser, '\0', sizeof(ser));
    ser.sin_family = AF_INET;
    ser.sin_port= htons(9000);	//port 번호 9000사용
    ser.sin_addr.s_addr = inet_addr("127.0.0.1"); //local host IP사용   

    if (connect(sd, (struct sockaddr *)&ser, sizeof(ser)) ) {
        perror("bind");
        exit(1);
    }			//서버와 연결 요청
   strcpy(buf, argv[1]);   
 for(int i=2; i< argc; i++){
 	strcat(buf," ");
	strcat(buf,argv[i]); 
    }				//표준 입력으로 받은 문자열 buf에 저장 
	 if (send(sd, buf, sizeof(buf), 0) == -1) {
        perror("send");			//buf 보내기
        exit(1);
    }
if (recv(sd, buf, sizeof(buf), 0) == -1) {
        perror("recv");
        exit(1);
    }					//뒤집혀진 문자열 받아서 출력
	printf("From Server: %s\n", buf);
	 close(sd);
}
