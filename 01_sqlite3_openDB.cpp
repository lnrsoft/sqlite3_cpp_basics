#include <sqlite3.h>
#include <stdio.h>

int main() {
  sqlite3 *db;
  char *zErrMsg = 0;
  int rc;
  rc = sqlite3_open("sqlite_demo.db", &db);
  if (rc) {
    fprintf(stderr, "Failed open database: %s\n", sqlite3_errmsg(db));
    return (0);
  } else {
    fprintf(stderr, "Database successfully opened \n");
  }
  sqlite3_close(db);
}
