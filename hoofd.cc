// file hoofd.cc
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "othellobord.h"
using namespace std;

int main ( ) {

	othellobord a;
	int i = 0;
    a.maakbord();

    while(!a.eindstand()){
        a.computerzet();
        a.score();
        a.drukaf();
        i++;
    }

}//main
