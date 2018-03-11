#!/usr/bin/env python2
import os
import shutil
from gi.repository import Gtk, Gdk


class encrypt_decrypt_gui:

    def on_select_folder_clicked(self, widget):
        if self.encryption_password.get_text() == "" or self.archive_name.get_text() == "":
            dialog = Gtk.MessageDialog(None, 0, Gtk.MessageType.WARNING,
                Gtk.ButtonsType.OK, "Archive name and the password field\ncannot be empty !")
            dialog.run()
            dialog.destroy()
        else:
            chooser_dialog = Gtk.FileChooserDialog(title="Select folder"
            ,action=Gtk.FileChooserAction.SELECT_FOLDER, buttons=["Select", Gtk.ResponseType.OK, "Cancel", Gtk.ResponseType.CANCEL])
            response = chooser_dialog.run()
            filename = chooser_dialog.get_filename()
            if response == Gtk.ResponseType.OK:
                os.system('7za a -tzip -p{0} -mem=AES256 "{1}/{2}".zip "{3}"'.format(self.encryption_password.get_text(), os.path.join(os.path.expanduser("~"), "Desktop"), self.archive_name.get_text(), filename))
                if os.path.isfile('{0}/{1}.zip'.format(os.path.join(os.path.expanduser("~"), "Desktop"), self.archive_name.get_text())):
                    dialog = Gtk.MessageDialog(None, 0, Gtk.MessageType.INFO,
                        Gtk.ButtonsType.OK, "Archive created & protected !")
                    dialog.format_secondary_text("See your Desktop directory")
                    chooser_dialog.destroy()
                    dialog.run()
                    dialog.destroy()
            if response == Gtk.ResponseType.CANCEL:
                pass
            chooser_dialog.destroy()

    def on_select_file_clicked(self, widget):
        if self.encryption_password.get_text() == "" or self.archive_name.get_text() == "":
            dialog = Gtk.MessageDialog(None, 0, Gtk.MessageType.WARNING,
                Gtk.ButtonsType.OK, "Archive name and the password field\ncannot be empty !")
            dialog.run()
            dialog.destroy()
        else:
            chooser_dialog = Gtk.FileChooserDialog(title="Select file"
            ,action=Gtk.FileChooserAction.OPEN, buttons=["Select", Gtk.ResponseType.OK, "Cancel", Gtk.ResponseType.CANCEL])
            response = chooser_dialog.run()
            filename = chooser_dialog.get_filename()
            if response == Gtk.ResponseType.OK:
                os.system('7za a -tzip -p{0} -mem=AES256 "{1}/{2}".zip "{3}"'.format(self.encryption_password.get_text(), os.path.join(os.path.expanduser("~"), "Desktop"), self.archive_name.get_text(), filename))
                if os.path.isfile('{0}/{1}.zip'.format(os.path.join(os.path.expanduser("~"), "Desktop"), self.archive_name.get_text())):
                    dialog = Gtk.MessageDialog(None, 0, Gtk.MessageType.INFO,
                        Gtk.ButtonsType.OK, "Archive created & protected !")
                    dialog.format_secondary_text("See your Desktop directory")
                    chooser_dialog.destroy()
                    dialog.run()
                    dialog.destroy()
            if response == Gtk.ResponseType.CANCEL:
                pass
            chooser_dialog.destroy()

    def on_encrypt_clicked(self, widget):
        chooser_dialog = Gtk.FileChooserDialog(title="Encrypt file"
        ,action=Gtk.FileChooserAction.OPEN
        ,buttons=["Encrypt", Gtk.ResponseType.OK, "Cancel", Gtk.ResponseType.CANCEL])
        response = chooser_dialog.run()
        filename = chooser_dialog.get_filename()
        if response == Gtk.ResponseType.OK:
            os.system('gpg -o encrypted-file.gpg --cipher-algo "{0}" --symmetric "{1}"'.format(self.combobox.get_active_text(), filename))
            if os.path.isfile('encrypted-file.gpg'):
                shutil.move('encrypted-file.gpg', filename)
                dialog = Gtk.MessageDialog(None, 0, Gtk.MessageType.INFO,
                    Gtk.ButtonsType.OK, "Encrypted !")
                dialog.format_secondary_text("{0}".format(filename))
                chooser_dialog.destroy()
                dialog.run()
                dialog.destroy()
        if response == Gtk.ResponseType.CANCEL:
            pass
        chooser_dialog.destroy()

    def on_decrypt_clicked(self, widget):
        chooser_dialog = Gtk.FileChooserDialog(title="Decrypt file"
        ,action=Gtk.FileChooserAction.OPEN
        ,buttons=["Decrypt", Gtk.ResponseType.OK, "Cancel", Gtk.ResponseType.CANCEL])
        response = chooser_dialog.run()
        filename = chooser_dialog.get_filename()	
        if response == Gtk.ResponseType.OK:
            shutil.copy(filename, filename + '.bak')
            shutil.move(filename, filename + '.gpg')
            os.system('gpg "{0}".gpg'.format(filename))

            if not os.path.isfile(filename):
                shutil.move(filename + '.bak', filename)
                os.remove(filename + '.gpg')
                dialog = Gtk.MessageDialog(None, 0, Gtk.MessageType.WARNING,
                    Gtk.ButtonsType.OK, "Wrong password, huh ?")
                dialog.format_secondary_text("")
                chooser_dialog.destroy()
                dialog.run()
                dialog.destroy()
            else:
                if os.path.isfile(filename + '.gpg'):
                    os.remove(filename + '.gpg')
                    os.remove(filename + '.bak')
                    dialog = Gtk.MessageDialog(None, 0, Gtk.MessageType.INFO,
                        Gtk.ButtonsType.OK, "Decrypted !")
                    dialog.format_secondary_text("{0}".format(filename))
                    chooser_dialog.destroy()
                    dialog.run()
                    dialog.destroy()
        if response == Gtk.ResponseType.CANCEL:
            pass
        chooser_dialog.destroy()

    def __init__(self):
        intf = Gtk.Builder()
        intf.add_from_file('enc_data/encrypt_decrypt_gui2.glade')
        intf.connect_signals(self)
        window = intf.get_object("window1")
        self.combobox = intf.get_object("comboboxtext1")
        self.archive_name = intf.get_object("archive_name")
        self.encryption_password = intf.get_object("encryption_password")

        self.screen = Gdk.Screen.get_default()
        self.css_provider = Gtk.CssProvider()
        self.css_provider.load_from_path('enc_data/style.css')
        self.priority = Gtk.STYLE_PROVIDER_PRIORITY_USER
        self.context = Gtk.StyleContext()
        self.context.add_provider_for_screen(self.screen, self.css_provider, self.priority)

        window.connect("delete-event", Gtk.main_quit)
        window.show_all()

if __name__ == '__main__':
    encrypt_decrypt_gui()
    Gtk.main()