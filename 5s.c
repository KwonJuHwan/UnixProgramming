#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

int main() {
    char buf[256];
    struct sockaddr_in ser, cli;
    int sd, nsd, len, clen, clentlen = sizeof(cli);
    int i =0;
    int count=0;
    char temp;
	   if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }
		//socket 생성`
    memset((char *)&ser,'\0', sizeof(ser));
    ser.sin_family = AF_INET;
    ser.sin_port = htons(9000);		//포트 번호 9000번 사용 
    ser.sin_addr.s_addr = inet_addr("127.0.0.1"); //local hostIP 사용

    if (bind(sd, (struct sockaddr *)&ser, sizeof(ser))) {
        perror("bind");
        exit(1);
    }
				//bind를 통해, 포트 연결
    if (listen(sd, 5) ) {
        perror("listen");
        exit(1);
    }
			//클라이언트의 연결 요청을 받을 수 있게됨
    if ((nsd = accept(sd, (struct sockaddr *)&cli, &clentlen)) == -1) {
        perror("accept");
        exit(1);
    }
			//클라이언트의 요청을 받아들임.
    if (recv(nsd, buf, sizeof(buf), 0) == -1) {
        perror("recv");
        exit(1);
    }			//문자열을 받음
  while(buf[i++] >0)
	count++;
   for(i=0; i<count /2; i++){
	temp = buf[i];	
	buf[i]= buf[count-i-1];
	buf[count-i-1]=temp;
	} 
				//받은 문자열 뒤집기
	if (send(nsd, buf, sizeof(buf), 0) == -1) {	//뒤집은 문자열 보내기
        perror("send");
        exit(1);
    }
    close(nsd);
    close(sd);
}
