#ifndef ORDER_H
#define ORDER_H
#include <string>
#include "Auto.h"
#include "Employee.h"
#include "Client.h"
using namespace std;



struct Date{
    int day;
    int month;
    int year;
};

class Order
{
public:
    Auto automobile;
    Employee employee;
    Client client;
    double price;
    string type_of_repair;
    string short_problem;
    Date execution_date;
    bool complete=false;

    Order(Auto A=Auto{}, Employee E=Employee{}, Client C=Client{}, double p=0, string type="", string problem="");
    void change_price();
    void change_SP();
    void change_Emp(Employee emp);
    void change_complete();


};

#endif // ORDER_H
