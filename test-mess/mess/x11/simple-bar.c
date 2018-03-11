/*
 Copyright 07/23/2016 Aaron Caffrey https://github.com/wifiextender
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
  gcc -Wall -Wextra -O2 -I/usr/include/freetype2 -lX11 -lXft -o test simple-bar.c
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include <X11/Xlib.h>
#include <X11/Xft/Xft.h>

#define WIDTH 500
#define HEIGHT 15

void close_smth(void);

XftColor brown, pink;
XftFont *xftfont;
XftDraw *xdraw;

Window win;
Display *display;
Colormap cmap;
Visual *visual;
 
int main(void) {

  atexit(close_smth);

  int screen = 0;
	XSetWindowAttributes wa;

	const char use_font[] = "xft#DejaVu Sans:size=8";
	char buf[300];

	display = XOpenDisplay(NULL);
	if (NULL == display) {
		exit(EXIT_FAILURE);
	}

	screen = DefaultScreen(display);
	cmap = DefaultColormap(display, screen);
	visual = DefaultVisual(display, screen);

	wa.override_redirect = 1;
	wa.background_pixmap = ParentRelative;
	wa.event_mask = ExposureMask|KeyPressMask;

	win = XCreateWindow(display, RootWindow(display, screen),
	    0, 0, WIDTH, HEIGHT, 0,
	    DefaultDepth(display, screen), CopyFromParent, visual,
	    CWOverrideRedirect | CWBackPixmap | CWEventMask, &wa
	);
	xdraw = XftDrawCreate(display, win, visual, cmap);

	XftColorAllocName(display, visual, cmap,  "#282a2e",  &brown);
	XftColorAllocName(display, visual, cmap,  "#b294bb",  &pink);

	xftfont = XftFontOpenXlfd(display, screen, use_font);
	if (!xftfont) {
		xftfont = XftFontOpenName(display, screen, use_font);
  }
	if (!xftfont) {
		exit(EXIT_FAILURE);
  }

	XMapWindow(display, win);
	XFlush(display);
  XftDrawRect(xdraw, &brown, 0, 0, WIDTH, HEIGHT);


	while (true) {

      if (NULL != fgets(buf, 200, stdin)) {
        XFlush(display);
        XftDrawRect(xdraw, &brown, 0, 0, WIDTH, HEIGHT);

        /* buf[len-1] = '\0'; */

        XftDrawStringUtf8(xdraw, &pink, xftfont,
          0, 1 + xftfont->ascent, (const FcChar8 *)buf, (strlen(buf) - 1));

      }

	}

	return EXIT_SUCCESS;
}

void close_smth(void) {
  fprintf(stderr, "%s\n", "hakuna matata");
	XftFontClose(display, xftfont);

	XftColorFree(display, visual, cmap, &brown);
	XftColorFree(display, visual, cmap, &pink);

	XftDrawDestroy(xdraw);

	XDestroyWindow(display, win);
	XCloseDisplay(display);
}
