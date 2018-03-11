#!/usr/bin/python
import os
import subprocess
import shlex
from gi.repository import Gtk, Gdk

dd_dir = '/home/frost/Documents/dd-my-python/dd3-python/'
desktop_dir = "/home/frost/Desktop/"
os.chdir(dd_dir)

class process_input:
    @staticmethod
    def search_changed(searchentry):
        if len(searchentry.get_text()) == 6:
            if os.path.isfile(desktop_dir + searchentry.get_text() + ".txt") == False:
                process = subprocess.Popen(shlex.split('python2 ' + dd_dir + 'dd.py ' + searchentry.get_text()))
                process.communicate()
            else:
                pass

            class PopUpPanedWindow:
                def insert_text(self, buffer):
                    txt = open(desktop_dir + searchentry.get_text() + ".txt")
                    iter = buffer.get_iter_at_offset(0)
                    buffer.insert(iter, txt.read())
                    txt.close()

                def create_text(self):
                    view = Gtk.TextView()
                    buffer = view.get_buffer()
                    scrolled_window = Gtk.ScrolledWindow()
                    #scrolled_window.set_policy(Gtk.POLICY_AUTOMATIC, Gtk.POLICY_AUTOMATIC)
                    scrolled_window.add(view)
                    self.insert_text(buffer)
                    scrolled_window.show_all()
                    return scrolled_window

                def __init__(self):
                    window = Gtk.Window()
                    window.set_title("Keys")
                    window.connect("destroy", lambda w: Gtk.main_quit())
                    window.override_background_color(Gtk.StateFlags.NORMAL, Gdk.RGBA(0, 0, 0, 1))
                    window.set_border_width(10)
                    window.set_size_request(350, 450)

                    vpaned = Gtk.VPaned()
                    window.add(vpaned)
                    vpaned.show()

                    text = self.create_text()
                    vpaned.add2(text)
                    text.show()
                    window.show()
            PopUpPanedWindow()


class MainWindow:

    def __init__(self):

        window = Gtk.Window()
        window.override_background_color(Gtk.StateFlags.NORMAL, Gdk.RGBA(0, 0, 0, 1))
        window.connect("destroy", lambda q: Gtk.main_quit())

        searchentry = Gtk.SearchEntry()
        searchentry.set_max_length(6)
        searchentry.connect("search-changed", process_input.search_changed)

        window.add(searchentry)

        window.show_all()

        Gtk.main()

if __name__ == '__main__':
    MainWindow()