#include<iostream>
#include <filesystem>
#include "headers/db_structure.h"

namespace fs = std::filesystem;

void parseSQL(std::string &,std::vector<std::string> &);



std::vector<std::string> parsedSQL;

int main()
{
    fs::path rootpath = "/home/abelgeorgeantony/abel_workspace/sideprojects/DBMS";
    std::string db_name;

    std::cout<<"Enter SQL:\n";
    std::string SQLin;
    std::getline(std::cin,SQLin);
    parseSQL(SQLin,parsedSQL);
    return(0);
    db_struct::create_db(rootpath,db_name);
    return(0);
}

void executeSQL()
{
    if(parsedSQL[0] == "create" || parsedSQL[0] == "CREATE")
    {
        if(parsedSQL[1] == "db" || parsedSQL[1] == "DB")
        {
            ;
        }
    }
}

void parseSQL(std::string &SQL, std::vector<std::string> &parsestorage)
{
    int sql_len = SQL.length();
    std::cout<<sql_len<<"\n";
    int sql_iter = 0;
    int word_base = 0;
    int word_last;
    int parsecount=0;

    while(sql_iter < sql_len)
    {
        while((SQL[sql_iter] != ' ') && (sql_iter < sql_len))
        {
            sql_iter++;
        }
        word_last = sql_iter - 1;

        parsestorage.push_back("");
        for(int i = word_base; i <= word_last;i++)
        {
            parsestorage[parsecount] = parsestorage[parsecount] + SQL[i];
        }
        parsecount++;

        sql_iter++;
        word_base = sql_iter;
    }
}