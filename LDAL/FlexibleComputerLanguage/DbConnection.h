//
// Created by AFAZD on 25-Nov-19.
//

#ifndef FLEXIBLECOMPUTERLANGUAGE_DBCONNECTION_H
#define FLEXIBLECOMPUTERLANGUAGE_DBCONNECTION_H

#include <string>
#include "MemMan.h"
#include <mysql.h>

class DbConnection {
public:
    virtual MYSQL* getConnection(MSTRING hostname,MSTRING username,MSTRING password,MSTRING dbname,int port)=0;

};
#endif //FLEXIBLECOMPUTERLANGUAGE_DBCONNECTION_H
