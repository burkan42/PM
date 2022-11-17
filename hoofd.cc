// file hoofd.cc
#include <iostream>
#include "othellobord.h"
using namespace std;

int main ( ) {
    cout << "test "<< endl; 
	othellobord a;
    a.breedte = 6;
    a.hoogte = 4;
    a.rijtje();
    a.maakbord();
    a.drukaf();
	return 0;
}//main
