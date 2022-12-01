// file othellobord.h
class bordvakje {
  public:
    char kleur;           //     7 0 1
    bordvakje* buren[8];  //     6   2
    bordvakje ( );        //     5 4 3
};//bordvakje

class othellobord {
  private:
    bordvakje* ingang;
    bordvakje* uitgang;
    void ritsen ( bordvakje * onder, bordvakje * boven );

  public:
    othellobord ( );
    ~othellobord ( );
    void menszet(int x, int y); //zet die een mens doet gegeven een coordinaat
    void computerzet ( );
    void drukaf ( );
    void maakbord ( );
    void menu( );
    bordvakje* kopieer(bordvakje* ingang); //kopieert de pointer structuur van gegeven ingangpointer
    bordvakje* kopieerRijtje(bordvakje* ingang, bordvakje* kopie); //kopieert een hele rij van een ingangpointer naar een kopiepointer
    bordvakje* rijtje (bordvakje* ingang); //maakt een rijtje van bordvakjes
    bordvakje* positie (int x, int y); //returnt pointer van bordvakje gegeven de coordinaten
    int breedte, hoogte;
    int beurt; //wie aan de beurt is (0 = zwart, 1 = wit)
    bool toegestaan (int x, int y); //kijkt of schijfje op een gegeven coordinaat geplaatst mag worden
    bool eindstand ( ); //kijken of spel nog gespeeld kan worden, of er nog mogelijke zetten zijn

};//othellobord
