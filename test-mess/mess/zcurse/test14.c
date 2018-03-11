#include <curses.h>

void init_EGA_colors()
  {
  int f, b;
  start_color();
  for (f = 0; f < 8; f++)
  for (b = 0; b < 8; b++)
    init_pair( (b *8) +f, f, b );
  }

int EGA_color_attribute( int f, int b )
  {
  return COLOR_PAIR( ((b %8) *8) +(f %8) )
       | ((f < 8) ? 0 : A_BOLD)
       | ((b < 8) ? 0 : A_BLINK);
  }

int main()
  {
  initscr();
  init_EGA_colors();

  bkgd( EGA_color_attribute( 0, 15 ) );  // black on white

  attrset( EGA_color_attribute( 14, 4 ) );  // yellow on red
  mvaddstr( 10, 32, " Press ENTER " );
  move( 24, 0 );
  refresh();

  getch();
  endwin();
  return 0;
  }
