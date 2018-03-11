/*
 Copyright 07/20/2016 Aaron Caffrey https://github.com/wifiextender

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 MA 02110-1301, USA.

 Compile with:
  gcc -Wall -Wextra -O2 volume.c -o test -lasound
*/

#include <stdio.h>
#include <stdlib.h>

#include <alsa/asoundlib.h>

#define ALSA_ERR "Error: alsa failed"

void exit_with_err(const char *);
void get_sound(void);

int main(void) {
  get_sound();
  return EXIT_SUCCESS;
}

void
exit_with_err(const char *str1) {
  printf("%s\n", str1);
  exit(EXIT_FAILURE);
}

void
get_sound(void) {
  snd_mixer_t *handle = NULL;
  snd_mixer_elem_t *elem = NULL;
  snd_mixer_selem_id_t *s_elem = NULL;
  long int vol, max, min;

  if (0 < (snd_mixer_open(&handle, 0))) {
    exit_with_err(ALSA_ERR);
  }

  if (0 < (snd_mixer_attach(handle, "default"))) {
    goto error;
  }

  if (0 < (snd_mixer_selem_register(handle, NULL, NULL))) {
    goto error;
  }

  if (0 < (snd_mixer_load(handle))) {
    goto error;
  }

  snd_mixer_selem_id_malloc(&s_elem);
  if (NULL == s_elem) {
    goto error;
  }

  snd_mixer_selem_id_set_name(s_elem, "Master");
  if (NULL == (elem = snd_mixer_find_selem(handle, s_elem))) {
    goto error;
  }

  if (0 < (snd_mixer_selem_get_playback_volume(elem, 0, &vol))) {
    goto error;
  }
  snd_mixer_selem_get_playback_volume_range(elem, &min, &max);

  snd_mixer_selem_id_free(s_elem);
  snd_mixer_close(handle);

  printf("%s %ld%%\n", "Volume set to", (vol * 100) / max);
  return;

error:
  if (NULL != s_elem) {
    snd_mixer_selem_id_free(s_elem);
    s_elem = NULL;
  }
  if (NULL != handle) {
    snd_mixer_close(handle);
    handle = NULL;
  }
  exit_with_err(ALSA_ERR);
}
