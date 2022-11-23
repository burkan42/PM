// file othellobord.cc
#include <iostream>
#include "othellobord.h"
using namespace std;

othellobord::othellobord ( ) {
	breedte = 8;
	hoogte = 8;
	ingang = new bordvakje;

}//othellobord::othellobord

othellobord::~othellobord ( ) {

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

    return ingang; //loper wordt nieuwe ingang
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

//kopieert de pointer structuur van gegeven ingangpointer
bordvakje* othellobord::kopieer(bordvakje* ingang){

    bordvakje* kopie = new bordvakje; //wijst naar ingang van huidige bord
    bordvakje* kopieLoper = kopie; //gaat mee met loper van kopie, represent vorige vakje
    bordvakje* ingangLoper = ingang; //loopt door oude bord
    bordvakje* rijIngangLoper = ingang; //loopt door rijen van originele bord
    bordvakje* rijKopieLoper = kopie; //loopt door rijen van kopie bord

    kopie->kleur = ingang->kleur; //kleur van het eerste originele vakje kopieren naar nieuwe vakje
    ingangLoper = ingangLoper->buren[2]; //ingangloper gaat naar volgende

    while (rijIngangLoper != nullptr){

        while (ingangLoper != nullptr){ //loop door kolom

            bordvakje* loper = new bordvakje; //loper is onze volgende vakje

            kopieLoper->buren[2] = loper;   //kopieLoper wijst naar rechter loper
            loper->buren[6] = kopieLoper ;  //loper wijst naast vorige vak

            loper->kleur = ingangLoper->kleur; //kleur van volgende originele vakje kopieren naar nieuwe vakje
            kopieLoper = loper; //kopieloper wordt loper
            ingangLoper = ingangLoper->buren[2]; //ingangloper gaat naar volgende
        }
        //!ritsen toevoegen
        bordvakje * newRowKopie = new bordvakje; //eerst vakje van nieuwe rij in kopie bord
        kopieLoper = newRowKopie; //kopieloper gaat door in volgende rij
        rijKopieLoper->buren[4] = newRowKopie ; //rijenloper wijst naar new vakje
        newRowKopie->buren[0] = rijKopieLoper; //new vakje wijst naar de rijenloper
        rijIngangLoper = rijIngangLoper->buren[4]; //springt naar volgende rij originele bord
        ingangLoper = rijIngangLoper; //ingangloper gaat door in volgende rij
        rijKopieLoper = rijKopieLoper->buren[4]; //springt naar volgende rij kopie bord

    }
    return kopie;//return ingang van het kopie bord

}

//We zetten het bord in elkaar door middel van twee lopers:
void othellobord::maakbord ( ){

    bordvakje * boven = ingang; //boven wijst naar ingang
    bordvakje * onder;
    rijtje(ingang); //eerste rijtje aanmaken
    //bordvakje * onder = rijtje(ingang);

    for ( int i = 0; i < hoogte - 1; i++){
        bordvakje * loper = new bordvakje; //nieuwe ingang voor nieuwe rij
        boven->buren[4] = loper; //de bovenbuur wijst naar onderrij
        onder = rijtje(loper); //op plaats van loper rij maken
        ritsen(boven, onder); //risten van de boven en onder rij
        boven = loper; //nieuwe rij wordt de bovenste rij
    }

}

void othellobord::drukaf ( ) {
    cout << "Dit Othellobord ziet er mooi uit." << endl;

    //cout << ingang << endl;
    bordvakje* loper1 = kopieer(ingang); //loper1 begint bij ingang
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


void othellobord::menu ( ){
    char i;
    cout << "WELCOME TO OTHELLO!!" << endl;
    cout <<  "Wil je voor de zwarte stenen als een mens of computer spelen?"<< endl;
    cout << "voor een mens type M en voor een computer type C!"<< endl;
    cin >> i;
    cout <<  "Wil je voor de witte stenen als een mens of computer spelen?"<< endl;
    cout << "voor een mens type M en voor een computer type C!"<< endl;
    cin>> i;
    cout << "De grootte van het bord is momenteel 8 bij 8 wil je die aanpassen?"<<endl;
    cout<< "Type J voor ja en N voor nee!"<< endl;
    cin >> i;

    switch (i){
        case 'M':
        case 'm':
            cout << "U heeft voor een mens gekozen!"<< endl;
            break;
        case 'C':
        case 'c':
            cout << "U heeft voor een computer gekozen!"<< endl;
            break;
        case 'J':
        case 'j':
            cout << "Type het gewenste aantal rijen (groter of gelijk aan 2 en even):"<<endl;
            cin >> breedte;//minstens 2 en even
                if (breedte < 2 && breedte%2==0){
                    cout << "breedte is te klein! Kies een even getal groter of gelijk aan 2!"<<endl;
                    cin >> breedte;
                }
                if (breedte > 2 && breedte%2==!0){
                    cout << "breedte is te klein! Kies een even getal groter of gelijk aan 2!"<<endl;
                    cin >> breedte;
                }

            cout << "Type het gewenste aantal kollomen:"<<endl;
            cin >> hoogte;//minstens 2 en even
                if (hoogte < 2 && hoogte%2==0){
                    cout << "breedte is te klein! Kies een even getal groter of gelijk aan 2!"<<endl;
                    cin >> breedte;
                }
                if (hoogte > 2 && hoogte%2==!0){
                    cout << "Hoogte is te klein! Kies een even getal groter of gelijk aan 2!"<<endl;
                    cin >> hoogte;
                }
            cout << "Het bord is gewijzigd naar "<< hoogte << "x"<< breedte;
            break;

        case 'N':
        case 'n':
            cout<< "De groote van het bord is " << hoogte <<"x" << breedte;
        default:
            cout << "No match! Please only input allowed characters!";
            break;
    }



}

// TODO
