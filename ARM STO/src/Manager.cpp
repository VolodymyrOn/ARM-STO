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
        cout<<"|\t\t  Авторизація  \t\t\t|\n=================================================\n\n";
        string l,p;
        do{
        cout<<"  Введіть логін:  ";
        cin>>l;
        cout<<"  Введіть пароль: ";
        cin>>p;
        clearConsole();
        if(l!=login||p!=password){
            cout<<"================================================="<<endl;
            cout<<"|\tНеправильно введено логін або пароль\t|\n";
            cout<<"=================================================\n\n";
        }
        }while(l!=login||p!=password);
        cout<<"================================================="<<endl;
        cout<<"|\t\tВітаю вас в системі\t\t|"<<endl;
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
        cout<<"|\t\t\tМеню\t\t\t|\n";
        cout<<"================================================="<<endl;
        cout<<"=================================================\n";
        cout<<"|  1. Додати замовлення.\t\t\t|\n";
        cout<<"|  2. Змінити/Переглянути замовлення.\t\t|\n";
        cout<<"|  3. Додати/Звільнити працівника.\t\t|\n";
        cout<<"|  4. Додати/Видалити клієнта.\t\t\t|\n";
        cout<<"|  5. Змінтити логін та пароль.\t\t\t|\n";
        cout<<"|  6. Зберегти дані в БД.\t\t\t|\n";
        cout<<"|  0. Вихід.\t\t\t\t\t|\n";
        cout<<"=================================================\n";
        cout<<"\n  Виберіть пункт меню: ";
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
                cout<<"|\tІнформацію успішно збережено!\t\t|"<<endl;
                cout<<"================================================="<<endl<<endl<<endl;
                return false;break;
            case 0:
                clearConsole();
                cout<<endl<<endl<<endl<<"Чи хочете зберегти незбережені дані(1-так, 0-ні): ";
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
                cout<<"|\tТакого пункту меню не існує\t\t|\n";
                cout<<"================================================="<<endl;
                return false;
                }

    }
        void Manager::addOrder(){
            cout<<"================================================="<<endl;
            cout<<"|\t\tДодавання замовлення\t\t|\n";
            cout<<"================================================="<<endl<<endl;
            cout<<"================================================="<<endl;
            cout<<"|\t\tВиберіть клієнта\t\t|\n";
            cout<<"================================================="<<endl;
            int c=client_chose();
            int a;
            clearConsole();
            cout<<"================================================="<<endl;
            cout<<"|\t\tДодавання замовлення\t\t|\n";
            cout<<"================================================="<<endl<<endl;
            cout<<"================================================="<<endl;
            cout<<"|\t\tВиберіть Авто клієнта\t\t|\n";
            cout<<"================================================="<<endl;
            a=auto_chose(c);
            clearConsole();
            cout<<"================================================="<<endl;
            cout<<"|\t\tДодавання замовлення\t\t|\n";
            cout<<"================================================="<<endl<<endl;
            cout<<"================================================="<<endl;
            cout<<"|\t\tВиберіть працівника\t\t|\n";
            cout<<"================================================="<<endl;
            int e=employee_chose();
            clearConsole();
            cout<<"================================================="<<endl;
            cout<<"|\t\tДодавання замовлення\t\t|\n";
            cout<<"================================================="<<endl<<endl;
            cout<<"  Введіть вартість ремонту:      ";
            double p;
            cin>>p;
            cout<<"  Введіть тип поломки:           ";
            string t;
            cin>>t;
            cout<<"  Введіть короткий опис поломки: ";
            string prob;
            getline(cin>>ws, prob);
            cout<<endl;
            orders.push_back(Order(clients[c].automobile[a],employeers[e],clients[c],p,t,prob));
        }

        void Manager::checkO(){
             cout<<"================================================="<<endl;
            cout<<"|\tЗмінити/Переглянути замовлення\t\t|\n";
            cout<<"================================================="<<endl<<endl;
            cout<<"=================================================";
            cout<<endl<<"|  1. Змінити замовлення.\t\t\t|"<<endl;
            cout<<"|  2. Переглянути не виконані замовлення\t|"<<endl;
            cout<<"|  3. Переглянути виконані замовлення\t\t|"<<endl;
            cout<<"|  0. Повернутися до меню\t\t\t|"<<endl;
            cout<<"================================================="<<endl<<endl;
               cout<<"\n  Виберіть пункт меню:  ";
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
                cout<<"|\t\tНе виконані замовлення\t\t|\n";
                cout<<"================================================="<<endl<<endl;
                showOrders(false);
                cout<<endl<<endl<<"Натисніть enter щоб продовжити>> ";
                getch();
                break;
            case 3:
                clearConsole();
                cout<<"================================================="<<endl;
                cout<<"|\t\tВиконані замовлення\t\t|\n";
                cout<<"================================================="<<endl<<endl;
                showOrders(true);
                cout<<endl<<endl<<"Натисніть enter щоб продовжити>> ";
                getch();
                break;
            case 0:
                break;
            default:
                clearConsole();
                cout<<"================================================="<<endl;
                cout<<"|\tТакого пункту меню не існує\t\t|\n";
                cout<<"================================================="<<endl;
                checkO();
                }
        }

            void Manager::changePass(){
                cout<<"================================================="<<endl;
                cout<<"|\t\tЗміна логіна та пароля:\t\t|"<<endl;
                cout<<"================================================="<<endl<<endl;
                string l,p;
                cout<<"  Введіть новий Логін:  ";
                cin>>l;
                cout<<"  Введіть новий Пароль: ";
                cin>>p;
                login=l;
                password=p;
                clearConsole();
                cout<<"================================================="<<endl;
                cout<<"|\tЛогін та пароль успішно змінений\t|";
                cout<<endl<<"================================================="<<endl<<endl;
            }
        int Manager::client_chose(){
            if(clients.size()==0){
                cout<<"================================================="<<endl;
                cout<<"|Список клієнтів порожній, додайте нового клієнта|\n";
                cout<<"================================================="<<endl<<endl;
                cout<<"Натисніть Enter, щоб продовжити >>";
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
            cout<<"|\t\tСписок клієнтів\t\t\t|\n";
            cout<<"================================================="<<endl<<endl;
            cout<<"-------------------------------------------------";
            cout<<"\n  0. Додати нового клієнта.\n";
            for(i=0;i<clients.size();i++){
                cout<<"-------------------------------------------------"<<endl;
                cout<<"  "<<i+1<<". Ім'я:\t\t"<<clients[i].name
                <<"\n     Прізвище:\t\t"<<clients[i].surname
                <<"\n     Номер телефону:\t"<<clients[i].phone<<endl;
                cout<<"-------------------------------------------------"<<endl;
            }
            cout<<endl<<endl<<"  Введіть номер клієнта: ";
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
                cout<<"|Список працівників порожній, додайте нового працівника|";
                cout<<endl<<"======================================================="<<endl;
                addEmployee();
                clearConsole();
            }
            long long unsigned int i;
            cout<<"=================================================";
            cout<<"\n|\t\tСписок працівників\t\t| \n";
            cout<<"================================================="<<endl<<endl;
            cout<<"-------------------------------------------------";
            cout<<"\n  0. Додати нового працівника.\n";
            for(i=0;i<employeers.size();i++){
                cout<<"-------------------------------------------------"<<endl;
                cout<<"  "<<i+1<<". Ім'я:\t\t"<<employeers[i].name<<"\n     Прізвище:\t\t"<<employeers[i].surname
                <<"\n     Спеціалізація:\t"<<employeers[i].specialization<<"\n     Зарплата:\t\t"<<employeers[i].salary<<endl;
                cout<<"-------------------------------------------------"<<endl;
            }
            cout<<endl<<endl<<"  Введіть номер працівника: ";
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
                cout<<"|Список авто в клієнта порожній, додайте новий автомобіль|";
                cout<<endl<<"============================================================="<<endl;
                Auto A1=addAuto();
                clients[c].automobile.push_back(A1);
                clearConsole();
            }
            long long unsigned int i;
            cout<<"=================================================";
            cout<<"\n|\t\tСписок автомобілів\t\t|\n";
            cout<<"=================================================\n\n";
            cout<<"-------------------------------------------------";
            cout<<"\n  0. Додати новий автомобіль клієнту.\n";
            for(i=0;i<clients[c].automobile.size();i++){
                cout<<"-------------------------------------------------"<<endl;
                cout<<"  "<<i+1<<". Марка:\t\t"<<clients[c].automobile[i].marka<<"\n     Модель:\t\t"<<clients[c].automobile[i].model
                <<"\n     Колір:\t\t"<<clients[c].automobile[i].color<<"\n     Державний знак:\t"<<clients[c].automobile[i].znak<<endl;
                cout<<"-------------------------------------------------"<<endl;
            }
            cout<<endl<<endl<<"  Введіть номер авто: ";
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
            cout<<"|\t\tДодавання Авто\t\t\t|\n";
            cout<<"================================================="<<endl<<endl;
            cout<<"  Введіть марку авто:         ";
            cin>>auto_for_changes.marka;
            cout<<"  Введіть модель авто:        ";
            cin>>auto_for_changes.model;
            cout<<"  Введіть колір авто:         ";
            cin>>auto_for_changes.color;
            cout<<"  Введіть номерний знак авто: ";
            cin>>auto_for_changes.znak;
            return auto_for_changes;
        }

        void Manager::addClient(){
            cout<<"================================================="<<endl;
            cout<<"|\t\tДодавання клієнта\t\t|\n";
            cout<<"================================================="<<endl<<endl;
            cout<<"  Введіть ім'я:           ";
            cin>>client_for_changes.name;
            cout<<"  Введіть прізвище:       ";
            cin>>client_for_changes.surname;
            cout<<"  Введіть номер телефону: ";
            cin>>client_for_changes.phone;
            clients.push_back(client_for_changes);
        }

        void Manager::addEmployee(){
            cout<<"================================================="<<endl;
            cout<<"|\t\tДодавання працівника\t\t|\n";
            cout<<"================================================="<<endl<<endl;
            cout<<"  Введіть ім'я:                     ";
            cin>>employee_for_changes.name;
            cout<<"  Введіть прізвище:                 ";
            cin>>employee_for_changes.surname;
            cout<<"  Введіть спеціалізацію працівника: ";
            cin>>employee_for_changes.specialization;
            cout<<"  Введіть зарплатню:                ";
            cin>>employee_for_changes.salary;
            employeers.push_back(employee_for_changes);
        }

        void Manager::changeOrder(){
            clearConsole();
            cout<<"================================================="<<endl;
            cout<<"|\t\tЗмінити замовлення\t\t|";
            cout<<endl<<"================================================="<<endl;
            showOrders(false);
            int i;
            cout<<endl<<"  Виберіть замовлення: ";
            cin>>i;
            bool ext=false;
            while(!ext){
            clearConsole();
            cout<<"================================================="<<endl;
            cout<<"|\t\tЗмінити замовлення\t\t|";
            cout<<endl<<"================================================="<<endl<<endl;
            cout<<"================================================="<<endl;
            cout<<"|  1. Змінити статус виконання.\t\t\t|"<<endl;
            cout<<"|  2. Змінити вартість.\t\t\t\t|"<<endl;
            cout<<"|  3. Змінити короткий опис проблеми.\t\t|"<<endl;
            cout<<"|  4. Змінити працівника.\t\t\t|"<<endl;
            cout<<"|  0. Завершити зміну замовлення.\t\t|"<<endl;
            cout<<"================================================="<<endl<<endl;
               cout<<"\n  Виберіть пункт меню:  ";
            int s;
             string problem1;
            cin>>s;
            cout<<endl<<endl;
            switch(s){
            case 1:
                orders[i-1].complete=true;
                Date d;
                cout<<"\n  Введіть дату закінчення ремонту: ";
                cout<<"\n  День: ";
                cin>>d.day;
                cout<<"  Місяць: ";
                cin>>d.month;
                cout<<"  Рік: ";
                cin>>d.year;
                orders[i-1].execution_date=d;
                break;
            case 2:
                cout<<"  Вартість: "<<orders[i-1].price;
                cout<<"\n\n  Введіть нову вартість: ";
                double p;
                cin>>p;
                orders[i-1].price=p;
                break;
            case 3:
                cout<<"  Короткий опис проблеми: "<<orders[i-1].short_problem;
                cout<<"\n\n  Введіть новий короткий опис проблеми: ";

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
                cout<<"|\tТакого пункту меню не існує\t\t|\n";
                cout<<"================================================="<<endl;
                cout<<endl<<endl<<"Натисніть enter щоб продовжити>> ";
                getch();
                break;
                }
                }

        }

        void Manager::showOrders(bool type){
            cout<<"-------------------------------------------------"<<endl;
            for(long long unsigned int i=0;i<orders.size();i++){
                if(orders[i].complete==type){
                    cout<<"  "<<i+1<<". "<<"Авто: "<<"\n       Марка:\t\t\t"<<orders[i].automobile.marka<<"\n       Модель:\t\t\t"<<orders[i].automobile.model
                <<"\n       Колір:\t\t\t"<<orders[i].automobile.color<<"\n       Державний знак:\t\t"<<orders[i].automobile.znak<<endl<<endl;

                    cout<<"     Працівник: ";
                    cout<<endl<<"       Ім'я:\t\t\t"<<orders[i].employee.name<<"\n       Прізвище:\t\t"<<orders[i].employee.surname
                <<"\n       Спеціалізація:\t\t"<<orders[i].employee.specialization<<"\n       Зарплата:\t\t"<<orders[i].employee.salary<<endl<<endl;

                    cout<<"     Клієнт: ";
                    cout<<endl<<"       Ім'я:\t\t\t"<<orders[i].client.name<<"\n       Прізвище:\t\t"<<orders[i].client.surname<<"\n       Номер телефону:\t\t"<<orders[i].client.phone<<endl;
                    cout<<"\n     Вартість:\t\t\t"<<orders[i].price<<"\n     Тип поломки:\t\t"
                    <<orders[i].type_of_repair<<"\n     Короткий опис проблеми:\t"<<orders[i].short_problem<<endl;
                    if(orders[i].complete==true){
                        cout<<"\n     Дата закінчення ремонту:\t"<<orders[i].execution_date.day<<"."<<orders[i].execution_date.month<<"."<<orders[i].execution_date.year<<endl;
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
            cout<<"|\t\tЗміна даних працівника\t\t|\n";
            cout<<"================================================="<<endl<<endl;

            cout<<"================================================="<<endl;
            cout<<"|  1. Змінити прізвище працівника.\t\t|"<<endl;
            cout<<"|  2. Змінити спеціалізацію працівника.\t\t|"<<endl;
            cout<<"|  3. Змінити заробітню плату працівника.\t|"<<endl;
            cout<<"|  0. Завершити зміну працівника.\t\t|"<<endl;
            cout<<"================================================="<<endl<<endl;
               cout<<"\nВиберіть пункт меню:  ";
            int s;
             string str;
            cin>>s;
            cout<<endl<<endl;
            switch(s){
            case 1:
                cout<<"  Прізвище: "<<employeers[e].surname;
                cout<<"\n\n  Введіть нове прізвище працівника: ";
                cin>>str;
                employeers[e].surname=str;
                clearConsole();
                break;
            case 2:
                cout<<"  Спеціалізація: "<<employeers[e].specialization;
                cout<<"\n\n  Введіть нову спеціалізацію працівника: ";
                cin>>str;
                employeers[e].specialization=str;
                clearConsole();
                break;
            case 3:
                double s;
                cout<<"  Зарплатня: "<<employeers[e].salary;
                cout<<"\n\n  Введіть нову зарплату працівника: ";
                cin>>s;
                employeers[e].salary=s;
                clearConsole();
                break;
            case 0:
                ext=true;
                break;
            default:
                cout<<"================================================="<<endl;
                cout<<"|\tТакого пункту меню не існує\t\t|\n";
                cout<<"================================================="<<endl;
                cout<<endl<<endl<<"Натисніть enter щоб продовжити>> ";
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
                    cout<<"|\t\tЗміна даних клієнта\t\t|\n";
                    cout<<"================================================="<<endl<<endl;

                    cout<<"================================================="<<endl;
                    cout<<"|  1. Змінити прізвище клієнта.\t\t\t|"<<endl;
                    cout<<"|  2. Змінити номер телефону клієнта.\t\t|"<<endl;
                    cout<<"|  3. Додати авто клієнту.\t\t\t|"<<endl;
                    cout<<"|  4. Вилучити авто клієнту.\t\t\t|"<<endl;
                    cout<<"|  0. Завершити зміну клієнта.\t\t\t|"<<endl;
                    cout<<"================================================="<<endl<<endl;
                    cout<<"\n  Виберіть пункт меню:  ";
            int s;
             string str;
            cin>>s;
            cout<<endl<<endl;
            switch(s){
            case 1:
                cout<<"  Прізвище: "<<clients[c].surname;
                cout<<"\n\n  Введіть нове прізвище клієнта: ";
                cin>>str;
                clients[c].surname=str;
                clearConsole();
                break;
            case 2:
                cout<<"  Номер телефону: "<<clients[c].phone;
                cout<<"\n\n  Введіть новий номер телефону клієнта: ";
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
        cout<<"|\tДодати/Видалити/Змінити працівника\t|\n";
        cout<<"================================================="<<endl<<endl;
        cout<<"=================================================";
            cout<<endl<<"|  1. Додати працівника.\t\t\t|"<<endl;
            cout<<"|  2. Видалити працівника.\t\t\t|"<<endl;
            cout<<"|  3. Змінити дані працівника.\t\t\t|"<<endl;
            cout<<"|  0. Меню.\t\t\t\t\t|"<<endl;
             cout<<"================================================="<<endl<<endl;
               cout<<"\n  Виберіть пункт меню:  ";
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
                cout<<"|\t\tВидалити працівника\t\t|\n";
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
            cout<<"|\tДодати/Видалити/Змінити клієнта\t\t|\n";
            cout<<"================================================="<<endl<<endl;
            cout<<"=================================================";
            cout<<endl<<"|  1. Додати клієнта.\t\t\t\t|"<<endl;
            cout<<"|  2. Видалити клієнта.\t\t\t\t|"<<endl;
            cout<<"|  3. Змінити дані клієнта.\t\t\t|"<<endl;
            cout<<"|  0. Меню\t\t\t\t\t|"<<endl;
            cout<<"================================================="<<endl<<endl;
               cout<<"\n  Виберіть пункт меню:  ";
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
                cout<<"|\t\tВидалити клієнта\t\t|\n";
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
