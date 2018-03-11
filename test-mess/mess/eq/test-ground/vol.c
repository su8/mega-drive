#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <ifaddrs.h>
#include <limits.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/param.h>
#include <sys/audioio.h>
#include <sys/sched.h>
#include <sys/resource.h>
#include <sys/sensors.h>
#include <sys/socket.h>
#include <sys/sysctl.h>

int main(void) {
    /* audio_info_t ai; */
    /* audio_info_t info; */
    /* FILE *fd; */

    /* fd = fopen("/dev/audio", "r"); */
    /* if (ioctl(fileno(fd), AUDIO_GETINFO, &info) < 0) */
    /*     fprintf(stderr, "%s\n", strerror(errno)); */
    /* AUDIO_INITINFO(&ai); */

    /* printf("%d", info.play); */
    /* fclose(fd); */

    int fd = open("/dev/mixer", O_RDONLY);
    static int cls = -1;
    struct mixer_devinfo mdi;
    struct mixer_ctrl mc;
    int v = -1;

    for (mdi.index = 0; cls == -1; mdi.index++) {
        if (ioctl(fd, AUDIO_MIXER_DEVINFO, &mdi) == -1) {
printf("%s\n", "1");
            break;
        }
        if (mdi.type == AUDIO_MIXER_CLASS &&
            !strcmp(mdi.label.name, AudioCoutputs))
                cls = mdi.index;
    }
    for (mdi.index = 0; v == -1; mdi.index++) {
        if (ioctl(fd, AUDIO_MIXER_DEVINFO, &mdi) == -1) {
printf("%s\n", "2");
            return -1;
    }
        if (mdi.type == AUDIO_MIXER_VALUE && mdi.prev == AUDIO_MIXER_LAST &&
            mdi.mixer_class == cls && !strcmp(mdi.label.name, AudioNmaster)) {
            mc.dev = mdi.index;
            if (ioctl(fd, AUDIO_MIXER_READ, &mc) == -1) {
printf("%s\n", "3");
            return -1;
    }
            v = mc.un.value.num_channels == 1 ?
                mc.un.value.level[AUDIO_MIXER_LEVEL_MONO] :
                (mc.un.value.level[AUDIO_MIXER_LEVEL_LEFT] >
                 mc.un.value.level[AUDIO_MIXER_LEVEL_RIGHT] ?
                 mc.un.value.level[AUDIO_MIXER_LEVEL_LEFT] :
                 mc.un.value.level[AUDIO_MIXER_LEVEL_RIGHT]);
        } /* todo: handle mute */
    }
  /* mixer_devinfo_t dinfo; */
  /* int ndev = 0, fd = 0, i =0, j = 0, pos = 0; */


  /* char *file = "/dev/mixer"; */
	/* if ((fd = open(file, O_RDWR)) == -1) */
		/* if ((fd = open(file, O_RDONLY)) == -1) */

  /* for (ndev = 0; ; ndev++) { */
  /*   dinfo.index = ndev; */
  /*   if (0 != (ioctl(fd, AUDIO_MIXER_DEVINFO, &dinfo))) { */
  /*     break; */
  /*   } */
  /* } */

	/* for (i = 0; i < ndev; i++) { */
		/* infos[i].index = i; */
		/* if (ioctl(fd, AUDIO_MIXER_DEVINFO, &infos[i]) < 0) { */
			/* ndev--; */
			/* i--; */
			/* continue; */
		/* } */
	/* } */

  printf("%s\n", "oh hi");
  printf("%d\n", (v * 100) / 255);

  close(fd);
  return 0;
}
