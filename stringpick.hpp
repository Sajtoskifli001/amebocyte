#ifndef STRINGPICK_HPP
#define STRINGPICK_HPP

#include "widget.hpp"

#include <string>
#include <vector>

struct optionBox
{
    int x,y;
    std::string option;
};

class StringPick : public Widget
{
    public:
        StringPick(Application*,int,int,int,int,std::vector<std::string>,int);      //konstruktor, kér: Applikáció amihez tartozik, bal felsõ sarok x koordinátája, y koordinátája, szélesség, magasság, opciók stringvektora, megjelenítendõ opciók száma
        virtual ~StringPick();

        virtual bool selected(int,int);                                             //kurzor rajta van-e, kér: kurzor x koordináta, y koordináta, ad: igaz/hamis
        void construct();                                                           //megjelenítendõ opciók vektorának (menü vektor) létrehozása, több opció mint megjeleníteni kívánt esetén offsetet beleszámítva (görgetés), kevesebb opció mint megjeleníteni kívánt esetén üres, nem választható opció hozzáadása
        virtual void draw();                                                        //widget kirajzolása
        bool on_btn(int,int);                                                       //kurzor gombon van-e, kér: kurzor x koordinátája, y koordinátája, ad: igaz/hamis
        bool on_menu(int,int);                                                      //kurzor menün van-e, kér: kurzor x koordinátája, y koordinátája, ad: igaz/hamis
        int on_option(int,int);                                                     //kurzor melyik opción van, kér: kurzor x koordinátája, y koordinátája, ad: menü vektorban opció indexe, vagy -1, ha egyiken sem
        std::string getPick();                                                      //választott opció lekérése
        virtual void handle(genv::event);                                           //widget kezelése, kér: event

        void removePick();                                                          //kiválasztott opció törlése az opcióvektorból
        void addOption(std::string);                                                //opció hozzáadása, kér: új opció

    protected:
        std::vector<std::string> _options;                                          //beadott opciók vektora
        std::vector<optionBox> _menu;                                               //megjelenített opciók vektora, opció típussal
        std::string _pick="";                                                       //választott opció
        int _showCount,_btnSize,_optionHover=-1,_offset=0;                          //megjelenítendõ opciók száma, gomb szélessége, kurzor melyik opción, megjelenítésnél eltolás a menüben
        bool _open=false, _hover=false;                                             //menü nyitva van-e, kurzor gombon van-e
};

#endif // STRINGPICK_HPP
