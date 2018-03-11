import os

PATH_JOIN  = os.path.join
STATIC_TXT = PATH_JOIN(os.getcwd(), 'static', 'text posts')

def read_or_write(filename, fmode, content=str()):
    with open(filename, fmode) as f:
        if fmode == 'wt':
            f.write(content)
        else:
            return f.read()

def create_new_post(args):
    from time import strftime, localtime
    try:
        from configparser import ConfigParser
        python3 = True
    except ImportError:
        from ConfigParser import ConfigParser
        python3 = False

    cfg = ConfigParser()
    (cfg.read_file(open('config.ini')) if python3 else cfg.readfp(open('config.ini')))
    def get_me(teddy, bear):
        for chocolate, milky in crispy_dict.items():
            if chocolate in teddy:
                teddy = teddy.replace(chocolate, (milky if bear == 'black' else ' '))
        return teddy
    # [(x, html.unescape('&#{};'.format(x))) for x in range(33, 127)]
    crispy_dict = {'?': '&#63;', '& ': '&amp; ', '=': '&#61;', '^': '&#94;',
                   '!': '&#33;', '@': '&#64;', ' #': ' &#35;', '%': '&#37;', 
                   '*': '&#42;', '~': '&#126;', '(': '&#40;', ')': '&#41;',
                   '<': '&lt;',  '>': '&gt;', '{': '&#123;', '+': '&#43',
                   '[': '&#91;', ']': '&#93;', '|': '&#124;', '}': '&#125;',
                   ':': '&#58;', ' ; ': ' &#59; ', '/': '&#47;', '$': '&#36;',
                   '\\': '&#92;'}
    p1  = args[(1 if len(args) == 2 else 0)]
    pwn = get_me(p1, 'brown')
    for i in ('.', '#', '&', ';', '"', "'"):
        pwn = pwn.replace(i, str())
    o_O    = [x for x in pwn.split(' ') if bool(x)]
    date_f = '-'.join(cfg.get('customizations', 'date format')\
                                   .split()).replace('*', '%')
    read_or_write(PATH_JOIN(STATIC_TXT, '_'.join(o_O).lower()),
                'wt', 'title:  {0}\ndate:   {1}\nauthor: {2}{3}'
                  .format(get_me(p1, 'black'),
                    strftime(date_f, localtime()),
                     (cfg.get('important', 'author')
                       if len(args) < 2 else args[0]),
                        '\n\n<p> </p>'*4))

def replace_str(args):
    os.chdir(STATIC_TXT)
    for post_name in os.listdir(os.getcwd()):
        the_lines = read_or_write(post_name, 'rt')
        if args[0] in the_lines:
            read_or_write(post_name, 'wt', the_lines.replace(args[0], args[1]))

def format_post(post_name):
    txt  = PATH_JOIN(STATIC_TXT, str().join(post_name))
    g    = read_or_write(txt, 'rt').split('\n')
    body = [('<p>' + x + '</p>' if not x.startswith('<') else x) for x in g[3:] if bool(x)]
    read_or_write(txt, 'wt', '{0[0]}\n{0[1]}\n{0[2]}\n\n'.format(g) + '\n\n'.join(body))

def optimize_modules(_):
    from sys import version_info
    from distutils.util import byte_compile
    os.chdir(PATH_JOIN(os.getcwd(), 'static', 'modules'))
    py_f = ['blogfy.py', 'templates.py', 'functions.py', 'strings_to_format.py']
    byte_compile(py_f, 2, True)
    if version_info[0] == 3:
        os.chdir('__pycache__')
        pyo_f = os.listdir(os.getcwd())
        pyc_f = [x[:-1]+'c' for x in pyo_f]
    else:
        pyo_f = [x+'o' for x in py_f]
        pyc_f = [x+'c' for x in py_f]
    [os.rename(x,z) for x,z in zip(pyo_f, pyc_f)]