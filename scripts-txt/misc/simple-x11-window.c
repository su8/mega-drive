/*gcc test.c -lX11 -o test*/
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <string.h>

int main(void)
{
    Display *mydisplay;
    Window mywindow;
    GC mygc;
    XEvent myevent;
    KeySym mykey;
    unsigned long myforeground, mybackground;
    unsigned int myscreen, width, height;
    int done;
    char *hello = "Hello World";


    mydisplay = XOpenDisplay(0);
    myscreen = DefaultScreen(mydisplay);
    mybackground = BlackPixel(mydisplay,myscreen);
    myforeground = WhitePixel(mydisplay,myscreen);


	width = (XDisplayWidth(mydisplay, myscreen) / 2) - 150;
	height = XDisplayHeight(mydisplay, myscreen) / 2;

    mywindow = XCreateSimpleWindow(mydisplay,DefaultRootWindow(mydisplay),


    width,height,300,50,1,myforeground,mybackground);


    mygc = XCreateGC(mydisplay,mywindow,0,0);
    XSetBackground(mydisplay,mygc,mybackground);
    XSetForeground(mydisplay,mygc,myforeground);
    XSelectInput(mydisplay,mywindow,ButtonPressMask|ExposureMask);
    XMapRaised(mydisplay,mywindow);


    while (1) {
        XNextEvent(mydisplay,&myevent);
        switch(myevent.type) {
        case Expose:
            if (myevent.xexpose.count==0)
                XDrawString(myevent.xexpose.display,myevent.xexpose.window,
                        mygc,10,30,hello,strlen(hello));
            break;

        case ButtonPress:
            XFreeGC(mydisplay,mygc);
            XCloseDisplay(mydisplay);
            return 0;
        }
    }


    return 0;
}
