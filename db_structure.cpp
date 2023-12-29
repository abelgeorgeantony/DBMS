#include <iostream>
#include <filesystem>
#include <fstream>
#include "headers/db_structure.h"

namespace fs = std::filesystem;
namespace dbc = db_struct::create;

bool createDirectory(const fs::path &);
bool createFile(const fs::path &);

bool dbc::db(const fs::path &, std::string);
bool dbc::dbmetafile(const fs::path &);
bool dbc::table(const fs::path &, std::string);
bool dbc::tablemetafile(const fs::path &);
bool dbc::column(const fs::path &, std::string);
bool dbc::columnmetafile(const fs::path &);

bool dbc::db(const fs::path &in_path, std::string with_name)
{
    fs::path dbPath = in_path / with_name;

    if (fs::is_directory(dbPath))
    {
        if (fs::exists(dbPath / "database.metadata"))
        {
            std::cerr << "A database with the same name already exists at '" << dbPath << "'\n";
            return false;
        }
        std::cout << "A folder with same name already exists at path '" << dbPath << "'\nTry to rename the existing folder!\n";
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

    createDirectory(dbPath);
    dbc::dbmetafile(dbPath);
    return true;
}
bool dbc::dbmetafile(const fs::path &db_path)
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

bool dbc::table(const fs::path &db_path, std::string with_name)
{
    fs::path tablePath = db_path / with_name;

    if (fs::is_directory(tablePath))
    {
        if (fs::exists(tablePath / "table.metadata"))
        {
            std::cerr << "A table with the same name already exists at '" << tablePath << "'\n";
            return false;
        }
        std::cout << "A folder with same name already exists at path '" << tablePath << "'\nTry to rename the existing folder!\n";
        return false;
    }

    if (fs::is_directory(db_path))
    {
        if(!fs::exists(db_path / "database.metadata"))
        {
            std::cerr << "Trying to create table inside a directory that's not a database.\n'" << db_path << "' is not a database\n";
            return false;
        }
        if (fs::exists(db_path / "table.metadata"))
        {
            std::cerr << "Trying to create table inside another table.\n'" << db_path << "' is a table\n";
            return false;
        }
    }

    createDirectory(tablePath);
    dbc::tablemetafile(tablePath);
    return true;
}
bool dbc::tablemetafile(const fs::path &table_path)
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

bool dbc::column(const fs::path &table_path, std::string with_name)
{
    fs::path columnPath = table_path / with_name;

    if (fs::is_directory(columnPath))
    {
        if (fs::exists(columnPath / "column.metadata"))
        {
            std::cerr << "A column with the same name already exists at '" << columnPath << "'\n";
            return false;
        }
        std::cout << "A folder with same name already exists at path '" << columnPath << "'\nTry to rename the existing folder!\n";
        return false;
    }

    if (fs::is_directory(table_path))
    {
        if(!fs::exists(table_path / "table.metadata"))
        {
            std::cerr << "Trying to create column inside a directory that's not a table.\n'" << table_path << "' is not a table\n";
            return false;
        }
        if (fs::exists(table_path / "column.metadata"))
        {
            std::cerr << "Trying to create column inside another column.\n'" << table_path << "' is a column\n";
            return false;
        }
    }

    createDirectory(columnPath);
    dbc::columnmetafile(columnPath);
    return true;
}
bool dbc::columnmetafile(const fs::path &column_path)
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