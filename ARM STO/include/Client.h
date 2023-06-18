#ifndef CLIENT_H
#define CLIENT_H
#include <string>
#include <vector>
#include "Auto.h"
using namespace std;
class Client
{
public:
    string name;
    string surname;
    string phone;
    vector<Auto> automobile;

    Client( string n="Null", string s="Null", string p="0");
};

#endif // CLIENT_H
