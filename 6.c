
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
        FILE *rfp, *wfp;
        int c;

        if((rfp =fopen("6.dat", "r")) ==NULL){
                perror("fopen: 6.dat");
                exit(1);}               //fopen을 이용한 읽기전용 6.dat파일 열기
        if((wfp =fopen("6.out", "w")) ==NULL){
                perror("fopen: 6.out");
                exit(1);}               //fopen을 이용한 쓰기전용 6.out 열기

        struct student {
                char name[5];
                int korean;
                int math;
                int english;
                int sum;
                float avg;
        };
				//이름, 점수, 합, 평균을 위한 구조체 선언

        struct student a[6];
        for(int n=0; n<5; n++){
                fscanf(rfp, "%s %d %d %d", a[n].name, &a[n].korean, &a[n].math, &a[n].english);
                a[n].sum=a[n].korean+a[n].math+a[n].english;
                a[n].avg=((float)a[n].sum)/3;
        }

					//fscanf를 이용하여 이름, 각 과목 점수, 합, 평균 받아오기
        for(int i=0; i<5; i++){
                for(int j=0; j<(4-i); j++){
                        if(a[j].sum < a[j+1].sum){
                                a[5]=a[j];
                                a[j]=a[j+1];
                                a[j+1]=a[5];
                        }
                }
        }					//bubble Sort를 이용한 내림차순 정렬

        fprintf(wfp, "	KOR	MATh	ENG	sum	Avg\n");
						//fprintf를 이용하여 위의 변수들 보여주기 
        for(int i=0; i<5; i++){

                fprintf(wfp, "%s	%d	%d	%d	%d	%.1f\n", a[i].name, a[i].korean, a[i].math, a[i].english, a[i].sum, a[i].avg);
        } 		//for문과 fprintf를 이용하여, 정렬된 값 출력
	float x,y,z;
	for(int i=0; i<5; i++){
		x+=(float)a[i].korean;
		y+=(float)a[i].math;
		z+=(float)a[i].english;
	}				//for문을 이용한 과목별 합계 구하기
	x= x/5;
	y= y/5;
	z= z/5;
					//평균 구하기
	fprintf(wfp,"	%.1f	%.1f	%.1f",x,y,z);
				//fpintf를 이용한 과목별 평균 출력	
}
