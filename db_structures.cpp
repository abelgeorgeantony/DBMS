#include <iostream>
#include <filesystem>
#include <fstream>
#include "headers/db_structures.h"

namespace fs = std::filesystem;
namespace create = db_struct::structure_creating_functions;
namespace ok_to_build = db_struct::structure_buildchecking_functions;

bool createDirectory(const fs::path &);
bool createFile(const fs::path &);

bool create_dbmetafile(const fs::path &);
bool create_tablemetafile(const fs::path &);
bool create_columnmetafile(const fs::path &);

bool create::db(const fs::path &in_path, std::string with_name)
{
    if (ok_to_build::db(in_path, with_name))
    {
        fs::path dbPath = in_path / with_name;
        createDirectory(dbPath);
        create_dbmetafile(dbPath);
        return true;
    }

    return false;
}

bool create::table(const fs::path &in_the_db, std::string with_name)
{
    if (ok_to_build::table(in_the_db, with_name))
    {
        fs::path table = in_the_db / with_name;
        createDirectory(table);
        create_tablemetafile(table);
        return true;
    }

    return false;
}

bool create::column(const fs::path &in_the_table, std::string with_name)
{
    if (ok_to_build::column(in_the_table, with_name))
    {
        fs::path column = in_the_table / with_name;
        createDirectory(column);
        create_columnmetafile(column);
        fs::path filePath = column / "rows.data";
        createFile(filePath);
        return true;
    }

    return false;
}

bool create_dbmetafile(const fs::path &db_path)
{
    fs::path filePath = db_path / "database.metadata";
    createFile(filePath);
    std::ofstream file(filePath);
    if (file.is_open())
    {
        file << "Name of the database\n";
        file << filePath.parent_path().filename();
        return true;
    }
    return false;
}
bool create_tablemetafile(const fs::path &table_path)
{
    fs::path filePath = table_path / "table.metadata";
    createFile(filePath);
    std::ofstream file(filePath);
    if (file.is_open())
    {
        file << "Name of the table\n";
        file << filePath.parent_path().filename();
        return true;
    }
    return false;
}
bool create_columnmetafile(const fs::path &column_path)
{
    fs::path filePath = column_path / "column.metadata";
    createFile(filePath);
    std::ofstream file(filePath);
    if (file.is_open())
    {
        file << "Name of the column\n";
        file << filePath.parent_path().filename();
        return true;
    }
    return false;
}

bool createDirectory(const fs::path &fullPath)
{
    if (!fs::create_directories(fullPath))
    {
        std::cerr << "Error creating directory '" << fullPath << "'\n";
        return false;
    }
    std::cout << "Directory " << fullPath.filename() << " created successfully\npath " << fullPath << "\n\n";
    return true;
}
bool createFile(const fs::path &fullPath)
{
    std::ofstream file(fullPath);
    if (!file.is_open())
    {
        std::cerr << "Error creating file '" << fullPath << "'\n";
        return false;
    }

    std::cout << "File " << fullPath.filename() << " created successfully\npath " << fullPath << "\n\n";
    return true;
}