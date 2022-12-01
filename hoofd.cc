// file hoofd.cc
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "othellobord.h"
using namespace std;

int main ( ) {

	othellobord a;
    //a.menu();
    a.maakbord();
    //cout << a.eindstand()<< endl;
    a.computerzet();
    //cout << a.toegestaan(2,8);
    a.drukaf();

}//main
