dnl Copyright 07/06/2015, 08/03/2016
dnl Aaron Caffrey https://github.com/wifiextender

dnl This program is free software; you can redistribute it and/or modify
dnl it under the terms of the GNU General Public License as published by
dnl the Free Software Foundation; either version 2 of the License, or
dnl (at your option) any later version.

dnl This program is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
dnl GNU General Public License for more details.

dnl You should have received a copy of the GNU General Public License
dnl along with this program; if not, write to the Free Software
dnl Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
dnl MA 02110-1301, USA.


dnl TEST_ALSA() function in configure.ac
dnl
dnl Check for the presence of ALSA headers and
dnl substitute the linker flags -lasound to the
dnl the variable 'ALSA_LIBS' if they are available.
AC_DEFUN([TEST_ALSA],[
  ALSA_LIBS=""

  AC_ARG_WITH([alsa],
    AS_HELP_STRING([--with-alsa],
      [ALSA linker flag for sound support]),
    [],
    [with_alsa=no]
  )

  AS_IF([test "x$with_alsa" = "xyes"], [
    AC_CHECK_HEADERS([alsa/asoundlib.h], [
      ALSA_LIBS="-lasound"
      ],[
        ERR_MUST_INSTALL([alsa-utils and alsa-lib])
      ])

    m4_foreach([LiB], [
        snd_mixer_open                              ,
        snd_mixer_attach                            ,
        snd_mixer_selem_register                    ,
        snd_mixer_load                              ,
        snd_mixer_selem_id_malloc                   ,
        snd_mixer_selem_id_set_name                 ,
        snd_mixer_find_selem                        ,
        snd_mixer_selem_get_playback_volume         ,
        snd_mixer_selem_get_playback_volume_range   ,
        snd_mixer_selem_id_free                     ,
        snd_mixer_close
      ],[
        AC_CHECK_LIB(asound,LiB,[],[
          ERR([Missing core ALSA function.])
        ])
    ])
  ])

  AC_SUBST(ALSA_LIBS)

  AS_IF([test "x$with_alsa" = "xyes"], [
    AC_LINK_IFELSE([
      AC_LANG_SOURCE([[
        #include <alsa/asoundlib.h>
        int main(void) {
          snd_mixer_t *handle = NULL;
          snd_mixer_elem_t *elem = NULL;
          snd_mixer_selem_id_t *s_elem = NULL;
          return 0;
        }
      ]])
    ],[],[
      LINK_FAILED([alsa])
      ]
    )
  ])

])
