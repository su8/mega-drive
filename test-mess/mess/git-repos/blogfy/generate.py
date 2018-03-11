#!/usr/bin/env python2
import os
from sys import argv, path
from importlib import import_module

class UmadBro(object):
    def __init__(self, len_argv=len(argv)):
        path.insert(0, os.path.join('static', 'modules'))
        if len_argv > 1:
            def few_arg_test(func, num1, num2):
                if len_argv > num1:
                    start_module_function = getattr(import_module('functions'), func)
                    start_module_function(icy)
                else:
                    raise SystemExit('\nWARNING "{0}" requires {1} arguments,'\
                    '\nyou have given me {2} !\n'.format(lenny, num2, len(icy)))
            dash_clash = lambda crash: '{0} -{0} --{0} {0[0]} -{0[0]} --{0[0]}'\
                                                          .format(crash).split()
            lenny = argv[1]
            icy   = argv[2:]
            if lenny in dash_clash('replace'):
                few_arg_test('replace_str', 3, 2)
            if lenny in dash_clash('new'):
                few_arg_test('create_new_post', 2, 1)
            if lenny in dash_clash('format'):
                few_arg_test('format_post', 2, 1)
            if lenny in dash_clash('optimize'):
                few_arg_test('optimize_modules', 1, 0)
        else:
            from blogfy import GenerateBlog
            GenerateBlog()

if __name__ == '__main__':
    UmadBro()