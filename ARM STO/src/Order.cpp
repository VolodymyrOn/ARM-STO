#include "Order.h"
#include <iostream>
#include <string.h>
using namespace std;

Order::Order(Auto A, Employee E, Client C, double p, string type, string problem):
    automobile(A), employee(E), client(C), price(p), type_of_repair(type), short_problem(problem){

        execution_date.day=0;
        execution_date.month=0;
        execution_date.year=0;

    }


        void Order::change_price(){
        double p;
        cout<<endl<<"Зміна вартості ремонту: "<<endl<<"Введіть вартість ремонту: ";
        cin>>p;
        price=p;
        cout<<"\nВартість ремонту успішно змінена на "<<p<<" днів\n";
    }

        void Order::change_SP(){
        string sp;
        cout<<endl<<"Зміна короткого опису поломки ремонту: "<<endl<<"Введіть короткий опис поломки ремонту: ";
        cin>>sp;
        short_problem=sp;
        cout<<"\nКороткий опис поломки успішно змінено\n";
    }
        void Order::change_Emp(Employee emp){
        employee=emp;
        cout<<"\nПрацівника успішно змінено\n";
    }

        void Order::change_complete(){
            complete=true;
            cout<<endl<<"Вітаю, замовлення завершене"<<endl;
        }


