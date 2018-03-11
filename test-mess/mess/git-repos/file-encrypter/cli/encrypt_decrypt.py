#!/usr/bin/python
import shlex
import subprocess
import sys
import shutil
import os

def remind_usage():
    sys.exit("\nUsage:  python encrypt_decrypt.py e a.txt\n\ne encrypt, d decrypt -> input file\n")

encrypt_decrypt_letters = ('e', 'd')
if not ((len(sys.argv) == 3) and (len(sys.argv[1]) == 1) and sys.argv[1].startswith(encrypt_decrypt_letters)):
    remind_usage()
elif sys.argv[1].startswith('e') and os.path.isfile(sys.argv[2]):
    process = subprocess.Popen(shlex.split('gpg -o encrypted-file.gpg --cipher-algo AES256 --symmetric "{0}"'.format(sys.argv[2])))
    process.communicate()
    shutil.move('encrypted-file.gpg', sys.argv[2])
elif sys.argv[1].startswith('d') and os.path.isfile(sys.argv[2]):
    shutil.copy(sys.argv[2], sys.argv[2] + '.bak')
    shutil.move(sys.argv[2], sys.argv[2] + '.gpg')
    process = subprocess.Popen(shlex.split('gpg "{0}".gpg'.format(sys.argv[2])))
    process.communicate()
    if not os.path.isfile(sys.argv[2]):
        shutil.move(sys.argv[2] + '.bak', sys.argv[2])
        os.remove(sys.argv[2] + '.gpg')
    else:
        if os.path.isfile(sys.argv[2] + '.gpg'):
            os.remove(sys.argv[2] + '.gpg')
            os.remove(sys.argv[2] + '.bak')
else:
    sys.exit("\nSuch file doesn't exist\n")