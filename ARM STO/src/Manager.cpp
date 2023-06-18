#include "Manager.h"
#include <iostream>
#include <string>
#include <vector>
#include "sqlite3.h"
#include "functions.h"
using namespace std;

Manager::Manager(){}
int auth=0;

    void Manager::autorithation(){
        cout<<"================================================="<<endl;
        cout<<"|\t\t  �����������  \t\t\t|\n=================================================\n\n";
        string l,p;
        do{
        cout<<"  ������ ����:  ";
        cin>>l;
        cout<<"  ������ ������: ";
        cin>>p;
        clearConsole();
        if(l!=login||p!=password){
            cout<<"================================================="<<endl;
            cout<<"|\t����������� ������� ���� ��� ������\t|\n";
            cout<<"=================================================\n\n";
        }
        }while(l!=login||p!=password);
        cout<<"================================================="<<endl;
        cout<<"|\t\t³��� ��� � ������\t\t|"<<endl;
        cout<<"================================================="<<endl<<endl<<endl;

    }

    bool Manager::main(){

        if(auth==0){
            sqlite3 *db;
            sqlite3_open("database.db", &db);
            readDataFromDatabase(db, clients, employeers, orders, login, password);
            autorithation();
            sqlite3_close(db);

            auth++;
        }
        int a;
        cout<<"================================================="<<endl;
        cout<<"|\t\t\t����\t\t\t|\n";
        cout<<"================================================="<<endl;
        cout<<"=================================================\n";
        cout<<"|  1. ������ ����������.\t\t\t|\n";
        cout<<"|  2. ������/����������� ����������.\t\t|\n";
        cout<<"|  3. ������/�������� ����������.\t\t|\n";
        cout<<"|  4. ������/�������� �볺���.\t\t\t|\n";
        cout<<"|  5. ������� ���� �� ������.\t\t\t|\n";
        cout<<"|  6. �������� ��� � ��.\t\t\t|\n";
        cout<<"|  0. �����.\t\t\t\t\t|\n";
        cout<<"=================================================\n";
        cout<<"\n  ������� ����� ����: ";
        cin>>a;
        clearConsole();
        sqlite3 *db;
        switch(a){
            case 1:
                addOrder();
                clearConsole();
                return false;break;
            case 2:
                checkO();
                clearConsole();
                return false;break;
            case 3:
                add_del_emp();
                clearConsole();
                return false;break;
            case 4:
                add_del_client();
                clearConsole();
                return false;break;
            case 5:
                changePass();
                return false;break;
            case 6:

                sqlite3_open("database.db", &db);
                writeDataToDatabase(db, clients,
                          employeers, orders, login, password);
                sqlite3_close(db);
                clearConsole();
                cout<<"================================================="<<endl;
                cout<<"|\t���������� ������ ���������!\t\t|"<<endl;
                cout<<"================================================="<<endl<<endl<<endl;
                return false;break;
            case 0:
                clearConsole();
                cout<<endl<<endl<<endl<<"�� ������ �������� ���������� ���(1-���, 0-�): ";
                cin>>auth;
                if(auth==1){
                sqlite3_open("database.db", &db);
                writeDataToDatabase(db, clients,
                          employeers, orders, login, password);
                sqlite3_close(db);}
                return true;
            default:
                clearConsole();
                cout<<"================================================="<<endl;
                cout<<"|\t������ ������ ���� �� ����\t\t|\n";
                cout<<"================================================="<<endl;
                return false;
                }

    }
        void Manager::addOrder(){
            cout<<"================================================="<<endl;
            cout<<"|\t\t��������� ����������\t\t|\n";
            cout<<"================================================="<<endl<<endl;
            cout<<"================================================="<<endl;
            cout<<"|\t\t������� �볺���\t\t|\n";
            cout<<"================================================="<<endl;
            int c=client_chose();
            int a;
            clearConsole();
            cout<<"================================================="<<endl;
            cout<<"|\t\t��������� ����������\t\t|\n";
            cout<<"================================================="<<endl<<endl;
            cout<<"================================================="<<endl;
            cout<<"|\t\t������� ���� �볺���\t\t|\n";
            cout<<"================================================="<<endl;
            a=auto_chose(c);
            clearConsole();
            cout<<"================================================="<<endl;
            cout<<"|\t\t��������� ����������\t\t|\n";
            cout<<"================================================="<<endl<<endl;
            cout<<"================================================="<<endl;
            cout<<"|\t\t������� ����������\t\t|\n";
            cout<<"================================================="<<endl;
            int e=employee_chose();
            clearConsole();
            cout<<"================================================="<<endl;
            cout<<"|\t\t��������� ����������\t\t|\n";
            cout<<"================================================="<<endl<<endl;
            cout<<"  ������ ������� �������:      ";
            double p;
            cin>>p;
            cout<<"  ������ ��� �������:           ";
            string t;
            cin>>t;
            cout<<"  ������ �������� ���� �������: ";
            string prob;
            getline(cin>>ws, prob);
            cout<<endl;
            orders.push_back(Order(clients[c].automobile[a],employeers[e],clients[c],p,t,prob));
        }

        void Manager::checkO(){
             cout<<"================================================="<<endl;
            cout<<"|\t������/����������� ����������\t\t|\n";
            cout<<"================================================="<<endl<<endl;
            cout<<"=================================================";
            cout<<endl<<"|  1. ������ ����������.\t\t\t|"<<endl;
            cout<<"|  2. ����������� �� ������� ����������\t|"<<endl;
            cout<<"|  3. ����������� ������� ����������\t\t|"<<endl;
            cout<<"|  0. ����������� �� ����\t\t\t|"<<endl;
            cout<<"================================================="<<endl<<endl;
               cout<<"\n  ������� ����� ����:  ";
            int i;
            cin>>i;
            switch(i){
            case 1:
                clearConsole();
                changeOrder();
                break;
            case 2:
                clearConsole();
                 cout<<"================================================="<<endl;
                cout<<"|\t\t�� ������� ����������\t\t|\n";
                cout<<"================================================="<<endl<<endl;
                showOrders(false);
                cout<<endl<<endl<<"�������� enter ��� ����������>> ";
                getch();
                break;
            case 3:
                clearConsole();
                cout<<"================================================="<<endl;
                cout<<"|\t\t������� ����������\t\t|\n";
                cout<<"================================================="<<endl<<endl;
                showOrders(true);
                cout<<endl<<endl<<"�������� enter ��� ����������>> ";
                getch();
                break;
            case 0:
                break;
            default:
                clearConsole();
                cout<<"================================================="<<endl;
                cout<<"|\t������ ������ ���� �� ����\t\t|\n";
                cout<<"================================================="<<endl;
                checkO();
                }
        }

            void Manager::changePass(){
                cout<<"================================================="<<endl;
                cout<<"|\t\t���� ����� �� ������:\t\t|"<<endl;
                cout<<"================================================="<<endl<<endl;
                string l,p;
                cout<<"  ������ ����� ����:  ";
                cin>>l;
                cout<<"  ������ ����� ������: ";
                cin>>p;
                login=l;
                password=p;
                clearConsole();
                cout<<"================================================="<<endl;
                cout<<"|\t���� �� ������ ������ �������\t|";
                cout<<endl<<"================================================="<<endl<<endl;
            }
        int Manager::client_chose(){
            if(clients.size()==0){
                cout<<"================================================="<<endl;
                cout<<"|������ �볺��� �������, ������� ������ �볺���|\n";
                cout<<"================================================="<<endl<<endl;
                cout<<"�������� Enter, ��� ���������� >>";
                getch();
                clearConsole();
                addClient();
                clearConsole();
                Auto A1=addAuto();
                clients[0].automobile.push_back(A1);
                clearConsole();
                }
            long long unsigned int i;
            cout<<"================================================="<<endl;
            cout<<"|\t\t������ �볺���\t\t\t|\n";
            cout<<"================================================="<<endl<<endl;
            cout<<"-------------------------------------------------";
            cout<<"\n  0. ������ ������ �볺���.\n";
            for(i=0;i<clients.size();i++){
                cout<<"-------------------------------------------------"<<endl;
                cout<<"  "<<i+1<<". ��'�:\t\t"<<clients[i].name
                <<"\n     �������:\t\t"<<clients[i].surname
                <<"\n     ����� ��������:\t"<<clients[i].phone<<endl;
                cout<<"-------------------------------------------------"<<endl;
            }
            cout<<endl<<endl<<"  ������ ����� �볺���: ";
            cin>>i;
            if(i==0){
                clearConsole();
                addClient();
                i=clients.size()-1;
                clearConsole();
                Auto A1=addAuto();
                clients[i].automobile.push_back(A1);
                clearConsole();
                return client_chose();
            }
            return i-1;
        }


        int Manager::employee_chose(){
            if(employeers.size()==0){
                cout<<endl<<"======================================================="<<endl;
                cout<<"|������ ���������� �������, ������� ������ ����������|";
                cout<<endl<<"======================================================="<<endl;
                addEmployee();
                clearConsole();
            }
            long long unsigned int i;
            cout<<"=================================================";
            cout<<"\n|\t\t������ ����������\t\t| \n";
            cout<<"================================================="<<endl<<endl;
            cout<<"-------------------------------------------------";
            cout<<"\n  0. ������ ������ ����������.\n";
            for(i=0;i<employeers.size();i++){
                cout<<"-------------------------------------------------"<<endl;
                cout<<"  "<<i+1<<". ��'�:\t\t"<<employeers[i].name<<"\n     �������:\t\t"<<employeers[i].surname
                <<"\n     ������������:\t"<<employeers[i].specialization<<"\n     ��������:\t\t"<<employeers[i].salary<<endl;
                cout<<"-------------------------------------------------"<<endl;
            }
            cout<<endl<<endl<<"  ������ ����� ����������: ";
            cin>>i;
            if(i==0){
                clearConsole();
                addEmployee();
                i=employeers.size()-1;
                clearConsole();
                return employee_chose();
            }
            return i-1;
        }

            int Manager::auto_chose(int c){
            if(clients[c].automobile.size()==0){
                cout<<endl<<"============================================================="<<endl;
                cout<<"|������ ���� � �볺��� �������, ������� ����� ���������|";
                cout<<endl<<"============================================================="<<endl;
                Auto A1=addAuto();
                clients[c].automobile.push_back(A1);
                clearConsole();
            }
            long long unsigned int i;
            cout<<"=================================================";
            cout<<"\n|\t\t������ ���������\t\t|\n";
            cout<<"=================================================\n\n";
            cout<<"-------------------------------------------------";
            cout<<"\n  0. ������ ����� ��������� �볺���.\n";
            for(i=0;i<clients[c].automobile.size();i++){
                cout<<"-------------------------------------------------"<<endl;
                cout<<"  "<<i+1<<". �����:\t\t"<<clients[c].automobile[i].marka<<"\n     ������:\t\t"<<clients[c].automobile[i].model
                <<"\n     ����:\t\t"<<clients[c].automobile[i].color<<"\n     ��������� ����:\t"<<clients[c].automobile[i].znak<<endl;
                cout<<"-------------------------------------------------"<<endl;
            }
            cout<<endl<<endl<<"  ������ ����� ����: ";
            cin>>i;
            if(i==0){
                clearConsole();
                Auto A1=addAuto();
                clients[c].automobile.push_back(A1);
                i=clients[c].automobile.size()-1;
                clearConsole();
                return auto_chose(c);
            }
            return i-1;
        }

        Auto Manager::addAuto(){
            cout<<"================================================="<<endl;
            cout<<"|\t\t��������� ����\t\t\t|\n";
            cout<<"================================================="<<endl<<endl;
            cout<<"  ������ ����� ����:         ";
            cin>>auto_for_changes.marka;
            cout<<"  ������ ������ ����:        ";
            cin>>auto_for_changes.model;
            cout<<"  ������ ���� ����:         ";
            cin>>auto_for_changes.color;
            cout<<"  ������ �������� ���� ����: ";
            cin>>auto_for_changes.znak;
            return auto_for_changes;
        }

        void Manager::addClient(){
            cout<<"================================================="<<endl;
            cout<<"|\t\t��������� �볺���\t\t|\n";
            cout<<"================================================="<<endl<<endl;
            cout<<"  ������ ��'�:           ";
            cin>>client_for_changes.name;
            cout<<"  ������ �������:       ";
            cin>>client_for_changes.surname;
            cout<<"  ������ ����� ��������: ";
            cin>>client_for_changes.phone;
            clients.push_back(client_for_changes);
        }

        void Manager::addEmployee(){
            cout<<"================================================="<<endl;
            cout<<"|\t\t��������� ����������\t\t|\n";
            cout<<"================================================="<<endl<<endl;
            cout<<"  ������ ��'�:                     ";
            cin>>employee_for_changes.name;
            cout<<"  ������ �������:                 ";
            cin>>employee_for_changes.surname;
            cout<<"  ������ ������������ ����������: ";
            cin>>employee_for_changes.specialization;
            cout<<"  ������ ���������:                ";
            cin>>employee_for_changes.salary;
            employeers.push_back(employee_for_changes);
        }

        void Manager::changeOrder(){
            clearConsole();
            cout<<"================================================="<<endl;
            cout<<"|\t\t������ ����������\t\t|";
            cout<<endl<<"================================================="<<endl;
            showOrders(false);
            int i;
            cout<<endl<<"  ������� ����������: ";
            cin>>i;
            bool ext=false;
            while(!ext){
            clearConsole();
            cout<<"================================================="<<endl;
            cout<<"|\t\t������ ����������\t\t|";
            cout<<endl<<"================================================="<<endl<<endl;
            cout<<"================================================="<<endl;
            cout<<"|  1. ������ ������ ���������.\t\t\t|"<<endl;
            cout<<"|  2. ������ �������.\t\t\t\t|"<<endl;
            cout<<"|  3. ������ �������� ���� ��������.\t\t|"<<endl;
            cout<<"|  4. ������ ����������.\t\t\t|"<<endl;
            cout<<"|  0. ��������� ���� ����������.\t\t|"<<endl;
            cout<<"================================================="<<endl<<endl;
               cout<<"\n  ������� ����� ����:  ";
            int s;
             string problem1;
            cin>>s;
            cout<<endl<<endl;
            switch(s){
            case 1:
                orders[i-1].complete=true;
                Date d;
                cout<<"\n  ������ ���� ��������� �������: ";
                cout<<"\n  ����: ";
                cin>>d.day;
                cout<<"  ̳����: ";
                cin>>d.month;
                cout<<"  г�: ";
                cin>>d.year;
                orders[i-1].execution_date=d;
                break;
            case 2:
                cout<<"  �������: "<<orders[i-1].price;
                cout<<"\n\n  ������ ���� �������: ";
                double p;
                cin>>p;
                orders[i-1].price=p;
                break;
            case 3:
                cout<<"  �������� ���� ��������: "<<orders[i-1].short_problem;
                cout<<"\n\n  ������ ����� �������� ���� ��������: ";

                cin>>problem1;
                orders[i-1].short_problem=problem1;
                break;
            case 4:
                orders[i-1].employee=employeers[employee_chose()];
                break;
            case 0:
                ext=true;
                break;
            default:
                cout<<"================================================="<<endl;
                cout<<"|\t������ ������ ���� �� ����\t\t|\n";
                cout<<"================================================="<<endl;
                cout<<endl<<endl<<"�������� enter ��� ����������>> ";
                getch();
                break;
                }
                }

        }

        void Manager::showOrders(bool type){
            cout<<"-------------------------------------------------"<<endl;
            for(long long unsigned int i=0;i<orders.size();i++){
                if(orders[i].complete==type){
                    cout<<"  "<<i+1<<". "<<"����: "<<"\n       �����:\t\t\t"<<orders[i].automobile.marka<<"\n       ������:\t\t\t"<<orders[i].automobile.model
                <<"\n       ����:\t\t\t"<<orders[i].automobile.color<<"\n       ��������� ����:\t\t"<<orders[i].automobile.znak<<endl<<endl;

                    cout<<"     ���������: ";
                    cout<<endl<<"       ��'�:\t\t\t"<<orders[i].employee.name<<"\n       �������:\t\t"<<orders[i].employee.surname
                <<"\n       ������������:\t\t"<<orders[i].employee.specialization<<"\n       ��������:\t\t"<<orders[i].employee.salary<<endl<<endl;

                    cout<<"     �볺��: ";
                    cout<<endl<<"       ��'�:\t\t\t"<<orders[i].client.name<<"\n       �������:\t\t"<<orders[i].client.surname<<"\n       ����� ��������:\t\t"<<orders[i].client.phone<<endl;
                    cout<<"\n     �������:\t\t\t"<<orders[i].price<<"\n     ��� �������:\t\t"
                    <<orders[i].type_of_repair<<"\n     �������� ���� ��������:\t"<<orders[i].short_problem<<endl;
                    if(orders[i].complete==true){
                        cout<<"\n     ���� ��������� �������:\t"<<orders[i].execution_date.day<<"."<<orders[i].execution_date.month<<"."<<orders[i].execution_date.year<<endl;
                    }
                    cout<<"-------------------------------------------------"<<endl;
                }
            }
        }

        void Manager::changeEmployee(){
            clearConsole();
            int e=employee_chose();
             bool ext=false;
            clearConsole();
             while(!ext){
            cout<<"================================================="<<endl;
            cout<<"|\t\t���� ����� ����������\t\t|\n";
            cout<<"================================================="<<endl<<endl;

            cout<<"================================================="<<endl;
            cout<<"|  1. ������ ������� ����������.\t\t|"<<endl;
            cout<<"|  2. ������ ������������ ����������.\t\t|"<<endl;
            cout<<"|  3. ������ �������� ����� ����������.\t|"<<endl;
            cout<<"|  0. ��������� ���� ����������.\t\t|"<<endl;
            cout<<"================================================="<<endl<<endl;
               cout<<"\n������� ����� ����:  ";
            int s;
             string str;
            cin>>s;
            cout<<endl<<endl;
            switch(s){
            case 1:
                cout<<"  �������: "<<employeers[e].surname;
                cout<<"\n\n  ������ ���� ������� ����������: ";
                cin>>str;
                employeers[e].surname=str;
                clearConsole();
                break;
            case 2:
                cout<<"  ������������: "<<employeers[e].specialization;
                cout<<"\n\n  ������ ���� ������������ ����������: ";
                cin>>str;
                employeers[e].specialization=str;
                clearConsole();
                break;
            case 3:
                double s;
                cout<<"  ���������: "<<employeers[e].salary;
                cout<<"\n\n  ������ ���� �������� ����������: ";
                cin>>s;
                employeers[e].salary=s;
                clearConsole();
                break;
            case 0:
                ext=true;
                break;
            default:
                cout<<"================================================="<<endl;
                cout<<"|\t������ ������ ���� �� ����\t\t|\n";
                cout<<"================================================="<<endl;
                cout<<endl<<endl<<"�������� enter ��� ����������>> ";
                getch();
                break;
                }
                }
             }


        void Manager::changeClient(){
            clearConsole();
            int c=client_chose();
             bool ext=false;
            clearConsole();
             while(!ext){
                    cout<<"================================================="<<endl;
                    cout<<"|\t\t���� ����� �볺���\t\t|\n";
                    cout<<"================================================="<<endl<<endl;

                    cout<<"================================================="<<endl;
                    cout<<"|  1. ������ ������� �볺���.\t\t\t|"<<endl;
                    cout<<"|  2. ������ ����� �������� �볺���.\t\t|"<<endl;
                    cout<<"|  3. ������ ���� �볺���.\t\t\t|"<<endl;
                    cout<<"|  4. �������� ���� �볺���.\t\t\t|"<<endl;
                    cout<<"|  0. ��������� ���� �볺���.\t\t\t|"<<endl;
                    cout<<"================================================="<<endl<<endl;
                    cout<<"\n  ������� ����� ����:  ";
            int s;
             string str;
            cin>>s;
            cout<<endl<<endl;
            switch(s){
            case 1:
                cout<<"  �������: "<<clients[c].surname;
                cout<<"\n\n  ������ ���� ������� �볺���: ";
                cin>>str;
                clients[c].surname=str;
                clearConsole();
                break;
            case 2:
                cout<<"  ����� ��������: "<<clients[c].phone;
                cout<<"\n\n  ������ ����� ����� �������� �볺���: ";
                cin>>str;
                clients[c].phone=str;
                clearConsole();
                break;
            case 3:
                clearConsole();
                auto_for_changes=addAuto();
                clients[c].automobile.push_back(auto_for_changes);
                clearConsole();
                break;
            case 4:
                clearConsole();
                {
                    auto avto=clients[c].automobile.begin()+auto_chose(c);
                    clients[c].automobile.erase(avto);
                }
                clearConsole();
                break;
            case 0:
                ext=true;
                break;
                }
             }
        }



        void Manager::add_del_emp(){
        cout<<"================================================="<<endl;
        cout<<"|\t������/��������/������ ����������\t|\n";
        cout<<"================================================="<<endl<<endl;
        cout<<"=================================================";
            cout<<endl<<"|  1. ������ ����������.\t\t\t|"<<endl;
            cout<<"|  2. �������� ����������.\t\t\t|"<<endl;
            cout<<"|  3. ������ ��� ����������.\t\t\t|"<<endl;
            cout<<"|  0. ����.\t\t\t\t\t|"<<endl;
             cout<<"================================================="<<endl<<endl;
               cout<<"\n  ������� ����� ����:  ";
            int s;
            cin>>s;
            cout<<endl<<endl;
            switch(s){
            case 1:
                clearConsole();
                addEmployee();
                break;
            case 2:
                clearConsole();
                cout<<"================================================="<<endl;
                cout<<"|\t\t�������� ����������\t\t|\n";
                cout<<"================================================="<<endl<<endl;
                {auto emp=employeers.begin()+employee_chose();
                employeers.erase(emp);}
                break;
            case 3:
                clearConsole();
                changeEmployee();
                break;
            case 0:
                break;
                }
        }


          void Manager::add_del_client(){
            cout<<"================================================="<<endl;
            cout<<"|\t������/��������/������ �볺���\t\t|\n";
            cout<<"================================================="<<endl<<endl;
            cout<<"=================================================";
            cout<<endl<<"|  1. ������ �볺���.\t\t\t\t|"<<endl;
            cout<<"|  2. �������� �볺���.\t\t\t\t|"<<endl;
            cout<<"|  3. ������ ��� �볺���.\t\t\t|"<<endl;
            cout<<"|  0. ����\t\t\t\t\t|"<<endl;
            cout<<"================================================="<<endl<<endl;
               cout<<"\n  ������� ����� ����:  ";
            int s;
            int i=0;
            Auto A1;
            cin>>s;
            cout<<endl<<endl;
            switch(s){
            case 1:
                clearConsole();
                addClient();
                i=clients.size()-1;
                clearConsole();
                A1=addAuto();
                clients[i].automobile.push_back(A1);
                clearConsole();
                break;
            case 2:
                clearConsole();
                cout<<"================================================="<<endl;
                cout<<"|\t\t�������� �볺���\t\t|\n";
                cout<<"================================================="<<endl<<endl;
                {auto cli=clients.begin()+client_chose();
                clients.erase(cli);}
                break;
            case 3:
                clearConsole();
                changeClient();
                break;
            case 0:
                break;
                }
        }
Manager::~Manager()
{
    //dtor
}
