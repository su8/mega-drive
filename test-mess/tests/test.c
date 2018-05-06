#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/extensions/XTest.h>
#include <stdio.h>

int X_error_handler(Display *d, XErrorEvent *e)
{
  (void)d;
  (void)e;
        return 0;
}

int main (void) {
    /* Window root_window; //<--one */
    /* int root_x, root_y; //<--two */
    /* int new = 0; */
    /* unsigned int mask; //<--three */
    /* int x, y; */
XSetErrorHandler(X_error_handler);
    Display *dpy = XOpenDisplay(NULL);

/* XWindowAttributes xw; */
/* Window root_window; */
/* Window child; */
    if (NULL == dpy) {
      return -1;
    }

/*root_window = DefaultRootWindow(dpy); */
/*/1* XTranslateCoordinates( dpy, root_window, root_window, 0, 0, &x, &y, &child ); *1/ */
/*XGetWindowAttributes(dpy, root_window, &xw); */
/*    XQueryPointer(dpy, root_window, &root_window, &root_window, &root_x, &root_y, &root_x, &root_y, &mask); //<--four */
/*XSelectInput(dpy, root_window, KeyReleaseMask); */
/*/1* printf("%d %d\n",xw.height, xw.width); *1/ */
/*XWarpPointer(dpy, None, root_window, 0, 0, 0, 0, (root_x + 100) % xw.width - 2, (root_y + 100) % xw.height - 2); */
/*XFlush(dpy); */
/*    /1* */
    /* Bool XQueryPointer(display, w, root_return, child_return, root_x_return, root_y_return,*/
    /*                      win_x_return, win_y_return, mask_return)*/
    /*       Display *display;*/
    /*       Window w;*/
    /*       Window *root_return, *child_return;*/
    /*       int *root_x_return, *root_y_return;*/
    /*       int *win_x_return, *win_y_return;*/
    /*       unsigned int *mask_return;*/
    /* */


    /* printf("Mouse coordinates (X: %d, Y: %d)\n", root_x, root_y); */
/* XTestFakeKeyEvent(display, XKeysymToKeycode(display, XK_Super_L), True, 0); */
    /* while(1) { */

XTestFakeKeyEvent(dpy, XKeysymToKeycode(dpy, XK_Super_L), True, 0);
XTestFakeKeyEvent(dpy, XKeysymToKeycode(dpy, XK_Z), True, 0);
XTestFakeKeyEvent(dpy, XKeysymToKeycode(dpy, XK_Z), False, 0);
XTestFakeKeyEvent(dpy, XKeysymToKeycode(dpy, XK_Super_L), False, 0);
    /* } */
/* XTestFakeKeyEvent(display, XKeysymToKeycode(display, XK_Super_L), False, 0); */
    XCloseDisplay(dpy);
    return 0;
}

/*
XK(	XK_Escape,		Key::Escape	)
XK(	XK_Linefeed,		Key::Enter	)
XK(	XK_Return,		Key::Enter	)
XK(	XK_Tab,			Key::Tab	)
XK(	XK_BackSpace,		Key::Backspace	)
XK(	XK_Delete,		Key::Delete	)
XK(	XK_Left,		Key::Left	)
XK(	XK_Up,			Key::Up		)
XK(	XK_Right,		Key::Right	)
XK(	XK_Down,		Key::Down	)
XK(	XK_Page_Up,		Key::PageUp	)
XK(	XK_Page_Down,		Key::PageDown	)
XK(	XK_Home,		Key::Home	)
XK(	XK_End,			Key::End	)
XK(	XK_Insert,		Key::Insert	)
XK(	XK_Prior,		Key::PageUp	)
XK(	XK_Next,		Key::PageDown	)
XK(	XK_Menu,		Key::Menu	)
XK(	XK_Shift_L,		Key::Shift	)
XK(	XK_Shift_R,		Key::Shift	)
XK(	XK_Control_L,		Key::Ctrl	)
XK(	XK_Control_R,		Key::Ctrl	)
XK(	XK_Meta_L,		Key::Alt	)
XK(	XK_Meta_R,		Key::Alt	)
XK(	XK_Alt_L,		Key::Alt	)
XK(	XK_Alt_R,		Key::Alt	)
XK(	XK_Super_L,		Key::Banner	)
XK(	XK_Super_R,		Key::Banner	)
XK(	XK_Hyper_L,		Key::Banner	)
XK(	XK_Hyper_R,		Key::Banner	)
XK(	XK_Begin,		Key::Home	)
XK(	XK_Print,		Key::Print	)
XK(	XK_Undo,		Key::Undo	)
XK(	XK_Redo,		Key::Redo	)
XK(	XK_Find,		Key::Find	)
XK(	XK_Cancel,		Key::Escape	)
XK(	XK_Help,		Key::Help	)
XK(	XK_Break,		Key::Break	)
XK(	XK_F1,			Key::F1		)
XK(	XK_F2,			Key::F2		)
XK(	XK_F3,			Key::F3		)
XK(	XK_F4,			Key::F4		)
XK(	XK_F5,			Key::F5		)
XK(	XK_F6,			Key::F6		)
XK(	XK_F7,			Key::F7		)
XK(	XK_F8,			Key::F8		)
XK(	XK_F9,			Key::F9		)
XK(	XK_F10,			Key::F10	)
XK(	XK_F11,			Key::F11	)
XK(	XK_F12,			Key::F12	)
XK(	XK_F13,			Key::F13	)
XK(	XK_F14,			Key::F14	)
XK(	XK_F15,			Key::F15	)
XK(	XK_F16,			Key::F16	)
XK(	XK_F17,			Key::F17	)
XK(	XK_F18,			Key::F18	)
XK(	XK_F19,			Key::F19	)
XK(	XK_F20,			Key::F20	)
XK(	XK_F21,			Key::F21	)
XK(	XK_F22,			Key::F22	)
XK(	XK_F23,			Key::F23	)
XK(	XK_F24,			Key::F24	)
XK(	XK_Num_Lock,		Key::NumLock	)
XK(	XK_Caps_Lock,		Key::CapsLock	)
XK(	XK_Shift_Lock,		Key::CapsLock	)
XK(	XK_Scroll_Lock,		Key::ScrollLock	)
XK(	XK_Pause,		Key::Pause	)
XK(	XK_Sys_Req,		Key::SysReq	)
XK(	XK_KP_Space,		Key::Space	)
XK(	XK_KP_Tab,		Key::Tab	)
XK(	XK_ISO_Left_Tab,	Key::Tab	)
XK(	XK_KP_Enter,		Key::Enter	)
XK(	XK_KP_F1,		Key::F1		)
XK(	XK_KP_F2,		Key::F2		)
XK(	XK_KP_F3,		Key::F3		)
XK(	XK_KP_F4,		Key::F4		)
XK(	XK_KP_Home,		Key::Home	)
XK(	XK_KP_Left,		Key::Left	)
XK(	XK_KP_Up,		Key::Up		)
XK(	XK_KP_Right,		Key::Right	)
XK(	XK_KP_Down,		Key::Down	)
XK(	XK_KP_Prior,		Key::PageUp	)
XK(	XK_KP_Page_Up,		Key::PageUp	)
XK(	XK_KP_Next,		Key::PageDown	)
XK(	XK_KP_Page_Down,	Key::PageDown	)
XK(	XK_KP_End,		Key::End	)
XK(	XK_KP_Begin,		Key::Center	)
XK(	XK_KP_Insert,		Key::Insert	)
XK(	XK_KP_Delete,		Key::Delete	)
XK(	XK_KP_Equal,		'='		)
XK(	XK_KP_Multiply,		'*'		)
XK(	XK_KP_Add,		'+'		)
XK(	XK_KP_Separator,	','		)
XK(	XK_KP_Subtract,		'-'		)
XK(	XK_KP_Decimal,		'.'		)
XK(	XK_KP_Divide,		'/'		)
XK(	XK_KP_0,		'0'		)
XK(	XK_KP_1,		'1'		)
XK(	XK_KP_2,		'2'		)
XK(	XK_KP_3,		'3'		)
XK(	XK_KP_4,		'4'		)
XK(	XK_KP_5,		'5'		)
XK(	XK_KP_6,		'6'		)
XK(	XK_KP_7,		'7'		)
XK(	XK_KP_8,		'8'		)
XK(	XK_KP_9,		'9'		)

#undef XK
#define XF(xkey,ekey)	xkey-XF86XK_Offset, (uint16_t)ekey,

XF(	XF86XK_AudioLowerVolume,Key::VolumeDown	)
XF(	XF86XK_AudioMute,	Key::Mute	)
XF(	XF86XK_AudioPlay,	Key::Play	)
XF(	XF86XK_AudioRaiseVolume,Key::VolumeUp	)
XF(	XF86XK_AudioStop,	Key::Stop	)
XF(	XF86XK_Back,		Key::Back	)
XF(	XF86XK_Calculater,	Key::Calculator	)
XF(	XF86XK_Close,		Key::Close	)
XF(	XF86XK_Copy,		Key::Copy	)
XF(	XF86XK_Cut,		Key::Cut	)
XF(	XF86XK_Documents,	Key::Documents	)
XF(	XF86XK_Eject,		Key::Eject	)
XF(	XF86XK_Explorer,	Key::Explorer	)
XF(	XF86XK_Favorites,	Key::Favorites	)
XF(	XF86XK_Forward,		Key::Forward	)
XF(	XF86XK_Hibernate,	Key::Hibernate	)
XF(	XF86XK_History,		Key::History	)
XF(	XF86XK_HomePage,	Key::WWW	)
XF(	XF86XK_LogOff,		Key::LogOff	)
XF(	XF86XK_Mail,		Key::Mail	)
XF(	XF86XK_MyComputer,	Key::Documents	)
XF(	XF86XK_New,		Key::New	)
XF(	XF86XK_Open,		Key::Open	)
XF(	XF86XK_Option,		Key::Options	)
XF(	XF86XK_Paste,		Key::Paste	)
XF(	XF86XK_PowerDown,	Key::PowerDown	)
XF(	XF86XK_PowerOff,	Key::PowerDown	)
XF(	XF86XK_Refresh,		Key::Refresh	)
XF(	XF86XK_Reload,		Key::Refresh	)
XF(	XF86XK_Save,		Key::Save	)
XF(	XF86XK_ScreenSaver,	Key::ScreenSaver)
XF(	XF86XK_ScrollDown,	Key::PageDown	)
XF(	XF86XK_ScrollUp,	Key::PageUp	)
XF(	XF86XK_Search,		Key::Find	)
XF(	XF86XK_Sleep,		Key::Hibernate	)
XF(	XF86XK_Spell,		Key::Spell	)
XF(	XF86XK_Start,		Key::Banner	)
XF(	XF86XK_Stop,		Key::Stop	)
XF(	XF86XK_TopMenu,		Key::Menu	)
XF(	XF86XK_WWW,		Key::WWW	)
XF(	XF86XK_WheelButton,	Key::WheelButton)
XF(	XF86XK_ZoomIn,		Key::ZoomIn	)
XF(	XF86XK_ZoomOut,		Key::ZoomOut	)
 * */
