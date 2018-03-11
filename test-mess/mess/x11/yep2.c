/* Simple XCB application drawing a box in a window */
/* to compile it use :
   gcc -Wall x.c -lxcb
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <xcb/xcb.h>

#include <unistd.h>

#define WIDTH 300
#define HEIGHT 100



static xcb_gc_t gc_font_get (xcb_connection_t *c,
                             xcb_screen_t     *screen,
                             xcb_window_t      window,
                             const char       *font_name);

static void text_draw (xcb_connection_t *c,
                       xcb_screen_t     *screen,
                       xcb_window_t      window,
                       int16_t           x1,
                       int16_t           y1,
                       const char       *label);

static void
text_draw (xcb_connection_t *c,
           xcb_screen_t     *screen,
           xcb_window_t      window,
           int16_t           x1,
           int16_t           y1,
           const char       *label)
{
  xcb_void_cookie_t    cookie_gc;
  xcb_void_cookie_t    cookie_text;
  xcb_generic_error_t *error;
  xcb_gcontext_t       gc;
  uint8_t              length;
  printf("%s\n", label);

  length = strlen (label);

  gc = gc_font_get(c, screen, window, "7x13");

  cookie_text = xcb_image_text_8_checked (c, length, window, gc,
                                          x1,
                                          y1, label);
  error = xcb_request_check (c, cookie_text);
  if (error) {
    fprintf (stderr, "ERROR: can't paste text : %d\n", error->error_code);
    xcb_disconnect (c);
    exit (EXIT_FAILURE);
  }

  cookie_gc = xcb_free_gc (c, gc);
  error = xcb_request_check (c, cookie_gc);
  if (error) {
    fprintf (stderr, "ERROR: can't free gc : %d\n", error->error_code);
    xcb_disconnect (c);
    exit (EXIT_FAILURE);
  }
}

static xcb_gc_t
gc_font_get (xcb_connection_t *c,
             xcb_screen_t     *screen,
             xcb_window_t      window,
             const char       *font_name)
{
  uint32_t             value_list[3];
  xcb_void_cookie_t    cookie_font;
  xcb_void_cookie_t    cookie_gc;
  xcb_generic_error_t *error;
  xcb_font_t           font;
  xcb_gcontext_t       gc;
  uint32_t             mask;

  font = xcb_generate_id (c);
  cookie_font = xcb_open_font_checked (c, font,
                                       strlen (font_name),
                                       font_name);

  error = xcb_request_check (c, cookie_font);
  if (error) {
    fprintf (stderr, "ERROR: can't open font : %d\n", error->error_code);
    xcb_disconnect (c);
    return -1;
  }

  gc = xcb_generate_id (c);
  mask = XCB_GC_FOREGROUND | XCB_GC_BACKGROUND | XCB_GC_FONT;
  value_list[1] = screen->black_pixel;
  value_list[0] = screen->white_pixel;
  value_list[2] = font;
  cookie_gc = xcb_create_gc_checked (c, gc, window, mask, value_list);
  error = xcb_request_check (c, cookie_gc);
  if (error) {
    fprintf (stderr, "ERROR: can't create gc : %d\n", error->error_code);
    xcb_disconnect (c);
    exit (-1);
  }

  cookie_font = xcb_close_font_checked (c, font);
  error = xcb_request_check (c, cookie_font);
  if (error) {
    fprintf (stderr, "ERROR: can't close font : %d\n", error->error_code);
    xcb_disconnect (c);
    exit (-1);
  }

  return (xcb_gc_t)gc;
}


int main(void)
{
    xcb_connection_t    *c;
    xcb_screen_t        *s;
    /* xcb_window_t         w; */
  /* xcb_generic_event_t  *e; */
  xcb_generic_error_t  *error;
  xcb_void_cookie_t     cookie_window;
  xcb_void_cookie_t     cookie_map;
    /* const xcb_setup_t *setup; */
    xcb_drawable_t w;
    xcb_gcontext_t       g;
    uint32_t             mask = 0;
    /* uint32_t             values[2]; */
    char buf[300];
    /* xcb_rectangle_t      r = { 20, 20, 60, 60 }; */

    /* open connection with the server */
    c = xcb_connect(NULL,NULL);
    if (xcb_connection_has_error(c)) {
        printf("Cannot open display\n");
        exit(1);
    }
    /* setup = xcb_get_setup(c); */

    /* get the first screen */
    s = xcb_setup_roots_iterator( xcb_get_setup(c) ).data;

    /* create black graphics context */
    g = xcb_generate_id(c);
    w = s->root;
mask = XCB_GC_FOREGROUND | XCB_GC_LINE_WIDTH | XCB_GC_SUBWINDOW_MODE;
uint32_t values[] = {
    s->black_pixel,
    4,
    XCB_SUBWINDOW_MODE_INCLUDE_INFERIORS
};
    /* values[0] = s->black_pixel; */
    /* values[1] = 0; */

    xcb_create_gc(c, g, w, mask, values);

        /* Create a black graphic context for drawing in the foreground */
        /* xcb_drawable_t  window   = screen->root; */
        /* xcb_gcontext_t  black    = xcb_generate_id (connection); */
        /* uint32_t        mask     = XCB_GC_FOREGROUND; */
        /* uint32_t        value[]  = { screen->black_pixel }; */

        /* xcb_create_gc (connection, black, window, mask, value); */


    /* create window */
    /* w = xcb_generate_id(c); */
    /* XCB_CW_BACK_PIXEL */
    /* mask = XCB_CW_OVERRIDE_REDIRECT | XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK; */
    /* values[0] = s->white_pixel; */
    /* values[1] = XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_KEY_PRESS; */
    /* cookie_window = xcb_create_window_checked(c, // conn */
    /*     XCB_COPY_FROM_PARENT, // depth s->root_depth */
    /*     w, // win */
    /*     s->root, // parent window */
    /*     0, 0, // x y */
    /*     150, 20, // width height */
    /*     0, // border_width */
    /*     XCB_WINDOW_CLASS_INPUT_OUTPUT, */
    /*     s->root_visual, */
    /*     mask, values); */

    /* /1* map (show) the window *1/ */
    /* cookie_map = xcb_map_window_checked(c, w); */
    /* error = xcb_request_check(c, cookie_window); */
    /* if (error) { */
    /*   printf("%s", "error 1"); */
    /*   xcb_disconnect(c); */
    /*   return -1; */
    /* } */
    /* error = xcb_request_check(c, cookie_map); */
    /* if (error) { */
    /*   printf("%s", "error 2"); */
    /*   xcb_disconnect(c); */
    /*   return -1; */
    /* } */

    xcb_map_window(c, w);
    xcb_flush(c);
/* xcb_rectangle_t rectangles[] = { */
/*   {50, 50, 600, 400}, */
/* }; */
    /* event loop */
    while (1) {
      if (NULL != (fgets(buf, 299, stdin))) {
        /* printf("%s\n", buf); */
        buf[strlen(buf)-1]='\0';
        /* xcb_poly_rectangle (c, w, g, 1, rectangles); */
        text_draw(c,s,w,1,30,buf);
        /* xcb_configure_window(c, win, mask, vals); */
        xcb_flush(c);
      }

      sleep(4);
      break;
    }
    /* close connection to server */
    xcb_unmap_window(c,w);
    xcb_destroy_window(c,w);
    xcb_flush(c);

    xcb_disconnect(c);

    return EXIT_SUCCESS;
}
