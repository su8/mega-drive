/*
 Embed an S-Lang interpreter in a Unicon loadfunc extension
 tectonics: gcc -o slang.so -shared -fpic slang.c -lslang
*/

#include <stdio.h>
#include <slang.h>
#include "icall.h"

/*
 Init S-Lang if necessary, and then evaluate a string argv[1]
 Usage from Unicon
     slang = loadfunc("./slang.so", "slang")
     x := slang("S-Lang statements;")
 The last result stacked by S-Lang is returned to Unicon
 Integer, Double, String and Array as List values allowed
*/
int slang(int argc, descriptor *argv) {
    static int slang_loaded = 0;

    int tos;
    int i, iv;
    double r;
    char *s, *slast = NULL;
    /* Limit to single dimension arrays for this version */
    word list;
    SLang_Array_Type *at;
    SLindex_Type ind;

    /* load slang, and all intrinsics */
    if (!slang_loaded) {
        if (-1 == SLang_init_all()) {
            /* Program malfunction */
#ifdef DEBUG
            fprintf(stderr, "Can't initialize S-Lang\n");
#endif
            Error(500);  
        } else {
            slang_loaded = 1;
        }
    }

    /* ensure argv[1] is a string */
    ArgString(1)

    /* evaluate argv[1] */
    if (-1 == SLang_load_string(StringVal(argv[1]))) {
        /* Reset S-Lang to allow later code attempts */
        SLang_restart(1);
        SLang_set_error(0);

        /* report invalid procedure type error to Unicon */
        Error(178);
    }
 
    tos = SLang_peek_at_stack();
    switch (tos) {
        case SLANG_INT_TYPE:
            /* return an integer to Unicon */
            SLang_pop_integer(&i);
            RetInteger(i);
            break;
        case SLANG_DOUBLE_TYPE:
            /* return a real to Unicon */
            SLang_pop_double(&r);
            RetReal(r);
            break;
        case SLANG_STRING_TYPE:
            /* return an allocated string to Unicon */
            /* memory allocation strategy; last string is freed */
            if (slast)  SLfree(slast);
            SLpop_string(&s);
            slast = s;
            RetString(s);
            break;
        case SLANG_ARRAY_TYPE:
	    /* return an array as a Unicon list */
            if (-1 == SLang_pop_array_of_type(&at, SLANG_DOUBLE_TYPE)) {
                /* report malfuntion */
                Error(500);
            }
            if (at->num_dims != 1) {
                /* report invalid value */
                Error(205);
            }
            double *doubles = malloc(sizeof(double) * at->num_elements);
            for (i = 0; i < at->num_elements; i++) {
                (void) SLang_get_array_element(at, &i, &r);
                doubles[i] = r;
            } 
            /* 
             mkRlist was defined as (int [], n) now (double [], n)
            */
            list = mkRlist(doubles, at->num_elements);
            
            /* *** unsure who owns the doubles input array *** */
            free(doubles);
            RetList(list);
            break;
        default:
#ifdef DEBUG
            fprintf(stderr, "Invalid S-Lang datatype %d\n", tos);
#endif
            /* report invalid value error to Unicon */
            Error(205);
    }
}
