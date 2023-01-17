#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#define N 100000000;

unsigned int s =0;
pthread_mutex_t mutex;
int cnt=0;

void *c(void *d){
	pthread_mutex_lock(&mutex); //상호배제를 위해 임계구역 전 lock을 걸음 
	for (int i = 0; i < 100000000 ; i++)
		s++;
	pthread_mutex_unlock(&mutex); //계산이 끝나고 lock을 풀음.
	return(NULL);	
	}

int main(void){
	pthread_t t[2];
	int r;
	pthread_mutex_init(&mutex, NULL); //동기화를 위해 mutex 생성
	r= pthread_create(&t[0], NULL, c, NULL);
	if (r != 0 ){
		perror("thread create: ");
		exit(1);
	}
	
	r = pthread_create(&t[1], NULL, c, NULL);
	if ( r !=0 ) {
		perror("thread creat: ");
		exit(2);
	}
	pthread_join(t[0], NULL);
	pthread_join(t[1], NULL);
	pthread_mutex_destroy(&mutex); //mutex 삭제 
		printf("%u\n", s);
	return 0;
}


