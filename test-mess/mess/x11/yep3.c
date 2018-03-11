 /* gcc -O2 -Wall `pkg-config --cflags --libs xcb` -o xcb_test_font
> xcb_test_font.c */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>

 #include <xcb/xcb.h>
 /* #include <xcb/xcbint.h> */

 int
 get_depth(XCBConnection *c,
 XCBSCREEN *root)
 {
 XCBDRAWABLE drawable = { root->root };
 XCBGetGeometryRep *geom;
 geom = XCBGetGeometryReply(c, XCBGetGeometry(c, drawable), 0);
 int depth;

 if(!geom)
 {
 perror("GetGeometry(root) failed");
 exit (0);
 }

 depth = geom->depth;
 fprintf(stderr, "Root 0x%lx: %dx%dx%d\n",
 root->root.xid, geom->width, geom->height, geom->depth);
 free(geom);

 return depth;
 }

 int
 main (int argc, char *argv[])
 {
 XCBConnection *c;
 XCBSCREEN *screen;
 XCBDRAWABLE win;
 CARD32 mask = 0;
 CARD32 values[2];

 XCBGCONTEXT bgcolor, fgcolor;
 XCBRECTANGLE rect = { 0, 0, 300, 300};
 CARD32 valgc[2];
 XCBDRAWABLE p;

 XCBGCONTEXT gcfont;
 CARD32 valfont[1];
 XCBFONTABLE fontable;
 XCBQueryFontRep *fontrep;
 char *fontname;
 char *str = "toto";

 /* Open the connexion to the X server */
 c = XCBConnectBasic ();

 /* Get the first screen */
 screen = XCBConnSetupSuccessRepRootsIter (c->setup).data;

 win.window = screen->root;

 fgcolor = XCBGCONTEXTNew(c);
 mask = GCForeground | GCGraphicsExposures;
 valgc[0] = screen->black_pixel;
 valgc[1] = 0; /* no graphics exposures */
 XCBCreateGC(c, fgcolor, win, mask, valgc);

 bgcolor = XCBGCONTEXTNew(c);
 mask = GCForeground | GCGraphicsExposures;
 valgc[0] = screen->white_pixel;
 valgc[1] = 0; /* no graphics exposures */
 XCBCreateGC(c, bgcolor, win, mask, valgc);

 p.pixmap = XCBPIXMAPNew (c);
 XCBCreatePixmap(c, get_depth (c, screen), p.pixmap, win, 300, 300);
 XCBPolyFillRectangle(c, p, bgcolor, 1, &rect);

 /* Ask for our window's Id */
 win.window = XCBWINDOWNew(c);

 /* Create the window */
 mask = XCBCWBackPixel | XCBCWEventMask;
 values[0] = screen->white_pixel;
 values[1] = ExposureMask | ButtonPressMask | ButtonReleaseMask |
 PointerMotionMask | ButtonMotionMask | EnterWindowMask |
 LeaveWindowMask | KeyPressMask | KeyReleaseMask;
 XCBCreateWindow (c, /* Connection */
 get_depth (c, screen), /* depth */
 win.window, /* window Id */
 screen->root, /* parent window */
 0, 0, /* x, y */
 300, 300, /* width, height */
 10, /* border_width */
 InputOutput, /* class */
 screen->root_visual, /* visual */
 mask, values); /* masks */

 /* Map the window on the screen */
 XCBMapWindow (c, win.window);

 /* The font stuff */

 fontable.font = XCBFONTNew (c);
 fontname = "*-helvetica-*-12-*";
 XCBOpenFont(c, fontable.font, strlen(fontname), fontname);
 fontrep = XCBQueryFontReply (c, XCBQueryFont (c, fontable), 0);

 mask = GCForeground | GCFont;
 valfont[0] = screen->black_pixel;
 valfont[1] = fontable.font.xid;
 gcfont = XCBGCONTEXTNew (c);
 XCBCreateGC (c, gcfont, p, mask, valfont);

 XCBPolyText8(c, p, gcfont, 10, 10, strlen(str), str);

 XCBCopyArea(c, p, win, fgcolor,
 0, 0, 0, 0, 300, 300);

 XCBSync (c, 0);

 free (fontrep);

 while (1) {}

 return 1;
 }
