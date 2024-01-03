#include <iostream>
#include <bits/stdc++.h>

namespace fs = std::filesystem;

namespace db_struct
{
    struct data
    {
        int integer_v;
        char character_v;
    };

    struct column
    {
        std::string name;
        std::string datatype;
        std::vector<data> rows;
        int lastindex;
    };

    struct table
    {
        std::string name;
        std::vector<column> cols;
    };

    struct database
    {
        std::string name;
        std::string relativefilepath;
        std::string globalfilepath;
        std::vector<table> tables;
    };

    namespace structure_creating_functions
    {
        bool db(const fs::path &, std::string);

        bool table(const fs::path &, std::string);

        bool column(const fs::path &, std::string);
    }
    namespace structure_buildchecking_functions
    {
        bool db(const fs::path &, std::string);
        bool table(const fs::path &, std::string);
        bool column(const fs::path &, std::string);
    }
}
