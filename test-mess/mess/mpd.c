#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>

#include <unistd.h>
#include <mpd/client.h>

int main(void) {
  struct mpd_connection *conn = NULL;
  struct mpd_song *song;

  if (NULL == (conn = mpd_connection_new(NULL, 0, 0))) {
    return EXIT_FAILURE;
  }
  if (!(mpd_send_command(conn, "currentsong", NULL)) ||
      0 != (mpd_connection_get_error(conn))) {
    goto error;
  }
  if (NULL == (song = mpd_recv_song(conn))) {
    goto error;
  }
  mpd_connection_free(conn);

  // TRACK ARTIST TITLE ALBUM DATE
  printf("%s\n", mpd_song_get_tag(song, MPD_TAG_TRACK, 0));
  printf("%s\n", mpd_song_get_tag(song, MPD_TAG_ARTIST, 0));
  printf("%s\n", mpd_song_get_tag(song, MPD_TAG_TITLE, 0));
  printf("%s\n", mpd_song_get_tag(song, MPD_TAG_ALBUM, 0));
  printf("%s\n", mpd_song_get_tag(song, MPD_TAG_DATE, 0));
  printf("%s\n", mpd_song_get_uri(song));
  printf("%d\n", mpd_song_get_duration(song));
     // mpd_song_get_uri(song));
  return EXIT_SUCCESS;

error:
  if (NULL != conn) {
    mpd_connection_free(conn);
    conn = NULL;
  }
  return EXIT_FAILURE;
}
