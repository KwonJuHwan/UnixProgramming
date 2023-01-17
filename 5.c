#include <time.h>
#include <stdio.h>

int main() {
	struct tm *tm; //time정보 받아올 구조체 생성
	time_t timep;
	char *str[7]={"(일)", "(월)", "(화)", "(수)", "(목)", "(금)", "(토)"};
	//char *를 이용해서 요일 숫자를 한글로 받아오기. 
	time(&timep); //time을 이용해 시간받아오기

	tm= localtime(&timep); //localtime을 이용해 지역시간 가져오기

	printf("%d. %d. %d. %s %d:%d:%d %s\n", tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday, str[tm->tm_wday],tm->tm_hour, tm->tm_min, tm->tm_sec, tm->tm_zone);
				//date 구조에 맞게 출력
}
