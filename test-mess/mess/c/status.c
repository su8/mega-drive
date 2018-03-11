/*
 * status.c for WMFS²
 * xorg62
 * cc status.c -lX11 -lmpdclient -o status
 */
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <unistd.h>
#include <sys/queue.h>
#include <mpd/status.h>
#include <mpd/connection.h>
#include <mpd/tag.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>

#define SEP(a) "^s["a";#898989; - ]"

/* sys */
static struct tm *tm;
static time_t t;
static long ocpu[4] = { 0 };

/* X */
static Display *dpy;
static Window root;
static Atom autf8, afunc, acmd;

#define STACKADD(ptr)                          \
  do {                                         \
    struct stack_s *s;                         \
    s = malloc(sizeof(struct stack_s));        \
    s->adr = (void*)ptr;                       \
    SLIST_INSERT_HEAD(&stackhead, s, next);    \
  } while(/* CONSTCOND */ 0)

#define STACKDEL()                             \
  do {                                         \
    struct stack_s *s;                         \
    while(!SLIST_EMPTY(&stackhead))            \
    {                                          \
      s = SLIST_FIRST(&stackhead);             \
      SLIST_REMOVE_HEAD(&stackhead, next);     \
      free(s->adr);                            \
      free(s);                                 \
    }                                          \
  } while(/* CONSTCOND */ 0)

struct stack_s
{
  void *adr;
  SLIST_ENTRY(stack_s) next;
};
static SLIST_HEAD(, stack_s) stackhead = SLIST_HEAD_INITIALIZER(&stackhead);

static void
status_send(const char *str, ...)
{
  va_list ap;
  char *p;
  XClientMessageEvent e = {
    .type         = ClientMessage,
    .message_type = afunc,
    .window       = root,
    .format       = 32,
    .data.l[4]    = true
  };

  va_start(ap, str);
  vasprintf(&p, str, ap);
  va_end(ap);

  XChangeProperty(dpy, root, afunc, autf8, 8, PropModeReplace, (unsigned char*)"status", 6);
  XChangeProperty(dpy, root, acmd, autf8, 8, PropModeReplace, (unsigned char*)p, strlen(p));

  free(p);
  XSendEvent(dpy, root, false, StructureNotifyMask, (XEvent*)&e);
  XSync(dpy, False);
}

static char*
status_date(void)
{
  static char date[128] = { 0 };
  char *ret;

  tm = localtime(&t);
  t  = time(NULL);
  strftime(date, 128, "%a, %d %b %Y %T", tm);

  asprintf(&ret, "^s[right;#DDDDDD;%s]", date);
  STACKADD(ret);

  return ret;
}

static char*
status_mpd(void)
{
  char *ret;
  int tx = 0;

  struct mpd_connection *co;
  struct mpd_song *song;
  struct mpd_status *status;

  if(!(co = mpd_connection_new("127.0.0.1", 0, 10000))
     || !(song = mpd_run_current_song(co))
     || !(status = mpd_run_status(co)))
    return " ";

  if(!(tx = mpd_status_get_total_time(status)))
    tx = 1;

  asprintf(&ret, "^s[left;#aabbaa;MPD ]"
                 "^p[left;7;12;0;%d;100;#666666;#119911] ^s[left;#000000; ]"
                 "^P[left;100;6;3;%d;%d;#888888;#11ff11]"
                 "^s[left;#666666; [%dkbps\\] ]"
                 "^s[left;#DDDDDD;%s - %s]",
           mpd_status_get_volume(status),
           mpd_status_get_elapsed_time(status), tx,
           mpd_status_get_kbit_rate(status),
           mpd_song_get_tag(song, MPD_TAG_ARTIST, 0),
           mpd_song_get_tag(song, MPD_TAG_TITLE, 0));

  STACKADD(ret);

  mpd_response_finish(co);
  mpd_song_free(song);
  mpd_status_free(status);
  mpd_connection_free(co);

  return ret;
}

static char*
status_mem(void)
{
  char *ret;
  long total, mfree, buf, cache;
  FILE *f = fopen("/proc/meminfo", "r");

  if(!f)
    return " ";

  fscanf(f, "MemTotal: %ld kB\n"
            "MemFree:  %ld kB\n"
            "Buffers:  %ld kB\n"
            "Cached:   %ld kB\n", &total, &mfree, &buf, &cache);
  fclose(f);

  asprintf(&ret, "^s[left;#aabbaa;RAM ]^p[left;100;8;0;%ld;%ld;#888888;#771144]",
           (total - (mfree + buf + cache)), total);

  STACKADD(ret);

  return ret;
}

static char*
status_cpu(void)
{
  char *ret;
  unsigned long total, c[4] = { 0 };
  double percent;
  FILE *f = fopen("/proc/stat", "r");

  if(!f)
    return " ";

  fscanf(f, "%*s %lu %lu %lu %lu", &c[0], &c[1], &c[2], &c[3]);
  fclose(f);

  total = (c[0] - ocpu[0]) + (c[1] - ocpu[1]) + (c[2] - ocpu[2]) + (c[3] - ocpu[3]);
  percent = 100 * ((double)(total - (c[3] - ocpu[3])) / (double)total);

  ocpu[0] = c[0];
  ocpu[1] = c[1];
  ocpu[2] = c[2];
  ocpu[3] = c[3];

  asprintf(&ret, "^s[left;#aabbaa;CPU ]^g[left;180;14;%d;100;#888888;#991111;cpu]", (int)percent);
  STACKADD(ret);

  return ret;
}

int
main(int argc, char **argv)
{
  /*
   * INIT
   */
  dpy   = XOpenDisplay(NULL);
  root  = DefaultRootWindow(dpy);
  autf8 = XInternAtom(dpy, "UTF8_STRING", false);
  afunc = XInternAtom(dpy, "_WMFS_FUNCTION", false);
  acmd  = XInternAtom(dpy, "_WMFS_CMD", false);
  t     = time(NULL);

  for(;;)
  {
    status_send("default "SEP("left")"%s"SEP("left")"%s"SEP("left")"%s%s",
                status_mem(), status_cpu(), status_mpd(), status_date());
    STACKDEL();
    sleep(1);
  }

  XCloseDisplay(dpy);
}
