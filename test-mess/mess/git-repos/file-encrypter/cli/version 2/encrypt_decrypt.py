#!/usr/bin/python
import shlex
import subprocess
import sys
import shutil
import os

class build_the_program:

    def encrypt(self):
        file_for_encryption = raw_input("\n" + " "*20  + "File name: " + bcolors.OKBLUE)
        if os.path.isfile(file_for_encryption):
            process = subprocess.Popen(shlex.split('gpg -o encrypted-file.gpg --cipher-algo AES256 --symmetric "{0}"'.format(file_for_encryption)))
            process.communicate()
            shutil.move('encrypted-file.gpg', file_for_encryption)
            print(bcolors.ENDC + "\n" + " "*15 + bcolors.OKBLUE + file_for_encryption + bcolors.ENDC + " has been " + bcolors.OKGREEN + "Encrypted" + bcolors.ENDC)
        else:
            print(bcolors.ENDC + "\n" + bcolors.WARNING + " "*15 + "Such file doesn't exist" + bcolors.ENDC)

    def decrypt(self):
        file_for_decryption = raw_input("\n" + " "*20  + "File name: " + bcolors.OKBLUE)
        if os.path.isfile(file_for_decryption):
            print(bcolors.ENDC + "\n")
            shutil.copy(file_for_decryption, file_for_decryption + '.bak')
            shutil.move(file_for_decryption, file_for_decryption + '.gpg')
            process = subprocess.Popen(shlex.split('gpg "{0}".gpg'.format(file_for_decryption)))
            process.communicate()
            if not os.path.isfile(file_for_decryption):
                shutil.move(file_for_decryption + '.bak', file_for_decryption)
                os.remove(file_for_decryption + '.gpg')
                print(bcolors.RED + "\n" + " "*15 + "Wrong password, huh ?" + bcolors.ENDC)
            else:
                if os.path.isfile(file_for_decryption + '.gpg'):
                    os.remove(file_for_decryption + '.gpg')
                    os.remove(file_for_decryption + '.bak')
                    print(bcolors.ENDC + "\n" + " "*15 + bcolors.OKBLUE + file_for_decryption + bcolors.ENDC + " has been " + bcolors.RED + "Decrypted" + bcolors.ENDC)
        else:
            print("\n" + bcolors.WARNING + " "*15 + "Such file doesn't exist" + bcolors.ENDC)

    def __init__(self):
        while True:
            try:
                os.system(['clear','cls'][os.name == 'nt'])
                # The Menu v2
                print(bcolors.OKBLUE + """
                 _________ """ + bcolors.HEADER + """File Encrypter v2""" + bcolors.ENDC + """ """ + bcolors.OKBLUE + """________
                |                                    |
                |          """ + bcolors.OKGREEN + """e""" + bcolors.ENDC + """""" + bcolors.OKBLUE + """)""" + bcolors.ENDC + """ Encrypt File           """ + bcolors.OKBLUE + """|
                |                                    |
                |          """ + bcolors.RED + """d""" + bcolors.ENDC + """""" + bcolors.OKBLUE + """)""" + bcolors.ENDC + """ Decrypt File           """ + bcolors.OKBLUE + """|
                |                                    |
                |          """ + bcolors.WARNING + """q""" + bcolors.ENDC + """""" + bcolors.OKBLUE + """)""" + bcolors.ENDC + """ Quit                   """ + bcolors.OKBLUE + """|
                |                                    |
                |____________________________________|""" + bcolors.ENDC + """\n\n""")

                selection = raw_input(" "*15 +"What would you like to do?  ")
                if selection == "e":
                        self.encrypt()
                elif selection == "d":
                        self.decrypt()
                elif selection == "w":
                        break
                elif selection == "q":
                        print("\n")
                        break
                else:
                    print(bcolors.WARNING + "\n" + " "*18 + "Not a valid choice." + bcolors.ENDC)
                raw_input("\n" + " "*15 + "Press enter to continue")
                exit
            except KeyboardInterrupt:
                sys.exit("\n\n" + " "*20 + "See you later\n")

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    RED = '\033[91m'
    ENDC = '\033[0m'

    def disable(self):
        self.HEADER = ''
        self.OKBLUE = ''
        self.OKGREEN = ''
        self.WARNING = ''
        self.RED = ''
        self.ENDC = ''

if __name__ == '__main__':
    build_the_program()



# The old menu, go figure how complex I made it...
        #print("\n")
        #print(bcolors.OKBLUE + " "*11 + "_"*14 + " " + bcolors.HEADER + "File Encrypter v2 " + bcolors.OKBLUE +  "_"*16 + bcolors.ENDC + "\n" + bcolors.OKBLUE + " "*10 + "|" + " "*49  + "|" + bcolors.ENDC)
        #print(bcolors.OKBLUE + " "*10 + "|" + " "*49 + "|" + bcolors.ENDC + "\n" + bcolors.OKBLUE + " "*10 + "|" + " "*49  + "|" + bcolors.ENDC)
        #print(bcolors.OKBLUE + " "*10 + "|" + bcolors.ENDC + " "*15 + bcolors.OKGREEN + "e" + bcolors.ENDC + ") Encrypt File" + " "*14 + bcolors.OKBLUE + " "*5 + "|" + bcolors.ENDC + "\n" + bcolors.OKBLUE + " "*10 + "|" + " "*49  + "|" + bcolors.ENDC)
        #print(bcolors.OKBLUE + " "*10 + "|" + bcolors.ENDC + " "*15 + bcolors.RED + "d" + bcolors.ENDC + ") Decrypt File" + " "*14 + bcolors.OKBLUE + " "*5 + "|" + bcolors.ENDC + "\n" + bcolors.OKBLUE + " "*10 + "|" + " "*49  + "|" + bcolors.ENDC)
        #print(bcolors.OKBLUE + " "*10 + "|" + bcolors.ENDC + " "*15 + bcolors.WARNING + "q" + bcolors.ENDC + ") Quit" + " "*17 + bcolors.OKBLUE + " "*10 + "|" + bcolors.ENDC + "\n" + bcolors.OKBLUE + " "*10 + "|" + " "*49  + "|" + bcolors.ENDC)
        #print(bcolors.OKBLUE + " "*10 + "|" + "_"*49 + "|" + bcolors.ENDC + "\n")