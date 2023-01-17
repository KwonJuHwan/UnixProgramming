#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h> // rand() 함수를 위한 LIB
#include <time.h>

int main()
{
    initscr();

    int start,end = 0;;

    scanw("%d %d",&start,&end);  // 3 7

    srand(time(NULL));

	printw("%d %d", start, end);
}
