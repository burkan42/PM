// file othellobord.cc
#include <iostream>
#include "othellobord.h"
using namespace std;

othellobord::othellobord ( ) {
	breedte = 8;
	hoogte = 8;
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
bordvakje* othellobord::rijtje ( ){
	
	
	bordvakje * nieuw = NULL; //new vakje wijst naar niks 
	bordvakje * loper; //zal lopen door vakjes
	
	for (int i = 0; i < breedte; i++){
		loper = new bordvakje; 
		loper->buren[2] = nieuw;//hij wijst naar meest rechtse bordvak
		
		if (nieuw != NULL) //zolang rechts niet leeg is
			nieuw->buren[6] = loper;		
		nieuw = loper; //ingang wordt nu de rechter buurman
		}
		
	return nieuw;
}

//Ritsen wordt gebruikt om een boven- en onderrij aan elkaar te binden. 
void othellobord::ritsen (bordvakje * boven, bordvakje * onder){
	

    for ( int i = 0; i < breedte; i++){
        onder -> buren[0] = boven; //onderrij aan bovenrij laten wijzen
        boven -> buren[6] = onder; //bovenrij aan onderrij laten wijzen

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
	
	ingang = rijtje();
    bordvakje * onder;
    bordvakje * boven = ingang;

    for ( int i = 0; i < hoogte; i++){
        boven= rijtje();
        ritsen (boven, onder);
        onder = boven;
    }
}

void othellobord::drukaf ( ) {
    cout << "Dit Othellobord ziet er mooi uit." << endl;
	
	ingang = new bordvakje;
    bordvakje* loper1 = ingang; //eerste loper
    bordvakje* loper2 = ingang; //tweede loper
	
    while (loper1 != NULL){ 
        loper2 = loper1; 
        while (loper2 != NULL){ 
			loper2->kleur = 'Z'; 
            cout << loper2->kleur << "  "; 
            loper2 = loper2->buren[2]; 
        }
        loper1 = loper1->buren[4]; 
    }
}//othellobord::drukaf

// TODO
