Backup-Like-King
================

When you have to deal with a multiple directories or files, sometimes you need a proper backup solution.
Once the program is ran for first time, it will ask few questions: which directories to backup, location to store the backup file, do you want md5sum reports, what file format to choose for the backup archive. Once given correct details it stores that information as a module and everytime you run the program it will backup automatically those directories from the module's list. Of course you can add,remove,replace,change the location of every single directory or md5sum reports. You'll find Backup Like King really useful when dealing with a lot of directories. 

If anything bad happens, it will be recorded in a log file in the same folder where the backup is meant to be.

## Requirements

* python3

## Archlinux support

Archlinux users can install the program directly from AUR, without the need to download it from here.

    yaourt -S blk

## Program Options:

    -list   List all directories or files in the backup list.
    -delete   Delete specific path from the list. Type -list to find which directories are in it.
    -add   Add existing directory or file to the list, so the program will include it to the backup file.
    -replace   Replace existing directory or file from the list ( /old/path/  /new/path/ )
    -location  Change the backup location. ( /path/to/new/location/ )
    -archive-format  Change the file format for the backup archive. ( bz2,gz )
    -md5sum-off / -md5sum-on  Turn on or off the md5sum log report for each backup.
    -purge-profile  Delete the existing profile.