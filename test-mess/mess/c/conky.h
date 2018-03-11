#ifndef _conky_h_
#define _conky_h_

//#include <mcheck.h>
#include "config.h"
#include <sys/utsname.h>
#include <stdio.h>
#include <stdlib.h>

#if defined(HAVE_CAIRO_H) && defined(HAVE_CAIRO_XLIB_H) && defined(WANT_CAIRO)
#define CAIRO
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <cairo.h>
#include <cairo-xlib.h>
#endif

#define TOP_CPU 1
#define TOP_NAME 2
#define TOP_PID 3
#define TOP_MEM 4

#define TEXT_BUFFER_SIZE (1024*4)

#ifdef METAR
#include <metar.h>
#endif

#include <sys/socket.h>

#define ERR(s, varargs...) \
fprintf(stderr, "Conky: " s "\n", ##varargs)

/* critical error */
#define CRIT_ERR(s, varargs...) \
{ fprintf(stderr, "Conky: " s "\n", ##varargs);  exit(EXIT_FAILURE); }

struct net_stat {
	const char *dev;
	int up;
	long long last_read_recv, last_read_trans;
	long long recv, trans;
	double recv_speed, trans_speed;
	struct sockaddr addr;
	int linkstatus;
	double net_rec[15], net_trans[15];
};

struct fs_stat {
	int fd;
	char *path;
	long long size;
	long long avail;
};

struct cpu_stat {
	unsigned int user, nice, system, idle, iowait, irq, softirq;
	int cpu_avg_samples;
};

#ifdef MPD
struct mpd_s {
	char *title;
	char *artist;
	char *album;
	char *status;
	int volume;
	unsigned int port;
	char *host;
	float progress;
	int bitrate;
};
#endif

enum {
	INFO_CPU = 0,
	INFO_MAIL = 1,
	INFO_MEM = 2,
	INFO_NET = 3,
#ifdef SETI
	INFO_SETI = 4,
#endif
	INFO_PROCS = 5,
	INFO_RUN_PROCS = 6,
	INFO_UPTIME = 7,
	INFO_BUFFERS = 8,
	INFO_FS = 9,
	INFO_I2C = 10,
	INFO_MIXER = 11,
	INFO_LOADAVG = 12,
	INFO_UNAME = 13,
	INFO_FREQ = 14,
#ifdef MPD
	INFO_MPD = 15,
#endif
	INFO_TOP = 16,
#ifdef METAR
	INFO_METAR     = 17,
#endif
#ifdef MLDONKEY
	INFO_MLDONKEY = 18,
#endif
        INFO_WIFI = 19,
};


#ifdef MPD
#include "libmpdclient.h"
#endif

struct information {
	unsigned int mask;

	struct utsname uname_s;

	char freq[10];

	double uptime;

	/* memory information in kilobytes */
	unsigned int mem, memmax, swap, swapmax;
	unsigned int bufmem, buffers, cached;

	unsigned int procs;
	unsigned int run_procs;

	float cpu_usage;
	struct cpu_stat cpu_summed;
	unsigned int cpu_count;
	unsigned int cpu_avg_samples;

	unsigned int net_avg_samples;

	float loadavg[3];

	int new_mail_count, mail_count;
#ifdef SETI
	float seti_prog;
	float seti_credit;
#endif
#ifdef MPD
	struct mpd_s mpd;
	mpd_Connection *conn;
#endif
	struct process *tops[10];
	unsigned long looped;
};

/* in x11.c */

#include <X11/Xlib.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>

#ifdef XFT
#include <X11/Xft/Xft.h>
#endif

#if defined(HAVE_XDBE) && defined(DOUBLE_BUFFER)
#define XDBE
#include <X11/extensions/Xdbe.h>
#endif

#define ATOM(a) XInternAtom(display, #a, False)

struct conky_window {
	Window window;
	Drawable drawable;
	GC gc;
#ifdef XDBE
	XdbeBackBuffer back_buffer;
#endif
#ifdef XFT
	XftDraw *xftdraw;
#endif

	int width;
	int height;
#ifdef OWN_WINDOW
	int x;
	int y;
#endif
};

#ifdef XDBE
extern int use_xdbe;
#endif

int out_to_console;

int top_sort_cpu;

int use_spacer;

char *tmpstring1;
char *tmpstring2;

#ifdef XFT
extern int use_xft;
#endif

extern Display *display;
extern int display_width;
extern int display_height;
extern int screen;

extern int workarea[4];

extern struct conky_window window;

void init_X11();
void init_window(int use_own_window, int width, int height);
void create_gc();
void set_transparent_background(Window win);
long get_x11_color(const char *);

/* in common.c */

/* struct that has all info */
struct information info;

void update_uname();
double get_time(void);
FILE *open_file(const char *file, int *reported);
void variable_substitute(const char *s, char *dest, unsigned int n);
void format_seconds(char *buf, unsigned int n, long t);
void format_seconds_short(char *buf, unsigned int n, long t);
struct net_stat *get_net_stat(const char *dev);

void update_stuff();

#define SET_NEED(a) need_mask |= 1 << (a)
extern unsigned int need_mask;

extern double current_update_time, last_update_time;

extern int no_buffers;

/* system dependant (in linux.c) */

void prepare_update(void);
void update_uptime(void);
void update_meminfo(void);
void update_net_stats(void);
void update_wifi_stats(void);
void update_cpu_usage(void);
void update_total_processes(void);
void update_running_processes(void);
char *get_freq();
void update_load_average();
int open_i2c_sensor(const char *dev, const char *type, int n, int *div,
		    char *devtype);
double get_i2c_info(int *fd, int arg, char *devtype, char *type);

char *get_adt746x_cpu(void);
char *get_adt746x_fan(void);

int open_acpi_temperature(const char *name);
double get_acpi_temperature(int fd);
char *get_acpi_ac_adapter(void);
char *get_acpi_fan(void);
void get_battery_stuff(char *buf, unsigned int n, const char *bat);

struct process {
	struct process *next;
	struct process *previous;

	pid_t pid;
	char *name;
	float amount;
	unsigned int user_time;
	unsigned int total;
	unsigned int kernel_time;
	unsigned int previous_user_time;
	unsigned int previous_kernel_time;
	unsigned int vsize;
	unsigned int rss;
	unsigned int time_stamp;
	unsigned int counted;
	unsigned int changed;
	float totalmem;
};

#ifdef METAR
double last_metar_update;
extern char *metar_station;
extern char *metar_server;
extern char *metar_path;
extern char ftp_ok;
extern char metar_worked;
extern Decoded_METAR data;

extern int calculateRelativeHumidity(int, int);
extern int calculateWindChill(int, int);
extern int knTokph(int);
extern const char *calculateWindDirectionString(int);
extern const char *calculateShortWindDirectionString(int);

void update_metar();
#endif



void update_top();


/* fs-stuff is possibly system dependant (in fs.c) */

void update_fs_stats(void);
struct fs_stat *prepare_fs_stat(const char *path);
void clear_fs_stats(void);

/* in mixer.c */

int mixer_init(const char *);
int mixer_get_avg(int);
int mixer_get_left(int);
int mixer_get_right(int);

/* in mail.c */

extern char *current_mail_spool;

void update_mail_count();

/* in seti.c */

#ifdef SETI
extern char *seti_dir;

void update_seti();
#endif

/* in mpd.c */

#ifdef MPD
void update_mpd();
#endif

#ifdef MLDONKEY
/* in mldonkey.c */
typedef long long int64;
/* The info necessary to connect to mldonkey. login and password can be NULL. */
typedef struct mldonkey_config {
	char *mldonkey_hostname;
	int mldonkey_port;
	char *mldonkey_login;
	char *mldonkey_password;
} mldonkey_config;

/* The MLDonkey status returned */
typedef struct mldonkey_info {
	int64  upload_counter;
	int64 download_counter;
	int nshared_files;
	int64 shared_counter;
	int  tcp_upload_rate;
	int  tcp_download_rate;
	int  udp_upload_rate;
	int  udp_download_rate;
	int  ndownloaded_files;
	int ndownloading_files;
	int nconnected_networks;
	int connected_networks[1];
} mldonkey_info;
	
extern mldonkey_info mlinfo;
extern mldonkey_config mlconfig;
	
int get_mldonkey_status(mldonkey_config *config, mldonkey_info *info);
#endif



/* in linux.c */

extern int show_nice_processes;

/* in cairo.c */

extern int do_it(void);

#endif
