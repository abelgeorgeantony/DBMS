#include <iostream>
#include <filesystem>
#include <fstream>
#include "headers/db_structure.h"
namespace fs = std::filesystem;

bool createDirectory(const fs::path &);
bool createFile(const fs::path &);

bool create_db(const fs::path &, std::string);
bool create_dbmetafile(const fs::path &);

bool db_struct::create_db(const fs::path &in_path, std::string with_name)
{
    fs::path folderPath = in_path / with_name;

    if (fs::is_directory(folderPath))
    {
        if (fs::exists(folderPath / "database.metadata"))
        {
            std::cerr << "A database with the same name already exists at '" << folderPath << "'\n";
            return false;
        }
        std::cout << "A folder with same name already exists at path '" << folderPath << "'\nTry to rename the existing folder!\n";
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

    createDirectory(folderPath);
    create_dbmetafile(folderPath);
    return true;
}
bool db_struct::create_dbmetafile(const fs::path &db_path)
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