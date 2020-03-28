//
//  main.cpp
//  FlexibleComputerLanguage
//
//  Created by Dileepa Jayathilaka on 5/8/18.
//  Copyright (c) 2018 Dileepa Jayathilaka. All rights reserved.
//
// VERSION 2

#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "json.hpp"
#include "MemMan.h"
#include "Node.h"
#include "MetaData.h"
#include "ExecutionTemplateList.h"
#include "ExecutionContext.h"
#include "TestCaseExecuter.h"
#include "Int.h"
#include "LogJsonParser.h"
#include "easylogging++.h"
#include <iostream>
#include <memory>
#include <pthread.h>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "QueryExecuter.h"
#include "CPlusPlusEntry.h"

using namespace rapidjson;
using json = nlohmann::json;

INITIALIZE_EASYLOGGINGPP

int main(int argc, const char * argv[])
{
    //onvert the log file to the node tree structure
    CPlusPlusEntry cppEntry;
    cppEntry.RunDefault();

    std::cout<<"Log analyzer masking started\n";
    std::string line;
    std::string jsonline;

    std::ifstream jsonfile ("../FlexibleComputerLanguage/resultJSON.json");

    if (jsonfile.is_open())
    {
        getline (jsonfile,line);
        jsonline = line;
        jsonfile.close();
    }

    Node* jsonroot = LogJsonParser::LogJSONToNodeTree(jsonline);

     std::string scriptline;
     std::ifstream scriptfile ("../../Files/maskingScript.txt");
     std::string script="";

     while(getline(scriptfile,scriptline))
     {
         script+=scriptline;
         script+="\n";
     }
     //Execute the query for masking
     std::string res = QueryExecuter::run(jsonroot,script);
     //std::cout<<res<<"\n";

     LogJsonParser::LogNodeTreetoJsonRecursivly(jsonroot);

    //Convert the masked node tree to the masked log file 
    LogJsonParser::LogNodeTreetoLog(jsonroot);

    std::cout<<"\n\nLog File Masked Successfully";

     std::cout<<"\n\nPress Enter To Exit";
     std::getchar();


    return 0;
}
