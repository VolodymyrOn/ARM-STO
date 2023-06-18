#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <string>
using namespace std;

class Employee
{
public:
    string name;
    string surname;
    string specialization;
    double salary;
    Employee(string n="Null", string sur="Null", string s="Null", double sal=0);
};

#endif // EMPLOYEE_H
