// file hoofd.cc
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "othellobord.h"
using namespace std;

void infoblokje();

int main ( ) {

    infoblokje();
	othellobord a;
    a.maakbord();
    a.drukaf();
    a.menu();
    a.win();

    //a.meerdere();
    //a.submenu();


    //while(!a.eindstand()){
      //  a.computerzet();
        //a.score();
        //a.drukaf();
        //i++;

       // a.menu();
       // a.submenu();
    //}

}//main



void infoblokje(){
// infoblokje
cout << "-------------------------------------------" << endl ;
cout << " >>>>>>>> Tolunay Ahmedov en Burak Ozdemir " << endl ;
cout << " >>>>>>>> 1998 en 1999 " << endl ;
cout << " >>>>>>>> 3,5 de jaar Informatica studenten" << endl ;
cout << " >>>>>>>> s2689596 / s2656205 "<< endl ;
cout << " >>>>>>>> Opdracht 4" << endl ;
cout << " >>>>>>>> Toets v o o r t o e g a n g t o t een u n i v e r s a i r s t u d i e" << endl ;
cout << endl ;
cout << " >>>>>>>> Het r e s u l t a a t van d e z e programma b e s l u i t " << endl ;
cout << " >>>>>>>> o f de g e b r u i k e r een a l f a − o f b e t a −s t u d i e kan v o l g e n " << endl ;
cout << " >>>>>>>> Veel succes ! ! " << endl ;
cout << endl ;
cout << " >>>>>>>> 12 december 2022 " << endl ;
cout << "-------------------------------------------" << endl ;
cout << "" << endl ;
}
