#include "DatabaseManager.h"
#include <iostream>

DatabaseManager::DatabaseManager(const std::string& dbPath):db(nullptr),dbPath(dbPath){
    if(sqlite3_open(dbPAth.c_str(),&db) != SQLITE_OK){
        std::cerr<<"error opening SQLite database"<<sqlite3_errmsg(db)<<std::endl;
        db = nullptr;
    }else {
        std::cout<<"Successfully opened SQLite database"<<std::endl;
    }
}

DatabaseManager::~DatabaseManager() {
    if (db) {
        sqlite3_close(db);
        std::cout << "SQLite database connection closed." << std::endl;
    }
}

bool DatabaseManager::createTable(const std::string& tableName, const std::string& columnsDefinition){
    std::string sql = "CREATE TABLE IF NOT EXISTS" + tableName +"("+columnsDefinition+")";
    return executeSQL(sql);
}

bool DatabaseManager::insertData(const std::string& tableName, const std::string& columnNames, const std::string& values){
    std::string sql = "INSERT INTO " + tableName +"("+columnNames+") VALUES (" + values + ")";
    return executeSQL(sql);
}

std::vector<std::vector<std::string>> DatabaseManager::queryData(const std::string& tableName, const std::string& columns, const std::string& condition){
    std::string sql = "SELECT" +columns+"FROM"+tableName;
    if(!condition.empty()){
        sql += " WHERE " + condition;
    }
    sql += ";";

    std::vector<<std::vector<std::string>> results;
    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql.c_str(), callback, &results, &errMsg) != SQLITE_OK) {
        std::cerr << "Error querying data: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    return results;
}

bool DatabaseManager::deleteDatabase(const std::string& tableName const std::string& condition){
    std::string sql = "DELETE FROM " + tableName;
    if(!condition.empty()){
        sql += " WHERE " + condition;
    }
    sql += ";";
    return executeSQL(sql);
}

bool DatabaseManager::executeSQL(const std::string& sql){
    char* errMsg = nullptr;
     if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "Error executing SQL: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}

int DatabaseManager::callback(void* data, int argc, char** argv, char** azColName){
    std::vector<std::vector<std::string>>* results = static_cast<std::vector<std::vector<std::string>>*>(data);
    std::vector<std::string> row;
    for(int i = 0; i < argc; i++){
        row.push_back(argv[i]? argv[i] : "NULL");
    }
    results->push_back(row);
    return 0;
}
