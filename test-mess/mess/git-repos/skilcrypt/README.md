# skilcrypt

Three file-based encryption scripts utilizing GPG. skilcrypt-looper and skilcrypt-daemon are trying to mimic EncFS, while the skilcrypt script is the most simplistic of the three and requires manual operation all the time.

GPG can be installed in most major operating systems, thus you will be able encrypt and decrypt your files no matter what OS or GPG program/port you've used.

# skilcrypt-looper (tries to mimic EncFS)
This script basically tries to mimic EncFS by mirroring your files from $DECRYPTED_FILES directory into $ENCRYPTED_FILES directory where they become encrypted. In order the script to know when and which file is added/removed/changed it uses dead simple database.

You can work on a project and only the files that you've changed will be re-encrypted. This way your $ENCRYPTED_FILES dir. can be in constant sync. with some "cloud" or external device/hdd/flash drive.

That's how I wrote this script. It was developed entirely in my $DECRYPTED_FILES dir. and whenever I saved it in vim, the script was automatically mirrored and re-encrypted in $ENCRYPTED_FILES dir. which on the other hand is Google Drive WebDAV folder.

Whenever $ENCRYPTED_FILES or $DECRYPTED_FILES directory become empty, the script will mirror and decrypt or encrypt the files from the one folder into the other, just make sure that you've supplied the correct GPG password for file decryption if $DECRYPTED_FILES is empty, but $ENCRYPTED_FILES has files in it.

This script is much more cpu and disk intensive than the daemon.

# skilcrypt-daemon (inspired by EncFS)
This fellow is suitable if you constantly edit & save files and want them to be automatically encrypted and ready for transfer A.S.A.P.

Whenever files (not ending with **.gpg**) are put inside the $SOURCE_FILES folder, they will be encrypted instantly in the background without your interaction, just make sure that you've edited the variable $PASSWORD_FILE. Please use the [diceware](https://en.wikipedia.org/wiki/Diceware) method for creating passwords.

The script will run in infinite loop, it's resource friendly don't worry.


[EncFS](https://defuse.ca/audits/encfs.htm) is pretty much out of the game.
