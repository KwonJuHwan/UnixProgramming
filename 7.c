#include <unistd.h>
#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

char words[][35] = { 
	"knife", "glass", "class", "art", "smart", "bell", "carry", "climb", "between", "blow", "album", "ago", "among", "animal", "any", "box",

"and", "board", "body", "child", "classmate", "city", "boy", "bridge", "clean",

"club", "coat", "bright", "coin", "chopstick", "coffee", "cold", "chance", "chalk", "chair",
};	//단어들
struct Test {
	int score;
	int wrong;
	int correct;
	int over;
};	//점수와 틀린,맞힌 ,시간경과된 단어의 수를 기록하기 위한 구조체.
struct Test test = { 0,0,0 ,0};

void sig_handler(int signo) {	//시간 경과시
	refresh();
	clear();
	test.over+=1;		//시간경과 단어 수에 +1
	test.score-=30; //점수 -30
	printw("time out!\n");
	usleep(500000);
	refresh();
	clear();	
	
}

void shortWrite() {		//단어를 출력하고,맞힐 수 있게 하는 함수
	signal(SIGALRM, sig_handler);
	int i = rand() % 35;
	printw("%s\n",words[i]);	//rand를 이용하여, random한 단어 출력
	char user[15]= "NULL";
	while(1){
	alarm(5);	//단어를 보여주고 5초 후에 alarm으로 인해, 시간경과 구현
	scanw("%s", user);		//단어 입력 받기
	refresh();	
	clear();
	if (strcmp(user, words[i]) == 0)	//단어를 맞혔을때
	{				
		test.correct += 1;
		test.score += 50;
		refresh();
		clear();	
		break;
	}
	else if (strcmp(user, words[i]) !=0)	//단어를 틀렸을때
	{
		test.wrong += 1;
		test.score -= 30;
		refresh();
		clear();	
		break;	
	}
	break;
}	
}
int main()
{
	initscr();
	printw("3 second wait...\n");
	refresh();
	usleep(1000000);
	clear();
	printw("2 second wait...\n");
	refresh();
	usleep(1000000); 
	clear();
	printw("1 second wait...\n"); //편의를 위해 구현
	refresh();
	usleep(1000000);
	clear();
	refresh();
	for(int i=0; i<30 ; i++){	//단어쓰기 30번 반복
	shortWrite();
	}
	test.wrong-=test.over;			//시간경과되었을때와 틀린단어의 수가 계산할때 중복되므로 빼줌
	test.score+=(test.over*30);	//위와 동일한 이유로 점수를 더해줌
	clear();
	refresh();
	printw("process complete!\n");
	printw("score: %d, wrong: %d, correct: %d, over: %d", test.score, test.wrong, test.correct, test.over);
	//점수와 틀린,맞힌 ,시간경과된 단어의 수를 출력
	refresh();		

	getch();
	endwin();	

}



