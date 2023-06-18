#include <windows.h>
#include "Manager.h"
using namespace std;

int main(){
    system("chcp 1251 > nul");
    Manager m1;
    bool exit=false;
    while(!exit){
        exit=m1.main();
    }
    return 0;
}
