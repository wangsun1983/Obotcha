#ifndef __SQL_DATA_HPP__
#define __SQL_DATA_HPP__

#include <map>
#include "String.hpp"
#include "StrongPointer.hpp"
#include "Object.hpp"

namespace obotcha {

typedef void (*sql_data_set)(void *,char *); 
//using sql_data_set = void (*)(sp<Object>,char *); 

#define DECLARE_SQL_ASSIGNMENT(Table) \
    public:static int isInit;\
    public: sql_data_set getSqlAssignment(int index,std::string col) { \
        printf("get trace1 \n");\
        if(_##Table::funclist_##Table[index] != nullptr) { \
            printf("get trace2 \n");\
            return _##Table::funclist_##Table[index]; \
        }\
        if(_##Table::isInit == 0) { \
            _##Table::preInitialize();\
            _##Table::isInit = 1;\
        }\
        std::map<std::string,sql_data_set>::iterator ite = _##Table::funcmap_##Table.find(col);\
        printf("get trace3 \n");\
        if(ite != _##Table::funcmap_##Table.end()) { \
            _##Table::funclist_##Table[index] = ite->second;\
            printf("get trace4 \n");\
            return ite->second;\
        }\
        printf("get trace4 \n");\
        return nullptr;\
    }\


#define DECLARE_TABLE(Table,X) \
    public:static std::map<std::string,sql_data_set> funcmap_##Table; \
    private:sql_data_set funclist_##Table[1];\
    public:static void preInitialize() { \
        _##Table::funcmap_##Table.insert(std::pair<std::string,sql_data_set>(#X,_##Table::set##X));\
    }\
    DECLARE_SQL_ASSIGNMENT(Table)


#define PUBLISH_TABLE(Table) \
    int _##Table::isInit = 0; \
    std::map<std::string,sql_data_set> _##Table::funcmap_##Table;\


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

#define DECLARE_STRING_DATA_MEMBER(Index,Member) \
    private:String Member; \
    public: String get##Member() {return Member;} \
    public: void set##Member(String v) {Member = v;} \
    public: void set##Member(char *v) { \
        Member = createString(v); \
    }\

#define DECLARE_FLOAT_DATA_MEMBER(Index,Member) \
    private:float Member; \
    public: float get##Member() {return Member;} \
    public: void set##Member(float v) {Member = v;} \
    public: void set##Member(char *v) { \
        char* pEnd; \
        Member = strtof (v, &pEnd); \
    }\

}
#endif