#include <iostream>
#include <filesystem>
#include "headers/db_structures.h"

namespace fs = std::filesystem;
namespace ok_to_build = db_struct::structure_buildchecking_functions;

bool exists_structure(const fs::path &, std::string);

bool ok_to_build::db(const fs::path &in_path, std::string with_name)
{
    fs::path db = in_path / with_name;

    if (exists_structure(db, "database.metadata"))
    {
        std::cerr << "A database with the same name already exists at '" << db << "'\n";
        return false;
    }
    if (fs::is_directory(db))
    {
        std::cerr << "A folder with same name already exists: '" << db << "'\nTry to rename the existing folder!\n";
        return false;
    }
    if (fs::is_directory(in_path))
    {
        if (fs::exists(in_path / "database.metadata"))
        {
            std::cerr << "Trying to create database inside an already existing database.\n'" << in_path << "' is a database\n";
            return false;
        }
    }
    return true;
}

bool ok_to_build::table(const fs::path &in_the_db, std::string with_name)
{
    fs::path table = in_the_db / with_name;

    if (exists_structure(table, "table.metadata"))
    {
        std::cerr << "A table with the same name already exists at '" << table << "'\n";
        return false;
    }
    if (fs::is_directory(table))
    {
        std::cout << "A folder with same name already exists at '" << table << "'\nTry to rename the existing folder!\n";
        return false;
    }

    if (!exists_structure(in_the_db, "database.metadata"))
    {
        std::cerr << "Trying to create table inside a directory that's not a database.\n'" << in_the_db << "' is not a database\n";
        return false;
    }
    if (exists_structure(in_the_db, "table.metadata"))
    {
        std::cerr << "Trying to create table inside another table.\n'" << in_the_db << "' is a table\n";
        return false;
    }

    return true;
}

bool ok_to_build::column(const fs::path &in_the_table, std::string with_name)
{
    fs::path column = in_the_table / with_name;

    if (exists_structure(column, "column.metadata"))
    {
        std::cerr << "A column with the same name already exists at '" << column << "'\n";
        return false;
    }
    if (fs::is_directory(column))
    {
        std::cout << "A folder with same name already exists at path '" << column << "'\nTry to rename the existing folder!\n";
        return false;
    }

    if (!exists_structure(in_the_table, "table.metadata"))
    {
        std::cerr << "Trying to create column inside a directory that's not a table.\n'" << in_the_table << "' is not a table\n";
        return false;
    }
    if (exists_structure(in_the_table, "column.metadata"))
    {
        std::cerr << "Trying to create column inside another column.\n'" << in_the_table << "' is a column\n";
        return false;
    }
    return true;
}

bool exists_structure(const fs::path &structurepath, std::string metafile)
{
    if ((fs::is_directory(structurepath)) && (fs::exists(structurepath / metafile)))
    {
        return true;
    }
    return false;
}