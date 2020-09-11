#ifndef __OBOTCHA_SQL_DATA_HPP__
#define __OBOTCHA_SQL_DATA_HPP__

#include <map>
#include "String.hpp"
#include "StrongPointer.hpp"
#include "Object.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(SqlConnection,1) {

public:
    _SqlConnection(T t);

    template<typename Q>
    ArrayList<Q> query(String sql) {
        //TODO
        //return mClient->query<Q>(sql);
    }

    int exec(String sql) {
        return mClient->exec();
    }

    int close() {
        return mClient->close();
    }

    int startTransaction() {
        return mClient->startTransaction();
    }

    int commitTransaction() {
        return mClient->commitTransaction();
    }

    int rollabckTransaction() {
        return mClient->rollabckTransaction();
    }


private:
    T mClient;

};

}

#endif