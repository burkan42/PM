// file othellobord.cc
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "othellobord.h"
using namespace std;

othellobord::othellobord ( )
{
    breedte = 8;
    hoogte = 8;
    ingang = new bordvakje;
    uitgang = nullptr;
    beurt = 0;//zwart begint altijd eerst
    beurtkleur = 'Z'; //zwart begint altijd eerste
    richting = 0;
    aantall = 0;
    aantalz = 0;
    aantalw = 0;

}//othellobord::othellobord

othellobord::~othellobord ( )
{
    bordwissen(); //reset het bord
}//othellobord::~othellobord

bordvakje::bordvakje ( )
{

    //buren moeten leeg zijn,
    //dus gelijkmaken aan NULL.
    for (int i = 0; i < 8; i++)
    {
        buren[i] = NULL;
    }
}
//Ritsen wordt gebruikt om een boven- en onderrij aan elkaar te binden.
void othellobord::ritsen (bordvakje * boven, bordvakje * onder)
{

    for ( int i = 0; i < breedte; i++)
    {

        boven -> buren[4] = onder; //bovenrij aan onderrij laten wijzen
        onder -> buren[0] = boven; //onderrij aan bovenrij laten wijzen

        if ( i < breedte)
        {
            boven -> buren [3] = onder-> buren [2]; //naar buur rechtsonder wijzen
            onder -> buren [1] = boven-> buren [2]; //naar buur rechtsboven wijzen
        }
        if ( i > 0 )
        {
            onder -> buren [7] = boven-> buren [6]; //naar buur linksboven wijzen
            boven -> buren [5] = onder-> buren [6]; //naar buur linksonder wijzen
        }

        boven= boven->buren [2]; //boven loper naar rechter vakje gaan
        onder= onder->buren [2]; //onder loper naar rechter vakje gaan
    }
}
//hier maken we een rij van bordvakjes
bordvakje* othellobord::rijtje (bordvakje * ingang)
{

    bordvakje * nieuw = ingang; //new vakje wijst naar ingang
    bordvakje * loper; //loper voor aanmaken van nieuwe vakje
    nieuw->kleur = '-'; //eerste ingang vullen

    for (int i = 0; i < breedte - 1; i++)
    {
        loper = new bordvakje; //maak nieuwe vakje aan
        loper->buren[6] = nieuw;//wijst linker vakje

        loper->kleur = '-';
        nieuw->buren[2] = loper;//wijst naar rechter vakje
        nieuw = loper; //ingang wordt nu de rechter buurman
    }

    nieuw->buren[2] = nullptr; //aan het einde van rij wijst naar niks

    return ingang; //loper wordt nieuwe ingang
}

//hier kopieeren we een rij van ingang naar kopie
bordvakje* othellobord::kopieerRijtje(bordvakje* ingang, bordvakje* kopie)
{

    bordvakje* ingangLoper = ingang; //loopt door oude bord
    bordvakje* kopieLoper = kopie; //gaat mee met loper van kopie, represent vorige vakje
    kopieLoper->kleur = ingangLoper->kleur; //kleur van het eerste originele vakje kopieren naar nieuwe vakje
    ingangLoper = ingangLoper->buren[2];//wijst naar volgende vak

    while (ingangLoper != nullptr)  //loop door ingang zolang hij nergens naartoe wijst
    {
        bordvakje* loper = new bordvakje; //loper is onze volgende vakje

        kopieLoper->buren[2] = loper;   //kopieLoper wijst naar rechter loper
        loper->buren[6] = kopieLoper ;  //loper wijst naast vorige vak

        loper->kleur = ingangLoper->kleur; //kleur van volgende originele vakje kopieren naar nieuwe vakje
        kopieLoper = loper; //kopieloper wordt loper
        ingangLoper = ingangLoper->buren[2]; //ingangloper gaat naar volgende
    }

    return kopie;
}

//kopieert de pointer structuur van gegeven ingangpointer
bordvakje* othellobord::kopieer(bordvakje* ingang)
{

    bordvakje* kopie = new bordvakje; //wijst naar ingang van huidige bord
    bordvakje* ingangLoper = ingang; //loopt door oude bord
    bordvakje* rijIngangLoper = ingang; //loopt door rijen van originele bord
    bordvakje* bovenKopie = kopie; //bovenrij van kopie bord
    bordvakje* onderKopie; //onderrij van kopie

    ingangLoper = ingangLoper->buren[2]; //ingangloper gaat naar volgende
    kopieerRijtje(ingang, kopie); //eerste rij kopieren

    while (rijIngangLoper != nullptr)
    {

        bordvakje * newRowKopie = new bordvakje; //eerst vakje van nieuwe rij in kopie bord
        bovenKopie->buren[4] = newRowKopie ; //bovenKopie wijst naar new vakje
        newRowKopie->buren[0] = bovenKopie; //new vakje wijst naar de bovenKopie
        onderKopie = kopieerRijtje(ingangLoper, newRowKopie); //ritsen van boven en onderij van kopie bord
        rijIngangLoper = rijIngangLoper->buren[4]; //springt naar volgende rij originele bord
        ingangLoper = rijIngangLoper; //ingangloper gaat door in volgende rij
        bovenKopie = newRowKopie; //springt naar volgende rij kopie bord

    }
    return kopie;//return ingang van het kopie bord

}

//We zetten het bord in elkaar door middel van twee lopers:
void othellobord::maakbord ( )
{

    bordvakje * boven = ingang; //boven wijst naar ingang
    bordvakje * onder;
    rijtje(ingang); //eerste rijtje aanmaken


    for ( int i = 0; i < hoogte - 1; i++)
    {
        bordvakje * loper = new bordvakje; //nieuwe ingang voor nieuwe rij
        boven->buren[4] = loper; //de bovenbuur wijst naar onderrij
        onder = rijtje(loper); //op plaats van loper rij maken
        ritsen(boven, onder); //risten van de boven en onder rij
        boven = loper; //nieuwe rij wordt de bovenste rij
    }

    //beginbord kleuren plaatsen
    bordvakje* kleurtje = ingang;
    bordvakje* loper; //door rijen lopen

    for ( int k = 0; k < hoogte - 1; k++)
    {
        loper = kleurtje;
        for ( int l = 0; l < breedte - 1; l++)
        {

            if (l == breedte/2 - 1 && k == hoogte/2 - 1 )
            {
                kleurtje->kleur = 'W';//eerste witte schijfje plaatsen
                kleurtje->buren[2]->kleur = 'Z';
                kleurtje->buren[4]->kleur = 'Z';
                kleurtje->buren[3]->kleur = 'W';
            }
            kleurtje = kleurtje->buren[2]; //naar volgende vakje
        }
        loper = loper->buren[4]; //loper naar volgende rij
        kleurtje = loper; //kleurtje wijst naar volgende rij
    }

}

//deze functie zal de schijven tussen de huidige schijf
//en de schijf tot waar de kleuren tegenovergesteld zijn
//omdraaien.
void othellobord::schijvenOmdraaien(bordvakje* ingang)
{
    char leeg = '-';
    char anderekleur = 'W'; //omgekeerde kleur van degene die aan beurt is

    if(beurt == 1)
    {
        anderekleur = 'Z';
    }

    for (int i = 0; i < 8; i ++)
    {
        bordvakje* start = ingang; //het vakje van de zet

        if(start->buren[i] != nullptr)  //zolang buren niet de grens van bord zijn
        {
            if(start->buren[i]->kleur != leeg && start->buren[i]->kleur == anderekleur) //indien er buren zijn en tegenovergesteld kleur van beurt
            {
                bordvakje* loper = start; //zal lopen tot einde van bord

                while(loper->buren[i] != nullptr && loper->buren[i]->kleur != leeg)  //loper zoekt zelfde kleur in de richting van buur
                {

                    if(loper->buren[i]->kleur == beurtkleur)  //als er na een tegenstelde kleur een buurtkleur komt
                    {
                        bordvakje* uitgang = loper->buren[i]; //locatie van vakje waar zelfde kleur is, wordt opgeslagen.
                        richting = i;

                        while(start != uitgang)
                        {
                            start ->kleur = beurtkleur;//kleur van huidige vak veranderen
                            start = start->buren[richting];//naar volgende vak gaan
                        }
                    }
                    loper = loper->buren[i]; //naar volgende buur
                }
            }
        }
    }
}

//returnt pointer van bordvakje gegeven de coordinaten
bordvakje* othellobord::positie (int x, int y)
{

    bordvakje* loper = ingang; //loper begint bij ingang
    bordvakje* loper2; //loper door rijen

    if (x> breedte|| y > hoogte || x < 1 || y < 1)
    {
        cout << "Coordinaten buiten het bord!" << endl;
        return 0;
    }

    for ( int k = 1; k <= hoogte; k++)
    {
        loper2 = loper;

        for ( int l = 1; l <= breedte; l++)
        {
            if(l == x && k == y)  //als zowel loper als loper2 op juiste coordinaat zijn
            {
                return loper; //returnt pointer van coordinaat
            }

            loper = loper->buren[2]; //naar volgende vakje
        }
        loper2 = loper2->buren[4]; //loper2 naar volgende rij
        loper = loper2; //loper wijst naar volgende rij
    }
}

//switch de beurt van speler nadat zet is gemaakt
void othellobord::switchBeurt()
{

    if(beurt == 1)
    {
        beurt = 0;
        beurtkleur = 'Z';
    }
    else
    {
        beurt = 1;
        beurtkleur = 'W';

    }
}

//men kan een zet doen door coordinaten in te voeren
void othellobord::menszet(int x, int y)
{
    bordvakje* start = positie(x,y); //bepaal positie van zet

    if(toegestaan(x, y))  //indien zet toegestaan,  invullen
    {

        cout << ">>>>beurt van " << beurtkleur << "<<<<"<<endl;
        cout << "zet(" << x << ", " << y << ")";
        start->kleur = beurtkleur;
        schijvenOmdraaien(start);
        switchBeurt();//switcht beurt
        aantalzetten++;
    }
    else
    {
        cout << "Zet niet toegestaan! Voer een geldige zet in!"<< endl;
    }

}

//deze functie houdt bij hoevaak elke schijf voorkomt
//in het huidige bord.
void othellobord::score ( )
{
    bordvakje* loper = ingang;
    bordvakje* loper2 = ingang;

    //alle tellers resetten
    aantall = 0;
    aantalz = 0;
    aantalw = 0;

    while (loper2 != nullptr)  // hij gaat door alle rijen heen
    {
        loper = loper2; // loper moet weer naar de ingang van rij toe

        while (loper != nullptr)  // hij gaat alle vakjes in een rij langs
        {

            if (loper->kleur == 'Z')  // als vakje een Z heeft dan aantalz tellen
            {
                aantalz++;
            }
            if (loper->kleur == 'W')  // als vakje een W heeft dan aantalw tellen
            {
                aantalw++;
            }
            if (loper->kleur == '-')  // als vakje een - heeft dan aantall tellen
            {
                aantall++;
            }

            loper = loper->buren[2]; //loper naar volgende vakje

        }
        loper2 = loper2->buren[4]; // loper naar volgende rij

    }
    cout << "<<<<SCORE>>>>"<< endl;
    cout << " " << "W"  << "  "<< "Z" << "  "<< "L" << endl;
    cout << " " << aantalw  << "  "<< aantalz << "  "<< aantall << endl;
}

// Gegeven een x en y coordinaat controleert deze functie
// of de zet mogelijk is voor de huidige speler
bool othellobord::toegestaan (int x, int y)
{
    char leeg = '-';
    if(positie(x,y) == 0)  //controleert of gegeven coordinaten toegestaan zijn, zo niet return false
    {
        return false;
    }

    bordvakje* start = positie(x, y); //neemt de pointer van positie opgegeven coordinate

    if (start->kleur != leeg) //als start op een schijf is, returnt false
        return false;

    for (int i = 0; i < 8; i ++)
    {
        if(start->buren[i] != nullptr)  //zolang buren niet de grens van bord zijn
        {
            if(start->buren[i]->kleur != leeg && start->buren[i]->kleur != beurtkleur) //indien er buren zijn en tegenovergesteld kleur van beurt, return true
            {
                bordvakje* loper = start; //zal lopen tot einde van bord

                while(loper->buren[i] != nullptr && loper->buren[i]->kleur != leeg)  //loper zoekt zelfde kleur in de richting van buur
                {

                    if(loper->buren[i]->kleur == beurtkleur)  //returnt true als er na een tegenstelde kleur een buurtkleur komt
                    {
                        uitgang = loper->buren[i]; //locatie van vakje waar zelfde kleur is, wordt opgeslagen.
                        richting = i;
                        //richtingen[i] = uitgang; //die richting op schijven draaien
                        return true;
                    }
                    loper = loper->buren[i]; //naar volgende buur

                }
            }
        }
    }
    return false;
}

//Deze functie bepaalde een random zet voor computer
void othellobord::computerzet()
{

    srand(time(NULL)); //maakt mogelijk om telkens een nieuwe rand() te genereren
    int x = (rand( ) % breedte) + 1, y = (rand( ) % hoogte) + 1; //definieren van x en y coordinaat

    while(!toegestaan(x, y))  //zolang er geen toegestane zet is gegeneerd, random creeeren
    {
        x = (rand( ) % breedte) + 1; //bepaal x coordinaat
        y = (rand( ) % hoogte) + 1; //bepaal y coordinaat

        if(toegestaan(x, y))  //indien wel een toegestaan zet mogelijk is, deze zet doen
        {
            //!cout << ">>>>beurt van " << beurtkleur << "<<<<"<<endl;
            //!cout << "zet(" << x << ", " << y << ")";
            bordvakje* start = positie(x, y); //bepaal een start positie voor zet
            start->kleur = beurtkleur;
            schijvenOmdraaien(start);
            switchBeurt();//switcht beurt
            aantalzetten++;

            break; //uit de loop gaan
        }
    }
}

//Deze functie loopt door alle vakjes en controleert of er nog toegestane zetten zijn.
// Indien wel, returnt hij false. Zo niet betekent het dat het spelt is geeindigd en returnt hij true.
bool othellobord::eindstand( )
{

    bordvakje* loper = ingang; //loper begint bij ingang
    bordvakje* loper2; //loper door rijen


    for ( int k = 1; k < hoogte + 1; k++)
    {
        loper2 = loper;

        for ( int l = 1; l < breedte + 1; l++)
        {
            if(toegestaan(l,k))  //indien er minimaal ??n toegestane zet is, return false
            {
                return false;
            }
            loper = loper->buren[2]; //naar volgende vakje
        }
        loper2 = loper2->buren[4]; //loper2 naar volgende rij
        loper = loper2; //loper wijst naar volgende rij
    }
    //cout << "!EIND SPEL!" << endl;
    return true;

}

//drukt bord af
void othellobord::drukaf ( )
{

    bordvakje* loper1 = ingang; //loper1 begint bij ingang
    bordvakje* loper2 = loper1; //loper2 begint bij ingang
    cout << endl;
    cout << "  ";
    for (int i = 1; i < breedte + 1; i++) //kolommen nummeren
    {
        cout << i << "  ";
    }
    cout << endl;

    int j = 1; //rijen nummeren
    while (loper1 != NULL)  //loop door rijen
    {
        loper2 = loper1;
        cout << j << " ";
        j++;
        while (loper2->buren[2] != NULL)  //loop door kolommen
        {
            cout << loper2->kleur << "  ";
            loper2 = loper2->buren[2]; //naar volgende vakje
        }
        cout << loper2->kleur << "  "; //laatse van rij printen
        cout << endl;
        loper1 = loper1->buren[4]; //naar volgende rij gaan
    }
}//othellobord::drukaf

//menu functie
void othellobord::menu ( )
{
    int x, y, p, q;
    cout << "WELCOME TO OTHELLO!!" << endl;
    cout <<  "Wil je voor de zwarte stenen als een mens of computer spelen?"<< endl;
    cout << "Voor een mens toets M en voor een computer toets C!"<< endl;
test:
    cin >> i;

    switch (i) //feedback op keuze van speler zwart
    {
    case 'C':
    case 'c':
        cout << "U heeft voor een computer gekozen!"<< endl;
        break;
    case 'M':
    case 'm':
        cout << "U heeft voor een mens gekozen!"<< endl;
        break;
    default :
        cout << "Geen match! Toets in M of C!" << endl;
        goto test;

    }

    cout <<  "Wil je voor de witte stenen als een mens of computer spelen?"<< endl;
    cout << "Voor een mens toets M en voor een computer toets C!"<< endl;
test2:
    cin >> k;

    switch (k)//feedback op keuze van speler wit
    {
    case 'M':
    case 'm':
        cout << "U heeft voor een mens gekozen!"<< endl;
        break;
    case 'C':
    case 'c':
        cout << "U heeft voor een computer gekozen!"<< endl;
        break;
    default :
        cout << "Geen match! Toets in M of C!" << endl;
        goto test2;
    }
    submenu();
}
//submenu functie
void othellobord::submenu ()
{
    cout << "De grootte van het bord is momenteel " << breedte << " bij " << hoogte <<" wil je die aanpassen?"<<endl;
    cout<< "Toets J voor ja en N voor nee!"<< endl;
test3:
    cin >> l;

    switch (l) //aanpassen van het bord
    {
    case 'J':
    case 'j':
        cout << "Toets het gewenste aantal rijen (groter of gelijk aan 2 en even):"<<endl;
        cin >> hoogte;//minstens 2 en even
        if (hoogte < 2) //als het invoer kleiner is dan 2
        {
            cout << "Getal is te klein! Kies een even getal groter of gelijk aan 2!"<<endl;
            cin >> hoogte;
            breedte = hoogte;
        }
        if (hoogte >= 2 && hoogte%2==!0) //als het invoer groter is dan twee maar niet even is
        {
            cout << "Kies een even getal aub!"<<endl;
            cin >> hoogte;
            breedte = hoogte;
        }
        breedte = hoogte;
        maakbord();
        cout << "Het bord is gewijzigd naar "<< hoogte << "x"<< breedte;
        drukaf();
        break;
    case 'N':
    case 'n':
        cout<< "De groote van het bord is " << hoogte <<"x" << breedte;
        drukaf();
        break;
    default:
        cout << "Geen match! Toets in J of N!" << endl;
        goto test3;
    }
    if (i == 'm'&& k == 'm')  // mens tegen mens
    {
        mtegenm ( );
    }
    if (i == 'c'&& k == 'm')  // mens wit pc zwart
    {
        ctegenm ( );
    }
    if (i == 'c'&& k == 'c')  // computer tegen computer
    {
        cout << "Hoeveel spelletjes moeten er gespeeld worden?"<<endl;
        cin >> u;
        if (u == 1)
        {
            ctegenc ( );
        }
        else
            meerdere (u);
    }
    if (i == 'm'&& k == 'c')  // mens zwart pc wit
    {
        mtegenc ( );
    }
}
//game case van zwart en wit als computer
void othellobord::ctegenc ()
{
    drukaf();
    while(!eindstand())
    {
        computerzet();
    }
    //!score();
    drukaf();
}
//game case van zwart mens en wit computer
void othellobord::mtegenc () // mens zwart pc wit
{
    cout << "Zwart begint als eerst."<< endl;
    while(!eindstand())
    {
        cout << "Toets de coordinaten van uw zet."<< endl;
        cout<< "X: ";
        cin >> p;
        cout<< "Y: ";
        cin >> q;
        menszet(p,q);
        drukaf();
        score();
        computerzet();
        drukaf();
        score();
    }
}
//game case van zwart computer en wit mens
void othellobord::ctegenm()
{    cout << "Zwart begint als eerst."<< endl;

    while(!eindstand())
    {
        computerzet();
        drukaf();
        score ();
        cout << "Toets de cordinaten van uw zet! Eerst de X cordinaat en dan Y."<< endl;
        cout<< "De cordinaten moeten toegestaan zijn en op een lege vakje "<< endl;
        cin >> p;
        cin >> q;
        menszet(p,q);
        drukaf();
        score ();
    }
}
//game case van zwart mens en wit mens
void othellobord::mtegenm ( )
{    cout << "Zwart begint als eerst."<< endl;

    while(!eindstand())
    {
        cout << "Toets de cordinaten van uw zet! Eerst de X cordinaat en dan Y."<< endl;
        cout<< "De cordinaten moeten toegestaan zijn en op een lege vakje "<< endl;
        cin >> p;
        cin >> q;
        menszet(p,q);
        drukaf();
        score();
    }
}
// dit is de functie dat de winaar afdrukt
void othellobord::win( )
{
    if (aantalw<aantalz)
    {
        cout<< "Zwart heeft gewonnen!"<<endl;
    }
    if (aantalz<aantalw)
    {
        cout<< "Wit heeft gewonnen!"<<endl;
    }
    if (aantalw == aantalz && aantalz==aantalw)
    {
        cout<< "Gelijkspel!"<<endl;
    }

    cout << "totaal aantalzetten is "<< aantalzetten << endl;
}

void othellobord::meerdere(int aantal)
{
    ofstream MyFile("stats.txt"); //bestand aanmaken voor de statistieken
    for (int i=0; i < aantal; i++)
    {
        cout << "-----------------------------------"<< endl;
        if (!eindstand())
        {
            ctegenc();
            bordwissen( ); //resetten van bord
            MyFile << i << " " << aantalzetten/2 << endl; //aantalzetten toevoegen aan file
            aantalzetten = 0;
        }
    }
    MyFile.close();

}

//deze functie verwijderd alle schijven in het huidige bord
void othellobord::bordwissen( )
{
    bordvakje* loper1 = ingang; //loper1 begint bij ingang
    bordvakje* loper2 = loper1; //loper2 begint bij ingang

    while (loper1 != NULL)  //loop door rijen
    {
        loper2 = loper1;
        while (loper2->buren[2] != NULL)  //loop door kolommen
        {
            loper2->kleur = ' - ';
            loper2 = loper2->buren[2]; //naar volgende vakje
        }
        loper1 = loper1->buren[4]; //naar volgende rij gaan
    }
    maakbord(); //bord opnieuw maken met beginposities ingevuld

}

void
