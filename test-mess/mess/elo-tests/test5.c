#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ncurses.h>

#define Black COLOR_BLACK
#define Red COLOR_RED
#define Green COLOR_GREEN
#define Yellow COLOR_YELLOW
#define Blue COLOR_BLUE
#define Magenta COLOR_MAGENTA
#define Cyan COLOR_CYAN
#define White COLOR_WHITE

int main(void) {	
  int ch = 0, elo = 0;
  initscr();
  noecho();
  cbreak();
  halfdelay(20);
  nonl();
  intrflush(stdscr, FALSE);
  curs_set(FALSE);
	if(has_colors() == FALSE)
	{	endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}
	start_color();			/* Start color 			*/
	init_pair(1, Cyan, Black);
	init_pair(2, Green, Black);
attron(COLOR_PAIR(1));
  while ('q' != (ch = getch())) {
    attron(COLOR_PAIR(2));
    mvprintw(0, 0, "%s%d\n", "A Big string which i didn't care to type fully", elo++);
    refresh();
attroff(COLOR_PAIR(2));
  }
attroff(COLOR_PAIR(1));
  endwin();
  return EXIT_SUCCESS;
}
