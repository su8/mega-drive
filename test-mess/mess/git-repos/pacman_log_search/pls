#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# Created by Aaron Caffrey
# License: GPLv3 - http://www.gnu.org/licenses/gpl.html
from glob import glob
from time import ctime
from os.path import getmtime
from re import match, findall
from datetime import datetime

class no_class_calls(type):
    def __call__(self, *args, **kwargs):
        raise TypeError("You should NOT instantiate the class, but it's functions !")

class last(metaclass=no_class_calls):
    def upgrade():
        # create new empty lists
        packages = []
        upg_list = []
        # add all upgraded dates to the list with 'for loop'
        for upgrades in package("starting full system upgrade"):
            upg_list.append(upgrades)

        # split the last item
        a = upg_list[-1].split()
        # remove the square bracket from the date, so we can pass it as yyyy-mmmm-dddd
        b = a[0].replace("[", "")
        # read the log
        for lines in open("/var/log/pacman.log", "r"):
            # if the date match and there are upgraded packages, append them to the list
            if match("(.*){0}(.*)".format(b), lines) and \
            match("(.*)upgraded(.*)", lines):
                packages.append(lines)
        # if the packages list is not empty, continue
        if packages:
            # yield the last upgrade date from the upg_list (slice the last item)
            yield upg_list[-1]
            # yield the last number(s) from the enumerated packages
            yield "-> {0} packages to upgrade ::".format(len(packages[0:]))
            # yield all the packages from the "packages" list and remove the newlines
            for packs in packages:
                yield packs.rstrip("\n")
        # packages list is empty, so start again with the previous upg. dates
        else:
            if not len(upg_list[0:]) > 1:
                pass
            else:
                last_upg_date = "{0}".format(upg_list[-1]).split()[0].replace("[", "")
                yield "-> Nothing to upgrade for {0} ::".format(last_upg_date)
                for lines in open("/var/log/pacman.log", "r"):
                    if match("(.*){0}(.*)".format(upg_list[-2].split()[0].replace("[", "")), lines) and \
                    match("(.*)upgraded(.*)", lines):
                        packages.append(lines)
                if packages:
                    yield upg_list[-2]
                    yield "-> {0} packages to upgrade ::".format(len(packages[0:]))
                    for packs in packages:
                        yield packs.rstrip("\n")
                else:
                    if not len(upg_list[0:]) > 2:
                        pass
                    else:
                        last_upg_date = "{0}".format(upg_list[-2]).split()[0].replace("[", "")
                        yield "-> Nothing to upgrade for {0} ::".format(last_upg_date)
                        for lines in open("/var/log/pacman.log", "r"):
                            if match("(.*){0}(.*)".format(upg_list[-3].split()[0].replace("[", "")), lines) and \
                            match("(.*)upgraded(.*)", lines):
                                packages.append(lines)
                        if packages:
                            yield upg_list[-3]
                            yield "-> {0} packages to upgrade ::".format(len(packages[0:]))
                            for packs in packages:
                                yield packs.rstrip("\n")
                        else:
                            last_upg_date = "{0}".format(upg_list[-3]).split()[0].replace("[", "")
                            # substract the current day from the last detected upg date
                            sub_last_upg = datetime.now() - datetime(int(last_upg_date.split('-')[0]),\
                                int(last_upg_date.split('-')[1]),int(last_upg_date.split('-')[2]))
                            yield "-> Nothing to upgrade for {0} ::".format(last_upg_date)
                            yield """-> You haven\'t upgraded your system for at least {0} days ::
-> Always keep your system up-to-date ! ::""".format(sub_last_upg.days)

    def access():
        # return the last modification date to the pacman.log
        return ctime(getmtime("/var/log/pacman.log"))

def package(package):
    # This is the package searching function, test the second character for numbers
    try:
        if isinstance(int(package[1]), int):
            pass
    except:
        pass
        # find all pacman logs
        for all_pacman_logs in glob("/var/log/pacman.*"):
            # read the logs
            for lines in open(all_pacman_logs, "r"):
                # if the package matches the given one, print it
                if match("(.*){0}(.*)".format(package), lines):
                    yield lines.rstrip("\n")

def action_package(action, package):
    # find all pacman logs
    for all_pacman_logs in glob("/var/log/pacman.*"):
        # read the logs
        for lines in open(all_pacman_logs, "r"):
            # if the action and the package matches the given one, print it
            if match("(.*){0} {1}(.*)".format(action, package), lines):
                yield lines.rstrip("\n")

def advanced(date, action, package):
    # find all pacman logs
    for all_pacman_logs in glob("/var/log/pacman.*"):
        # read the logs
        for lines in open(all_pacman_logs, "r"):
            # if the date, action, package matches the given one, print it
            if match("(.*){0} {1}(.*)".format(action, package), lines) and \
            match("(.*){0}(.*)".format(date), lines):
                yield lines.rstrip("\n")

def date(date):
    # if the findall pattern matches the synthax x3(numbers dash), continue
    if findall(r"\d+-\d+\-\d+", date):
        # find all pacman logs
        for all_pacman_logs in glob("/var/log/pacman.*"):
            # read the logs
            for lines in open(all_pacman_logs, "r"):
                # if the date matches the given one, print it
                if match("(.*){0}(.*)".format(date), lines):
                    yield lines.rstrip("\n")