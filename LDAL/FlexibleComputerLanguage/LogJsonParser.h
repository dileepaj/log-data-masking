//
// Created by AfazD on 31-Oct-19.
//

#ifndef FLEXIBLECOMPUTERLANGUAGE_LOGJSONPARSER_H
#define FLEXIBLECOMPUTERLANGUAGE_LOGJSONPARSER_H

#include "CommonIncludes.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
class LogJsonParser {
public:
    static Node *LogJSONToNodeTree(std::string otpsString);
    static Node *LOGJSONToNodeTreeRecursively(rapidjson::Value& j,PNODE parent);
    static void LogNodeTreetoJsonRecursivly(PNODE root);
    static void PrintTreeToFileRecursivly(MOFSTREAM &newjsonfile,PNODE node);
    static void LogNodeTreetoLog(PNODE root);
    static void PrintTreeToLog(MOFSTREAM &newjsonfile,PNODE node);
};


#endif //FLEXIBLECOMPUTERLANGUAGE_LOGJSONPARSER_H
