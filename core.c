#include <unistd.h>
#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
char words[35][25] = {
	"knife", "glass", "class", "art", "smart", "bell", "carry", "climb", "between", "blow", "album", "ago", "among", "animal", "any", "box",

"and", "board", "body", "child", "classmate", "city", "boy", "bridge", "clean",

"club", "coat", "bright", "coin", "chopstick", "coffee", "cold", "chance", "chalk", "chair",
};//기본 단어들
char rain[35][25];//화면에 출력할 단어
char user[15];//입력받은 단어
int count = 1;	//현재 진행 라운드수,35= game end
int cut = 1;	//10라운드 이상부터 10개씩 단어를 자르기위한 수단
int life = 5;	//사용자의 life=마지막줄의 단어를 입력 못할 시 깎임
char a[20]="juhwan";	//사용자가 단어를 맞히면 이 단어로 대체
WINDOW *win;
int  screeny[35] = { 0 };	//단어들의 y 좌표
int screenx[35] = { 0 };	//단어들의 x 좌표;
struct Test {
	int correct;
	char answer[35][25];
};
struct Test test = { 0 };
				//얼마나 맞힌지를 나타내주는 구조체
void sig_handler(int signo) { //make rain
				//산성비를 만들기 위한 handler
	wrefresh(win);
	wclear(win);
	wrefresh(win);
	box(win,0,0);
	wrefresh(win);
	mvwprintw(win,0,0,"LIFE: %d",life);	//현재 life 표시;
	wrefresh(win);
	screenx[count - 1] =(int) rand() % 50;	//표시될 단어의 x좌표 랜덤설정;
	for (int i = 0; i < count; i++) {
		screeny[i]++;
	}			//아래로 내려가는 산성비를 만들기위해 y증가
	strcpy(rain[count - 1], words[count-1]); //단어생성;
	if (count <= 10) {	
		for (int i = 0; i < count; i++) {
			if (strcmp(rain[i],a)==0) { //맞힌단어는 표시X
				mvwprintw(win,screeny[i], screenx[i], " ");
			}
			else		//아직 맞추지 못한 단어만 화면에 표시 
			mvwprintw(win,screeny[i], screenx[i], "%s", rain[i]);
		}
	}
	else if (count <=35){	//count가 10초과일때, 다른 알고리즘으로 화면 출력
		if (strcmp(rain[cut - 1],a)!=0) {
			life--;
		}
		for (int i = 0; i < 10; i++) {
			if (strcmp(rain[i],a)==0) {
				mvwprintw(win,screeny[i+cut], screenx[i + cut], " ");
			}
			else
				mvwprintw(win,screeny[i + cut], screenx[i + cut], "%s", rain[i + cut]);
		}
		cut++;
	}	//출력된 단어를 세기위한 cut, count 증가
	count++;
	wrefresh(win);
}
	

	void shortWrite() {
		signal(SIGALRM, sig_handler);
		while (1) {
			alarm(1);
			if (life == 0) {			//game over
				refresh();
				clear();
				refresh();
				printw("GAME OVER!\n");
				usleep(2);
				break;
			}
			refresh();
			mvprintw(15,25,"answer: ");
			mvscanw(15,35,"%s", user);		//word insert
			if (count <= 10) {		//보여지는 단어 중 사용자가 입력한 단어가 동일한지 체크
				for (int i = 0; i < count; i++) {
					if (strcmp(user, rain[i])==0 && strcmp(user," ")!=0) {
						strcpy(test.answer[i], rain[i]);		
						strcpy(rain[i], a);
						test.correct++;
						
						}		//맞으면 correct에 +1
				}
			}
			else if (count <= 35) {		//앞선 것과 같이 count의 수에 따른 다른 알고리즘
				for (int i = 0; i < 10; i++) {
					if (strcmp(user, rain[i+cut]) == 0 && strcmp(user," ")!=0) {
						strcpy(test.answer[i], rain[i]);		
						strcpy(rain[i], a);
						test.correct++;	
					}
				}
			}

			else 
				break;		//count 36이상 = 라운드 종료
		}
	}

int main()
{
	int fd[2];
    pid_t pid;
	test.correct=0;
	FILE* wfp=fopen("answer.txt","w");
	int len,status;
	char buf[257];
	if (pipe(fd) == -1){
		perror("pipe");
		exit(1);
	}
	    switch (pid = fork()) {
        case -1 : /* fork failed */
            perror("fork");
            exit(1);
            break;
        case 0 : /* child process에서 산성비게임 실행 */
		 initscr();
                win=newwin(15,60,0,0);                  //산성비를 보여줄 윈도우 생성
                refresh();
                printw("3 second wait...\n");
                refresh();
                usleep(1000000);
                clear();
                printw("2 second wait...\n");
                refresh();
                usleep(1000000);
                clear();
                printw("1 second wait...\n");           //3초 후 게임시작
                refresh();
                usleep(1000000);
                box(win,0,0);
                wrefresh(win);
                shortWrite();
						//게임시작
                clear();
                refresh();
                endwin();
		for(int j=0; j<35; j++){
			int i=0;		//맞힌 단어를 answer.txt에 저장 	
			while(true){
				char c = test.answer[j][i];
				if(c== '\0')
					break;
				fputc(c,wfp);
				i++;
			}
		}
		fclose(wfp);
		close(fd[0]);			//맞힌 단어를 pipe를 통해 부모 프로세스에게 전달	
		for(int i =0 ; i<35; i++){	
			if(strcmp(test.answer[i], a) !=0)	
			write(fd[1],test.answer[i], 256);
		}
		close(fd[1]);	
		 break;
   	 default :
		while( wait(&status) != pid)
			continue;			//wait함수를 통해, 자식 프로세스 실행종료를 기다림	
		close(fd[1]);
		write(1, "corret words: ",15);
		len = read(fd[0], buf, 256);
		write(1, buf, len);			//맞힌 단어를 출력
	
		printf("\n correct number: %d\n", test.correct);	
			close(fd[0]);		//맞힌 단어의 수 출력	
		break;
	}
			
	}
