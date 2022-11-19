// file othellobord.cc
#include <iostream>
#include "othellobord.h"
using namespace std;

othellobord::othellobord ( ) {
	breedte = 8;
	hoogte = 8;
	ingang = new bordvakje;
  // TODO
}//othellobord::othellobord

othellobord::~othellobord ( ) {
  // TODO
}//othellobord::~othellobord

bordvakje::bordvakje ( ){

    //buren moeten leeg zijn,
    //dus gelijkmaken aan NULL.
    for (int i = 0; i < 8; i++){
        buren[i] = NULL;
    }
}

//hier maken we een rij van bordvakjes
bordvakje* othellobord::rijtje (bordvakje * ingang){

    bordvakje * nieuw = ingang; //new vakje wijst naar ingang
    bordvakje * loper; //loper voor aanmaken van nieuwe vakje

    for (int i = 0; i < breedte - 1; i++){
        loper = new bordvakje; //maak nieuwe vakje aan
        loper->buren[6] = nieuw;//wijst linker vakje
        nieuw->kleur = '-';
        loper->kleur = '-';
        nieuw->buren[2] = loper;//wijst naar rechter vakje
        nieuw = loper; //ingang wordt nu de rechter buurman
    }

    nieuw->buren[2] = nullptr; //aan het einde van rij wijst naar niks
    loper = new bordvakje; //nieuw vakje voor rijtje eronder
    ingang->buren[4] = loper; //wijs naar volgende rij

    return loper; //loper wordt nieuwe ingang
}

//Ritsen wordt gebruikt om een boven- en onderrij aan elkaar te binden.
void othellobord::ritsen (bordvakje * boven, bordvakje * onder){

    for ( int i = 0; i < breedte; i++){

        boven -> buren[6] = onder; //bovenrij aan onderrij laten wijzen
        onder -> buren[0] = boven; //onderrij aan bovenrij laten wijzen

        if ( i < breedte){
            boven -> buren [3] = onder-> buren [2]; //naar buur rechtsonder wijzen
            onder -> buren [1] = boven-> buren [2]; //naar buur rechtsboven wijzen
        }
        if ( i > 0 ){
            onder -> buren [7] = boven-> buren [6]; //naar buur linksboven wijzen
            boven -> buren [5] = onder-> buren [6]; //naar buur linksonder wijzen
        }

        boven= boven->buren [2]; //boven loper naar rechter vakje gaan
        onder= onder->buren [2]; //onder loper naar rechter vakje gaan
    }
}

//We zetten het bord in elkaar door middel van twee lopers:
void othellobord::maakbord ( ){

    bordvakje * boven = ingang;
    bordvakje * onder = rijtje(ingang);

    for ( int i = 0; i < hoogte; i++){
        ritsen (boven, onder);
        onder = boven;
        boven = rijtje(); //controleren
        //nog een onder toevoegen

    }

}

void othellobord::drukaf ( ) {
    cout << "Dit Othellobord ziet er mooi uit." << endl;

    bordvakje* loper1 = ingang; //loper1 begint bij ingang
    bordvakje* loper2 = loper1; //loper2 begint bij ingang

    while (loper1 != NULL){ //loop door rijen
        loper2 = loper1;
        while (loper2->buren[2] != NULL){ //loop door kolommen
            cout << loper2->kleur << "  ";
            loper2 = loper2->buren[2]; //naar volgende vakje
        }
        cout << loper2->kleur << "  "; //laatse van rij printen
        cout << endl;
        loper1 = loper1->buren[4]; //naar volgende rij gaan
    }
}//othellobord::drukaf

// TODO
