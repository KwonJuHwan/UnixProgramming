

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


        struct student a[6];
        for(int n=0; n<5; n++){
                fscanf(rfp, "%s %d %d %d", a[n].name, &a[n].korean, &a[n].math, &a[n].english);
                a[n].sum=a[n].korean+a[n].math+a[n].english;
                a[n].avg=((float)a[n].sum)/3;
        }

        for(int i=0; i<5; i++){
                for(int j=0; j<(4-i); j++){
                        if(a[j].sum < a[j+1].sum){
                                a[4]=a[j];
                                a[j]=a[j+1];
                                a[j+1]=a[4];
                        }
                }
        }
        fprintf(wfp, "          KOR     MATH    ENG     sum     Avg");

        for(int i=0; i<5; i++){

                fprintf(wfp, "%s        %d      %d      %d      %d      %.1f", a[i].name, a[i].korean, a[i].math, a[i].english, a[i].sum, a[i].avg);
        }
}

