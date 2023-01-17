#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
        int n;
        extern char *optarg; 		//option의 인자를 저장할 외부 변수
        extern int optind;		//argv의 주소를 담는 외부 변수, 초깃값 1

        long r;

        while((n=getopt(argc, argv, "a:m:")) != -1){	//argv에 opstring("-a,-m")에서 지정된 옵션과 동일한 옵션문자가 있으면 반환

                switch (n){			//옵션이 a인 경우
                        case 'a':
                                r=0;
                                for(--optind; optind < argc; optind++)	//optind를 인덱스로 사용하여 argv 접근
                                        r=r+atol(argv[optind]);
                        break;
                        case 'm':		//옵션이 m인 경우
                                r=1;
                                for(--optind; optind < argc; optind++)	//optind를 인덱스로 사용하여 argv 접근
                                        r= r*atol(argv[optind]);
                        break;
        }
        printf("res=%ld\n",r);
        }
}
