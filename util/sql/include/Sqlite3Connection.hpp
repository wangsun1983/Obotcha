#ifndef __OBOTCHA_SQLITE3_CONNECTION_H__
#define __OBOTCHA_SQLITE3_CONNECTION_H__

#include "sqlite3.h"
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "SqlConnection.hpp"
#include "HashMap.hpp"
#include "ArrayList.hpp"

namespace obotcha {

enum Sqlite3FailReason {
    Sqlite3FailWrongParam = 200,
    Sqlite3FailOpen,
    Sqlite3FailNoDb,
    Sqlite3FailExecErr,
    Sqlite3FailQueryErr,
    Sqlite3FailTransactionErr,
};

struct SqliteQueryParam {
    SqlRecordBuilder r;
    ArrayList<SqlRecord> l;
};

DECLARE_SIMPLE_CLASS(Sqlite3Connection) IMPLEMENTS(SqlConnection){

public:
    int connect(HashMap<String,String>args);

    ArrayList<SqlRecord> query(String,SqlRecordBuilder);

    int exec(String);

    int close();

    int startTransaction();

    int commitTransaction();

    int rollabckTransaction();

    static String SQLITE3_CONNECT_TAG_PATH;

private:
    static int sqlQueryCallback(void *ctx, int argc, char *argv[], char *col[]);

    sqlite3 *mSqlDb;

    String mPath;
};

}

#endif