MinGW must be installed, then copy all files to C:\MinGW\Bin and compile them there

Win: gcc -fomit-frame-pointer -O3 -funroll-all-loops stkeys.c sha1.c -ostkeys

Linux: gcc -fomit-frame-pointer -O3 -funroll-all-loops stkeys.c -lcrypto -ostkeys
