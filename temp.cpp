
#include <sqlite3.h>
#include <bits/stdc++.h>
#include "header.h"
sqlite3 *DB;
string add;

static int callback(void *data, int argc, char **argv, char **azColName)
{
    int i;
    fprintf(stderr, "%s: ", (const char *)data);

    for (i = 0; i < argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    //string query = "UPDATE ADDRESS FROM PERSON WHERE ID=2";
    //sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);
    printf("\n");
    return 0;
}

static int addTransaction(void *data, int argc, char **argv, char **azColName)
{
    int n = strlen(argv[0]) + add.size() + 1;
    int sss = strlen(argv[0]);
    argv[0]="fse";
    //cout << argv[0] << " " << strlen(argv[0]) << endl;
    //char *tmp = (argv[0] + (strlen(argv[0])));
    //tmp = (char *)malloc(sizeof(char) * n);
    //char *tmp=argv[0];
    //argv[0]=(char*)realloc(tmp,sizeof(char)*n);
    //for (int i = strlen(argv[0]); i < n - 1; ++i)
      //  argv[0][i] = add[i - sss];
    string sql = "UPDATE  set SALARY = 25000.00 where ID=1; " \
         "SELECT * from COMPANY";
    char *mssg = 0;
   /* Execute SQL statement */
   int rc = sqlite3_exec(DB, sql, callback, (void*)data, &mssg);
   
   if( rc != SQLITE_OK ) {
      fprintf(stderr, "SQL error: %s\n", mssg);
      sqlite3_free(mssg);
   } else {
      fprintf(stdout, "Operation done successfully\n");
   }
    cout << argv[0] << endl;
    return 0;
}



int main()
{

    char *messaggeError;
    int exit = sqlite3_open("example.db", &DB);
    string query = "SELECT ADDRESS FROM PERSON WHERE ID=2;";
    add = "ygbygbn";
    sqlite3_exec(DB, query.c_str(), addTransaction, NULL, NULL);
    sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);
    //cout << "STATE OF TABLE BEFORE INSERT" << endl;

    return (0);
}