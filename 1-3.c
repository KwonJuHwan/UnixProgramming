#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(void){
	char *str;
//	str= malloc(sizeof(char)*20);	//malloc을 통해 char크기의 20칸 배열 메모리공간 할당

	strcpy(str, "Hello");		//문자열 hello를 str에 복사
	printf("%s\n",str);

	strcpy(str, "Good morning");	//문자열 Good moring을 str에 복사

	printf("%s\n", str);

	free(str);		//str에 할당한 메모리 반환
	return 0 ;
}
