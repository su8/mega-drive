#include <EXTERN.h>
#include <perl.h>

static PerlInterpreter *my_perl = NULL;

static void xs_init (pTHX);

EXTERN_C void boot_DynaLoader (pTHX_ CV* cv);
/* EXTERN_C void boot_Socket (pTHX_ CV* cv); */

EXTERN_C void
xs_init(pTHX) {
  char *file = __FILE__;
  /* DynaLoader is a special case */
  newXS("DynaLoader::boot_DynaLoader", boot_DynaLoader, file);
  /* newXS("Socket::bootstrap", boot_Socket, file); */
}

static void
PerlPower(void) {
   SV *sva = NULL; // Scalar value object, there is also Array Value and Hash Value available (AV & HV)
   STRLEN len = 0;
   char elo[200];

   dSP;                            /* initialize stack pointer      */
   ENTER;                          /* everything created after here */
   SAVETMPS;                       /* ...is a temporary variable.   */

   PUSHMARK(SP);                   /* remember the stack pointer    */
   /* XPUSHs(sv_2mortal(newSViv(a))); /1* push the base onto the stack  *1/ */
   /* XPUSHs(sv_2mortal(newSViv(b))); /1* push the exponent onto stack  *1/ */
   PUTBACK;                      /* make local stack pointer global */

   call_pv("uzer_func", G_SCALAR);      /* call the function             */
   SPAGAIN;                        /* refresh stack pointer         */
                                 /* pop the return value from stack */
   /* printf ("%d to the %dth power is %d.\n", a, b, POPi); */
   sva = POPs; // pop the return var off the stack, expected to be a string
   if (NULL != sva) {
    printf("%s\n", (char *)SvPV(sva, len));
     /* snprintf(elo, 190, "%s", SvPV(sva, len)); */
   }

   PUTBACK;
   FREETMPS;                       /* free that return value        */
   LEAVE;                       /* ...and the XPUSHed "mortal" args.*/
}

int main(void) {
 char *my_argv[] = { "", "power.pl" };

 /* PERL_SYS_INIT3(&argc,&argv,&env); */

 PERL_SYS_INIT3((int *)NULL, (char ***)NULL, (char ***)NULL);
 my_perl = perl_alloc();
 if (NULL == my_perl) {
   return -1;
 }

 perl_construct( my_perl );

 perl_parse(my_perl, xs_init, 2, my_argv, (char **)NULL);
 PL_exit_flags |= PERL_EXIT_DESTRUCT_END;
 perl_run(my_perl);

 PerlPower();

 perl_destruct(my_perl);
 perl_free(my_perl);
 PERL_SYS_TERM();

 return 0;
}
