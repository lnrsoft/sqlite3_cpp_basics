#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
  int i;
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

  rc = sqlite3_open("sqlite3_demo.db", &db);
  if (rc) {
    fprintf(stderr, "Failed open database: %s\n", sqlite3_errmsg(db));
    return (0);
  } else {
    fprintf(stdout, "Database successfully opened \n");
  }
  sql = "CREATE TABLE CANDIDATE("
        "ID INT PRIMARY KEY     NOT NULL,"
        "NAME           TEXT    NOT NULL,"
        "AGE            INT     NOT NULL,"
        "ROLE           TEXT    NOT NULL,"
        "SALARY         TEXT    NOT NULL);";
  rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  } else {
    fprintf(stdout, "Table successfully created \n");
  }
  sqlite3_close(db);
  return 0;
}
