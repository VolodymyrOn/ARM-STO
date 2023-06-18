#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <iostream>
#include <windows.h>
#include <vector>
#include "Auto.h"
#include "Employee.h"
#include "Client.h"
#include "Order.h"
#include "Manager.h"
#include <conio.h>
#include "sqlite3.h"
#include <string>
using namespace std;

    void clearConsole();
    int executeQueryForCreateAndDrop(sqlite3* db, const string& query);
    /*void createTables(sqlite3* db);
    void dropTables(sqlite3* db);*/
    void writeDataToDatabase(sqlite3* db, const vector<Client>& clients,
                         const vector<Employee>& employeers, const vector<Order>& orders, string login, string password);
    void readDataFromDatabase(sqlite3* db, vector<Client>& clients,
                          vector<Employee>& employeers, vector<Order>& orders, string& login, string& password);
    int executeQuery(sqlite3* db, const string& query, vector<vector<string>>& results);


#endif
