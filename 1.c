#include<stdio.h>
#include<stdlib.h>
int main(int argc, char *argv[]){
	int n;
	float sum=0.0; //숫자들의 합	
	for(n=1; n< argc; n++){
		sum+=atof(argv[n]);
	}
	printf("%.6f\n",sum);	


	return 0; }

//argc, argv를 이용한 sum

