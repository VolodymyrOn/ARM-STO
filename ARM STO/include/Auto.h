#ifndef AUTO_H
#define AUTO_H
#include <string>
using namespace std;

class Auto
{
public:
    string marka;
    string model;
    string color;
    string znak;

    Auto(string mar="Null", string mod="Null", string c="Null", string z="Null");
};

#endif // AUTO_H
