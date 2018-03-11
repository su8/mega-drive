#!/usr/bin/env python2
import os
import shlex
import thread
import getpass
import subprocess
from gi.repository import Gtk, Gdk, GLib

class no_device:
    def __init__(self):
        no_device_dialog = Gtk.MessageDialog(None, 0, Gtk.MessageType.WARNING, Gtk.ButtonsType.OK, 
        "Before starting the program,\nplease plug in some device.")
        no_device_dialog.run()
        no_device_dialog.destroy()

class usb2format:

    def progressbar_pulse(self):
        self.progressbar.pulse()
        return True

    def trigger_progressbar(self, user_data):
        new_value = self.progressbar.get_fraction() + 0.01
        if new_value > 1:
            new_value = 1.00
        self.progressbar.set_fraction(new_value)
        return True

    def thread_ntfs(self, widget):
        self.format_button.set_sensitive(False)
        self.close_button.set_sensitive(False)
        self.progressbar.set_text("Formatting... please wait")
        #GObject.timeout_add(300, self.trigger_progressbar, None)
        sp = subprocess.Popen(shlex.split('mkfs.ntfs --fast --force --label "{0}" {1}'.format(self.device_label.get_text(), self.device_path)), stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        out, err = sp.communicate()
        os.system("echo '{0}{1}' > /home/".format(out, err) + getpass.getuser() + "/Desktop/usb2format.txt")
        GLib.source_remove(self.progress_pulse)
        self.progress_pulse = 0
        self.progressbar.set_fraction(1.00)
        self.progressbar.set_text('"{0}" was formatted successfully with NTFS'.format(self.device_label.get_text()))
        self.format_button.set_sensitive(True)
        self.close_button.set_sensitive(True)

    def thread_fat(self, widget):
        self.format_button.set_sensitive(False)
        self.close_button.set_sensitive(False)
        self.progressbar.set_text("Formatting... please wait")
        #GObject.timeout_add(300, self.trigger_progressbar, None)
        sp = subprocess.Popen(shlex.split('mkfs.vfat -n "{0}" -I {1}'.format(self.device_label.get_text(), self.device_path)), stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        out, err = sp.communicate()
        os.system("echo '{0}{1}' > /home/".format(out, err) + getpass.getuser() + "/Desktop/usb2format.txt")
        self.progressbar.set_fraction(1.00)
        GLib.source_remove(self.progress_pulse)
        self.progress_pulse = 0
        self.progressbar.set_text('"{0}" was formatted successfully with FAT32'.format(self.device_label.get_text()))
        self.format_button.set_sensitive(True)
        self.close_button.set_sensitive(True)

    def on_format_clicked(self, widget):
        sp = subprocess.Popen(shlex.split("umount {0}".format(self.device_path)), stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        out, err = sp.communicate()
        if err.startswith("umount: {0}: No such file or directory".format(self.device_path)):
            self.format_button.set_sensitive(False)
            self.close_button.set_sensitive(False)
            self.device_label.set_text("Die Hard !")
            self.progressbar.set_text('Batman said: don\'t try to fool the program')
            dont_do_that_again = Gtk.MessageDialog(None, 0, Gtk.MessageType.WARNING, Gtk.ButtonsType.OK, 
            'Warning !')
            dont_do_that_again.format_secondary_text(
                "There is no active USB device to format.\nRestart the program and don\'t remove\nyour devices before clicking Format.")
            dont_do_that_again.run()
            dont_do_that_again.destroy()
            Gtk.main_quit()
        else:
            if self.file_system.get_active_text() == "fat":
                self.progressbar.set_fraction(0.00)
                self.progress_pulse = GLib.timeout_add(100, self.progressbar_pulse)
                thread.start_new_thread(self.thread_fat, ("start_fat_in_new_thread", ))

            if self.file_system.get_active_text() == "ntfs":
                self.progressbar.set_fraction(0.00)
                self.progress_pulse = GLib.timeout_add(100, self.progressbar_pulse)
                thread.start_new_thread(self.thread_ntfs, ("start_ntfs_in_new_thread", ))

    def on_close_clicked(self, widget):
        Gtk.main_quit()

    def list_all_devices(self):
        current_directory = os.getcwd()
        list_devices = subprocess.Popen(shlex.split("python2 {0}/data_usb2format/list_usb_devices.py".format(current_directory)), stdout=subprocess.PIPE).communicate()[0]
       # list_devices = list_devices.decode()
        list_devices = list_devices.strip().split('\n')
        for item in list_devices:
            name, size = item.split(',')
            self.show_devices.append_text(name + ' (' + size.lstrip() + ')')
        self.device_label.set_text(name[0:-7])
        self.show_devices.set_active(0)

    def __init__(self):
        self.intf = Gtk.Builder()
        self.intf.add_from_file('data_usb2format/usb2format.glade')
        self.intf.connect_signals(self)
        self.window = self.intf.get_object("window1")
        self.show_devices = self.intf.get_object("comboboxtext1")
        self.file_system = self.intf.get_object("comboboxtext2")
        self.progressbar = self.intf.get_object("progressbar1")
        self.device_label = self.intf.get_object("entry1")
        self.format_button = self.intf.get_object("format")
        self.close_button = self.intf.get_object("close")
        self.list_all_devices()
        self.device_path = self.show_devices.get_active_text().split('(')[1].rstrip(')')

        self.screen = Gdk.Screen.get_default()
        self.css_provider = Gtk.CssProvider()
        self.css_provider.load_from_path('data_usb2format/style.css')
        self.priority = Gtk.STYLE_PROVIDER_PRIORITY_USER
        self.context = Gtk.StyleContext()
        self.context.add_provider_for_screen(self.screen, self.css_provider, self.priority)


        self.window.connect("delete-event", Gtk.main_quit)
        self.window.show_all()

try:
    if __name__ == '__main__':
        usb2format()
        Gtk.main()
except ValueError:
    no_device()