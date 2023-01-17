#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]){
	int i, sum = 0;

	for(i=1; i<argc; i++){
		sum += atoi(argv[i]); 	//명령행 인자(문자열)을 정수로 전환 후 주어진 정수 합을 sum 변수에 저장
	}
	printf("%d\n",sum);
	return 0;
}
