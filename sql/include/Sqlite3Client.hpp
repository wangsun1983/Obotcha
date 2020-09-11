#ifndef __OBOTCHA_SQLITE3_CLIENT_H__
#define __OBOTCHA_SQLITE3_CLIENT_H__

#include "sqlite3.h"
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "SqlConnection.hpp"
#include "HashMap.hpp"
#include "ArrayList.hpp"
#include "Reflect.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(Sqlite3Client) {

public:
    int connect(HashMap<String, String> args);
    template <typename T>
    void createObject(sp<T> & value) {
        T *data = new T();
        value.set_pointer(data);
    }

    template <typename T>
    ArrayList<T> query(String sql) {
        char **dbResult;
        int nRow, nColumn;
        char *errmsg = NULL;
        ArrayList<T> reslut = createArrayList<T>();
        int result = sqlite3_get_table(mSqlDb, sql->toChars(), &dbResult, &nRow, &nColumn, &errmsg);
        if (SQLITE_OK == result) {
            int index = nColumn;
            for (int i = 0; i < nRow; i++) {
                //printf( “第 %d 条记录\n”, i);
                T data;
                createObject(data);
                for (int j = 0; j < nColumn; j++) {
                    //printf( “字段名:%s ?> 字段值:%s\n”, dbResult[j], dbResult [index] );
                    //Field field = data->get
                    index++;
                    // dbResult 的字段值是连续的，从第0索引到第 nColumn - 1索引都是字段名称，
                    //从第 nColumn 索引开始，后面都是字段值，它把一个二维的表（传统的行列表示法）用一个扁平的形式来表示
                }
            }
        }
    }

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

} // namespace obotcha
#endif