pacman_log_search
=================

A module which will search thru all of the pacman.* log files. Also you don't have to type the whole name of the package.

It can search for:

* package name 
* action and package name 
* date only
* advanced: date, action, package.
* last modification date to the pacman.log
* last upgrade date and upgraded packages

## Installation

    sudo python3 setup.py install

## Usage scenarios

```python
import pls
pls.action_package("installed", "openshot")
<generator object action_package at 0x7f5ccf13faa0>

for x in pls.action_package("installed", "openshot"):
    print(x)
[2014-01-15 10:52] [PACMAN] installed openshot (1.4.3-3)

next(iter(pls.action_package("installed", "openshot")))
'[2014-01-15 10:52] [PACMAN] installed openshot (1.4.3-3)'

next(iter(pls.package("openshot")))
"[2014-01-15 10:49] [PACMAN] Running 'pacman -S openshot'"
for x in pls.package("openshot"):
    print(x)
[2014-01-15 10:49] [PACMAN] Running 'pacman -S openshot'
[2014-01-15 10:52] [PACMAN] installed openshot (1.4.3-3)
[2014-01-15 17:04] [PACMAN] Running 'pacman -R openshot'
[2014-01-15 17:04] [PACMAN] removed openshot (1.4.3-3)
[2014-01-27 19:30] [PACMAN] Running 'pacman -S --noconfirm openshot'

next(iter(pls.advanced("2014-01-27", "upgraded", "kde-base-artwork")))
'[2014-01-27 13:46] [PACMAN] upgraded kde-base-artwork (4.12.0-1 -> 4.12.1-1)'
for x in pls.advanced("2014-01-27", "upgraded", "kde-base-artwork"):
    print(x)
[2014-01-27 13:46] [PACMAN] upgraded kde-base-artwork (4.12.0-1 -> 4.12.1-1)

next(iter(pls.date("2014-01-12")))
"[2014-01-12 11:15] [PACMAN] Running 'pacman -S opencv'"
for x in pls.date("2014-01-12"):
    print(x)
[2014-01-12 11:15] [PACMAN] Running 'pacman -S opencv'


for x in pls.last.upgrade():
    print(x)
[2014-02-09 12:58] [PACMAN] starting full system upgrade
-> 4 packages to upgrade ::
[2014-02-09 13:30] [PACMAN] upgraded krb5 (1.11.4-1 -> 1.12.1-1)
[2014-02-09 13:30] [PACMAN] upgraded curl (7.34.0-3 -> 7.35.0-1)
[2014-02-09 13:30] [PACMAN] upgraded dhcpcd (6.1.0-1 -> 6.2.1-1)
[2014-02-09 13:31] [PACMAN] upgraded openssh (6.4p1-1 -> 6.5p1-2)

pls.last.access()
'Sun Feb 9 13:31:16 2014' 

```
## Small Tutorial
```python
>>> line = "[2014-01-15 10:52] [PACMAN] installed openshot (1.4.3-3)"
>>> date, time, pacman, action, package, version = line.split()
>>> date
'[2014-01-15'
>>> time
'10:52]'
>>> pacman
'[PACMAN]'
>>> action
'installed'
>>> package
'openshot'
>>> version
'(1.4.3-3)'
>>> date.replace("[", "")
'2014-01-15'
>>> time.replace("]", "")
'10:52'
>>> print(date.replace("[", ""), time.replace("]", ""), pacman, action, package, version, sep=" ")
2014-01-15 10:52 [PACMAN] installed openshot (1.4.3-3)
>>> line
'[2014-01-15 10:52] [PACMAN] installed openshot (1.4.3-3)'
>>>
```

## Uninstall

    python3 --version
    sudo rm -rf /usr/lib/python3.3/site-packages/pls.py

* You may tweak the module and create similar GUI program like this one - <a href="http://qt-apps.org/content/show.php/Pacman+Log+Viewer?content=150484" target="_blank">http://qt-apps.org/content/show.php/Pacman+Log+Viewer?content=150484</a>