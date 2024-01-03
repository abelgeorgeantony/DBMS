#include <iostream>
#include <filesystem>
#include "headers/db_structures.h"

namespace fs = std::filesystem;
namespace create = db_struct::structure_creating_functions;

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

void divideSQL(std::string &, std::vector<token> &);
bool executeSQL(std::vector<token> &);
void assign_tokentype(token &);

std::vector<token> dividedSQL;

int main()
{
    fs::path rootpath = "/home/abelgeorgeantony/abel_workspace/sideprojects/DBMS";
    std::string db_name = "DB_test";
    std::string table_name = "TABLE_test";
    
    create::db(rootpath, db_name);
    create::table(rootpath/db_name,table_name);
    create::column(rootpath/db_name/table_name,"column1");
    create::column(rootpath/db_name/table_name,"column2");
    create::column(rootpath/db_name/table_name,"column3");
    return(0);

    std::cout << "Enter SQL:\n";
    std::string SQLin;
    std::getline(std::cin, SQLin);
    divideSQL(SQLin, dividedSQL);
    std::cout << dividedSQL[0].value << "\n";
    std::cout << dividedSQL[1].value << "\n";
    std::cout << dividedSQL[2].value << "\n";
    return (0);
}

void divideSQL(std::string &SQL, std::vector<token> &parse_storage)
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