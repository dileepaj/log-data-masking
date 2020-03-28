//
// Created by AfazD on 02-Dec-19.
//

#ifndef FLEXIBLECOMPUTERLANGUAGE_MYSQLCONNECTOR_H
#define FLEXIBLECOMPUTERLANGUAGE_MYSQLCONNECTOR_H

#include <string>
#include "MemMan.h"
#include "DbConnection.h"

class MysqlConnector: public DbConnection {

public:
    virtual MYSQL* getConnection(MSTRING hostname,MSTRING username,MSTRING password,MSTRING dbname,int port);
    void insertQuery(MYSQL* conn);
    MSTRING selectPostalCode(MYSQL* conn,int id);
    int existsFirstNameMale(MYSQL* conn,MSTRING fname);
    int existsFirstNameFemale(MYSQL* conn,MSTRING fname);
    MSTRING selectFirstNameMale(MYSQL* conn,int id);
    MSTRING selectFirstNameFemale(MYSQL* conn,int id);
    MSTRING selectFirstNameUnisex(MYSQL* conn,int id);
    MSTRING selectLastName(MYSQL* conn,int id);
    MSTRING selectAddress(MYSQL* conn,int id);
    MSTRING selectCityCode(MYSQL* conn,int id);
};

#endif //FLEXIBLECOMPUTERLANGUAGE_MYSQLCONNECTOR_H
