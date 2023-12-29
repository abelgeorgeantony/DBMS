#include <iostream>
#include <filesystem>
#include "headers/db_structure.h"

namespace fs = std::filesystem;
namespace dbc = db_struct::create;

enum tokentypes
{
    KEYWORD = 299,
    OPERATOR = 300,
    IDENTIFIER = 301
};

struct token
{
    int type;
    std::string value;
};

std::string Keywords[] = {"CREATE", "SELECT", "UPDATE", "DELETE"};

void parseSQL(std::string &, std::vector<token> &);
bool executeSQL(std::vector<token> &);
void assign_tokentype(token &);

std::vector<token> parsedSQL;

int main()
{
    fs::path rootpath = "/home/abelgeorgeantony/abel_workspace/sideprojects/DBMS";
    std::string db_name = "DB_test";
    std::string table_name = "TABLE_test";
    
    dbc::db(rootpath, db_name);
    dbc::table(rootpath/db_name,table_name);
    dbc::column(rootpath/db_name/table_name,"column1");
    dbc::column(rootpath/db_name/table_name,"column2");
    dbc::column(rootpath/db_name/table_name,"column3");
    return(0);

    std::cout << "Enter SQL:\n";
    std::string SQLin;
    std::getline(std::cin, SQLin);
    parseSQL(SQLin, parsedSQL);
    std::cout << parsedSQL[0].value << "\n";
    std::cout << parsedSQL[1].value << "\n";
    std::cout << parsedSQL[2].value << "\n";
    return (0);
    if (executeSQL(parsedSQL))
    {
        std::cout << "SQL sent to execute\n";
    }
    else
    {
        std::cout << "SQL NOT sent to execute. SQL doesn't have logic\n";
    }
    return (0);
    //dbc::db(rootpath, db_name);
    return (0);
}

bool executeSQL(std::vector<token> &parsedSQL)
{
    if (parsedSQL[0].value == "create" || parsedSQL[0].value == "CREATE")
    {
        if (parsedSQL[1].value == "db" || parsedSQL[1].value == "DB")
        {
            ;
        }
    }
    return false;
}

void parseSQL(std::string &SQL, std::vector<token> &parse_storage)
{
    int sql_len = SQL.length();
    int sql_i = 0;
    int word_base = 0;
    int word_last;
    int parsecount = 0;

    while (sql_i < sql_len)
    {
        while ((SQL[sql_i] != ' ') && (sql_i < sql_len))
        {
            sql_i++;
        }
        word_last = sql_i - 1;

        token *temp_memory = new token;
        parse_storage.push_back(*temp_memory);
        for (int i = word_base; i <= word_last; i++)
        {
            parse_storage[parsecount].value = parse_storage[parsecount].value + SQL[i];
        }
        assign_tokentype(parse_storage[parsecount]);
        parsecount++;
        delete temp_memory;

        sql_i++;
        word_base = sql_i;
    }
}
void assign_tokentype(token &tokn)
{
    std::string str = tokn.value;
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    for (int i = 0; i < 4; i++)
    {
        if (str == Keywords[i])
        {
            tokn.type = KEYWORD;
            return;
        }
    }
}