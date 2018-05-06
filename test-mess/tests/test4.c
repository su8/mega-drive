/* #include <stdio.h> */
/* #include <sqlite3.h> */ 

/* int main(int argc, char* argv[]) { */
/*    sqlite3 *db; */
/*    char *zErrMsg = 0; */
/*    int rc; */

/*    rc = sqlite3_open("test.db", &db); */

/*    if( rc ) { */
/*       fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db)); */
/*       return(0); */
/*    } else { */
/*       fprintf(stderr, "Opened database successfully\n"); */
/*    } */
/*    sqlite3_close(db); */
/* } */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h> 

static int callback(void *buf, int count, char **data, char **columns){
  size_t len = (size_t)count * 200;
  char *buf2 = (char *)malloc(len);
  char *all = buf2;
   for(int i = 0; i<count; i++){
      all += snprintf(all, len - 1, "%s = %s ", columns[i], (data[i] ? data[i] : "NULL"));
   }
   
   *(--all) = '\0';

   snprintf(buf, 199, "%s", buf2);
   free(buf2);
   return 0;
}

int main(void) {
   sqlite3 *db = NULL;
   char buf[200] = "empty";
   char *errmsg = "empty";
   char *sql = "SELECT * from COMPANY where ID=1";

   /* Open database */
   if( sqlite3_open_v2("test.db", &db, SQLITE_OPEN_READONLY, NULL) ) {
      fprintf(stderr, "%s\n", sqlite3_errmsg(db));
      return(-1);
   }

   /* Execute SQL statement */
   if( SQLITE_OK != sqlite3_exec(db, sql, callback, buf, &errmsg)) {
      fprintf(stderr, "SQL error: %s\n", errmsg);
   }
   printf("%s\n", buf);

   sqlite3_free(errmsg);
   sqlite3_close_v2(db);
   return 0;
}
