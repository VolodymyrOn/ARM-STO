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
        cout<<endl<<"���� ������� �������: "<<endl<<"������ ������� �������: ";
        cin>>p;
        price=p;
        cout<<"\n������� ������� ������ ������ �� "<<p<<" ���\n";
    }

        void Order::change_SP(){
        string sp;
        cout<<endl<<"���� ��������� ����� ������� �������: "<<endl<<"������ �������� ���� ������� �������: ";
        cin>>sp;
        short_problem=sp;
        cout<<"\n�������� ���� ������� ������ ������\n";
    }
        void Order::change_Emp(Employee emp){
        employee=emp;
        cout<<"\n���������� ������ ������\n";
    }

        void Order::change_complete(){
            complete=true;
            cout<<endl<<"³���, ���������� ���������"<<endl;
        }


