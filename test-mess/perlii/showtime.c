#include <EXTERN.h>
#include <perl.h>

#ifndef RETURN_SUCCESS
#define RETURN_SUCCESS 0
#define RETURN_FAILURE 1
#endif

static PerlInterpreter *my_perl = NULL;

int main(int argc, char **argv, char **env) {
    char *args[] = { NULL };

    my_perl = perl_alloc();
    if (NULL == my_perl) {
      return -1;
    }

    perl_construct(my_perl);
    perl_parse(my_perl, NULL, argc, argv, (char **)NULL);

    /* skipping perl_run() */

/* char *my_argv[] = { "", "NAME_HERE.pl" }; */
/* perl_parse(my_perl_interpreter, NULL, 2, my_argv, (char **)NULL); */

    call_argv("showtime", G_DISCARD | G_NOARGS, args);

    perl_destruct(my_perl);
    perl_free(my_perl);
}
