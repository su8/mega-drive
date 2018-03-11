#include <string.h>
#include <stdio.h>
#include <xcb/xcb.h>

// link -lvlc, -lX11, -lxcb

int main(void) {

    // XCB

    xcb_connection_t       *connection = xcb_connect (NULL, NULL);
    const xcb_setup_t      *setup  = xcb_get_setup (connection);
    xcb_screen_iterator_t   iter   = xcb_setup_roots_iterator (setup);
    xcb_screen_t           *screen = iter.data;

    // Create Window
    xcb_window_t xcb_window = xcb_generate_id (connection);
    xcb_create_window (connection,                    /* Connection          */
                       XCB_COPY_FROM_PARENT,          /* depth (same as root)*/
                       xcb_window,                        /* window Id           */
                       screen->root,                  /* parent window       */
                       0, 0,                          /* x, y                */
                       1, 1,                      /* width, height       */
                       1,                            /* border_width        */
                       XCB_WINDOW_CLASS_INPUT_OUTPUT, /* class               */
                       screen->root_visual,           /* visual              */
                       0, NULL );                     /* masks, not used yet */

    // Set window name
    /* const std::string wtitle("WindowName"); */
    xcb_change_property (connection,
                         XCB_PROP_MODE_REPLACE,
                         xcb_window,
                         XCB_ATOM_WM_NAME,
                         XCB_ATOM_STRING,
                         8,
                         10,
                         "10" );

    // Resize window
    static const uint32_t values[] = { 1280, 720 };
    xcb_configure_window (connection,
                          xcb_window,
                          XCB_CONFIG_WINDOW_WIDTH | XCB_CONFIG_WINDOW_HEIGHT,
                          values);

    xcb_map_window (connection, xcb_window);
    xcb_flush (connection);

    // LibVLC

    printf("%s\n", "oh hi");
    // xcb simple event loop
    xcb_generic_event_t* event;
    while((event = xcb_wait_for_event(connection)))
    {
        switch((*event).response_type & ~0x80)
        {
          case XCB_EXPOSE:
            break;
          case XCB_CLIENT_MESSAGE: {
            // window has been closed
            break;
          }
        }
    }

    // stop
    xcb_disconnect (connection);
    return 0;
}
