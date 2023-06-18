#include <iostream>
#include <windows.h>
#include <vector>
#include <string>
#include <conio.h>
#include "sqlite3.h"
#include "Auto.h"
#include "Employee.h"
#include "Client.h"
#include "Order.h"
#include "Manager.h"

using namespace std;

    void clearConsole() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coordScreen = {0, 0};
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;

    GetConsoleScreenBufferInfo(hConsole, &csbi);
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    FillConsoleOutputCharacter(hConsole, ' ', dwConSize, coordScreen, &cCharsWritten);
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
    SetConsoleCursorPosition(hConsole, coordScreen);
}


int executeQueryForCreateAndDrop(sqlite3* db, const string& query) {
    char* errorMessage = nullptr;
    int result = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errorMessage);
    if (result != SQLITE_OK) {
        cerr << "Error executing query: " << errorMessage << endl;
        sqlite3_free(errorMessage);
    }
    return result;
}



int executeQuery(sqlite3* db, const string& query, vector<vector<string>>& results) {
    char* errorMessage = nullptr;
    int result = sqlite3_exec(db, query.c_str(), [](void* data, int argc, char** argv, char** columnNames) {
        vector<string> row;
        for (int i = 0; i < argc; i++)
            row.push_back(argv[i] ? argv[i] : "");
        vector<vector<string>>& results = *static_cast<vector<vector<string>>*>(data);
        results.push_back(row);
        return 0;
    }, &results, &errorMessage);

    if (result != SQLITE_OK) {
        cerr << "Error executing query: " << errorMessage << endl;
        sqlite3_free(errorMessage);
    }
    return result;
}


void readDataFromDatabase(sqlite3* db, vector<Client>& clients,
                          vector<Employee>& employeers, vector<Order>& orders, string& login, string& password) {

    // Зчитування логіна та пароля

    string selectLPQuery="SELECT login, password FROM LogPass;";
    vector<vector<string>> LogPassResults;

    if(executeQuery(db, selectLPQuery, LogPassResults)== SQLITE_OK){
    login=LogPassResults[0][0];
    password=LogPassResults[0][1];
    }
    // Зчитування таблиці Clients
    string selectClientsQuery = "SELECT name, surname, phone FROM Clients;";
    vector<vector<string>> clientsResults;
    executeQuery(db, selectClientsQuery, clientsResults);
    for (const auto& row : clientsResults) {
        Client client;
        client.name = row[0];
        client.surname = row[1];
        client.phone = row[2];
        clients.push_back(client);
    }

        // Зчитування таблиці Auto
    string selectAutoQuery = "SELECT client_id, marka, model, color, znak FROM Auto;";
    vector<vector<string>> autoResults;
    executeQuery(db, selectAutoQuery, autoResults);
    for (const auto& row : autoResults) {
        Auto aut;
        int c=stoi(row[0]);
        aut.marka = row[1];
        aut.model = row[2];
        aut.color = row[3];
        aut.znak = row[4];
        clients[c].automobile.push_back(aut);
    }

    // Зчитування таблиці Employees
    string selectEmployeesQuery = "SELECT name, surname, specialization, salary FROM Employees;";
    vector<vector<string>> employeesResults;
    executeQuery(db, selectEmployeesQuery, employeesResults);
    for (const auto& row : employeesResults) {
        Employee employee;
        employee.name = row[0];
        employee.surname = row[1];
        employee.specialization = row[2];
        employee.salary = stod(row[3]);
        employeers.push_back(employee);
    }




// Зчитування таблиці Orders

    string selectOrdersQuery =
        "SELECT auto_id, employee_id,client_id, price, type_of_repair, short_problem, execution_date_day, execution_date_month, execution_date_year, complete "
        "FROM Orders;";
    vector<vector<string>> ordersResults;
    executeQuery(db, selectOrdersQuery, ordersResults);
    for (const auto& row : ordersResults) {
        int a=stoi(row[0]);
        int e=stoi(row[1]);
        int c=stoi(row[2]);

        Order order;
        order.automobile = clients[c].automobile[a];
        order.employee = employeers[e];
        order.client = clients[c];
        order.price = stod(row[3]);
        order.type_of_repair = row[4];
        order.short_problem = row[5];
        order.execution_date.day = stoi(row[6]);
        order.execution_date.month = stoi(row[7]);
        order.execution_date.year = stoi(row[8]);
        order.complete = (row[9] == "1");
        orders.push_back(order);
    }
    }

void writeDataToDatabase(sqlite3* db, const vector<Client>& clients,
                         const vector<Employee>& employeers, const vector<Order>& orders, string login, string password) {
    // Видалення таблиць, якщо вони існують
    executeQueryForCreateAndDrop(db, "DROP TABLE IF EXISTS Auto;");
    executeQueryForCreateAndDrop(db, "DROP TABLE IF EXISTS LogPass;");
    executeQueryForCreateAndDrop(db, "DROP TABLE IF EXISTS Clients;");
    executeQueryForCreateAndDrop(db, "DROP TABLE IF EXISTS Employees;");
    executeQueryForCreateAndDrop(db, "DROP TABLE IF EXISTS Orders;");

    // Створення таблиць Auto, Clients, Employees, Orders
    executeQueryForCreateAndDrop(db, "CREATE TABLE Auto (client_id INT, marka TEXT, model TEXT, color TEXT, znak TEXT);");
    executeQueryForCreateAndDrop(db, "CREATE TABLE Clients (name TEXT, surname TEXT, phone TEXT);");
    executeQueryForCreateAndDrop(db, "CREATE TABLE LogPass (login TEXT, password TEXT);");
    executeQueryForCreateAndDrop(db, "CREATE TABLE IF NOT EXISTS Employees (name TEXT, surname TEXT, specialization TEXT, salary REAL);"
        "CREATE TABLE Orders (auto_id INTEGER, employee_id INTEGER, client_id INTEGER, price REAL, "
        "type_of_repair TEXT, short_problem TEXT, execution_date_day INTEGER, execution_date_month INTEGER, execution_date_year INTEGER, complete INTEGER);");

    //Запис логіну та пароля
    string LogPassQuery="INSERT INTO LogPass (login, password) VALUES( "+ login + ", " + password + ");";
    executeQueryForCreateAndDrop(db, LogPassQuery);

    // Запис даних в таблицю Auto
    for(int c=0;c<clients.size();c++){
    for (const auto& aut : clients[c].automobile) {
        string query = "INSERT INTO Auto (client_id ,marka, model, color, znak) VALUES ( "+ to_string(c) +",'" + aut.marka + "', '" +
                       aut.model + "', '" + aut.color + "', '" + aut.znak + "');";
        executeQueryForCreateAndDrop(db, query);
    }}

    // Запис даних в таблицю Clients
    for (const auto& client : clients) {
        string query = "INSERT INTO Clients (name, surname, phone) VALUES ('" + client.name + "', '" + client.surname +
                       "', '" + client.phone + "');";
        executeQueryForCreateAndDrop(db, query);
    }

    // Запис даних в таблицю Employees
    for (const auto& employee : employeers) {
        string query = "INSERT INTO Employees (name, surname, specialization, salary) VALUES ('" + employee.name +
                       "', '" + employee.surname + "', '" + employee.specialization + "', " +
                       to_string(employee.salary) + ");";
        executeQueryForCreateAndDrop(db, query);
    }

    // Запис даних в таблицю Orders
    for (const auto& order : orders) {
        // Отримання ідентифікаторів об'єктів з інших таблиць
        int autoId = executeQueryForCreateAndDrop(db, "SELECT rowid FROM Auto WHERE marka='" + order.automobile.marka +
                                          "' AND model='" + order.automobile.model + "' AND color='" +
                                          order.automobile.color + "' AND znak='" + order.automobile.znak + "';");

        int employeeId = executeQueryForCreateAndDrop(db, "SELECT rowid FROM Employees WHERE name='" + order.employee.name +
                                              "' AND surname='" + order.employee.surname + "' AND specialization='" +
                                              order.employee.specialization + "' AND salary=" +
                                              to_string(order.employee.salary) + ";");

        int clientId = executeQueryForCreateAndDrop(db, "SELECT rowid FROM Clients WHERE name='" + order.client.name +
                                            "' AND surname='" + order.client.surname + "' AND phone='" +
                                            order.client.phone + "';");

        string query =
            "INSERT INTO Orders (auto_id, employee_id, client_id, price, type_of_repair, short_problem, "
            "execution_date_day, execution_date_month, execution_date_year, complete) VALUES ("+ to_string(autoId) +
            ", " + to_string(employeeId) + ", " + to_string(clientId) + ", " +
            to_string(order.price) + ", '" + order.type_of_repair + "', '" + order.short_problem + "', '" +
            to_string(order.execution_date.day) + "', '" + to_string(order.execution_date.month) + "', '" + to_string(order.execution_date.year) + "', " + (order.complete ? "1" : "0") + ");";
        executeQueryForCreateAndDrop(db, query);
    }
}



