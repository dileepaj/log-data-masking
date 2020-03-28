//
// Created by AfazD on 14-Nov-19.
//

#include <string>
#include <Node.h>
#include <DefFileReader.h>
#include <ScriptReader.h>
#include <ExecutionContext.h>
#include "QueryExecuter.h"
#include "ResultGenerator.h"

// shared data
int id = 0;
MSTRING QueryExecuter::run(Node *root, MSTRING querycode)
{

    DefFileReader dfr;
    MetaData *pMD = dfr.Read("../FlexibleComputerLanguage/Defs.txt");
    //MetaData *pMD = dfr.Read("../FlexibleComputerLanguage/testDefs.txt");
    ScriptReader sr;
    ScriptReaderOutput op;
    //bool bSucc = sr.ProcessScript(pMD->s_RuleFileName, pMD, op);
    bool bSucc = sr.ProcessScript(pMD, op, querycode);
    if (!bSucc)
    {
        std::wcout << "\nFailed to read script\n";
    }
    ExecutionContext ec;
    ec.p_mapFunctions = &op.map_Functions;
    ec.p_MD = pMD;
    Node *pY = MemoryManager::Inst.CreateNode(++id);
    Node *dbConn = MemoryManager::Inst.CreateNode(++id);
    Node *fName = MemoryManager::Inst.CreateNode(++id);
    Node *lName = MemoryManager::Inst.CreateNode(++id);
    Node *fullName = MemoryManager::Inst.CreateNode(++id);
    Node *date = MemoryManager::Inst.CreateNode(++id);
    Node *month = MemoryManager::Inst.CreateNode(++id);
    Node *year = MemoryManager::Inst.CreateNode(++id);
    Node *hour = MemoryManager::Inst.CreateNode(++id);
    Node *minute = MemoryManager::Inst.CreateNode(++id);
    Node *seconds = MemoryManager::Inst.CreateNode(++id);
    Node *telNum = MemoryManager::Inst.CreateNode(++id);
    Node *address = MemoryManager::Inst.CreateNode(++id);
    Node *postalCode = MemoryManager::Inst.CreateNode(++id);
    Node *integer = MemoryManager::Inst.CreateNode(++id);
    Node *price = MemoryManager::Inst.CreateNode(++id);
    Node *nic = MemoryManager::Inst.CreateNode(++id);
    Node *email = MemoryManager::Inst.CreateNode(++id);
    Node *pRESULT = MemoryManager::Inst.CreateNode(++id);


    std::string s = "52";
    std::string fname = "FIRST_NAME";
    std::string lname = "LAST_NAME";
    std::string fullname = "FULL_NAME";
    std::string date_ = "DATE";
    std::string month_ = "MONTH";
    std::string year_ = "YEAR";
    std::string hour_ = "HOUR";
    std::string minute_ = "MINUTE";
    std::string seconds_ = "SECONDS";
    std::string telnum = "TELEPHONE_NUMBER";
    std::string address_ = "ADDRESS";
    std::string postalcode = "POSTAL_CODE";
    std::string integer_ = "INTEGER";
    std::string price_ = "PRICE";
    std::string nic_ = "NIC";
    std::string email_ = "EMAIL";

    root->SetValue((char *)s.c_str());
    fName->SetValue((char *)fname.c_str());
    lName->SetValue((char *)lname.c_str());
    fullName->SetValue((char *)fullname.c_str());
    date->SetValue((char *)date_.c_str());
    month->SetValue((char *)month_.c_str());
    year->SetValue((char *)year_.c_str());
    hour->SetValue((char *)hour_.c_str());
    minute->SetValue((char *)minute_.c_str());
    seconds->SetValue((char *)seconds_.c_str());
    telNum->SetValue((char *)telnum.c_str());
    address->SetValue((char *)address_.c_str());
    postalCode->SetValue((char *)postalcode.c_str());
    integer->SetValue((char *)integer_.c_str());
    price->SetValue((char *)price_.c_str());
    nic->SetValue((char *)nic_.c_str());
    email->SetValue((char *)email_.c_str());

    ec.map_Var["X"] = root;
    ec.map_Var["Y"] = pY;
    ec.map_Var["DB_CONNECTION_STRING"] = dbConn;
    ec.map_Var["FIRST_NAME"] = fName;
    ec.map_Var["LAST_NAME"] = lName;
    ec.map_Var["FULL_NAME"] = fullName;
    ec.map_Var["DATE"] = date;
    ec.map_Var["MONTH"] = month;
    ec.map_Var["YEAR"] = year;
    ec.map_Var["HOUR"] = hour;
    ec.map_Var["MINUTE"] = minute;
    ec.map_Var["SECONDS"] = seconds;
    ec.map_Var["TELEPHONE_NUMBER"] = telNum;
    ec.map_Var["ADDRESS"] = address;
    ec.map_Var["POSTAL_CODE"] = postalCode;
    ec.map_Var["INTEGER"] = integer;
    ec.map_Var["PRICE"] = price;
    ec.map_Var["NIC"] = nic;
    ec.map_Var["EMAIL"] = email;
    ec.map_Var["RESULT"] = pRESULT;
    op.p_ETL->Execute(&ec);

    return ResultGenerator::CreateResult(pRESULT);

}
