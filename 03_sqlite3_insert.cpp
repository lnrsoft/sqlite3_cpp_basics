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

int main(int argc, char *argv[]) {
  sqlite3 *db;
  char *zErrMsg = 0;
  int rc;
  const char *sql;

  rc = sqlite3_open("sqlite3_demo.db", &db);

  if (rc) {
    fprintf(stderr, "Failed open database: %s\n", sqlite3_errmsg(db));
    return (0);
  } else {
    fprintf(stderr, "Database successfully opened \n");
  }

  sql = "INSERT INTO CANDIDATE (ID,NAME,AGE,ROLE,SALARY) "
        "VALUES (1, 'Daniel', 29, 'CCO', 130000 ); "
        "INSERT INTO CANDIDATE (ID,NAME,AGE,ROLE,SALARY) "
        "VALUES (2, 'Roland', 35, 'CTO', 175000 ); "
        "INSERT INTO CANDIDATE (ID,NAME,AGE,ROLE,SALARY)"
        "VALUES (3, 'Leslie', 33, 'CEO', 200000 );";

  rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

  if (rc != SQLITE_OK) {
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  } else {
    fprintf(stdout, "Records created successfully\n");
  }
  sqlite3_close(db);
  return 0;
}
