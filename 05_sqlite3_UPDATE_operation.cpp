#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>

static int callback(void *data, int argc, char **argv, char **azColName) {
  int i;
  fprintf(stderr, "%s: ", (const char *)data);
  for (i = 0; i < argc; i++) {
    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  printf("\n");
  return 0;
}

int main() {
  sqlite3 *db;
  char *zErrMsg = 0;
  int rc;
  const char *sql;
  const char *data = "Callback function call";
  rc = sqlite3_open("sqlite3_demo.db", &db);
  if (rc) {
    fprintf(stderr, "Failed open database: %s\n", sqlite3_errmsg(db));
    return (0);
  } else {
    fprintf(stderr, "Database successfully opened \n\n");
  }
  sql = "UPDATE CANDIDATE set SALARY = 150000 where ID=1; "
        "SELECT * from CANDIDATE";
  rc = sqlite3_exec(db, sql, callback, (void *)data, &zErrMsg);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  } else {
    fprintf(stdout, "Execution completed successfully \n");
  }
  sqlite3_close(db);
  return 0;
}
