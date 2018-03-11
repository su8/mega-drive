#include <curses.h>

struct COLOR_DATA {
    int pair;
    int fore;
    int back;
    bool bold;
    bool blink;
} COLOR;

void send_out3( WINDOW *win, char *fmt, ...)
{
    char InStr[1024];
    int x, i;
    va_list args;

    va_start( args, fmt );
    vsprintf( InStr, fmt, args );
    va_end( args );

    if( ! win ) win = stdscr;

    for ( x = 0; x < 1024; x++ )
    {
      if ( InStr[x] == '\0' )
        break;
      else if ( InStr[x] == '&' ) // Change the Foreground Color
      {
        ++x;
        if( InStr[x] == 'C' ) { COLOR.fore = COLOR_CYAN; COLOR.bold = true; }
        if( InStr[x] == 'Y' ) { COLOR.fore = COLOR_YELLOW; COLOR.bold = true; }
        if( InStr[x] == 'G' ) { COLOR.fore = COLOR_GREEN; COLOR.bold = true; }
        if( InStr[x] == 'R' ) { COLOR.fore = COLOR_RED; COLOR.bold = true; }
        if( InStr[x] == 'B' ) { COLOR.fore = COLOR_BLUE; COLOR.bold = true; }
        if( InStr[x] == 'W' ) { COLOR.fore = COLOR_WHITE; COLOR.bold = true; }
        if( InStr[x] == 'K' ) { COLOR.fore = COLOR_BLACK; COLOR.bold = true; }
        if( InStr[x] == 'P' ) { COLOR.fore = COLOR_MAGENTA; COLOR.bold = true; }

        i = ((COLOR.back %8) *8) +(COLOR.fore %8);
        wattrset( win, COLOR_PAIR(i) | (COLOR.bold ? A_BOLD : 0) | (COLOR.blink ? A_BLINK : 0) );
      }
      else if ( InStr[x] == '^' ) // Background Color
      {
        ++x;
        if( InStr[x] == 'C' ) { COLOR.back = COLOR_CYAN; COLOR.blink = true; }
        if( InStr[x] == 'Y' ) { COLOR.back = COLOR_YELLOW; COLOR.blink = true; }
        if( InStr[x] == 'G' ) { COLOR.back = COLOR_GREEN; COLOR.blink = true; }
        if( InStr[x] == 'R' ) { COLOR.back = COLOR_RED; COLOR.blink = true; }
        if( InStr[x] == 'B' ) { COLOR.back = COLOR_BLUE; COLOR.blink = true; }
        if( InStr[x] == 'W' ) { COLOR.back = COLOR_WHITE; COLOR.blink = true; }
        if( InStr[x] == 'K' ) { COLOR.back = COLOR_BLACK; COLOR.blink = true; }
        if( InStr[x] == 'P' ) { COLOR.back = COLOR_MAGENTA; COLOR.blink = true; }

        i = ((COLOR.back %8) *8) +(COLOR.fore %8);
        wattrset( win, COLOR_PAIR(i) | (COLOR.bold ? A_BOLD : 0) | (COLOR.blink ? A_BLINK : 0) );
      }
      else
        addch( InStr[x] );
    }
}


void init_color_pairs() 
{
    int f, b, i;

    for (f = 0; f < 16; f++)
      for (b = 0; b < 16; b++)
      {
        i = ((b %8) *8) +(f %8);
        init_pair( i, f %8, b %8 ); // Initialize all of the possible color combo's
      }

}

int main( int argc, char *argv[] )
{
    initscr();
    start_color();
    init_color_pairs();

    /* my_bkgd( COLOR_WHITE, COLOR_RED, true, false ); */

    /* send_out3( stdscr, "Hello, World!\n\n" ); */
    /* send_out3( stdscr, "&RRED &BBLUE &GGREEN &PPURPLE &WWHITE &KBLACK &YYELLOW &CCYAN\n" ); */
    /* send_out3( stdscr, "&rRED &bBLUE &gGREEN &pPURPLE &wWHITE &kBLACK &yYELLOW &cCYAN\n\n" ); */
    /* send_out3( stdscr, "^K&CThis is a test ^W&kOf the different ^b&BColor Combinations.\n\n" ); */
    send_out3( stdscr, "^K&CThis is a ^K&Ptest combinations.\n\n" );
    /* send_out3( stdscr, "^r&WBack to Normal.\n" ); */

    getch();
    endwin();
    return 0;
}
