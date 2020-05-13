#ifndef __OBOTCHA_SQL_DATA_HPP__
#define __OBOTCHA_SQL_DATA_HPP__

#include <map>
#include "String.hpp"
#include "StrongPointer.hpp"
#include "Object.hpp"

namespace obotcha {

typedef void (*sql_data_set)(void *,char *); 
//using sql_data_set = void (*)(sp<Object>,char *); 

#define DECLARE_SQL_ASSIGNMENT(Table,Size) \
    public: static int isInit;\
    public: sql_data_set getSqlAssignment(int index,std::string col) { \
        if(Size <= index) { \
            return nullptr;\
        }\
        if(_##Table::funclist_##Table[index] != nullptr) { \
            return _##Table::funclist_##Table[index]; \
        }\
        if(_##Table::isInit == 0) { \
            _##Table::preInitialize();\
            _##Table::isInit = 1;\
        }\
        std::map<std::string,sql_data_set>::iterator ite = _##Table::funcmap.find(col);\
        if(ite != _##Table::funcmap.end()) { \
            _##Table::funclist_##Table[index] = ite->second;\
            return ite->second;\
        }\
        return nullptr;\
    }\
    public:SqlRecord createNewData() { \
        sp<_##Table> data = create##Table(); \
        return data;\
    }\

//table declare function start
#define DECLARE_TABLE_1(Table,X) \
    public:static std::map<std::string,sql_data_set> funcmap; \
    private:sql_data_set funclist_##Table[1];\
    public:static void preInitialize() { \
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#X,_##Table::set##X));\
    }\
    DECLARE_SQL_ASSIGNMENT(Table,1)

#define DECLARE_TABLE_2(Table,X,Y) \
    public:static std::map<std::string,sql_data_set> funcmap; \
    private:sql_data_set funclist_##Table[2];\
    public:static void preInitialize() { \
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#X,_##Table::set##X));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Y,_##Table::set##Y));\
    }\
    DECLARE_SQL_ASSIGNMENT(Table,2)

#define DECLARE_TABLE_3(Table,X,Y,Z) \
    public:static std::map<std::string,sql_data_set> funcmap; \
    private:sql_data_set funclist_##Table[3];\
    public:static void preInitialize() { \
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#X,_##Table::set##X));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Y,_##Table::set##Y));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Z,_##Table::set##Z));\
    }\
    DECLARE_SQL_ASSIGNMENT(Table,3)

#define DECLARE_TABLE_4(Table,X,Y,Z,X1) \
    public:static std::map<std::string,sql_data_set> funcmap; \
    private:sql_data_set funclist_##Table[4];\
    public:static void preInitialize() { \
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#X,_##Table::set##X));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Y,_##Table::set##Y));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Z,_##Table::set##Z));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#X1,_##Table::set##X1));\
    }\
    DECLARE_SQL_ASSIGNMENT(Table,4)

#define DECLARE_TABLE_5(Table,X,Y,Z,X1,Y1) \
    public:static std::map<std::string,sql_data_set> funcmap; \
    private:sql_data_set funclist_##Table[5];\
    public:static void preInitialize() { \
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#X,_##Table::set##X));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Y,_##Table::set##Y));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Z,_##Table::set##Z));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#X1,_##Table::set##X1));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Y1,_##Table::set##Y1));\
    }\
    DECLARE_SQL_ASSIGNMENT(Table,5)

#define DECLARE_TABLE_6(Table,X,Y,Z,X1,Y1,Z1) \
    public:static std::map<std::string,sql_data_set> funcmap; \
    private:sql_data_set funclist_##Table[6];\
    public:static void preInitialize() { \
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#X,_##Table::set##X));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Y,_##Table::set##Y));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Z,_##Table::set##Z));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#X1,_##Table::set##X1));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Y1,_##Table::set##Y1));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Z1,_##Table::set##Z1));\
    }\
    DECLARE_SQL_ASSIGNMENT(Table,6)

#define DECLARE_TABLE_7(Table,X,Y,Z,X1,Y1,Z1,X2) \
    public:static std::map<std::string,sql_data_set> funcmap; \
    private:sql_data_set funclist_##Table[7];\
    public:static void preInitialize() { \
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#X,_##Table::set##X));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Y,_##Table::set##Y));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Z,_##Table::set##Z));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#X1,_##Table::set##X1));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Y1,_##Table::set##Y1));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Z1,_##Table::set##Z1));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#X2,_##Table::set##X2));\
    }\
    DECLARE_SQL_ASSIGNMENT(Table,7)

#define DECLARE_TABLE_8(Table,X,Y,Z,X1,Y1,Z1,X2,Y2) \
    public:static std::map<std::string,sql_data_set> funcmap; \
    private:sql_data_set funclist_##Table[8];\
    public:static void preInitialize() { \
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#X,_##Table::set##X));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Y,_##Table::set##Y));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Z,_##Table::set##Z));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#X1,_##Table::set##X1));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Y1,_##Table::set##Y1));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Z1,_##Table::set##Z1));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#X2,_##Table::set##X2));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Y2,_##Table::set##Y2));\
    }\
    DECLARE_SQL_ASSIGNMENT(Table,8)

#define DECLARE_TABLE_9(Table,X,Y,Z,X1,Y1,Z1,X2,Y2,Z2) \
    public:static std::map<std::string,sql_data_set> funcmap; \
    private:sql_data_set funclist_##Table[9];\
    public:static void preInitialize() { \
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#X,_##Table::set##X));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Y,_##Table::set##Y));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Z,_##Table::set##Z));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#X1,_##Table::set##X1));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Y1,_##Table::set##Y1));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Z1,_##Table::set##Z1));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#X2,_##Table::set##X2));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Y2,_##Table::set##Y2));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Z2,_##Table::set##Z2));\
    }\
    DECLARE_SQL_ASSIGNMENT(Table,9)    

#define DECLARE_TABLE_10(Table,X,Y,Z,X1,Y1,Z1,X2,Y2,Z2,X3) \
    public:static std::map<std::string,sql_data_set> funcmap; \
    private:sql_data_set funclist_##Table[10];\
    public:static void preInitialize() { \
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#X,_##Table::set##X));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Y,_##Table::set##Y));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Z,_##Table::set##Z));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#X1,_##Table::set##X1));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Y1,_##Table::set##Y1));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Z1,_##Table::set##Z1));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#X2,_##Table::set##X2));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Y2,_##Table::set##Y2));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Z2,_##Table::set##Z2));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#X3,_##Table::set##X3));\
    }\
    DECLARE_SQL_ASSIGNMENT(Table,10)    

#define DECLARE_TABLE_11(Table,X,Y,Z,X1,Y1,Z1,X2,Y2,Z2,X3,Y3) \
    public:static std::map<std::string,sql_data_set> funcmap; \
    private:sql_data_set funclist_##Table[11];\
    public:static void preInitialize() { \
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#X,_##Table::set##X));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Y,_##Table::set##Y));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Z,_##Table::set##Z));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#X1,_##Table::set##X1));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Y1,_##Table::set##Y1));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Z1,_##Table::set##Z1));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#X2,_##Table::set##X2));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Y2,_##Table::set##Y2));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Z2,_##Table::set##Z2));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#X3,_##Table::set##X3));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Y3,_##Table::set##Y3));\
    }\
    DECLARE_SQL_ASSIGNMENT(Table,11)

#define DECLARE_TABLE_12(Table,X,Y,Z,X1,Y1,Z1,X2,Y2,Z2,X3,Y3,Z3) \
    public:static std::map<std::string,sql_data_set> funcmap; \
    private:sql_data_set funclist_##Table[12];\
    public:static void preInitialize() { \
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#X,_##Table::set##X));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Y,_##Table::set##Y));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Z,_##Table::set##Z));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#X1,_##Table::set##X1));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Y1,_##Table::set##Y1));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Z1,_##Table::set##Z1));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#X2,_##Table::set##X2));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Y2,_##Table::set##Y2));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Z2,_##Table::set##Z2));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#X3,_##Table::set##X3));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Y3,_##Table::set##Y3));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Z3,_##Table::set##Z3));\
    }\
    DECLARE_SQL_ASSIGNMENT(Table,12)   

#define DECLARE_TABLE_13(Table,X,Y,Z,X1,Y1,Z1,X2,Y2,Z2,X3,Y3,Z3,X4) \
    public:static std::map<std::string,sql_data_set> funcmap; \
    private:sql_data_set funclist_##Table[13];\
    public:static void preInitialize() { \
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#X,_##Table::set##X));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Y,_##Table::set##Y));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Z,_##Table::set##Z));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#X1,_##Table::set##X1));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Y1,_##Table::set##Y1));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Z1,_##Table::set##Z1));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#X2,_##Table::set##X2));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Y2,_##Table::set##Y2));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Z2,_##Table::set##Z2));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#X3,_##Table::set##X3));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Y3,_##Table::set##Y3));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Z3,_##Table::set##Z3));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#X4,_##Table::set##X4));\
    }\
    DECLARE_SQL_ASSIGNMENT(Table,13)       

#define DECLARE_TABLE_14(Table,X,Y,Z,X1,Y1,Z1,X2,Y2,Z2,X3,Y3,Z3,X4,Y4) \
    public:static std::map<std::string,sql_data_set> funcmap; \
    private:sql_data_set funclist_##Table[14];\
    public:static void preInitialize() { \
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#X,_##Table::set##X));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Y,_##Table::set##Y));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Z,_##Table::set##Z));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#X1,_##Table::set##X1));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Y1,_##Table::set##Y1));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Z1,_##Table::set##Z1));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#X2,_##Table::set##X2));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Y2,_##Table::set##Y2));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Z2,_##Table::set##Z2));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#X3,_##Table::set##X3));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Y3,_##Table::set##Y3));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Z3,_##Table::set##Z3));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#X4,_##Table::set##X4));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Y4,_##Table::set##Y4));\
    }\
    DECLARE_SQL_ASSIGNMENT(Table,14)

#define DECLARE_TABLE_15(Table,X,Y,Z,X1,Y1,Z1,X2,Y2,Z2,X3,Y3,Z3,X4,Y4,Z4) \
    public:static std::map<std::string,sql_data_set> funcmap; \
    private:sql_data_set funclist_##Table[15];\
    public:static void preInitialize() { \
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#X,_##Table::set##X));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Y,_##Table::set##Y));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Z,_##Table::set##Z));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#X1,_##Table::set##X1));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Y1,_##Table::set##Y1));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Z1,_##Table::set##Z1));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#X2,_##Table::set##X2));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Y2,_##Table::set##Y2));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Z2,_##Table::set##Z2));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#X3,_##Table::set##X3));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Y3,_##Table::set##Y3));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Z3,_##Table::set##Z3));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#X4,_##Table::set##X4));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Y4,_##Table::set##Y4));\
        _##Table::funcmap.insert(std::pair<std::string,sql_data_set>(#Z4,_##Table::set##Z4));\
    }\
    DECLARE_SQL_ASSIGNMENT(Table,15)        
//table declare function end

#define PUBLISH_TABLE(Table) \
    std::map<std::string,sql_data_set> _##Table::funcmap;\
    int _##Table::isInit = 0;\
    DECLARE_SIMPLE_CLASS(Build##Table) IMPLEMENTS(SqlRecordBuilder){ \
        public :SqlRecord create() { \
            sp<_##Table> data;\
            _##Table *t = new _##Table();\
            data.set_pointer(t);\
            return data;\
        }\
    };\

#define DECLARE_INT_DATA_MEMBER(Table,Member) \
    private:int Member; \
    public: int get##Member() {return Member;} \
    public: void set##Member(int v) {\
        Member = v;\
    } \
    public: static void set##Member(void *t,char *v) { \
        _##Table* _t = (_##Table *)t;\
        _t->Member = atoi(v);\
    }\

#define DECLARE_STRING_DATA_MEMBER(Table,Member) \
    private:String Member; \
    public: String get##Member() {return Member;} \
    public: void set##Member(String v) {\
        Member = v;\
    } \
    public: static void set##Member(void *t,char *v) { \
        _##Table* _t = (_##Table *)t;\
        _t->Member = createString(v);\
    }\

#define DECLARE_FLOAT_DATA_MEMBER(Table,Member) \
    private:float Member; \
    public: float get##Member() {return Member;} \
    public: void set##Member(float v) {Member = v;} \
    public: void set##Member(void *t,char *v) { \
        _##Table* _t = (_##Table *)t;\
        char* pEnd; \
        _t->Member = strtof (v, &pEnd); \
    }\

DECLARE_SIMPLE_CLASS(SqlRecord) {
public:
    //virtual SqlRecord createNewData() = 0;
    virtual sql_data_set getSqlAssignment(int index,std::string col) = 0;
};

DECLARE_SIMPLE_CLASS(SqlRecordBuilder) {
public:
    virtual SqlRecord create() = 0;
};

#define RECORD_BUILDER(X) createBuild##X()

}

#endif