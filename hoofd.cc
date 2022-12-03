// file hoofd.cc
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "othellobord.h"
using namespace std;

int main ( ) {

	othellobord a;
	int i = 0;
    //a.menu();
    a.maakbord();
    //cout << a.eindstand()<< endl
    while(i < 9){
        cin >> i;
        a.computerzet();
        a.drukaf();
        i++;
    }

}//main
