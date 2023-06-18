#ifndef MANAGER_H
#define MANAGER_H
#include <iostream>
#include <string.h>
#include "functions.h"
#include "Auto.h"
#include "Employee.h"
#include "Client.h"
#include "Order.h"
#include "sqlite3.h"

using namespace std;

class Manager
{
    public:
        Manager();
        virtual ~Manager();
        void autorithation();
        bool main();
        void addOrder();
        void checkO();
        void changePass();
        int client_chose();
        int employee_chose();
        int auto_chose(int c);
        Auto addAuto();
        void addClient();
        void addEmployee();
        void changeOrder();
        void showOrders(bool type);
        void add_del_emp();
        void add_del_client();
        void changeEmployee();
        void changeClient();

    protected:

    private:
            string login="123";
            string password="123";
            Auto auto_for_changes=Auto{};
            Client client_for_changes=Client{};
            Employee employee_for_changes=Employee{};
            Order order_for_changes=Order{};
            vector<Order> orders;
            vector<Employee> employeers;
            vector<Client> clients;
};

#endif // MANAGER_H
