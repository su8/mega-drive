#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <signal.h>
#include <unistd.h>
#include <poll.h>
#include <curses.h>

#define READ_TIME 50

static void sighandler(int sig) {
  (void)sig;
  endwin();
  exit(EXIT_FAILURE);
}

static int nb_stdin() {
  struct pollfd desc;
  desc.fd = STDIN_FILENO;
  desc.events = POLLIN;
  int ret = poll(&desc, 1, READ_TIME);
  if (ret > 0) {
    assert(desc.revents & POLLIN);
    unsigned char buf[1];
    ssize_t bytes = read(STDIN_FILENO, buf, 1);
    assert(bytes == 1);
    return (int)buf[0];
  } else if (ret < 0) {
    perror("poll");
    raise(SIGINT);
  }
  return -1;
}

int main() {
  signal(SIGINT, sighandler);

  //initscr();
  const char* term_type = getenv("TERM");
  if (term_type == NULL || *term_type == '\0') {
    term_type = "unknown";
  }
  FILE* term_in = fopen("/dev/tty", "r");
  if (term_in == NULL) {
    perror("fopen(/dev/tty)");
    exit(EXIT_FAILURE);
  }
  SCREEN* main_screen = newterm(term_type, stdout, term_in);
  set_term(main_screen);

  nonl();
  noecho();
  cbreak();
  timeout(READ_TIME);

  for (;;) {
    int c = getch();
    if (c != ERR) {
      mvaddch(0,0,c);
      mvaddch(1,1,c);
      mvaddch(2,2,c);
    }
    refresh();
    int b = nb_stdin();
    if (b != -1) {
      mvaddch(0,2,b);
      mvaddch(1,1,b);
      mvaddch(2,0,b);
    }
    refresh();
  }

  endwin();

  return 0;
}
