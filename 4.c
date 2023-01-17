#include <stdio.h>
#include <string.h>
int main(int argc, char** argv) {
	char *contry[BUFSIZ];
	char *str;
	int j=0;
	for(int i=1; i<argc; i++){
		contry[j]=argv[i];
		j++;	
		}			//country에 표준출력으로 받은 문자열들 넣기
printf("Queue Order: \n");
	for (int i = 1; i < argc; i++) {
		printf("%s ", argv[i]);
	}				//queue 순서대로 출력 
	printf("\nStack Order: \n");
	for (int i = argc-1; i>0 ; i--) {
		printf("%s ", argv[i]);
	}
					//stack 순서대로 출력
	 for(int j=0; j<argc-2; j++){
                for(int i=0; i<argc-2-j; i++){
                        if(strcmp(contry[i], contry[i+1]) >0){
				str = contry[i+1];
				contry[i+1] = contry[i];
				contry[i] = str;
                        }
                }
        }			//bubble sort를 이용해서 오름차순 정렬
	printf("\nAlphabetical Order: \n");
	for (int i = 0; i < argc-1; i++) {
		printf("%s ", contry[i]);
	}
	printf("\nReverse Alphabetical Order: \n");
	for (int i = argc-2; i>=0; i--){	// 내림차순으로 출력
		printf("%s ", contry[i]);
	}
	printf("\n");
	return 0;
}
