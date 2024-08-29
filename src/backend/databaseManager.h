#ifndef DATABASEMANGER_H
#define DATABASEMANGER_H

#include <string>
#include <vector>
#include <sqlite3.h>

class DatabaseManager{
    public:
        DatabaseManager(const std::string& dbPath);
        ~DatabaseManager();

        bool createTable(const std::string& tableName, const std::vector<std::string>& columnNames);

        bool insertData(const std::string& tableName, const std::vector<std::string>& columnNames, const std::vector<std::string>& values);

        bool updateData(const std::string& tableName, const std::string& columnName, const std::string& value, const std::string& condition);

        bool deleteData(const std::string& tableName, const std::string& condition);

        std::vector<std::vector<std::string>> queryData(const std::string& tableName, const std::string& columns, const std::string& condition = "");
        
    private:
       sqlite3* db;
       std::string dbFilePath;

       bool executeSQL(const std::string& sql);

       static int callback(void* data , int argc, char** argv, char** azColName);

};

#endif