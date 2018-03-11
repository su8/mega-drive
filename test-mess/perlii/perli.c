/* 
http://www.perlmonks.org/?node_id=830663
 * */

#include <EXTERN.h>               /* from the Perl distribution     */
#include <perl.h>                 /* from the Perl distribution     */

static PerlInterpreter *my_perl = NULL;		// The master object

EXTERN_C void xs_init (pTHX);	

EXTERN_C void boot_DynaLoader (pTHX_ CV* cv);	// Standard required declaration for runtime bootstrap loading

#ifndef RETURN_SUCCESS
#define RETURN_SUCCESS 0
#define RETURN_FAILURE 1
#endif

/*
 *   xs_init  - Behind the scenes stuff so that Perl can dynamically load modules it needs
 *          Don't touch unless you know what you're doing
 */ 
EXTERN_C void xs_init(pTHX)
{
        char *file = __FILE__;
        dXSUB_SYS;

        /* DynaLoader is a special case */
        newXS("DynaLoader::boot_DynaLoader", boot_DynaLoader, file);
	// Other declarations can be put here, again if you know what you're doing
}


/*
 *   perl_env_check_service - Returns service availability status
 *       @out   return_val      RETURN_SUCCESS or RETURN_FAILURE
 */
int perl_env_check_service ( )
{
    int return_val = RETURN_SUCCESS;
    int count = 0;

    return_val = perl_env_init();
    if (return_val == RETURN_SUCCESS) {
        SV * sva;

        STRLEN len;

	/* Standard macro calls required to manipulate the Perl stack to get data to & from  */
        dSP;                            /* initialize stack pointer      */
        ENTER;                          /* everything created after here */
        SAVETMPS;                       /* ...is a temporary variable.   */

        PUSHMARK(SP);                   /* remember the stack pointer    */
        PUTBACK;                      /* make local stack pointer global */

	/* Make the call to Perl using one of four functions available (call_sv, call_pv, call_method, and call_argv)  */
        count = call_pv("perl_env_check_service", G_SCALAR);    	
	/* G_SCALAR says I want to check the return value and it should be a scalar, many other options are available  */  

        SPAGAIN;                        /* refresh stack pointer         */

        if (count != 1) {
                return_val = RETURN_FAILURE;
        } else {
		// Return value from this call is also just a success or failure indicator
                return_val = POPi;
        }

        FREETMPS;                       /* free that return value        */
        LEAVE;                       /* ...and the XPUSHed "mortal" args.*/
    }
    return return_val;
}



/*
 *   perl_env_init - Initializes the PCI (Perl) environment
 *          All interface methods will call this to ensure PCI environment is initialized
 *       @out   return_val      RETURN_SUCCESS or RETURN_FAILURE
 */
int perl_env_init() {

   int return_val = RETURN_SUCCESS;

   // Only run the Perl environment setup once
   if (my_perl == NULL) {
        // No need to pass any main() params for this example
        return_val = perl_env_start(0, NULL, (char **)NULL);
   }

   return return_val;
}



/*
 *   perl_env_start - Starts up the environment
 *       @in    my_string       unused, just to pass in the required params
 *       @out   return_val      RETURN_SUCCESS or RETURN_FAILURE
 */
int perl_env_start(int argc, char **argv, char **env) {
        int return_val = RETURN_SUCCESS;

	// This is the Perl module we're calling
        char *my_argv[] = { "", "/project/c_to_perl/bin/perl_env_file.pl" };

        PERL_SYS_INIT3(&argc,&argv,&env);
        my_perl = perl_alloc();
        if (my_perl == NULL) {
                return_val = RETURN_FAILURE;
        }
        perl_construct(my_perl);

        perl_parse(my_perl, xs_init, 2, my_argv, env);

        return return_val;
}



/*
 *   perl_env_end - Cleanup.  Needs to be called by users for proper cleanup.
 */
void perl_env_end() {
        perl_destruct(my_perl);
        perl_free(my_perl);
        PERL_SYS_TERM();
}



/*
 *   perl_env_file_read_line - Returns the next line from the file contents
 *       @out   my_string       Will contain the next line contents of the current file
 *       @out   return_val      RETURN_SUCCESS or RETURN_FAILURE
 */
int perl_env_file_read_line ( char* my_string )
{
    int return_val = RETURN_SUCCESS;
    int count = 0;

    return_val = perl_env_init();
    if (return_val == RETURN_SUCCESS) {
        SV * sva;	// Scalar value object, there is also Array Value and Hash Value available (AV & HV)

        STRLEN len;
    
        dSP;                            /* initialize stack pointer      */
        ENTER;                          /* everything created after here */
        SAVETMPS;                       /* ...is a temporary variable.   */
        
        PUSHMARK(SP);                   /* remember the stack pointer    */
        PUTBACK;                      /* make local stack pointer global */
        count = call_pv("perl_env_file_read_line", G_SCALAR);      /* call the function             */
        SPAGAIN;                        /* refresh stack pointer         */
        
        if (count != 1) {
                return_val = RETURN_FAILURE;
        } else {
                sva = POPs;	// Pop the return var off the stack, expected to be a string
                if (sva) {
                        strcpy(my_string, SvPV(sva, len));
                }
                PUTBACK;
        }

        FREETMPS;                       /* free that return value        */
        LEAVE;                       /* ...and the XPUSHed "mortal" args.*/
    }   
    return return_val;
} 


/*
 *   perl_env_file_open - Opens a PCI file for reading
 *       @in    filename        Filename to open
 *       @out   return_val      RETURN_SUCCESS or RETURN_FAILURE
 */
int perl_env_file_open ( char* filename )
{
    int return_val = RETURN_SUCCESS;
    int count = 0;

    return_val = perl_env_init();
    if (return_val == RETURN_SUCCESS) {
        dSP;

        ENTER;
        SAVETMPS;

        PUSHMARK(SP);
	// Push the input var onto the stack
        XPUSHs(sv_2mortal(newSVpv(filename, 0)));
        PUTBACK;

        count = call_pv("perl_env_file_open", G_SCALAR);

        SPAGAIN;

        if (count != 1) {
                return_val = RETURN_FAILURE;
        } else {
		// Return value from this call is also just a success or failure indicator
                return_val = POPi;
        }

        PUTBACK;
        FREETMPS;
        LEAVE;
    }    
    return return_val;
}


/*
 *   perl_env_file_write - Write the input string to the current data buffer
 *       @in    my_string       Data to store in output file
 *       @out   return_val      RETURN_SUCCESS or RETURN_FAILURE
 */
int perl_env_file_write ( const char* my_string )
{
    int return_val = RETURN_SUCCESS;
    int count = 0; 
    
    return_val = perl_env_init();
    if (return_val == RETURN_SUCCESS) {
        dSP;
        
        ENTER;
        SAVETMPS;
        
        PUSHMARK(SP);
	// Push the input var onto the stack
        XPUSHs(sv_2mortal(newSVpv(my_string, 0)));
        PUTBACK;
        
        count = call_pv("perl_env_file_write", G_SCALAR);
        
        SPAGAIN;
        
        if (count != 1) {
                return_val = RETURN_FAILURE;
        } else {
		// Return value from this call is also just a success or failure indicator
                return_val = POPi;
        }       
        
        PUTBACK;
        FREETMPS;
        LEAVE;
    }   
    return return_val;
} 


/*
 *   perl_env_file_close - Close the current data contents and write to specified filename
 *       @in    filename        Filename to write output to
 *       @out   return_val      RETURN_SUCCESS or RETURN_FAILURE
 */
int perl_env_file_close ( char* filename )
{
    int return_val = RETURN_SUCCESS;
    int count = 0;

    return_val = perl_env_init();
    if (return_val == RETURN_SUCCESS) {

        dSP;

        ENTER;
        SAVETMPS;

        PUSHMARK(SP);
	// Push the input var onto the stack
        XPUSHs(sv_2mortal(newSVpv(filename, 0)));
        PUTBACK;

        count = call_pv("perl_env_file_close", G_SCALAR);
        SPAGAIN;

        if (count != 1) {
                return_val = RETURN_FAILURE;
        } else {
                return_val = POPi;
        }

        PUTBACK;
        FREETMPS;
        LEAVE;
    }
    return return_val;
}


/*
 *   Examples:  (evaluating return values are ignored for simplicity)
 * 
 *      Writing a file  
 *
 *	char mybuf[LARGE_BUFFER_SIZE] = {0};
 *      if (perl_env_check_service() == RETURN_SUCCESS) {     // Will initialize and startup
 *	   while (read_from_some_data_source(mybuf) == RETURN_SUCCESS) {
 *            perl_env_file_write(mybuf);
 *	   }
 *         perl_env_file_close("/project/tmp/myfile.txt");
 *         perl_env_end();
 *      }
 *
 *
 *      Reading a file
 *
 *      char mybuf[LARGE_BUFFER_SIZE] = {0};
 *      int i=0;
 *      if (perl_env_check_service() == RETURN_SUCCESS) {
 *         perl_env_file_open("/project/tmp/myfile.txt");
 *	   perl_env_file_read_line(mybuf);
 *         while (strlen(mybuf) > 0) {
 *              i++;
 *              printf("Line %d is >%s< \n", i, mybuf);
 *              perl_env_file_read_line(mybuf);
 *         }
 *         printf("All done reading file\n");
 *         // do NOT call close, that's for output files only
 *         perl_env_end();
 *	}
 */
