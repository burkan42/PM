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
    void menszet( );
    void computerzet ( );
    void drukaf ( );
    void maakbord ( );
    void menu( );
    bordvakje* kopieer(bordvakje* ingang); //kopieert de pointer structuur van gegeven ingangpointer
    bordvakje* rijtje (bordvakje* ingang);
    int breedte, hoogte;
    // TODO
};//othellobord
