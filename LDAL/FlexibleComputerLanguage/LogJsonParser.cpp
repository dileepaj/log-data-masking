//
// Created by AfazD on 31-Oct-19.
//

#include "LogJsonParser.h"
#include "MemMan.h"
#include "Node.h"
#include "MetaData.h"
#include "Strings.h"
#include "Entity.h"
#include "easylogging++.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "json.hpp"

using json = nlohmann::json;

Node *LogJsonParser::LogJSONToNodeTree(std::string jsonString)
{
    int id=0;
    rapidjson::Document logs;
    logs.Parse(jsonString.c_str());
    Node *root = MemoryManager::Inst.CreateNode(++id);
    for(rapidjson::Value::ConstValueIterator itr = logs.Begin(); itr != logs.End(); ++itr){

        for(rapidjson::Value::ConstMemberIterator tps = itr->MemberBegin(); tps != itr->MemberEnd(); ++tps) {
            Node* currentNode=MemoryManager::Inst.CreateNode(++id);
            //std::cout << tps->name.GetString() << "\n";
            currentNode->SetValue((char *) tps->name.GetString());
            rapidjson::Value &jsonvalue = (rapidjson::Value &) (itr->GetObjectA()[tps->name.GetString()]);
            currentNode=LogJsonParser::LOGJSONToNodeTreeRecursively(jsonvalue,currentNode);
            root->AppendNode(currentNode);
        }

    }

    return root;
}

Node* LogJsonParser::LOGJSONToNodeTreeRecursively(rapidjson::Value &j,Node* parent){

    int id=0;
    for(rapidjson::Value::ConstMemberIterator data=j.MemberBegin(); data!=j.MemberEnd();data++){
        rapidjson::Value &jsonvalue = j[data->name.GetString()];
        if(jsonvalue.IsObject()){
            //std::cout<<"\t"<<data->name.GetString()<<"\n";
            Node *dataNode=MemoryManager::Inst.CreateNode(++id);
            dataNode->SetValue((char *) data->name.GetString());
            parent->AppendNode(dataNode);
            LOGJSONToNodeTreeRecursively(jsonvalue,dataNode);
        }
        else{
            //std::cout<<"\t not object : "<<data->name.GetString()<<"\n";
            Node *dataNode=MemoryManager::Inst.CreateNode(++id);
            dataNode->SetValue((char *) data->name.GetString());
            Node *valueNode=MemoryManager::Inst.CreateNode(++id);
            valueNode->SetValue(const_cast<PMCHAR>(data->value.GetString()));
            dataNode->AppendNode(valueNode);
            parent->AppendNode(dataNode);
        }
    }

    return parent;
}

void LogJsonParser::LogNodeTreetoJsonRecursivly(Node* root)
{
    MOFSTREAM newjsonfile;
    newjsonfile.open("../FlexibleComputerLanguage/maskedJSON.json");
    newjsonfile<<"[";
    LogJsonParser::PrintTreeToFileRecursivly(newjsonfile,root->GetFirstChild());
    newjsonfile<<"]";
}
void LogJsonParser::PrintTreeToFileRecursivly(MOFSTREAM &newjsonfile,PNODE node){
    Node* curr=node;
    Node* prev;
    newjsonfile<<"{";
    while(curr){
        MSTRING currNodeValue = curr->GetValue();
        if(currNodeValue=="Value"){
            json value= curr->GetValue();
            newjsonfile<<value<<_MSTR(:);
            value=curr->GetFirstChild()->GetValue();
            newjsonfile<<value;
            if(curr->GetParent()->GetRightSibling()!=NULL){
                newjsonfile<<"},";
            }
            else{
                newjsonfile<<"}";
            }
            return;
        }
        else{
            json value=curr->GetValue();
            newjsonfile<<value<<_MSTR(:);
            PrintTreeToFileRecursivly(newjsonfile,curr->GetFirstChild());
            prev=curr;
            curr=curr->GetRightSibling();
        }
    }
    if(prev->GetParent()->GetRightSibling()!=NULL){
        newjsonfile<<"},";
    }
    else{
        newjsonfile<<"}";
    }
}

void LogJsonParser::LogNodeTreetoLog(Node* root)
{
    MOFSTREAM newjsonfile;
    newjsonfile.open("../../Files/maskedLog.txt");
    LogJsonParser::PrintTreeToLog(newjsonfile,root->GetFirstChild());
}

void LogJsonParser::PrintTreeToLog(MOFSTREAM &newjsonfile,PNODE node){
    Node* curr=node;
    Node* prev;
    while(curr)
    {
        MSTRING currNodeValue = curr->GetValue();
        if(currNodeValue=="Value"){
            MSTRING value= curr->GetValue();
            value=curr->GetFirstChild()->GetValue();
            return;
        }
        else{
            MSTRING value=curr->GetValue();
            MSTRING substr = value.substr(0, 4);
            if(substr=="LINE")
            {
                MSTRING printvalue=curr->GetFirstChild()->GetFirstChild()->GetFirstChild()->GetValue();
                newjsonfile<<printvalue<<_MSTR(\n);
            }
            PrintTreeToLog(newjsonfile,curr->GetFirstChild());
            prev=curr;
            curr=curr->GetRightSibling();
        }
    }
}
