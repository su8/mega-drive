#include <stdlib.h>
#include <stdio.h>

#include <xcb/xcb.h>

void
print_modifiers (uint32_t mask)
{
  const char **mod, *mods[] = {
    "Shift", "Lock", "Ctrl", "Alt",
    "Mod2", "Mod3", "Mod4", "Mod5",
    "Button1", "Button2", "Button3", "Button4", "Button5"
  };
  printf ("Modifier mask: ");
  for (mod = mods ; mask; mask >>= 1, mod++)
    if (mask & 1)
      printf(*mod);
  putchar ('\n');
}

int
main ()
{
  xcb_connection_t    *c;
  xcb_screen_t        *screen;
  xcb_window_t         win;
  xcb_generic_event_t *e;
  uint32_t             mask = 0;
  uint32_t             values[2];

  /* Open the connection to the X server */
  c = xcb_connect (NULL, NULL);

  /* Get the first screen */
  screen = xcb_setup_roots_iterator (xcb_get_setup (c)).data;

  /* Ask for our window's Id */
  win = xcb_generate_id (c);

  /* Create the window */
  mask = XCB_CW_OVERRIDE_REDIRECT|XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
  values[0] = screen->white_pixel;
  values[1] = XCB_EVENT_MASK_EXPOSURE       | XCB_EVENT_MASK_KEY_PRESS ;
  xcb_create_window (c,                             /* Connection          */
                     XCB_COPY_FROM_PARENT,                             /* depth               */
                     win,                           /* window Id           */
                     screen->root,                  /* parent window       */
                     0, 0,                          /* x, y                */
                     150, 5,                      /* width, height       */
                     0,                            /* border_width        */
                     XCB_WINDOW_CLASS_INPUT_OUTPUT, /* class               */
                     screen->root_visual,           /* visual              */
                     mask, values);                 /* masks */

  /* Map the window on the screen */
  xcb_map_window (c, win);

  xcb_flush (c);

  while ((e = xcb_wait_for_event (c))) {
    switch (e->response_type & ~0x80) {
    case XCB_EXPOSE: {
      xcb_expose_event_t *ev = (xcb_expose_event_t *)e;

      /* printf ("Window %ld exposed. Region to be redrawn at location (%d,%d), with dimension (%d,%d)\n", */
      /*         ev->window, ev->x, ev->y, ev->width, ev->height); */
      break;
    }
    default:
      /* Unknown event type, ignore it */
      printf("Unknown event: %d\n", e->response_type);
      break;
    }
    /* Free the Generic Event */
    free (e);
  }

  return 0;
}
